# 🚀 System Design Prep — 15-Day / 150-Topic Sheet (Senior SWE)

> A structured, interview-focused roadmap for a **Senior / Staff Software Engineer** system-design loop.
> Covers timeless fundamentals **and** the latest (2024–2025) infrastructure: event-driven architecture, CDC, vector databases, LLM/RAG serving, cell-based architecture, observability, and multi-region resilience.

## How to use this sheet

- **~2–3 focused hours/day.** Each day = **10 topics** + **1–2 design drills**.
- Check off `[ ] → [x]` as you go. Don't just read — **draw the diagram** and **state the trade-off** out loud.
- For every topic, be able to answer: *What problem does it solve? What does it cost? When would I NOT use it?*
- Days 1–13 build the toolkit. **Days 14–15 are full mock designs** — do them under a timer (45 min each).
- Golden rule for the interview: **Requirements → Estimation → API → High-level design → Deep dive → Bottlenecks → Trade-offs.**

### The 5-step interview framework (memorize this)

1. **Scope & requirements** — functional + non-functional (SLA, QPS, latency, consistency), clarify assumptions.
2. **Back-of-envelope estimation** — QPS, storage/yr, bandwidth, memory for cache.
3. **API + data model** — endpoints, schema, access patterns.
4. **High-level architecture** — components + data flow diagram.
5. **Deep dive & scale** — pick 1–2 components, remove bottlenecks, discuss trade-offs & failure modes.

---

## 📅 Day 1 — Fundamentals & Trade-offs

- [ ] 1. Performance vs. scalability; latency vs. throughput
- [ ] 2. Vertical vs. horizontal scaling; statelessness & why it matters
- [ ] 3. CAP theorem (CP vs. AP) and the PACELC extension
- [ ] 4. Consistency models: strong, eventual, causal, read-your-writes, monotonic
- [ ] 5. Availability math: the "nines", availability in series vs. parallel
- [ ] 6. Back-of-the-envelope estimation (QPS, storage, bandwidth, memory)
- [ ] 7. Latency numbers every engineer should know (L1 → cross-continent RTT)
- [ ] 8. Powers of two & data-size intuition (KB→MB→GB→TB→PB)
- [ ] 9. SLA / SLO / SLI and error budgets
- [ ] 10. Read-heavy vs. write-heavy systems; read:write ratios shaping design
- **Drill:** Estimate storage + QPS for a URL shortener handling 100M new URLs/month.

## 📅 Day 2 — Networking & Communication

- [ ] 11. OSI model essentials; where L4 vs. L7 decisions live
- [ ] 12. TCP vs. UDP; when to choose each (reliability vs. latency)
- [ ] 13. HTTP/1.1 → HTTP/2 → HTTP/3 (QUIC) and multiplexing
- [ ] 14. DNS resolution, TTL, and routing policies (latency/geo/weighted)
- [ ] 15. TLS handshake, SSL termination, mTLS
- [ ] 16. REST design & richness constraints (HATEOAS, idempotency)
- [ ] 17. gRPC / Protobuf / Thrift — RPC trade-offs vs. REST
- [ ] 18. GraphQL: over/under-fetching, N+1, schema federation
- [ ] 19. WebSockets, Server-Sent Events, long polling (real-time transport)
- [ ] 20. Idempotency keys, retries, timeouts, exponential backoff + jitter
- **Drill:** Design the client↔server protocol for a live chat app (delivery + presence).

## 📅 Day 3 — Databases: Relational & Transactions

- [ ] 21. ACID properties in depth
- [ ] 22. Transaction isolation levels & anomalies (dirty/non-repeatable/phantom)
- [ ] 23. MVCC and how modern RDBMSs implement isolation
- [ ] 24. Indexing: B-tree vs. hash vs. covering vs. composite indexes
- [ ] 25. Query planning & optimization; EXPLAIN, slow-query analysis
- [ ] 26. Normalization vs. denormalization trade-offs
- [ ] 27. Connection pooling & the "too many connections" problem
- [ ] 28. Read replicas & replication lag; read-your-writes handling
- [ ] 29. Two-phase commit (2PC) and its failure modes
- [ ] 30. Materialized views & precomputation for read performance
- **Drill:** Design the schema + indexes for an e-commerce orders/inventory system.

## 📅 Day 4 — NoSQL & Data Modeling

- [ ] 31. Key-value stores (Redis, DynamoDB) — access patterns
- [ ] 32. Document stores (MongoDB) — embedding vs. referencing
- [ ] 33. Wide-column stores (Cassandra, Bigtable, HBase) & LSM trees
- [ ] 34. Graph databases (Neo4j) — when relationships dominate
- [ ] 35. Time-series databases (InfluxDB, TimescaleDB, Prometheus TSDB)
- [ ] 36. BASE vs. ACID; tunable consistency (quorum reads/writes, R+W>N)
- [ ] 37. Data modeling for NoSQL: query-first (single-table design)
- [ ] 38. Secondary indexes in distributed stores (global vs. local)
- [ ] 39. SQL vs. NoSQL decision criteria; polyglot persistence
- [ ] 40. NewSQL / distributed SQL (Spanner, CockroachDB, TiDB, Vitess)
- **Drill:** Model a social-media feed store optimized for fan-out reads (DynamoDB single-table).

## 📅 Day 5 — Caching & Content Delivery

- [ ] 41. Cache layers: client, CDN, reverse proxy, app, DB
- [ ] 42. Cache strategies: cache-aside, read-through, write-through, write-behind, refresh-ahead
- [ ] 43. Eviction policies: LRU, LFU, FIFO, TTL, ARC
- [ ] 44. Cache invalidation strategies (the "hardest problem")
- [ ] 45. Thundering herd, cache stampede, and dogpile prevention
- [ ] 46. Hot-key / celebrity problem & mitigation (key splitting, local cache)
- [ ] 47. Redis deep dive: data structures, persistence (RDB/AOF), clustering
- [ ] 48. Distributed cache consistency & cache coherence
- [ ] 49. CDN: push vs. pull, edge caching, cache-control headers
- [ ] 50. Edge compute / edge functions (Cloudflare Workers, Lambda@Edge)
- **Drill:** Add a caching layer to a read-heavy product-catalog API; handle invalidation on price change.

## 📅 Day 6 — Scaling, Load Balancing & Sharding

- [ ] 51. Load balancing algorithms (round-robin, least-conn, weighted, hash)
- [ ] 52. L4 vs. L7 load balancers; reverse proxy vs. LB
- [ ] 53. Health checks, connection draining, graceful degradation
- [ ] 54. Consistent hashing (+ virtual nodes) for partition/rebalancing
- [ ] 55. Sharding strategies: range, hash, geo, directory-based
- [ ] 56. Resharding / rebalancing without downtime
- [ ] 57. Hotspot detection & shard-key selection pitfalls
- [ ] 58. Autoscaling: reactive vs. predictive; scale-to-zero
- [ ] 59. Rate limiting algorithms: token bucket, leaky bucket, sliding window
- [ ] 60. Distributed rate limiting (Redis-backed, sticky counters)
- **Drill:** Design a distributed API rate limiter (per-user, 1000 req/min, multi-region).

## 📅 Day 7 — Messaging, Streaming & Async

- [ ] 61. Message queues vs. pub/sub vs. event streaming
- [ ] 62. Kafka deep dive: partitions, offsets, consumer groups, ordering
- [ ] 63. Delivery semantics: at-most-once, at-least-once, exactly-once
- [ ] 64. Idempotent consumers & deduplication
- [ ] 65. Dead-letter queues, poison messages, retry topics
- [ ] 66. Backpressure & flow control (bounded queues, 503 shedding)
- [ ] 67. Event-driven architecture & choreography vs. orchestration
- [ ] 68. Change Data Capture (CDC) with Debezium / outbox pattern
- [ ] 69. Stream processing (Flink, Kafka Streams, Spark Streaming); windowing
- [ ] 70. Lambda vs. Kappa architecture for data pipelines
- **Drill:** Design an order-processing pipeline with the transactional outbox + CDC.

## 📅 Day 8 — Consistency, Consensus & Coordination

- [ ] 71. Leader election & the split-brain problem
- [ ] 72. Consensus: Paxos (concept) and Raft (practical)
- [ ] 73. Quorums, read/write quorum tuning (R + W > N)
- [ ] 74. Vector clocks & Lamport timestamps (ordering events)
- [ ] 75. Conflict resolution: last-write-wins, CRDTs
- [ ] 76. Distributed locks (Redlock debate, ZooKeeper, etcd)
- [ ] 77. Coordination services: ZooKeeper, etcd, Consul
- [ ] 78. Saga pattern for distributed transactions (compensating actions)
- [ ] 79. Two-phase vs. three-phase commit; why 2PC blocks
- [ ] 80. Gossip protocols & anti-entropy (membership, failure detection)
- **Drill:** Design a distributed lock service; discuss correctness under network partition.

## 📅 Day 9 — Microservices, APIs & Service Mesh

- [ ] 81. Monolith vs. microservices vs. modular monolith trade-offs
- [ ] 82. Service discovery (client-side vs. server-side)
- [ ] 83. API Gateway responsibilities (auth, routing, throttling, aggregation)
- [ ] 84. Backend-for-Frontend (BFF) pattern
- [ ] 85. Service mesh (Istio, Linkerd): sidecars, mTLS, traffic shaping
- [ ] 86. Circuit breaker, bulkhead, timeout, retry (resilience patterns)
- [ ] 87. API versioning & backward compatibility
- [ ] 88. Contract testing & schema evolution (Protobuf/Avro compatibility)
- [ ] 89. Distributed tracing (OpenTelemetry, correlation IDs)
- [ ] 90. Deployment: blue-green, canary, rolling, feature flags
- **Drill:** Decompose a monolithic ride-sharing app into services; define boundaries + APIs.

## 📅 Day 10 — Storage, Search & Indexing

- [ ] 91. Blob/object storage (S3): durability, storage classes, lifecycle
- [ ] 92. Block vs. file vs. object storage
- [ ] 93. Distributed file systems (GFS/HDFS) & the metadata server
- [ ] 94. Inverted index & full-text search fundamentals
- [ ] 95. Elasticsearch / OpenSearch: shards, replicas, relevance scoring
- [ ] 96. Bloom filters & other probabilistic structures (Count-Min, HyperLogLog)
- [ ] 97. LSM-tree vs. B-tree storage engines (write vs. read amplification)
- [ ] 98. Write-ahead logs (WAL) & durability guarantees
- [ ] 99. Data lakes, warehouses, and lakehouse (Iceberg/Delta/Hudi)
- [ ] 100. Columnar formats (Parquet/ORC) & OLAP vs. OLTP
- **Drill:** Design a full-text search system for a product catalog with typo tolerance + ranking.

## 📅 Day 11 — Reliability, Observability & Operations

- [ ] 101. The three pillars: metrics, logs, traces
- [ ] 102. RED / USE methods for monitoring
- [ ] 103. Alerting, on-call, runbooks, and incident response
- [ ] 104. Health checks: liveness vs. readiness; graceful shutdown
- [ ] 105. Chaos engineering & fault injection
- [ ] 106. Disaster recovery: RTO / RPO, backup & restore strategies
- [ ] 107. Multi-region & active-active vs. active-passive
- [ ] 108. Idempotency & exactly-once at the API boundary
- [ ] 109. Graceful degradation & load shedding
- [ ] 110. Zero-downtime deployments & database migrations (expand/contract)
- **Drill:** Design a multi-region failover strategy for a payments service (RPO ≈ 0).

## 📅 Day 12 — Security, Privacy & Compliance

- [ ] 111. AuthN vs. AuthZ; sessions vs. tokens
- [ ] 112. OAuth 2.0 / OIDC flows; JWT structure, validation, revocation
- [ ] 113. RBAC vs. ABAC; principle of least privilege
- [ ] 114. Encryption in transit & at rest; key management (KMS, envelope encryption)
- [ ] 115. OWASP Top 10 (injection, XSS, SSRF, broken access control)
- [ ] 116. Secrets management (Vault, rotation, no secrets in code)
- [ ] 117. DDoS mitigation, WAF, bot protection
- [ ] 118. PII handling, data residency, GDPR/CCPA basics
- [ ] 119. Audit logging & tamper-evidence
- [ ] 120. API security: rate limiting, input validation, CORS, signing
- **Drill:** Design authentication + authorization for a multi-tenant SaaS platform.

## 📅 Day 13 — Modern / AI-Era Infrastructure (2024–2025)

- [ ] 121. Vector databases (Pinecone, Milvus, pgvector) & embeddings
- [ ] 122. Approximate Nearest Neighbor search (HNSW, IVF, product quantization)
- [ ] 123. RAG (Retrieval-Augmented Generation) system architecture
- [ ] 124. LLM inference serving: batching, KV-cache, GPU utilization
- [ ] 125. Model gateway, prompt caching, semantic caching
- [ ] 126. Feature stores for ML (online vs. offline features)
- [ ] 127. Real-time recommendation & ranking pipelines
- [ ] 128. Cell-based architecture (blast-radius isolation)
- [ ] 129. Serverless & FaaS trade-offs (cold starts, statelessness)
- [ ] 130. Cost-aware design: FinOps, tiered storage, spot/GPU economics
- **Drill:** Design a RAG-powered document Q&A service (ingest → embed → retrieve → generate) at scale.

## 📅 Day 14 — Classic Design Problems (timed mocks)
>
> Do each in 30–45 min: requirements → estimation → API → HLD → deep dive → trade-offs.

- [ ] 131. Design a URL shortener (TinyURL / Bit.ly)
- [ ] 132. Design a pastebin
- [ ] 133. Design a rate limiter (revisit end-to-end)
- [ ] 134. Design a news feed (Twitter/Facebook) — fan-out on write vs. read
- [ ] 135. Design a chat/messaging system (WhatsApp) — delivery + presence
- [ ] 136. Design a notification system (push/email/SMS, multi-channel)
- [ ] 137. Design a web crawler
- [ ] 138. Design a typeahead / autocomplete service
- [ ] 139. Design a unique ID generator (Snowflake)
- [ ] 140. Design a key-value store (Dynamo-style)
- **Drill:** Pick two above and write full solutions with diagrams.

## 📅 Day 15 — Advanced / Staff-Level Design Problems + Mock
>
> These emphasize scale, consistency, and trade-off depth expected at senior/staff level.

- [ ] 141. Design a video streaming platform (YouTube/Netflix) — transcoding + CDN
- [ ] 142. Design a ride-sharing service (Uber) — geospatial matching, surge
- [ ] 143. Design a distributed job scheduler / cron
- [ ] 144. Design a payment system (idempotency, ledger, exactly-once)
- [ ] 145. Design a photo/file storage service (Instagram/Dropbox) — sync + dedupe
- [ ] 146. Design a real-time analytics / metrics system
- [ ] 147. Design a stock exchange / order-matching engine
- [ ] 148. Design a collaborative editor (Google Docs) — OT/CRDT
- [ ] 149. Design a distributed search engine (Google-scale)
- [ ] 150. Full mock interview end-to-end + self-review against a rubric
- **Drill:** Record yourself doing #150 in 45 min; grade on scoping, trade-offs, and communication.

---

## 🎯 Evaluation rubric (grade yourself each mock)

| Dimension | Weak | Strong |
|---|---|---|
| Requirement scoping | Jumps to solution | Clarifies functional + NFRs, states assumptions |
| Estimation | Skips numbers | QPS/storage/bandwidth back-of-envelope |
| High-level design | Vague boxes | Clear components + data flow + API |
| Deep dive | Stays shallow | Picks bottleneck, quantifies, iterates |
| Trade-offs | "It depends" | Names options + explicit pros/cons/failure modes |
| Communication | Rambles | Structured, drives the conversation |

## 📚 Core resources

- **System Design Primer** — github.com/donnemartin/system-design-primer
- **Designing Data-Intensive Applications** (Kleppmann) — the canonical deep-dive book
- **Grokking the Modern System Design Interview** (educative)
- **ByteByteGo** (Alex Xu) — *System Design Interview* Vol 1 & 2 + newsletter
- Engineering blogs: Netflix, Uber, Discord, Stripe, Cloudflare, Meta, DoorDash
- **Papers to skim:** Dynamo, Bigtable, Spanner, Kafka, Raft, GFS, MapReduce

> **Tip:** Depth > breadth in the interview. Know ~10 problems cold and the trade-offs behind every component you name.
