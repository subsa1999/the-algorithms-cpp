# 6 Hard Java 21 Multithreading + LLD Problems (SSE/SDE-3)

These six problems are designed to cover **Java concurrency, asynchronous programming, design patterns, production engineering, and advanced LLD** through implementation.

**Target:** After completing all six, you should be able to handle most Senior Software Engineer concurrency and LLD interviews without needing a separate theory-first preparation track.

Each problem should be implemented as a production-grade Java 21 library or service, not just a machine-coding solution.

---

## Problem 1: Build a Production-Grade Task Scheduler

**Difficulty:** 9.5/10
**Inspired by:** Quartz Scheduler, ScheduledThreadPoolExecutor, AWS SQS

### Problem Statement

Design an in-memory task execution engine supporting 100,000 scheduled tasks and thousands of concurrent submissions.

The system must support:

1. Immediate, delayed, and recurring task execution.
2. Fixed-rate and fixed-delay scheduling.
3. Priority-based task execution.
4. Configurable worker thread pools.
5. Task cancellation, interruption, and timeout.
6. Retries with exponential backoff and jitter.
7. Graceful shutdown and forced shutdown.
8. Bounded queues and backpressure.
9. Task dependencies (DAG execution).
10. Metrics for queue latency, execution time, and failures.

**Hard extension:** Support task deduplication, persistence, and recovery following process crashes.

### Concepts you must implement

**Concurrency**

* `Thread`, `Runnable`, `Callable`
* `Future`, `FutureTask`
* `ExecutorService`, `ScheduledExecutorService`
* `ThreadPoolExecutor`
* `BlockingQueue`, `DelayQueue`, `PriorityBlockingQueue`
* `ReentrantLock`, `Condition`
* `AtomicInteger`, `AtomicReference`
* `volatile`
* `CompletableFuture`
* Thread interruption and cooperative cancellation

**Design patterns**

* Strategy: Retry and scheduling policies
* Factory: Worker pool creation
* State: Task lifecycle
* Observer: Task events
* Command: Executable tasks
* Decorator: Metrics, tracing, logging

**Must solve:** How do you atomically cancel a task while another worker is attempting to execute it?

---

## Problem 2: Design a Concurrent In-Memory Cache

**Difficulty:** 9.5/10
**Inspired by:** Caffeine, Guava Cache, Redis

### Problem Statement

Build a thread-safe, high-throughput in-memory caching library supporting millions of entries.

Requirements:

1. `get()`, `put()`, `delete()`, `computeIfAbsent()`.
2. LRU and LFU eviction.
3. TTL and time-to-idle expiration.
4. Concurrent reads/writes with minimal contention.
5. Async cache loading.
6. Cache stampede prevention.
7. Background expiration and cleanup.
8. Maximum memory/weight-based eviction.
9. Cache refresh without blocking readers.
10. Metrics for hit rate, miss rate, and eviction.

**Hard extension:** Implement sharded storage and dynamic shard resizing without losing entries.

### Concepts you must implement

**Concurrency**

* `ConcurrentHashMap`
* `computeIfAbsent`
* `ReentrantReadWriteLock`
* `StampedLock`
* Lock striping
* CAS operations
* `AtomicLong`, `LongAdder`
* `CompletableFuture`
* `ScheduledExecutorService`
* Concurrent eviction coordination
* Java Memory Model and happens-before relationships

**Design patterns**

* Strategy: Eviction algorithms
* Factory: Cache construction
* Decorator: Metrics
* Proxy: Cache-aside access
* Observer: Eviction notifications

**Must solve:** When 10,000 threads request the same expired key, how do you ensure only one backend request executes?

---

## Problem 3: Build an Asynchronous Event Bus and Message Broker

**Difficulty:** 10/10
**Inspired by:** Kafka, RabbitMQ, Reactor, Spring Application Events

### Problem Statement

Design an in-process message broker that supports high-throughput asynchronous event delivery.

Requirements:

1. Publish and subscribe to topics.
2. Multiple publishers and subscribers.
3. Partitioned topics.
4. Ordered processing within partitions.
5. Consumer groups and competing consumers.
6. Asynchronous event dispatch.
7. At-least-once delivery.
8. Retry queues and dead-letter queues.
9. Backpressure and bounded buffering.
10. Graceful shutdown without losing acknowledged messages.

**Hard extension:** Implement durable append-only logging with consumer offsets and crash recovery.

### Concepts you must implement

**Concurrency**

* Producer-consumer problem
* `BlockingQueue`
* `ArrayBlockingQueue`
* `ConcurrentLinkedQueue`
* `Semaphore`
* `CountDownLatch`
* `CyclicBarrier`
* `Phaser`
* `CompletableFuture`
* `ExecutorService`
* Virtual threads (Java 21)
* Thread confinement
* Thread-safe offset management

**Design patterns**

* Observer: Pub/Sub
* Strategy: Partitioning and retry policies
* Factory: Consumer creation
* Command: Event handlers
* State: Consumer lifecycle
* Template Method: Processing pipeline

**Must solve:** How do you guarantee partition-level ordering while processing different partitions concurrently?

---

## Problem 4: Design a Distributed API Rate Limiter and Bulkhead Engine

**Difficulty:** 9.5/10
**Inspired by:** Resilience4j, Envoy, Bucket4j, API Gateway

### Problem Statement

Build a concurrent rate-limiting and resilience library for backend services.

Requirements:

1. Token Bucket.
2. Leaky Bucket.
3. Fixed Window Counter.
4. Sliding Window Log.
5. Sliding Window Counter.
6. Per-user and per-API limits.
7. Concurrent token acquisition.
8. Async permit acquisition with timeout.
9. Maximum in-flight requests.
10. Circuit breaker with CLOSED, OPEN, HALF_OPEN states.
11. Request timeout handling.
12. Queueing, rejection, and load shedding.
13. Runtime configuration changes.
14. Metrics and health reporting.

**Hard extension:** Implement a distributed rate limiter using Redis atomic operations, including failure policies when Redis becomes unavailable.

### Concepts you must implement

**Concurrency**

* `Semaphore`
* `ReentrantLock`
* `Condition`
* `AtomicLong`
* CAS loops
* `LongAdder`
* `CompletableFuture`
* `ScheduledExecutorService`
* `ThreadLocal`
* Safe publication
* Synchronization and contention reduction

**Design patterns**

* Strategy: Rate-limiting algorithms
* State: Circuit breaker
* Chain of Responsibility: Request policies
* Decorator: Timeout, retries, metrics
* Factory: Policy creation
* Builder: Configuration

**Must solve:** How do you prevent concurrent requests from exceeding the configured limit during a race condition?

---

## Problem 5: Build a Concurrent Workflow Orchestration Engine

**Difficulty:** 10/10
**Inspired by:** Temporal, Airflow, Netflix Conductor, AWS Step Functions

### Problem Statement

Design an asynchronous workflow engine executing thousands of workflows concurrently.

Each workflow consists of multiple dependent tasks represented as a DAG.

Requirements:

1. Parallel execution of independent tasks.
2. Sequential execution of dependent tasks.
3. Dynamic DAG construction.
4. Conditional branching.
5. Async task execution.
6. Retries, timeouts, and cancellation.
7. Workflow pause and resume.
8. Failure propagation.
9. Compensation and rollback.
10. Workflow status tracking.
11. Execution history and observability.
12. Bounded concurrency across workflows.

**Hard extension:** Implement checkpointing and deterministic crash recovery. Define explicitly which activities can execute more than once.

### Concepts you must implement

**Concurrency**

* `CompletableFuture.allOf()`
* `thenCompose()`, `thenCombine()`
* `ForkJoinPool`
* Work stealing
* `StructuredTaskScope` (Java 21 preview)
* Virtual threads
* `Semaphore`
* `Phaser`
* `CountDownLatch`
* Atomic state transitions
* Cancellation propagation
* Exception aggregation

**Design patterns**

* Command: Workflow tasks
* Composite: Nested workflows
* State: Workflow lifecycle
* Strategy: Retry and failure policies
* Saga: Compensating transactions
* Observer: Workflow events
* Template Method: Task execution lifecycle

**Must solve:** Task A completes, B and C run concurrently, D depends on both. If C fails after B performs an external side effect, what exactly happens?

---

## Problem 6: Build a Concurrent Database Connection Pool and Transaction Manager

**Difficulty:** 10/10
**Inspired by:** HikariCP, JDBC, Spring Transaction Management

### Problem Statement

Design a high-performance, thread-safe database connection pool and transaction management framework.

Requirements:

1. Fixed-size and dynamically sized connection pools.
2. Concurrent connection acquisition.
3. Blocking acquisition with timeout.
4. FIFO or configurable waiter fairness.
5. Connection validation and health checking.
6. Idle connection eviction.
7. Connection leak detection.
8. Graceful shutdown.
9. Transaction begin, commit, rollback.
10. Nested transactions and savepoints.
11. Thread-bound transaction contexts.
12. Isolation-level configuration.
13. Connection lifecycle and failure recovery.
14. Metrics for active, idle, and waiting connections.

**Hard extension:** Support virtual threads safely and redesign transaction context propagation for asynchronous execution across multiple threads.

### Concepts you must implement

**Concurrency**

* `Semaphore`
* `ReentrantLock`
* `Condition`
* `ThreadLocal`
* `ConcurrentHashMap`
* `BlockingQueue`
* `AtomicInteger`
* `AtomicBoolean`
* `compareAndSet()`
* `volatile`
* Thread confinement
* Resource ownership
* Java Memory Model
* Deadlock prevention

**Design patterns**

* Object Pool: Connection reuse
* Proxy: Connection wrappers
* Factory: Connection creation
* Template Method: Transaction execution
* Strategy: Pool configuration
* State: Connection lifecycle
* Decorator: Metrics and diagnostics

**Must solve:** How do you ensure that two threads never use the same physical connection simultaneously, even when release, timeout, cancellation, and shutdown race?

---

# Coverage Matrix

The six problems collectively cover the following areas.

| Concept                                     | Problems   |
| ------------------------------------------- | ---------- |
| Thread lifecycle and interruption           | 1, 3, 5    |
| `synchronized`, intrinsic monitors          | 1, 2, 6    |
| `volatile`, visibility, happens-before      | 1, 2, 4, 6 |
| `ReentrantLock`, `Condition`                | 1, 2, 4, 6 |
| Read/write locks, `StampedLock`             | 2          |
| CAS, atomics, `LongAdder`                   | 1, 2, 4, 5 |
| Concurrent collections                      | 1, 2, 3, 6 |
| `BlockingQueue`, producer-consumer          | 1, 3, 6    |
| `Semaphore`, bounded concurrency            | 3, 4, 5, 6 |
| `CountDownLatch`, `CyclicBarrier`, `Phaser` | 3, 5       |
| Thread pools and rejection policies         | 1, 3, 5    |
| `Future`, `CompletableFuture`               | 1, 2, 3, 5 |
| Virtual threads (Java 21)                   | 3, 5, 6    |
| Structured concurrency (preview)            | 5          |
| `ForkJoinPool`, work stealing               | 5          |
| `ThreadLocal`, context propagation          | 4, 6       |
| Lock-free concepts and ABA problem          | 2, 3       |
| Deadlocks, livelocks, starvation            | 1, 3, 5, 6 |
| Backpressure and load shedding              | 1, 3, 4    |
| Timeouts, cancellation, cleanup             | 1, 4, 5, 6 |
| Idempotency and duplicate execution         | 1, 3, 5    |
| State machines and lifecycle races          | 1, 4, 5, 6 |
| Java Memory Model and safe publication      | 2, 4, 6    |
| Spring-style AOP and interception           | 4, 6       |
| Concurrency testing and race detection      | All six    |

**Important:** Merely using these APIs does not establish mastery. For each problem, you must explain the correctness invariants, locking scope, linearization points, failure modes, and contention bottlenecks.

These problems also cover the core GoF patterns relevant to backend LLD. They do not replace every possible LLD interview topic, such as domain modeling for payment systems or parking lots.

---

# Reusable Master Prompt

Use the following prompt with **any of the six problem statements**. It is designed to produce a complete, implementation-oriented study guide rather than a superficial theoretical explanation.

# ROLE

Act as a Principal Java Engineer, concurrency specialist, and expert LLD interviewer with experience designing production-grade backend infrastructure.

I will provide a hard real-world engineering problem.

Your responsibility is to create a comprehensive, implementation-focused Markdown study guide that teaches me everything required to design, implement, test, and defend the solution in a Senior Software Engineer / SDE-3 interview.

**Primary language:** Java 21.

**Technical depth:** Senior to Staff Engineer.

**Learning objective:** I should understand the underlying concurrency concepts, design decisions, implementation details, and production failure modes without needing a separate theoretical tutorial.

Avoid vague explanations. Every important concept must be demonstrated through actual code and realistic execution scenarios.

---

# 1. PROBLEM ANALYSIS

Explain:

* What exactly are we building?
* Real-world use cases.
* Functional requirements.
* Non-functional requirements.
* Expected throughput, latency, and concurrency.
* Important assumptions and constraints.
* What makes the problem difficult?
* Which race conditions and failure scenarios must be handled?

Define the correctness invariants that must always hold.

Explain which guarantees are achievable and which guarantees cannot be achieved without additional infrastructure.

---

# 2. CORE DESIGN

Provide:

1. High-level architecture.
2. Component responsibilities.
3. Interfaces and their contracts.
4. Main Java classes.
5. UML class diagram using Mermaid.
6. Sequence diagrams for important operations.
7. State machine diagrams where appropriate.
8. Thread ownership model.
9. Shared mutable state inventory.
10. Synchronization strategy.

Explain why each class exists.

Follow SOLID principles without introducing unnecessary abstractions.

Distinguish domain entities, services, strategies, infrastructure components, and concurrency primitives.

---

# 3. IMPLEMENTATION — JAVA 21

Implement the entire core solution using Java 21.

Requirements:

* Prefer syntactically correct, compilable Java 21 code over vague pseudocode.
* Explicitly label any pseudocode or omitted implementation.
* Never present pseudocode as compilable Java.
* Use records, sealed interfaces, enums, and modern switch expressions where appropriate.
* Use generics where necessary.
* Implement complete class and method contracts.
* Show thread-safe initialization and shutdown.
* Include exception handling.
* Include cancellation and timeout logic.
* Include resource cleanup.
* Avoid deprecated or unsafe concurrency APIs.

When using virtual threads, explain when they are beneficial and when they are inappropriate.

Use only stable Java 21 features by default.

If demonstrating preview features, label them explicitly and explain the required compiler/runtime flags. Provide a stable Java 21 alternative.

For complex methods, provide:

1. Java code.
2. Step-by-step execution explanation.
3. Thread interaction explanation.
4. Race-condition analysis.
5. Time complexity.
6. Space complexity.
7. Potential optimizations.

Every critical code block must explain why it is thread-safe.

---

# 4. JAVA CONCURRENCY DEEP DIVE

Identify every concurrency concept relevant to the problem.

For each concept, explain:

### A. What problem does it solve?

Describe the actual race condition, contention issue, or visibility problem.

### B. How does it work internally?

Explain relevant JVM and Java Memory Model behavior.

### C. Why is it used here?

Compare it against competing approaches.

For example:

* synchronized vs ReentrantLock
* ReentrantLock vs StampedLock
* volatile vs AtomicReference
* AtomicLong vs LongAdder
* BlockingQueue vs ConcurrentLinkedQueue
* Semaphore vs bounded ThreadPoolExecutor
* Platform threads vs virtual threads
* Future vs CompletableFuture
* CompletableFuture vs structured concurrency
* ThreadLocal vs explicit context propagation
* CAS vs mutex

Only include comparisons relevant to the problem.

### D. What goes wrong without it?

Provide a broken implementation.

Show an execution interleaving demonstrating the failure.

Then provide the corrected implementation.

### E. What are the hidden pitfalls?

Cover relevant issues including:

* Race conditions
* Data races
* Lost updates
* Visibility problems
* Reordering
* Deadlocks
* Livelocks
* Starvation
* Priority inversion
* Thread pool exhaustion
* Lock contention
* ABA problems
* False sharing
* Cancellation races
* Lost notifications
* Resource leaks

Do not force unrelated concepts into the design. Clearly identify concepts that are not applicable.

---

# 5. DESIGN PATTERNS

Identify every design pattern actually used.

For each pattern:

1. Name the pattern.
2. Explain the underlying design problem.
3. Identify participating classes.
4. Show a minimal Java 21 implementation.
5. Explain why the pattern fits.
6. Explain alternatives.
7. Explain how it improves extensibility or testability.
8. Identify situations where it would be overengineering.

Cover applicable creational, structural, and behavioral patterns.

Include architecture patterns such as Saga, CQRS, or event-driven design only when relevant.

Do not claim that a pattern is used unless the implementation genuinely demonstrates it.

---

# 6. HARD CONCURRENCY SCENARIOS

Create at least 10 difficult concurrency scenarios specific to this system.

Examples:

* Two threads update the same state simultaneously.
* Shutdown begins while work is being submitted.
* A task is cancelled while executing.
* A timeout races with successful completion.
* A resource is released twice.
* A worker crashes after executing a side effect.
* A lock holder is interrupted.
* A callback executes synchronously and causes reentrancy.
* Thousands of requests contend for one resource.
* A stale worker attempts to modify newer state.

For every scenario, provide:

**Initial state → Concurrent operations → Dangerous interleaving → Possible failure → Correct synchronization → Final state**

Identify the linearization point when the operation is intended to be linearizable.

Explain which operation wins each race and why.

---

# 7. TESTING STRATEGY

Use JUnit 5.

Provide:

* Unit tests.
* Multithreaded integration tests.
* Stress tests.
* Deterministic concurrency tests using barriers/latches.
* Timeout tests.
* Cancellation tests.
* Shutdown tests.
* Fault-injection tests.
* Resource-leak tests.

Explain why `Thread.sleep()` is generally unreliable for coordinating concurrency tests.

Demonstrate how to reproduce at least three real race conditions.

Explain how to use:

* Java Flight Recorder (JFR)
* Thread dumps
* JMH
* jcstress

Distinguish performance benchmarks from correctness tests.

---

# 8. PERFORMANCE AND SCALABILITY

Analyze:

1. Throughput bottlenecks.
2. Lock contention.
3. Queue growth.
4. Memory overhead.
5. Thread counts.
6. Context-switching overhead.
7. Tail latency (p95, p99, p99.9).
8. GC pressure.
9. Backpressure strategies.
10. CPU-bound vs I/O-bound execution.

Discuss scaling from:

* 10 concurrent requests
* 1,000 concurrent requests
* 100,000 concurrent requests

State assumptions rather than inventing benchmark results.

Explain when additional threads stop improving throughput.

Provide relevant Big-O analysis, while distinguishing algorithmic complexity from real concurrency performance.

---

# 9. FAILURE HANDLING AND PRODUCTION READINESS

Explain:

* What happens during crashes?
* What happens during partial failures?
* How are retries handled?
* How is duplicate processing prevented or tolerated?
* What happens when downstream services become slow?
* How are resources reclaimed?
* What happens during shutdown?
* How are unhandled exceptions surfaced?
* How is overload detected?
* What metrics should be exposed?

Where appropriate, distinguish in-process guarantees from distributed guarantees.

Discuss persistence and recovery limitations explicitly.

---

# 10. INTERVIEW DEFENSE

Create 20 difficult interview follow-up questions.

For every question, provide:

* A precise answer.
* The engineering reasoning.
* Relevant Java/JVM details.
* Trade-offs.
* A code example where useful.

Include questions an experienced Staff Engineer would ask to challenge the design.

---

# 11. FINAL REVISION CHEAT SHEET

End with:

### A. Core Classes

Table containing class, responsibility, shared state, and synchronization primitive.

### B. Concurrency Invariants

The 10 most important correctness properties.

### C. Design Patterns

Pattern → Implementation class → Why it exists.

### D. Critical Java APIs

API → Purpose → Important behavior → Common mistake.

### E. Common Failure Modes

Failure → Root cause → Prevention.

### F. Interview Summary

Explain the entire solution in a concise 5-minute technical walkthrough.

### G. Implementation Checklist

An ordered checklist that allows me to implement the system from scratch without looking at the solution.

---

# PRESENTATION REQUIREMENTS

* Produce a single, well-organized Markdown document.
* Use Mermaid diagrams.
* Keep explanations in simple, technically precise English.
* Prefer Java 21 code to abstract theory.
* Explain non-obvious lines of code.
* Never hide synchronization details behind pseudocode.
* Do not skip implementation-critical sections.
* Explicitly distinguish thread safety, atomicity, visibility, ordering, and liveness.
* Identify which operations are linearizable and which are eventually consistent.
* Avoid unnecessary frameworks and dependencies.
* Use Spring Boot only if it adds genuine value.
* Do not confuse virtual-thread concurrency with CPU parallelism.
* Do not claim that `CompletableFuture` automatically makes code non-blocking.
* Treat retries, cancellation, shutdown, and timeout races as first-class requirements.
* Favor correctness before performance optimization.
* Where guarantees conflict, explain the trade-off instead of silently weakening requirements.
* Do not invent benchmarks, guarantees, or Java API capabilities.

**Do not compress the explanation merely to keep the answer short.**

If the complete implementation is too large, prioritize a fully functional core and clearly separate optional extensions. Never present an incomplete implementation as production-ready.

# PROBLEM STATEMENT

[PASTE ONE OF THE SIX PROBLEMS HERE]

---

## Recommended Completion Order

| Order | Problem          | Main expertise gained                             | Estimated implementation effort |
| ----- | ---------------- | ------------------------------------------------- | ------------------------------- |
| 1     | Task Scheduler   | Executors, futures, queues, cancellation          | 8–12 hours                      |
| 2     | Concurrent Cache | Locks, CAS, concurrent data structures            | 10–14 hours                     |
| 3     | Event Bus        | Producer-consumer, ordering, backpressure         | 12–16 hours                     |
| 4     | Rate Limiter     | Atomic operations, semaphores, state machines     | 8–12 hours                      |
| 5     | Workflow Engine  | Async orchestration, DAGs, structured concurrency | 14–20 hours                     |
| 6     | Connection Pool  | Resource ownership, lifecycle races, transactions | 12–16 hours                     |

**Total estimated hands-on effort:** 64–90 hours, excluding optional distributed extensions.

### What you should be able to do afterward

For each implementation, you should be able to:

1. **Code:** Implement the critical classes without reference material.
2. **Prove correctness:** Explain every synchronization decision and invariant.
3. **Debug:** Identify race conditions, deadlocks, starvation, and leaks.
4. **Optimize:** Explain contention bottlenecks and measurable alternatives.
5. **Defend:** Handle Staff-level follow-ups about failure scenarios and trade-offs.

**Important distinction:** These six projects provide broad practical coverage of core Java 21 concurrency and infrastructure-oriented LLD. They cannot guarantee mastery of every Java concurrency topic or every LLD framework. To avoid returning to theory, make concurrency tests, execution interleavings, and implementation from scratch mandatory parts of each project—not optional reading.
