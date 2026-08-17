# Microsoft Software Engineer II — Azure Data / DI Team
## Interview Preparation Checklist

**Role:** Software Engineer II  
**Location:** Hyderabad / Bangalore  
**Phone Screen:** 21 August 2026  
**Primary focus:** Backend + Azure Data + ETL/Data Integration + DSA + LLD + System Design

---

# 1. Priority Order

- [ ] DSA + coding
- [ ] ETL / ELT / data integration
- [ ] Data migration and CDC
- [ ] LLD / production-quality coding
- [ ] Distributed systems
- [ ] System design
- [ ] Concurrency
- [ ] Resume deep dive
- [ ] Microsoft behavioral / culture questions

---

# 2. HackerRank / Coding Assessment

## Arrays / Hashing

- [ ] Subarray Sum Equals K
- [ ] Longest Consecutive Sequence
- [ ] Product of Array Except Self
- [ ] Merge Intervals
- [ ] Insert Interval
- [ ] Prefix sum patterns
- [ ] Frequency-map patterns
- [ ] Sweep-line basics

## Sliding Window

- [ ] Longest Substring Without Repeating Characters
- [ ] Longest Repeating Character Replacement
- [ ] Minimum Window Substring
- [ ] Be able to explain the window invariant clearly

## Binary Search

- [ ] Search in Rotated Sorted Array
- [ ] Find Minimum in Rotated Sorted Array
- [ ] Binary Search on Answer
- [ ] Understand `low <= high` vs `low < high`
- [ ] Understand when and why to `return low`

## Trees

- [ ] Recursive DFS
- [ ] Iterative DFS
- [ ] BFS / level-order traversal
- [ ] Validate BST
- [ ] Lowest Common Ancestor
- [ ] Diameter of Binary Tree
- [ ] Binary Tree Maximum Path Sum
- [ ] Serialize / Deserialize Binary Tree

## Graphs

- [ ] BFS
- [ ] DFS
- [ ] Connected components
- [ ] Cycle detection
- [ ] Course Schedule / Topological Sort
- [ ] Kahn's Algorithm
- [ ] Dijkstra
- [ ] Bellman-Ford concept
- [ ] Union-Find
- [ ] Multi-source BFS
- [ ] Number of Islands
- [ ] Clone Graph
- [ ] Network Delay Time
- [ ] Accounts Merge
- [ ] Rotting Oranges

## Heap / Priority Queue

- [ ] Top K Frequent Elements
- [ ] Kth Largest Element
- [ ] Merge K Sorted Lists
- [ ] Median from Data Stream
- [ ] Meeting Rooms II
- [ ] Understand min-heap vs max-heap selection

## Dynamic Programming

- [ ] House Robber I
- [ ] House Robber II
- [ ] Coin Change
- [ ] Longest Increasing Subsequence
- [ ] Word Break
- [ ] Target Sum
- [ ] Partition Equal Subset Sum
- [ ] Define DP state before coding
- [ ] Explain transition clearly

## Trie

- [ ] Implement Trie
- [ ] Prefix search
- [ ] Word Search II
- [ ] Autocomplete use case
- [ ] Know trie time/space trade-offs

---

# 3. Java Coding Readiness

Know these without searching documentation:

- [ ] `HashMap`
- [ ] `HashSet`
- [ ] `TreeMap`
- [ ] `TreeSet`
- [ ] `PriorityQueue`
- [ ] `ArrayDeque`
- [ ] `ArrayList`
- [ ] `Comparator`
- [ ] `Collections.sort`
- [ ] `Arrays.sort`
- [ ] `computeIfAbsent`
- [ ] `merge`
- [ ] `getOrDefault`
- [ ] Custom comparator syntax
- [ ] Graph adjacency-list implementation
- [ ] BFS template
- [ ] DFS template

---

# 4. Concurrency

## Fundamentals

- [ ] Thread vs Runnable
- [ ] ExecutorService
- [ ] Future
- [ ] CompletableFuture
- [ ] `synchronized`
- [ ] `volatile`
- [ ] `Lock`
- [ ] `ReentrantLock`
- [ ] AtomicInteger
- [ ] ConcurrentHashMap
- [ ] BlockingQueue
- [ ] Semaphore
- [ ] CountDownLatch

## Concepts

- [ ] Race condition
- [ ] Deadlock
- [ ] Starvation
- [ ] Visibility
- [ ] Atomicity
- [ ] Happens-before
- [ ] CAS
- [ ] Lock contention
- [ ] Why `volatile` does not make `count++` atomic

## Practice

- [ ] Producer-consumer
- [ ] Bounded blocking queue
- [ ] Worker pool
- [ ] Thread-safe cache
- [ ] Concurrent task executor
- [ ] Retry + graceful shutdown

---

# 5. ETL / Data Integration — Highest Priority

## Foundations

- [ ] ETL vs ELT
- [ ] Batch vs streaming
- [ ] Full load vs incremental load
- [ ] CDC — Change Data Capture
- [ ] Snapshot + CDC migration
- [ ] Checkpointing
- [ ] Watermarks
- [ ] Replay
- [ ] Backfill

## Reliability

- [ ] At-most-once
- [ ] At-least-once
- [ ] Exactly-once limitations
- [ ] Idempotency
- [ ] Deduplication
- [ ] Retry
- [ ] Exponential backoff
- [ ] Dead-letter queue
- [ ] Poison messages

## Data correctness

- [ ] Schema validation
- [ ] Schema evolution
- [ ] Backward compatibility
- [ ] Nullable/default fields
- [ ] Duplicate detection
- [ ] Referential integrity
- [ ] Row-count reconciliation
- [ ] Aggregate reconciliation
- [ ] Hash/checksum validation
- [ ] Business-level invariants

## Scale

- [ ] Partitioning
- [ ] Consistent partition keys
- [ ] Hot partitions
- [ ] Data skew
- [ ] Rebalancing
- [ ] Consumer lag
- [ ] Backpressure
- [ ] Batching
- [ ] Autoscaling

---

# 6. Data Migration

Be able to design:

> Migrate a multi-terabyte on-prem database to Azure with near-zero downtime.

Checklist:

- [ ] Clarify data size
- [ ] Clarify downtime requirement
- [ ] Initial snapshot
- [ ] Parallel bulk export
- [ ] Staging/raw storage
- [ ] Parallel import
- [ ] CDC from source transaction log
- [ ] Catch-up phase
- [ ] Reconciliation
- [ ] Shadow validation
- [ ] Cutover
- [ ] Rollback plan
- [ ] Monitoring after cutover
- [ ] Data-security considerations

---

# 7. Azure Data Technologies

Know the architectural purpose of:

- [ ] Azure Data Factory
- [ ] Azure Synapse
- [ ] Azure Data Lake Storage
- [ ] Azure Functions
- [ ] Event Hubs
- [ ] Cosmos DB
- [ ] Azure SQL
- [ ] Databricks / Spark
- [ ] Azure Monitor
- [ ] Key Vault
- [ ] Managed Identity

Do not spend interview-prep time memorizing service APIs.

---

# 8. LLD

## LRU Cache

- [ ] Generic `LRUCache<K,V>`
- [ ] HashMap + Doubly Linked List
- [ ] O(1) get
- [ ] O(1) put
- [ ] Capacity management
- [ ] Eviction policy abstraction
- [ ] Thread safety
- [ ] TTL extension
- [ ] Metrics
- [ ] Edge cases

## Rate Limiter

- [ ] Fixed Window
- [ ] Sliding Window
- [ ] Token Bucket
- [ ] Leaky Bucket
- [ ] Per-user / per-tenant policy
- [ ] Thread safety
- [ ] Distributed implementation
- [ ] Redis atomicity
- [ ] TTL
- [ ] Clock issues

## Notification System

- [ ] Notification entity
- [ ] Email channel
- [ ] SMS channel
- [ ] Push channel
- [ ] Strategy pattern
- [ ] Factory pattern
- [ ] Templates
- [ ] User preferences
- [ ] Retry
- [ ] DLQ
- [ ] Rate limiting
- [ ] Idempotency

## LLD Answering Framework

For every LLD question:

- [ ] Clarify functional requirements
- [ ] Clarify scope
- [ ] Clarify concurrency expectations
- [ ] Identify entities
- [ ] Define interfaces
- [ ] Define relationships
- [ ] Implement core flow
- [ ] Discuss thread safety
- [ ] Handle errors
- [ ] Discuss extension points
- [ ] Test edge cases
- [ ] State complexity where relevant

---

# 9. Distributed Systems

- [ ] CAP theorem
- [ ] Strong consistency
- [ ] Eventual consistency
- [ ] Replication
- [ ] Partitioning
- [ ] Leader/follower model
- [ ] Retry
- [ ] Exponential backoff
- [ ] Circuit breaker
- [ ] Timeout
- [ ] Idempotency
- [ ] Outbox pattern
- [ ] Distributed locks
- [ ] Kafka partitions
- [ ] Consumer groups
- [ ] Consumer offsets
- [ ] Delivery semantics
- [ ] Backpressure
- [ ] High availability
- [ ] Autoscaling

---

# 10. System Design

Prepare these designs first:

- [ ] Distributed ETL platform
- [ ] Large-scale data migration service
- [ ] CDC pipeline: SQL → Azure
- [ ] Event ingestion pipeline
- [ ] Distributed job scheduler
- [ ] Telemetry / log aggregation system

## System Design Framework

For each design, cover:

- [ ] Functional requirements
- [ ] Non-functional requirements
- [ ] Scale estimation
- [ ] APIs
- [ ] Data model
- [ ] High-level architecture
- [ ] Data flow
- [ ] Storage choice
- [ ] Partitioning
- [ ] Consistency
- [ ] Reliability
- [ ] Failure recovery
- [ ] Security
- [ ] Observability
- [ ] Bottlenecks
- [ ] Trade-offs

---

# 11. Distributed ETL Design Drill

Be able to explain this flow:

```text
Sources
  |
  v
Connectors
  |
  v
Ingestion Layer
  |
  v
Raw / Staging Storage
  |
  v
Transformation
  |
  v
Validation
  |
  v
Destination / Sink
```

Control plane:

```text
Configuration
     |
Scheduler ---- Metadata Store
     |
Workers
```

Prepare answers for:

- [ ] Worker crashes after processing 900 GB
- [ ] Event arrives twice
- [ ] Upstream schema changes
- [ ] Destination becomes unavailable
- [ ] One tenant produces 80% of traffic
- [ ] Historical data needs replay
- [ ] Backfill must run while live traffic continues
- [ ] Tenant isolation is required
- [ ] Processing falls behind
- [ ] Source sends corrupt records

---

# 12. Security Checklist

Mention these proactively in system design:

- [ ] TLS in transit
- [ ] Encryption at rest
- [ ] Managed Identity
- [ ] Key Vault
- [ ] RBAC
- [ ] Least privilege
- [ ] Secret rotation
- [ ] Tenant isolation
- [ ] PII handling
- [ ] Audit logging

---

# 13. Observability

## Metrics

- [ ] Throughput
- [ ] Latency
- [ ] Error rate
- [ ] Queue depth
- [ ] Consumer lag
- [ ] Records processed
- [ ] Records rejected
- [ ] Retry rate

## Logs

Include:

- [ ] Correlation ID
- [ ] Job ID
- [ ] Tenant ID
- [ ] Partition ID
- [ ] Error category

## Alerts

- [ ] Consumer lag threshold
- [ ] Error-rate threshold
- [ ] Pipeline stalled
- [ ] DLQ growth
- [ ] SLA violation

---

# 14. Resume Deep Dive

## Microsoft — Query Seg / User Seg Pipelines

Prepare:

- [ ] Business problem
- [ ] Input data
- [ ] Pipeline architecture
- [ ] Transformations
- [ ] Scale
- [ ] Partitioning
- [ ] Failure handling
- [ ] Validation
- [ ] Monitoring
- [ ] Your exact contribution
- [ ] Measured impact
- [ ] What you would improve today

## Microsoft — Production Debugging

Prepare:

- [ ] Symptom
- [ ] Initial hypothesis
- [ ] Telemetry used
- [ ] Root cause
- [ ] Fix
- [ ] Validation
- [ ] Preventive improvement

## Microsoft — Cross-team Compliance

Prepare:

- [ ] Ambiguity
- [ ] Stakeholders
- [ ] Dependencies
- [ ] Technical constraint
- [ ] Deadline
- [ ] Communication strategy
- [ ] Result

## Walmart — Outbox Pattern

Prepare:

- [ ] Dual-write problem
- [ ] Business DB transaction
- [ ] Outbox table/event
- [ ] Outbox publisher
- [ ] Kafka
- [ ] Duplicate handling
- [ ] Consumer idempotency
- [ ] Failure scenarios

---

# 15. Behavioral / Microsoft Culture

Prepare STAR(R) stories for:

- [ ] Major technical impact
- [ ] Production failure
- [ ] Difficult technical decision
- [ ] Disagreement with engineer
- [ ] Cross-team collaboration
- [ ] Negative feedback received
- [ ] Ambiguous requirement
- [ ] Customer-impacting incident
- [ ] Learning unfamiliar technology
- [ ] Helping another engineer succeed
- [ ] Inclusion / diverse perspectives
- [ ] Delivering under deadline pressure

For each story:

- [ ] Situation
- [ ] Task
- [ ] Action
- [ ] Result
- [ ] Reflection
- [ ] Quantified impact if available
- [ ] Explain your personal contribution clearly

---

# 16. Questions to Practice Aloud

## Data

- [ ] Design an ETL system processing billions of records daily.
- [ ] How would you migrate a database without downtime?
- [ ] ETL vs ELT?
- [ ] Batch vs streaming?
- [ ] Explain CDC.
- [ ] How do you resume a failed pipeline?
- [ ] How do you prevent duplicates?
- [ ] How do you handle schema changes?
- [ ] How do you process late-arriving data?
- [ ] How do you handle poison records?
- [ ] How do you backfill six months of data?
- [ ] How do you handle a hot partition?
- [ ] How do you validate a migration?
- [ ] How do you replay historical data?
- [ ] How do you guarantee idempotency?

## Distributed Systems

- [ ] At-least-once vs at-most-once vs exactly-once?
- [ ] How does Kafka partitioning work?
- [ ] What is backpressure?
- [ ] Explain CAP theorem.
- [ ] Strong vs eventual consistency?
- [ ] Explain Outbox Pattern.
- [ ] How would you implement distributed locking?
- [ ] How can retries cause cascading failures?
- [ ] What is exponential backoff?
- [ ] What is circuit breaking?

## LLD / Coding

- [ ] Implement LRU Cache.
- [ ] Design Rate Limiter.
- [ ] Design Notification System.
- [ ] Implement Producer-Consumer.
- [ ] Build a thread-safe task scheduler.

## Resume

- [ ] Explain one Microsoft data pipeline end-to-end.
- [ ] Describe your hardest production bug.
- [ ] How did the system scale?
- [ ] How did you measure reliability?
- [ ] What would you redesign today?

---

# 17. Coding Interview Communication Checklist

Before coding:

- [ ] Clarify requirements
- [ ] Clarify input constraints
- [ ] Clarify expected output
- [ ] State brute-force approach
- [ ] State optimized approach
- [ ] Explain why chosen data structure fits
- [ ] State important invariant

While coding:

- [ ] Use meaningful names
- [ ] Keep methods small
- [ ] Avoid unnecessary abstractions
- [ ] Handle edge cases
- [ ] Explain important decisions

After coding:

- [ ] Dry-run normal case
- [ ] Test empty input
- [ ] Test one element
- [ ] Test duplicates
- [ ] Test boundaries
- [ ] State time complexity
- [ ] State space complexity
- [ ] Discuss scale-up follow-up

---

# 18. Four-Day Preparation Plan

## 17 August — DSA Stabilization

- [ ] Search in Rotated Sorted Array
- [ ] Merge Intervals
- [ ] Subarray Sum Equals K
- [ ] Minimum Window Substring
- [ ] Course Schedule
- [ ] Number of Islands
- [ ] Lowest Common Ancestor
- [ ] Binary Tree Maximum Path Sum
- [ ] Top K Frequent Elements
- [ ] Coin Change
- [ ] Review PriorityQueue
- [ ] Review TreeMap
- [ ] Review ArrayDeque
- [ ] Review Comparator
- [ ] Implement LRU Cache from scratch

## 18 August — Data Engineering

- [ ] ETL vs ELT
- [ ] CDC
- [ ] Batch vs streaming
- [ ] Checkpointing
- [ ] Watermarks
- [ ] Idempotency
- [ ] Deduplication
- [ ] Schema evolution
- [ ] Backpressure
- [ ] Partitioning
- [ ] Data skew
- [ ] DLQ
- [ ] Retry
- [ ] Backfill
- [ ] Reconciliation
- [ ] Design: 10 TB SQL → Azure migration
- [ ] Design: Generic ETL platform

## 19 August — LLD + Concurrency

- [ ] Implement LRU Cache
- [ ] Implement / design Rate Limiter
- [ ] Design Notification System
- [ ] Producer-Consumer
- [ ] Thread-safe cache
- [ ] Worker pool
- [ ] Concurrent task executor
- [ ] Timed DSA medium #1
- [ ] Timed DSA medium #2
- [ ] Timed DSA hard #1

## 20 August — Mock Interview Day

### Coding Mock

- [ ] 60-minute medium/hard DSA
- [ ] Speak throughout
- [ ] Test code manually
- [ ] State complexity

### System Design Mock

- [ ] Design scalable data migration platform
- [ ] Requirements
- [ ] Scale
- [ ] Architecture
- [ ] Failure scenarios
- [ ] Security
- [ ] Observability

### LLD Mock

- [ ] Concurrent LRU Cache
- [ ] TTL
- [ ] Thread safety
- [ ] Extensibility

### Behavioral Mock

- [ ] Tell me about yourself
- [ ] Why this Microsoft role?
- [ ] Largest technical challenge
- [ ] Failure
- [ ] Feedback
- [ ] Conflict
- [ ] Customer impact
- [ ] Ambiguous problem
- [ ] Cross-team project
- [ ] Why should we hire you?

---

# 19. Interview Day — 21 August

## Morning Revision Only

- [ ] BFS / DFS
- [ ] Topological sort
- [ ] Dijkstra
- [ ] Binary search
- [ ] Sliding window
- [ ] Heap
- [ ] DP state definition
- [ ] LRU Cache
- [ ] Rate limiter
- [ ] CDC
- [ ] Idempotency
- [ ] Checkpointing
- [ ] Schema evolution
- [ ] Partitioning
- [ ] Backpressure
- [ ] CAP
- [ ] Replication
- [ ] Retry / DLQ
- [ ] Outbox Pattern
- [ ] STAR(R) stories

Do not learn new major topics on interview morning.

---

# 20. Final Readiness Gate

Do not consider preparation complete until you can answer **yes** to all of these:

## DSA

- [ ] I can solve most medium problems in ~30 minutes.
- [ ] I can explain my invariant before coding.
- [ ] I can code BFS/DFS/topological sort from memory.
- [ ] I can code Dijkstra from memory.
- [ ] I can implement a heap-based solution without syntax issues.
- [ ] I can recognize common DP states.

## LLD

- [ ] I can implement LRU Cache from scratch.
- [ ] I can design a Rate Limiter.
- [ ] I can design a Notification System.
- [ ] I can discuss thread safety and extensibility.

## Data Engineering

- [ ] I can explain ETL vs ELT.
- [ ] I can explain CDC deeply.
- [ ] I can design snapshot + CDC migration.
- [ ] I can explain checkpoints and replay.
- [ ] I can explain idempotency.
- [ ] I can handle schema evolution.
- [ ] I can explain backpressure.
- [ ] I can discuss partitioning and hot partitions.
- [ ] I can design retries and DLQs.
- [ ] I can explain migration validation.

## System Design

- [ ] I can design a distributed ETL platform for 45 minutes.
- [ ] I can design near-zero-downtime migration.
- [ ] I proactively discuss failures.
- [ ] I proactively discuss security.
- [ ] I proactively discuss observability.
- [ ] I explain trade-offs instead of naming technologies blindly.

## Resume

- [ ] I can explain my Microsoft data pipeline end-to-end.
- [ ] I can distinguish my contribution from the team's contribution.
- [ ] I have a strong production-debugging story.
- [ ] I have a strong cross-team story.
- [ ] I can explain Walmart Outbox Pattern deeply.

## Behavioral

- [ ] I have at least 8 STAR(R) stories.
- [ ] Every story contains a measurable result where possible.
- [ ] I can discuss a genuine failure.
- [ ] I can discuss feedback and what I changed.
- [ ] I can demonstrate customer focus.
- [ ] I can demonstrate cross-team collaboration.
- [ ] I can demonstrate growth mindset.

---

# 21. What Not to Prioritize

Until the interview, avoid spending significant time on:

- [ ] React internals
- [ ] Redux internals
- [ ] CSS
- [ ] Advanced JavaScript
- [ ] Advanced Spring annotations
- [ ] Kubernetes certification-level details
- [ ] LLM internals
- [ ] Obscure competitive-programming tricks
- [ ] Rare graph algorithms
- [ ] Random system-design questions unrelated to backend/data systems

---

# 22. Core Positioning

Keep this mental model throughout the interview:

> **Backend Software Engineer + Microsoft/Azure experience + data pipelines + distributed systems + production engineering.**

Your strongest interview stories should repeatedly reinforce:

- [ ] Backend engineering depth
- [ ] Large-scale data processing
- [ ] Azure experience
- [ ] ETL/data integration relevance
- [ ] Distributed-system reasoning
- [ ] Production ownership
- [ ] Reliability and debugging
- [ ] Cross-team execution
