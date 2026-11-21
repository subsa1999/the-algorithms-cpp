# Payment Gateway — Low-Level Design (LLD)

> Java 21-oriented interview study notes. Provider capabilities and example API payloads are illustrative; real integrations must follow each PSP's current API and security requirements.

## 1. Scope and Requirements

### Functional
- Create and query payments for merchant orders.
- Support UPI, credit cards, debit cards, net banking, and extensible payment methods.
- Route transactions to compatible, healthy PSPs (e.g., Razorpay, PayU, Cashfree).
- Store provider-specific attempts separately from logical payments.
- Enforce idempotency, process asynchronous provider webhooks, and reconcile uncertain outcomes.
- Support retries/fallback only when safe, and full or partial refunds.
- Reliably notify merchants of confirmed payment/refund outcomes.

### Non-functional / invariants
- No duplicate *logical* payment for the same merchant + idempotency key.
- Prevent duplicate successful collection of the same amount due; understand that cross-provider exactly-once charging cannot be guaranteed purely by local locking.
- Never treat an HTTP timeout as a confirmed PSP failure.
- Verify webhook authenticity; deduplicate delivery; make transitions idempotent.
- Persist state durably; use conditional updates/optimistic locking and atomic database transactions.
- Never store raw card numbers, CVV, or UPI PIN; use provider tokens/hosted checkout and follow relevant compliance requirements.
- Use integral minor currency units (`long`) or an appropriate precise Money type, not floating point.

## 2. Overall Architecture

```text
Merchant app / Customer
       |
       v
PaymentController  ----> PaymentService
                             |  |  |  \
                             |  |  |   --> IdempotencyService -> IdempotencyRepository
                             |  |  +------> PaymentRepository / AttemptRepository
                             |  +---------> PaymentStateMachine
                             +------------> PaymentRouter -> PaymentProcessor (interface)
                                                        |       |      |
                                                   Razorpay   PayU   Cashfree
                                                        |
                                                   External PSP
                                                        |
                                            customer authorizes payment
                                                        |
                                                 PSP webhook
                                                        v
WebhookController -> WebhookService -> Provider WebhookHandler
                           |
                           +--> Verified durable WebhookInbox
                                        |
                                  Async Worker
                                        |
                                PaymentService.applyPaymentEvent()
                                        |
                             Database transaction:
                             attempt + payment + outbox + inbox
                                        |
                                 Outbox worker
                                        |
                                 Merchant notification
```

**Ownership boundary:** `PaymentService` owns the logical payment lifecycle; `PaymentRouter` chooses providers; `PaymentProcessor` handles outgoing PSP APIs; `WebhookService` owns inbound event receipt and coordination; provider-specific `WebhookHandler` validates/parses provider payloads; `RefundService` owns the refund lifecycle.

## 3. Entities and Enums

```text
Enums
-----
PaymentMethod: UPI, CREDIT_CARD, DEBIT_CARD, NET_BANKING, WALLET
PaymentStatus: CREATED, PENDING, SUCCESS, FAILED, CANCELLED
AttemptStatus: CREATED, INITIATED, PENDING, SUCCESS, FAILED, UNKNOWN
RefundStatus: CREATED, PENDING, SUCCESS, FAILED
ProviderType: RAZORPAY, PAYU, CASHFREE

Merchant
- merchantId
- name, email, status
- enabledPaymentMethods: Set<PaymentMethod>
- enabledProviders: Set<ProviderType>

Order
- orderId, merchantId
- amountInMinorUnits, currency, status, createdAt

Payment
- paymentId, merchantId, orderId
- amountInMinorUnits, currency, paymentMethod
- status: PaymentStatus
- idempotencyKey, requestFingerprint
- version, createdAt, updatedAt

PaymentAttempt
- attemptId, paymentId
- providerType, providerPaymentId, providerIdempotencyKey
- status: AttemptStatus
- failureReason, createdAt, updatedAt

Refund
- refundId, paymentId, successfulAttemptId
- providerRefundId, amountInMinorUnits
- status: RefundStatus, idempotencyKey
- createdAt, updatedAt

WebhookEvent (inbox record)
- providerType, eventId, providerPaymentId
- rawPayload, processingStatus
- receivedAt, processedAt

OutboxEvent
- outboxId, merchantId, aggregateId, eventType
- payload, deliveryStatus, attempts, createdAt
```

### Relationships

```text
Merchant 1 ------ N Order
Order    1 ------ N Payment
Payment  1 ------ N PaymentAttempt
Payment  1 ------ N Refund
PaymentAttempt N -- 1 ProviderType
```

An **order** is the purchase, a **payment** is a logical request to collect money, and a **payment attempt** is one concrete PSP attempt. Multiple attempts may belong to a payment; a confirmed successful attempt must stop further collection attempts for the same amount due.

## 4. Requests, Responses and APIs

```text
PaymentRequest
- orderId, amountInMinorUnits, currency, paymentMethod, paymentDetails
- merchantId is resolved from authenticated merchant identity (not trusted from request body)
- idempotencyKey from HTTP Idempotency-Key header

PaymentResponse
- paymentId, orderId, status, attemptId, provider, paymentAction

ProviderResponse
- providerPaymentId, providerStatus, paymentAction, failureReason

PaymentEvent
- eventId, providerType, providerPaymentId, eventType, timestamp
```

```http
POST /v1/payments
Idempotency-Key: KEY_123
Content-Type: application/json

{"orderId":"ORDER_101","amount":100000,"currency":"INR","method":"UPI"}

GET  /v1/payments/{paymentId}
POST /v1/payments/{paymentId}/retry
POST /v1/payments/{paymentId}/refunds
GET  /v1/refunds/{refundId}
POST /v1/webhooks/{provider}
```

`100000` paise = ₹1,000. A hypothetical response:

```json
{"paymentId":"PAY_001","status":"PENDING","provider":"RAZORPAY","paymentAction":{"type":"OPEN_UPI_APP"}}
```

## 5. Complete Class / Interface Structure

```text
PaymentController
- PaymentService paymentService
+ PaymentResponse createPayment(PaymentRequest, idempotencyKey)
+ PaymentResponse getPayment(paymentId)
+ PaymentResponse retryPayment(paymentId, retryKey)

PaymentService
- MerchantService, OrderService
- PaymentRepository, PaymentAttemptRepository
- PaymentRouter, IdempotencyService, PaymentStateMachine
- OutboxRepository
+ PaymentResponse createPayment(request, key)
+ PaymentResponse getPayment(paymentId)
+ PaymentResponse retryPayment(paymentId, retryKey)
+ void applyPaymentEvent(PaymentEvent)
+ void reconcilePayment(paymentId)

PaymentRouter
- ProviderRegistry, ProviderHealthService, RoutingStrategy
+ PaymentProcessor selectProcessor(method, merchant)
+ List<PaymentProcessor> getAvailableProcessors(method, merchant)
+ PaymentProcessor selectFallback(method, excludedProviders)

RoutingStrategy (interface)
+ ProviderType select(List<ProviderType> candidates)
PriorityBasedRouting implements RoutingStrategy
+ ProviderType select(candidates)

ProviderHealthService
+ boolean isHealthy(provider)
+ void updateHealth(provider, health)

PaymentProcessor (interface)
+ ProviderType getProviderType()
+ boolean supports(method)
+ ProviderResponse initiate(attempt, paymentDetails)
+ ProviderPaymentStatus getStatus(providerReferenceOrIdempotencyKey)
+ ProviderRefundResponse refund(refund)

RazorpayProcessor implements PaymentProcessor
- RazorpayClient
PayUProcessor implements PaymentProcessor
- PayUClient
CashfreeProcessor implements PaymentProcessor
- CashfreeClient

IdempotencyService
- IdempotencyRepository
+ ClaimResult claim(merchantId, key, requestFingerprint)
+ PaymentResponse getExistingResult(merchantId, key)
+ void markCompleted(merchantId, key, paymentId)

PaymentStateMachine
+ boolean canTransition(from, to)
+ void transition(payment, nextStatus)

WebhookController
- WebhookService
+ HttpResponse receiveWebhook(provider, rawBody, headers)

WebhookService
- WebhookHandlerRegistry, WebhookInboxRepository
+ void receive(provider, rawBody, headers)
+ void processEvent(event)

WebhookHandler (interface)
+ boolean verify(rawBody, headers)
+ PaymentEvent parse(rawBody)
RazorpayWebhookHandler implements WebhookHandler
PayUWebhookHandler implements WebhookHandler
CashfreeWebhookHandler implements WebhookHandler

WebhookProcessingWorker
+ void processPendingWebhooks()
PaymentReconciliationWorker
+ void reconcilePendingPayments()
MerchantNotificationWorker
+ void deliverPendingNotifications()

RefundController
- RefundService
+ Refund createRefund(paymentId, amount, idempotencyKey)
+ Refund getRefund(refundId)

RefundService
- RefundRepository, PaymentRepository, AttemptRepository
- ProviderRegistry, IdempotencyService, OutboxRepository
+ Refund createRefund(paymentId, amount, key)
+ Refund getRefund(refundId)
+ void applyRefundEvent(refundEvent)

PaymentRepository
+ Payment save(payment)
+ Optional<Payment> findById(paymentId)
+ boolean compareAndSetStatus(paymentId, expectedVersion, status)

PaymentAttemptRepository
+ PaymentAttempt save(attempt)
+ Optional<PaymentAttempt> findByProviderPaymentId(provider, providerPaymentId)
+ List<PaymentAttempt> findByPaymentId(paymentId)

WebhookInboxRepository
+ boolean insertIfAbsent(provider, eventId, verifiedEvent)
+ List<WebhookEvent> getPendingEvents()
+ void markProcessed(provider, eventId)

RefundRepository
+ Refund save(refund)
+ Optional<Refund> findById(refundId)
+ long calculateReservedAndCompletedRefundAmount(paymentId)
```

## 6. `requestFingerprint` and Idempotency

The **idempotency key** identifies a logical client operation; the **request fingerprint** confirms that another request using that key has *identical payment-defining parameters*.

```text
Request A: merchant=M1, key=K123, order=O1, amount=100000 -> fingerprint=hash_A
Request B: merchant=M1, key=K123, order=O1, amount=200000 -> fingerprint=hash_B

Same merchant + key + same fingerprint      => reuse existing result or return in-progress
Same merchant + key + different fingerprint => 409 Conflict
New merchant + key                           => independent namespace
```

```java
String fingerprint = sha256(canonicalSerialize(
    merchantId, orderId, amountInMinorUnits, currency, paymentMethod
));
```

In implementation, use stable canonical serialization with all material fields (including meaningful payment options) and unambiguous field boundaries. Avoid including raw sensitive payment credentials. **The hash does not provide concurrency control:** enforce a database `UNIQUE(merchant_id, idempotency_key)` and claim atomically.

Provider-side idempotency is **separate**. Generate a durable `providerIdempotencyKey` per attempt before external calls, and reuse it when retrying *that same uncertain attempt*, if supported by the PSP.

## 7. Payment State Model

```text
Payment:
CREATED -> PENDING -> SUCCESS
   |          |-----> FAILED
   |          `-----> CANCELLED (only if cancellation is conclusively safe)
   +-----> FAILED / CANCELLED

Attempt:
CREATED -> INITIATED -> PENDING -> SUCCESS
                    |          `----> FAILED
                    `----> UNKNOWN -> reconcile -> SUCCESS / FAILED / remains UNKNOWN

Refund:
CREATED -> PENDING -> SUCCESS / FAILED
```

Rules:
- `Payment.SUCCESS` is terminal for collection; an old failure event cannot overwrite it.
- A failed *attempt* does not necessarily fail its parent payment; another attempt may follow after a conclusive failure.
- A terminal `Payment.FAILED` is not retried in place; create a new logical payment if appropriate.
- Handle duplicates/out-of-order webhooks by event dedupe **and** state-transition checks.
- Refund progress is modeled separately from `Payment.SUCCESS`.

## 8. Method Chain — Main Flows

### Flow 1: Create Payment — Happy Path

**Scenario:** customer chooses UPI; router selects Razorpay.

```text
PaymentController.createPayment(request, idempotencyKey)
  -> PaymentService.createPayment(request, key)
       -> MerchantService.validateMerchant(merchantId)
       -> OrderService.validateOrder(orderId, amount)
       -> FingerprintService.generate(request)
       -> IdempotencyService.claim(key, fingerprint)
            -> IdempotencyRepository.insertIfAbsent(...)
       -> PaymentRepository.save(Payment[CREATED])
       -> PaymentRouter.selectProcessor(UPI, merchant)
            -> ProviderRegistry.getCandidates(UPI)
            -> ProviderHealthService.isHealthy(provider)
            -> RoutingStrategy.select(candidates)
       -> PaymentAttemptRepository.save(Attempt[CREATED], providerIdempotencyKey)
       -> RazorpayProcessor.initiate(attempt, paymentDetails)
            -> RazorpayClient.createPayment(...)
       -> PaymentAttemptRepository.updateStatus(INITIATED/PENDING)
       -> PaymentStateMachine.transition(CREATED, PENDING)
       -> PaymentRepository.updateStatus(PENDING)
       -> return PaymentResponse(PENDING, paymentAction)
```

**Why:** PaymentService orchestrates; router selects; processor calls PSP. Save intent and durable attempt identifiers **before** outbound calls. The return says payment is pending, **not** paid. Local commits and external HTTP cannot be one atomic transaction; recover by reconciliation.

### Flow 2: Successful PSP Webhook

```text
PSP POST /webhooks/razorpay
  -> WebhookController.receiveWebhook(provider, rawBody, headers)
       -> WebhookService.receive(...)
            -> WebhookHandlerRegistry.get(RAZORPAY)
            -> RazorpayWebhookHandler.verify(rawBody, headers)
            -> RazorpayWebhookHandler.parse(rawBody)
            -> WebhookInboxRepository.insertIfAbsent(event)
       -> HTTP 200 after verified event is durably persisted

ASYNC:
WebhookProcessingWorker.processPendingWebhooks()
  -> WebhookInboxRepository.getPendingEvents()
  -> WebhookService.processEvent(event)
       -> PaymentService.applyPaymentEvent(event)
            -> PaymentAttemptRepository.findByProviderPaymentId(...)
            -> PaymentRepository.findById(...)
            -> PaymentStateMachine.canTransition(PENDING, SUCCESS)
            -> DB TRANSACTION:
                 * PaymentAttemptRepository.updateStatus(SUCCESS)
                 * PaymentRepository.compareAndSetStatus(..., SUCCESS)
                 * OutboxRepository.save(PAYMENT_SUCCESS)
                 * WebhookInboxRepository.markProcessed(eventId)
```

**Why:** The provider is the source of transaction confirmation. Signature verification uses **raw** payload; inbox dedupes redelivery. The worker atomically changes state and enqueues merchant notification, so a crash won't silently lose notification. Handle failed verification without acknowledging as a valid event. If inbox and domain stores do not share a database transaction, design additional recovery guarantees.

### Flow 3: Provider Capability Fallback (Before Initiation)

```text
PaymentService.createPayment(...)
  -> PaymentRouter.selectProcessor(UPI, merchant)
       -> ProviderRegistry.getCandidates(UPI)
            * Razorpay.supports(UPI) -> false [hypothetical]
            * PayU.supports(UPI)     -> true
       -> ProviderHealthService.isHealthy(PAYU) -> true
       -> RoutingStrategy.select([PAYU]) -> PAYU
  -> PaymentAttemptRepository.save(PayU attempt)
  -> PayUProcessor.initiate(...)
  -> PaymentResponse(PENDING)
```

**Why:** A provider filtered out *before any PSP request* does not need a failed attempt. This is capability-based routing, not a risky charge retry. If **no** PSP supports UPI, return `PAYMENT_METHOD_UNAVAILABLE`; do not silently substitute cards.

### Flow 4: PSP Timeout / Unknown Outcome

```text
PaymentService.createPayment(...)
  -> RazorpayProcessor.initiate(attempt, details)
       -> RazorpayClient.createPayment(...) -> TIMEOUT
  -> PaymentAttemptRepository.markUnknown(attemptId)
  -> PaymentRepository.keepPending(paymentId)
  -> PaymentResponse(PENDING / PROCESSING)

ASYNC:
PaymentReconciliationWorker.reconcilePendingPayments()
  -> PaymentAttemptRepository.findUnknownAttempts()
  -> PaymentService.reconcilePayment(paymentId)
       -> PaymentAttemptRepository.findActiveAttempt(paymentId)
       -> ProviderRegistry.getProcessor(RAZORPAY)
       -> RazorpayProcessor.getStatus(providerReferenceOrIdempotencyKey)
       -> PaymentService.applyReconciledStatus(...)
            * confirmed SUCCESS -> payment SUCCESS
            * confirmed failure -> attempt FAILED
            * still UNKNOWN     -> schedule next reconciliation
```

**Why:** Timeout means the *reply* was lost, not necessarily the money. Do not route to PayU while outcome is unknown. Persist a queryable provider reference or provider idempotency key before initiation. Reconciliation may need provider-supported search APIs and escalations for unresolved cases.

### Flow 5: Duplicate Payment Request / Concurrency

```text
PaymentController.createPayment(request, "KEY_123")
  -> PaymentService.createPayment(...)
       -> FingerprintService.generate(request)
       -> IdempotencyService.claim(merchantId, key, fingerprint)
            -> IdempotencyRepository.insertIfAbsent(...)
                 * NEW KEY: winner creates Payment
                 * SAME KEY + SAME HASH: existing result/in-progress
                 * SAME KEY + DIFFERENT HASH: 409 Conflict
```

**Why:** Two JVMs cannot coordinate reliably using `synchronized`. A unique DB constraint ensures one *logical* claim; carefully handle a crash between claim and payment creation (same transaction or recoverable state). Idempotency must cover retries after network failures.

### Flow 6: Retry After Confirmed Failed Attempt

```text
PaymentController.retryPayment(paymentId, retryKey)
  -> PaymentService.retryPayment(paymentId, retryKey)
       -> PaymentRepository.findById(paymentId)
       -> PaymentAttemptRepository.findLatestAttempt(paymentId)
       -> assert lastAttempt == FAILED, parentPayment == PENDING
       -> atomic claim to prevent multiple active retry attempts
       -> PaymentRouter.selectFallback(UPI, [RAZORPAY])
       -> PaymentAttemptRepository.save(PayU attempt)
       -> PayUProcessor.initiate(newAttempt, details)
       -> PaymentResponse(PENDING)
```

**Why:** A fresh attempt is safe only after the previous one is *conclusively* failed (or never initiated). If prior attempt status is UNKNOWN, reconcile instead. Reuse the same parent Payment only while it is PENDING; a terminally failed Payment requires a new logical Payment.

### Flow 7: Partial / Full Refund

```text
RefundController.createRefund(paymentId, 40000, key)
  -> RefundService.createRefund(paymentId, amount, key)
       -> IdempotencyService.claimRefund(key, fingerprint)
       -> PaymentRepository.findById(paymentId)
       -> validate Payment == SUCCESS
       -> PaymentAttemptRepository.findSuccessfulAttempt(paymentId)
       -> DB TRANSACTION: reserve refundable amount + save Refund[CREATED]
       -> ProviderRegistry.getProcessor(originalSuccessfulProvider)
       -> RazorpayProcessor.refund(refund)
            -> RazorpayClient.createRefund(...)
       -> RefundRepository.updateStatus(PENDING)
       -> return Refund(PENDING)

LATER:
WebhookService.processRefundEvent(event)
  -> RefundService.applyRefundEvent(event)
       -> RefundRepository.findByProviderRefundId(...)
       -> RefundStateMachine.validateTransition(...)
       -> DB TRANSACTION:
            * RefundRepository.updateStatus(SUCCESS)
            * OutboxRepository.save(REFUND_SUCCESS)
```

**Why:** Refund with the *original collecting PSP*, not a newly routed PSP. For a ₹1,000 captured payment, a ₹400 refund is `40000` paise. Reserve refund amounts atomically, so `sum(successful + pending/reserved refunds) <= captured amount`. Refund initiation timeout is also UNKNOWN until reconciled.

## 9. Provider Selection and Fallback Decision Table

| Situation | Action |
|---|---|
| Selected PSP doesn't support UPI, no request sent | Pick compatible PSP |
| PSP is unhealthy before initiation | Choose healthy PSP |
| PSP explicitly rejects request before charge creation | Record definitive failure; possibly choose another PSP |
| PSP returns confirmed payment failure | May create a new attempt, if parent payment still eligible |
| PSP HTTP request times out after dispatch | Mark attempt UNKNOWN; reconcile; **do not immediately fallback** |
| PSP confirms success | Mark payment SUCCESS; stop other collection attempts |
| All PSPs lack requested method | Return method unavailable; offer explicit customer choice |

## 10. Data Consistency, Concurrency and Delivery

**Recommended constraints/indexes**

```sql
UNIQUE (merchant_id, idempotency_key) -- idempotency records
UNIQUE (provider_type, provider_payment_id) -- where providerPaymentId exists
UNIQUE (provider_type, event_id) -- webhook inbox
UNIQUE (payment_id, provider_idempotency_key) -- attempt key as applicable
```

- Use `version` or conditional `UPDATE ... WHERE status = 'PENDING'` for terminal transitions.
- Ensure only one currently chargeable attempt exists per parent payment, through transactional state/locking and a suitable index or claim.
- Make `Payment.SUCCESS` monotonic; stale FAILED events must not reverse it.
- A processed webhook inbox record and corresponding payment/outbox updates should commit together when stored in the same DB.
- Webhooks and notifications are usually **at-least-once**, not magically exactly-once: dedupe event IDs and make handlers idempotent.
- Use a transactional outbox rather than publishing a merchant notification directly before committing payment state.
- Distinguish *initiation* (`PENDING`) from *verified capture* (`SUCCESS`).
- Match incoming webhook to **provider + providerPaymentId** and validated merchant/amount/currency where available.

## 11. Java Interface Sketches

```java
public interface PaymentProcessor {
    ProviderType getProviderType();
    boolean supports(PaymentMethod method);
    ProviderResponse initiate(PaymentAttempt attempt, PaymentDetails details);
    ProviderPaymentStatus getStatus(String providerReferenceOrIdempotencyKey);
    ProviderRefundResponse refund(Refund refund);
}

public interface WebhookHandler {
    boolean verify(byte[] rawPayload, Map<String, String> headers);
    PaymentEvent parse(byte[] rawPayload);
}

public interface RoutingStrategy {
    ProviderType select(List<ProviderType> healthyCompatibleCandidates);
}

public interface PaymentRepository {
    Payment save(Payment payment);
    Optional<Payment> findById(UUID paymentId);
    boolean compareAndSetStatus(UUID paymentId, long expectedVersion,
                                PaymentStatus nextStatus);
}
```

Keep `RazorpayProcessor` (outbound) separate from `RazorpayWebhookHandler` (inbound). Both can share a provider config/client factory without combining responsibilities.

## 12. End-to-End Example Timeline

```text
T0: Merchant POST /payments with Idempotency-Key K1, ₹1,000 UPI
T1: Gateway validates, creates logical payment PAY_001 [CREATED]
T2: Router selects compatible healthy PSP
T3: Gateway saves ATT_001 and provider idempotency key
T4: PSP initiation returns pending + payment action
T5: PAY_001 becomes PENDING; response sent to customer
T6: Customer authorizes UPI in app
T7: PSP sends signed SUCCESS webhook
T8: Gateway verifies and stores inbox event; responds 200
T9: Worker validates and commits ATT_001 + PAY_001 as SUCCESS
T10: Outbox worker notifies merchant; merchant marks order paid
```

## 13. Interview Implementation Order (60 minutes)

1. `Payment`, `PaymentAttempt`, enums, request/response DTOs.
2. `PaymentProcessor` + two mock implementations.
3. `PaymentRouter` with supported-method filtering.
4. `PaymentService.createPayment` and repositories.
5. Idempotent create with DB unique claim and fingerprint.
6. `PaymentStateMachine` and verified `WebhookService`.
7. Explain (or implement) concurrency, timeout reconciliation, safe retries.
8. Add refunds and transactional outbox as follow-ups.

### Common interview questions

- Why separate Payment from PaymentAttempt?
- Why is a PSP timeout not a payment failure?
- Why isn't a JVM mutex sufficient for idempotency?
- How do you stop two simultaneous retries from creating two active attempts?
- What if the same webhook arrives twice, or arrives out of order?
- How does the merchant learn that an async payment succeeded?
- Why must refunds use the provider that originally captured the payment?
- How do you prevent two concurrent partial refunds from exceeding the captured amount?
- How do you ensure a crash between local DB commit and outgoing notification doesn't lose the notification?

## 14. Summary: Who Owns What?

| Component | Owns |
|---|---|
| PaymentController | HTTP validation and delegation |
| PaymentService | Logical payment workflow and business invariants |
| PaymentRouter | PSP selection by capabilities, policy, and health |
| PaymentProcessor | PSP-specific outbound initiation/status/refund calls |
| IdempotencyService | Deduplication of logical API requests |
| PaymentStateMachine | Legal payment state transitions |
| WebhookController | HTTP receiving raw PSP callbacks |
| WebhookService | Signature verification orchestration, durable receipt, event coordination |
| WebhookHandler | PSP-specific inbound signature and schema |
| ReconciliationWorker | Resolve unknown PSP outcomes |
| RefundService | Refund validation, reservation, and lifecycle |
| MerchantNotificationWorker | Reliable outbox-based delivery to merchants |

**Core rule:** Only a confirmed provider outcome changes a payment to `SUCCESS`; unknown attempts are reconciled, not blindly retried through another PSP.
