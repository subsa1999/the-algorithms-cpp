# Walmart SSE / IN4 — Top 100 Java Questions With Answers

---

# 1. Core Java + OOP

### 1. 🔴 What are the four pillars of OOP?

**Encapsulation** hides internal state and exposes controlled operations.

```java
class BankAccount {
    private long balance;

    public void deposit(long amount) {
        if (amount <= 0) throw new IllegalArgumentException();
        balance += amount;
    }
}
```

**Abstraction** exposes what an object does without exposing implementation details.

```java
interface PaymentProcessor {
    void pay(long amount);
}
```

**Inheritance** allows specialization of an existing abstraction.

```java
class Animal {}
class Dog extends Animal {}
```

**Polymorphism** lets code work against an abstraction while runtime chooses the implementation.

```java
PaymentProcessor processor = new UpiProcessor();
processor.pay(1000);
```

For production systems, **composition + interfaces** are usually preferred over deep inheritance.

---

### 2. 🔴 Interface vs abstract class?

Use an **interface** when defining a capability/contract:

```java
interface PaymentStrategy {
    PaymentResult pay();
}
```

Use an **abstract class** when related implementations genuinely share state or implementation:

```java
abstract class BaseHttpClient {
    protected final HttpClient client;

    protected BaseHttpClient(HttpClient client) {
        this.client = client;
    }
}
```

Java classes can:

```text
implement multiple interfaces
extend only one class
```

Modern interfaces can contain:

```text
default methods
static methods
private helper methods
```

But they should not become disguised base classes with shared mutable state.

---

### 3. 🔴 Composition vs inheritance?

Inheritance:

```java
class Car extends Vehicle {}
```

Composition:

```java
class Car {
    private Engine engine;
}
```

Composition is usually preferred because it creates looser coupling.

Inheritance tightly couples subclasses to superclass behavior and creates the fragile-base-class problem.

Prefer:

```text
HAS-A
```

when possible instead of:

```text
IS-A
```

unless the subtype relationship is genuinely stable.

---

### 4. Overloading vs overriding?

**Overloading**:

Same method name, different parameter list.

```java
void send(String message) {}
void send(String message, int priority) {}
```

Resolved primarily at **compile time**.

**Overriding**:

Subclass replaces inherited implementation.

```java
class Parent {
    void execute() {}
}

class Child extends Parent {
    @Override
    void execute() {}
}
```

Runtime polymorphism determines which override executes.

---

### 5. Can you override `static`, `private`, or `final` methods?

`final`:

```text
Cannot be overridden.
```

`private`:

```text
Not inherited, therefore not overridden.
```

A subclass can declare another method with the same signature, but it is unrelated.

`static`:

```text
Hidden, not overridden.
```

Static method resolution depends on the **reference/class type**, not runtime object type.

---

### 6. What are covariant return types?

An overridden method can return a subtype of the original return type.

```java
class Animal {}

class Dog extends Animal {}

class Parent {
    Animal create() {
        return new Animal();
    }
}

class Child extends Parent {
    @Override
    Dog create() {
        return new Dog();
    }
}
```

`Dog` is covariant with `Animal`.

---

### 7. 🔴 Explain SOLID

**S — Single Responsibility**

One class should have one main reason to change.

Bad:

```text
PaymentService
- payment
- email
- DB SQL
- PDF generation
```

Better separation.

**O — Open/Closed**

Open for extension, closed for modification.

```java
interface PaymentStrategy {}
```

Adding another implementation should not require rewriting the orchestrator.

**L — Liskov Substitution**

Subtype must be usable wherever parent type is expected without breaking behavioral expectations.

**I — Interface Segregation**

Prefer:

```java
interface Printer {}
interface Scanner {}
```

over a huge interface forcing implementations to support operations they don't need.

**D — Dependency Inversion**

Depend on abstractions:

```java
class OrderService {
    private final PaymentGateway gateway;
}
```

not:

```java
private final RazorpayClient gateway;
```

---

### 8. What is immutability?

An immutable object's observable state cannot change after construction.

Typical rules:

```text
class final
fields private final
no mutating methods
defensive copies for mutable objects
do not expose internal mutable collections
```

Example:

```java
public final class User {

    private final String id;
    private final List<String> roles;

    public User(String id, List<String> roles) {
        this.id = id;
        this.roles = List.copyOf(roles);
    }

    public List<String> roles() {
        return roles;
    }
}
```

---

### 9. 🔴 Why is `String` immutable?

Major reasons:

```text
String pool safety
safe sharing
hash-code stability
security
thread safety
```

Strings are frequently used as:

```text
HashMap keys
class names
file paths
URLs
security-related identifiers
```

If the contents could change after creation, caching/hash-based collections and security assumptions would become unreliable.

---

### 10. `==` vs `equals()`?

For objects:

```java
a == b
```

checks whether references point to the **same object**.

```java
a.equals(b)
```

checks logical equality as defined by the class.

Example:

```java
String a = new String("java");
String b = new String("java");

a == b        // false
a.equals(b)   // true
```

For primitives, `==` compares values.

---

### 11. 🔴 `equals()` / `hashCode()` contract?

If:

```java
a.equals(b) == true
```

then:

```java
a.hashCode() == b.hashCode()
```

must also be true.

The reverse is not required.

Two unequal objects are allowed to have the same hash.

Also `equals()` should be:

```text
reflexive
symmetric
transitive
consistent
false against null
```

---

### 12. What happens if `equals()` is overridden but `hashCode()` isn't?

Hash-based collections may behave incorrectly.

Example:

```java
HashSet<Person>
HashMap<Person, ...>
```

Two logically equal instances may end up in different buckets because their hash codes differ.

Always override them together.

---

### 13. What are marker interfaces?

Interfaces with no methods.

Examples:

```java
Serializable
Cloneable
```

They indicate metadata through the Java type system.

Modern code often uses annotations instead where inheritance/type compatibility is unnecessary.

---

### 14. Association vs aggregation vs composition?

**Association**

General relationship.

```text
Doctor ↔ Patient
```

**Aggregation**

Weak ownership.

```text
Team has Players
```

Players can exist without the team.

**Composition**

Strong ownership/lifecycle dependency.

```text
House owns Rooms
```

If the parent disappears, the composed child conceptually disappears with it.

---

### 15. 🔴 Dependency inversion example?

Bad:

```java
class OrderService {

    private RazorpayClient razorpay =
            new RazorpayClient();
}
```

Now business logic depends directly on infrastructure.

Better:

```java
interface PaymentGateway {
    PaymentResult pay(PaymentRequest request);
}

class OrderService {

    private final PaymentGateway gateway;

    OrderService(PaymentGateway gateway) {
        this.gateway = gateway;
    }
}
```

Now:

```text
OrderService -> abstraction
RazorpayGateway -> abstraction
StripeGateway -> abstraction
```

---

# 2. HashMap + Collections

### 16. 🔴 How does `HashMap` work internally?

`HashMap` uses an array of buckets.

Conceptually:

```text
table[]
  |
  +-- bucket 0
  +-- bucket 1
  +-- bucket 2 -> Node -> Node
  +-- ...
```

For a key:

```text
hashCode()
   ↓
hash spreading
   ↓
bucket index
   ↓
search bucket
```

Java 8+ buckets can become red-black trees under heavy collision.

Average:

```text
get -> O(1)
put -> O(1)
```

Worst case with treeified bins:

```text
O(log n)
```

---

### 17. 🔴 What happens during `HashMap.put()`?

Simplified:

```text
1. Calculate hash
2. Determine bucket index
3. If bucket empty -> insert
4. Otherwise:
      compare hash
      compare key via equals()
5. Existing key -> replace value
6. Collision -> add node / insert into tree
7. Treeify when collision threshold is reached
8. Resize if size exceeds threshold
```

Bucket:

```java
index = (capacity - 1) & hash;
```

because capacity is maintained as a power of two.

---

### 18. 🔴 What happens during a hash collision?

Two keys generate the same bucket index.

Example:

```text
bucket 5

KeyA -> KeyB -> KeyC
```

HashMap compares:

```text
hash
then equals()
```

to locate the correct key.

Java 8+ may convert a heavily populated linked bin into a red-black tree.

---

### 19. When does HashMap treeify?

Important values:

```text
TREEIFY_THRESHOLD = 8
UNTREEIFY_THRESHOLD = 6
MIN_TREEIFY_CAPACITY = 64
```

If a bucket grows sufficiently large **and** the entire table capacity is at least 64, the bucket can be converted to a red-black tree.

Before capacity 64, HashMap generally prefers resizing instead.

---

### 20. 🔴 Why should HashMap keys be immutable?

Suppose:

```java
map.put(key, value);
```

Then you mutate a field participating in:

```java
hashCode()
```

Now:

```java
map.get(key)
```

may calculate a different bucket.

The object physically remains in the old bucket and becomes effectively unreachable through normal lookup.

Therefore keys should ideally have stable:

```text
equals()
hashCode()
```

for their lifetime in the map.

---

### 21. How does HashMap calculate bucket index?

First Java spreads the hash:

```java
h ^ (h >>> 16)
```

Then:

```java
(n - 1) & hash
```

where `n` is table capacity.

This is efficient because `n` is a power of two.

The high-bit XOR improves distribution into lower bits used by the bucket calculation.

---

### 22. What are load factor and capacity?

Capacity:

```text
number of buckets
```

Default initial capacity:

```text
16
```

Default load factor:

```text
0.75
```

Resize threshold roughly:

```text
capacity * loadFactor
```

Example:

```text
16 * 0.75 = 12
```

Once size exceeds the threshold, HashMap grows.

---

### 23. Why load factor `0.75`?

It is an engineering trade-off between:

```text
memory usage
collision probability
resize frequency
lookup performance
```

Lower load factor:

```text
more memory
fewer collisions
```

Higher:

```text
less memory
more collisions
```

`0.75` is a good general-purpose compromise.

---

### 24. 🔴 HashMap vs ConcurrentHashMap?

`HashMap`:

```text
not thread-safe
allows one null key
allows null values
```

`ConcurrentHashMap`:

```text
thread-safe
high concurrency
does not allow null keys/values
iterators are weakly consistent
```

Modern `ConcurrentHashMap` does **not** use the old fixed `Segment[]` design.

Java 8+ primarily uses:

```text
CAS
volatile accesses
bin-level synchronization when needed
```

Reads are mostly non-blocking.

---

### 25. 🔴 Why does ConcurrentHashMap prohibit null?

Suppose:

```java
map.get(key) == null
```

With concurrent access, what does that mean?

```text
key absent?
or
key exists with null value?
```

That ambiguity is problematic for concurrent APIs where another thread can modify the map between operations.

Therefore null keys and values are prohibited.

---

### 26. ArrayList vs LinkedList?

`ArrayList`:

```text
backed by dynamic array
random access O(1)
append amortized O(1)
middle insertion/removal O(n)
good cache locality
```

`LinkedList`:

```text
doubly linked nodes
random access O(n)
known-node insertion/removal O(1)
higher memory overhead
poor cache locality
```

In most real applications, `ArrayList` is preferable.

---

### 27. How does HashSet work?

`HashSet` internally uses a `HashMap`.

Conceptually:

```java
HashMap<E, Object>
```

Elements are stored as map keys with a shared dummy value.

Therefore uniqueness relies on:

```text
hashCode()
equals()
```

---

### 28. TreeMap vs HashMap?

`HashMap`:

```text
average lookup O(1)
unordered
```

`TreeMap`:

```text
red-black tree
operations O(log n)
sorted keys
```

Use `TreeMap` when you require:

```text
sorted iteration
floorKey
ceilingKey
range queries
```

---

### 29. Comparable vs Comparator?

`Comparable` defines the object's **natural ordering**:

```java
class Employee implements Comparable<Employee> {
    public int compareTo(Employee other) {}
}
```

`Comparator` defines external/custom ordering:

```java
Comparator<Employee> bySalary =
        Comparator.comparing(Employee::salary);
```

One class may have only one natural ordering but many comparators.

---

### 30. 🔴 Fail-fast vs fail-safe?

`ArrayList`/`HashMap` iterators are typically **fail-fast**.

Structural modification during iteration may produce:

```java
ConcurrentModificationException
```

This is best-effort bug detection, not a concurrency guarantee.

Concurrent collections such as `ConcurrentHashMap` generally provide **weakly consistent** iterators:

```text
do not throw ConcurrentModificationException
may observe some concurrent changes
do not necessarily represent one immutable snapshot
```

“Fail-safe” is commonly used informally but is not a precise Java API term.

---

# 3. Generics

### 31. What problem do generics solve?

Generics provide compile-time type safety.

Without:

```java
List list = new ArrayList();
list.add("hello");

Integer n = (Integer) list.get(0); // runtime failure
```

With:

```java
List<String> list = new ArrayList<>();
```

incorrect insertion is rejected at compile time.

They also eliminate many explicit casts.

---

### 32. 🔴 What is type erasure?

Most generic type information is removed during compilation.

Conceptually:

```java
List<String>
List<Integer>
```

both become approximately:

```java
List
```

at runtime.

The compiler inserts:

```text
casts
bridge methods where necessary
```

This maintains compatibility with pre-generics JVM bytecode/runtime design.

---

### 33. Why can't you do `new T()`?

After erasure, JVM does not generally know what `T` is.

```java
class Box<T> {
    T create() {
        return new T(); // illegal
    }
}
```

Instead provide a factory:

```java
class Box<T> {

    private final Supplier<T> factory;

    T create() {
        return factory.get();
    }
}
```

---

### 34. Why can't you create `new List<String>[10]`?

Arrays are:

```text
reified
```

They know their runtime component type.

Generics are mostly:

```text
erased
```

Combining them would break type safety.

Therefore generic array creation is restricted.

---

### 35. 🔴 `? extends T` vs `? super T`?

`? extends T`:

```java
List<? extends Number>
```

Useful when you primarily **read/produce** values as `Number`.

You cannot safely add arbitrary `Number` values because the actual list may be:

```java
List<Integer>
```

`? super T`:

```java
List<? super Integer>
```

Useful when you want to **write/consume** `Integer`.

---

### 36. Explain PECS

```text
Producer Extends
Consumer Super
```

If a structure produces `T`:

```java
List<? extends T>
```

If it consumes `T`:

```java
List<? super T>
```

Example:

```java
static <T> void copy(
        List<? extends T> src,
        List<? super T> dst) {
}
```

---

### 37. Can these methods coexist?

```java
void process(List<String> x)
void process(List<Integer> x)
```

No.

After type erasure, both effectively become:

```java
void process(List x)
```

Their erased signatures clash.

---

# 4. Modern Java

### 38. 🔴 What is a functional interface?

An interface with exactly one abstract method.

```java
@FunctionalInterface
interface Calculator {
    int calculate(int a, int b);
}
```

Can be implemented using a lambda:

```java
Calculator add = (a, b) -> a + b;
```

It may still contain:

```text
default methods
static methods
Object-method declarations
```

---

### 39. Predicate, Function, Consumer, Supplier?

```java
Predicate<T>
T -> boolean
```

```java
Function<T,R>
T -> R
```

```java
Consumer<T>
T -> void
```

```java
Supplier<T>
() -> T
```

Examples:

```java
Predicate<Integer> even = x -> x % 2 == 0;

Function<String, Integer> length = String::length;

Consumer<String> print = System.out::println;

Supplier<UUID> uuid = UUID::randomUUID;
```

---

### 40. How are lambdas implemented internally?

Java generally uses:

```text
invokedynamic
LambdaMetafactory
```

rather than blindly generating a permanent anonymous class for every lambda expression.

This gives the JVM flexibility in how lambda objects are created and optimized.

---

### 41. 🔴 Stream vs Collection?

Collection:

```text
stores data
```

Stream:

```text
describes computation over data
```

A stream:

```text
does not own elements
is generally single-use
supports lazy intermediate operations
can create sequential/parallel pipelines
```

Example:

```java
users.stream()
     .filter(User::active)
     .map(User::email)
     .toList();
```

---

### 42. Intermediate vs terminal operations?

Intermediate:

```text
filter
map
flatMap
sorted
distinct
```

They return another stream and are generally lazy.

Terminal:

```text
collect
toList
reduce
forEach
count
```

They trigger pipeline execution.

---

### 43. `map()` vs `flatMap()`?

`map()`:

```text
T -> R
```

Example:

```java
users.stream()
     .map(User::name)
```

`flatMap()`:

```text
T -> Stream<R>
```

and flattens nested results.

```java
orders.stream()
      .flatMap(order -> order.items().stream())
```

Instead of:

```text
Stream<List<Item>>
```

you obtain:

```text
Stream<Item>
```

---

### 44. 🔴 Why can parallel streams be dangerous?

Parallel streams usually use the shared:

```java
ForkJoinPool.commonPool()
```

Problems include:

```text
shared global pool contention
poor performance for small workloads
blocking I/O occupying worker threads
ordering complications
side-effect races
harder latency prediction
```

Use them only when the workload is:

```text
CPU-heavy
large enough
easily partitioned
mostly stateless
```

For server workloads, explicit executors are often easier to control.

---

### 45. What does stream laziness mean?

Intermediate operations don't execute immediately.

```java
Stream<String> stream =
        names.stream()
             .filter(this::expensiveCheck);
```

Nothing may happen until:

```java
stream.toList();
```

Laziness allows optimization such as short-circuiting:

```java
findFirst()
anyMatch()
limit()
```

---

### 46. `orElse()` vs `orElseGet()`?

```java
optional.orElse(expensiveOperation())
```

evaluates `expensiveOperation()` **even if the Optional has a value**.

```java
optional.orElseGet(() -> expensiveOperation())
```

evaluates lazily only when empty.

Use `orElseGet()` when the fallback is expensive or has side effects.

---

### 47. 🔴 What are records?

Records are concise data carriers.

```java
record User(
    String id,
    String name
) {}
```

Java generates:

```text
private final fields
accessors
constructor
equals
hashCode
toString
```

Records are **shallowly immutable**: component references cannot be reassigned, but referenced mutable objects can still mutate.

Avoid records when you need:

```text
significant mutable lifecycle
class inheritance
framework behavior requiring mutable beans/proxies
rich entity identity semantics
```

---

### 48. 🔴 What are sealed classes?

Sealed classes restrict which classes may extend/implement them.

```java
sealed interface PaymentResult
        permits Success, Failure {}

record Success(String id)
        implements PaymentResult {}

record Failure(String reason)
        implements PaymentResult {}
```

Useful when the domain has a known closed set of alternatives.

They work particularly well with exhaustive pattern-matching switches.

---

### 49. Pattern matching with `instanceof`?

Old:

```java
if (obj instanceof String) {
    String s = (String) obj;
}
```

Modern:

```java
if (obj instanceof String s) {
    System.out.println(s.length());
}
```

The variable `s` is available where the compiler knows the match succeeded.

---

### 50. Pattern matching with `switch`?

Example:

```java
static String describe(Object obj) {
    return switch (obj) {
        case Integer i -> "Integer: " + i;
        case String s  -> "String: " + s;
        case null      -> "null";
        default        -> "Other";
    };
}
```

Particularly useful with sealed hierarchies because the compiler can verify exhaustiveness.

---

### 51. 🔴 What are virtual threads?

Virtual threads are lightweight Java threads managed mainly by the JVM rather than mapping every Java thread permanently to one OS thread.

Java 21:

```java
Thread.startVirtualThread(() -> {
    // blocking I/O
});
```

or:

```java
try (var executor =
        Executors.newVirtualThreadPerTaskExecutor()) {
}
```

They allow very large numbers of blocking tasks without huge platform-thread pools.

Best suited to:

```text
I/O-bound
request-per-thread
blocking API workloads
```

---

### 52. 🔴 When do virtual threads NOT help?

They do not make CPU work faster.

If 100,000 virtual threads perform CPU-heavy work on an 8-core machine:

```text
you still have roughly 8 cores
```

Virtual threads mainly improve scalability when tasks spend significant time blocked.

In Java 21, long blocking while holding certain `synchronized` monitors or entering native/foreign operations can **pin** a virtual thread to its carrier thread, reducing scalability.

Also don't create huge virtual-thread concurrency against a limited external resource without controlling pressure, such as:

```text
database with only 50 connections
```

Use semaphores/resource limits when necessary.

---

# 5. Concurrency + Java Memory Model

### 53. 🔴 Process vs thread?

Process:

```text
independent OS execution environment
separate address space
heavier isolation
```

Thread:

```text
execution unit inside a process
shares process heap/resources
has its own stack and program counter
```

Threads are cheaper to communicate between, but shared memory introduces race conditions.

---

### 54. 🔴 What is a race condition?

When correctness depends on thread timing/interleaving.

```java
class Counter {
    int value;

    void increment() {
        value++;
    }
}
```

`value++` is approximately:

```text
read
increment
write
```

Two threads can both read `10` and both write `11`.

Expected:

```text
12
```

actual:

```text
11
```

---

### 55. What is a critical section?

Code accessing shared mutable state that must not be executed concurrently in conflicting ways.

Example:

```java
lock.lock();
try {
    balance -= amount;
} finally {
    lock.unlock();
}
```

The protected balance modification is a critical section.

---

### 56. 🔴 What does `synchronized` guarantee?

Main guarantees:

### Mutual exclusion

Only one thread can hold a given monitor at a time.

### Visibility / memory ordering

An unlock on a monitor **happens-before** a subsequent lock on the same monitor.

So writes performed before unlock become visible to a later thread acquiring the same monitor.

It also provides reentrancy.

---

### 57. 🔴 Object lock vs class lock?

Instance synchronized:

```java
synchronized void method() {}
```

locks:

```text
this
```

Static synchronized:

```java
static synchronized void method() {}
```

locks:

```text
MyClass.class
```

Therefore two different instances can simultaneously execute synchronized instance methods because they use different monitors.

---

### 58. Can two synchronized methods on the same object run simultaneously?

For two different threads:

```text
No
```

if both require the same object's monitor.

Example:

```java
synchronized void a() {}
synchronized void b() {}
```

If thread 1 is executing `a()` on object `x`, thread 2 cannot execute `b()` on the same `x`.

But synchronization is **reentrant**, so the thread already holding the lock can enter another synchronized method using the same monitor.

---

### 59. 🔴 What is `volatile`?

`volatile` primarily provides:

```text
visibility
ordering
```

Example:

```java
volatile boolean shutdown;
```

A write:

```java
shutdown = true;
```

becomes visible to another thread reading the same volatile variable according to JMM happens-before guarantees.

It does **not** turn compound operations into atomic operations.

---

### 60. 🔴 Why isn't `volatile int i; i++` thread-safe?

Because:

```java
i++;
```

means:

```text
read i
calculate i + 1
write i
```

Two threads can interleave those operations.

`volatile` guarantees visibility of individual reads/writes, but not atomicity of the whole read-modify-write sequence.

Use:

```java
AtomicInteger.incrementAndGet()
```

or locking.

---

### 61. 🔴 Visibility vs atomicity vs ordering?

**Visibility**

Does another thread see your write?

**Atomicity**

Can an operation be observed/interleaved halfway?

**Ordering**

Can the compiler/CPU/JVM legally reorder memory operations?

Example:

```java
volatile boolean ready;
```

helps visibility and establishes ordering around volatile access.

But:

```java
counter++;
```

still isn't atomic.

---

### 62. 🔴 What is happens-before?

A Java Memory Model relationship guaranteeing that writes from operation A are visible to operation B.

Important examples:

```text
monitor unlock
    happens-before
later lock on same monitor
```

```text
volatile write
    happens-before
subsequent read of same volatile
```

```text
Thread.start()
```

Actions before `start()` happen-before actions in the started thread.

And completion of a thread happens-before another thread successfully returns from `join()` on it.

---

### 63. 🔴 `synchronized` vs `ReentrantLock`?

Both support mutual exclusion and memory visibility.

`synchronized`:

```text
simpler
automatic unlock
JVM-managed
reentrant
```

`ReentrantLock` offers additional APIs:

```text
tryLock()
tryLock(timeout)
lockInterruptibly()
Condition
optional fairness
```

Use `synchronized` when basic locking is sufficient.

Use `ReentrantLock` when explicit lock capabilities are needed.

Always:

```java
lock.lock();
try {
    ...
} finally {
    lock.unlock();
}
```

---

### 64. What is `tryLock()` useful for?

Allows avoiding indefinite blocking.

```java
if (lock.tryLock()) {
    try {
        ...
    } finally {
        lock.unlock();
    }
}
```

Or:

```java
lock.tryLock(100, TimeUnit.MILLISECONDS)
```

Useful for:

```text
timeouts
deadlock avoidance strategies
best-effort operations
responsive cancellation
```

---

### 65. What is lock fairness?

A fair `ReentrantLock`:

```java
new ReentrantLock(true);
```

roughly favors threads that have waited longest.

Fairness can reduce starvation but usually costs throughput due to reduced barging/optimization opportunities.

Default is:

```text
non-fair
```

---

### 66. 🔴 What is deadlock?

Threads permanently wait for locks held by each other.

Example:

```text
T1 holds A -> waits B
T2 holds B -> waits A
```

Four Coffman conditions:

```text
mutual exclusion
hold and wait
no preemption
circular wait
```

All four are necessary for deadlock.

---

### 67. How do you prevent deadlocks?

Common approaches:

```text
consistent global lock ordering
avoid nested locks
minimize lock scope
tryLock with timeout
don't call unknown/external code while holding locks
```

Example rule:

```text
always acquire Account locks by ascending accountId
```

Then circular wait cannot occur.

---

### 68. 🔴 AtomicInteger vs synchronized counter?

`AtomicInteger` uses atomic operations typically built around CAS.

```java
counter.incrementAndGet();
```

Good for simple independent atomic state transitions.

`synchronized` is more appropriate when multiple fields/invariants must change atomically:

```text
balance
transactionCount
lastUpdated
```

CAS is not a replacement for all locking.

---

### 69. Explain CAS

Compare-And-Set conceptually:

```text
if currentValue == expectedValue:
    currentValue = newValue
    success
else:
    fail
```

Example:

```java
atomic.compareAndSet(10, 11);
```

Many lock-free algorithms loop:

```text
read
calculate
CAS
retry if failed
```

CAS is usually supported by CPU atomic instructions.

---

### 70. What is the ABA problem?

A thread sees value:

```text
A
```

Later checks again and sees:

```text
A
```

and assumes nothing changed.

But state may actually have gone:

```text
A -> B -> A
```

CAS only sees the current value and cannot detect that history.

Potential solutions include:

```java
AtomicStampedReference
AtomicMarkableReference
version numbers
```

---

### 71. 🔴 What is false sharing?

Two independent variables happen to reside on the same CPU cache line.

Example:

```text
Core 1 writes counter A
Core 2 writes counter B
```

Even though logically unrelated, cache coherence repeatedly invalidates the same cache line.

Result:

```text
poor scalability
high cache-coherence traffic
```

This matters in extremely hot concurrent counters/data structures.

---

### 72. What is starvation?

A thread is technically runnable but repeatedly fails to obtain the resource/CPU/lock it needs.

Example:

```text
high-priority work continually wins
non-fair lock continually barged by other threads
```

Unlike deadlock, the system overall may still be making progress.

---

### 73. Livelock vs deadlock?

Deadlock:

```text
threads blocked
no progress
```

Livelock:

```text
threads actively react to each other
still no useful progress
```

Example:

Two people repeatedly step aside in the same direction to avoid each other.

Retry algorithms without randomized backoff can produce similar behavior.

---

# 6. Executors + CompletableFuture

### 74. 🔴 Why use ExecutorService?

Instead of:

```java
new Thread(...).start();
```

for every task, an executor provides:

```text
thread reuse
queueing
concurrency limits
lifecycle management
Future results
rejection handling
```

It separates:

```text
task submission
from
thread management
```

---

### 75. `execute()` vs `submit()`?

`execute()`:

```java
executor.execute(runnable);
```

returns:

```text
void
```

`submit()`:

```java
Future<?> future = executor.submit(runnable);
```

returns a `Future`.

A key exception difference:

With `submit()`, task exceptions are captured inside the `Future` and are normally observed through:

```java
future.get()
```

which throws `ExecutionException`.

---

### 76. Runnable vs Callable?

`Runnable`:

```java
void run()
```

No result and cannot declare checked exceptions.

`Callable<V>`:

```java
V call() throws Exception
```

Returns a value and can throw checked exceptions.

---

### 77. Future vs CompletableFuture?

`Future` gives basic asynchronous result retrieval:

```text
get
cancel
isDone
```

But composition is awkward.

`CompletableFuture` supports pipelines:

```java
fetchUser()
    .thenCompose(this::fetchOrders)
    .thenApply(this::calculateTotal)
    .exceptionally(this::fallback);
```

It supports asynchronous composition and completion without manually blocking on every stage.

---

### 78. 🔴 How does ThreadPoolExecutor work?

Simplified execute logic:

```text
task submitted
   |
   v
workers < corePoolSize?
   |
 yes -> create worker
   |
 no
   v
queue.offer(task)?
   |
 yes -> queued
   |
 no
   v
workers < maximumPoolSize?
   |
 yes -> create additional worker
   |
 no
   v
RejectedExecutionHandler
```

This ordering is critical.

---

### 79. Explain ThreadPoolExecutor parameters

`corePoolSize`

Baseline number of worker threads maintained when tasks require them.

`maximumPoolSize`

Maximum workers.

`keepAliveTime`

How long excess idle workers survive.

`workQueue`

Stores waiting tasks.

Examples:

```text
ArrayBlockingQueue
LinkedBlockingQueue
SynchronousQueue
```

`RejectedExecutionHandler`

What happens when no more workers/queue capacity are available.

Examples:

```text
AbortPolicy
CallerRunsPolicy
DiscardPolicy
DiscardOldestPolicy
```

---

### 80. 🔴 Bounded vs unbounded queue?

Unbounded queue:

```text
easy
but can grow until memory pressure/OOM
maximumPoolSize often becomes effectively irrelevant
```

Bounded queue:

```text
limits memory
creates backpressure
forces explicit overload policy
```

For backend systems, bounded queues are generally safer when load can exceed processing capacity.

---

### 81. What if executor queue keeps growing?

This means:

```text
arrival rate > processing rate
```

Consequences:

```text
increasing latency
memory growth
eventual OOM
stale requests
```

Possible fixes:

```text
bounded queue
backpressure
load shedding
increase throughput
reduce work
scale workers/services
```

A queue is not infinite capacity.

---

### 82. 🔴 `thenApply()` vs `thenCompose()`?

Suppose:

```java
CompletableFuture<User> userFuture;
```

`thenApply()` transforms:

```java
User -> String
```

```java
CompletableFuture<String> name =
        userFuture.thenApply(User::name);
```

If your callback returns another future:

```java
User -> CompletableFuture<Orders>
```

using `thenApply()` creates:

```text
CompletableFuture<CompletableFuture<Orders>>
```

Use `thenCompose()` to flatten it:

```java
CompletableFuture<Orders> orders =
        userFuture.thenCompose(this::fetchOrders);
```

Equivalent conceptually to `flatMap`.

---

### 83. `thenCombine()` vs `allOf()`?

`thenCombine()` combines two futures and their results:

```java
priceFuture.thenCombine(
    taxFuture,
    (price, tax) -> price + tax
);
```

`allOf()` waits for many futures:

```java
CompletableFuture.allOf(f1, f2, f3)
```

but returns:

```java
CompletableFuture<Void>
```

You then extract individual results separately.

---

# 7. Concurrent Collections

### 84. 🔴 How does ConcurrentHashMap achieve concurrency?

Modern Java uses a combination of:

```text
volatile reads
CAS
fine-grained synchronization at bin level when required
```

It does not lock the entire map for ordinary operations.

Reads are generally non-blocking.

Different buckets can often be updated concurrently.

Resizing is also designed so multiple threads can assist migration.

---

### 85. ConcurrentHashMap vs synchronizedMap?

```java
Collections.synchronizedMap(new HashMap<>())
```

wraps operations with synchronization around a common mutex.

This can create higher contention.

`ConcurrentHashMap` provides much finer concurrency.

It also offers atomic APIs such as:

```java
putIfAbsent()
compute()
computeIfAbsent()
merge()
```

Its iterators are weakly consistent rather than requiring the same external synchronization pattern as synchronized wrappers.

---

### 86. 🔴 What does `computeIfAbsent()` solve?

Instead of unsafe:

```java
if (!map.containsKey(key)) {
    map.put(key, createValue());
}
```

use:

```java
map.computeIfAbsent(
    key,
    k -> createValue()
);
```

With `ConcurrentHashMap`, the operation provides atomic absent-to-present coordination for the key.

Useful for:

```text
per-key locks
memoization
registries
frequency structures
```

The mapping function should be short and should not perform problematic recursive updates to the same map.

If it returns `null` or throws, no mapping is established, so a future call may run it again.

---

### 87. When use CopyOnWriteArrayList?

Every mutation creates a new backing array.

Excellent when:

```text
reads vastly outnumber writes
lists are small/moderate
snapshot iteration is useful
```

Example:

```text
event listeners
configuration listeners
```

Bad for:

```text
write-heavy workloads
very large collections
```

because each write copies the array.

---

### 88. How does BlockingQueue help producer/consumer?

Producer:

```java
queue.put(item);
```

may block when full.

Consumer:

```java
queue.take();
```

blocks when empty.

It encapsulates much of the condition-waiting coordination.

Example:

```text
Producers
    |
    v
BlockingQueue
    |
    v
Consumers
```

Common implementations:

```text
ArrayBlockingQueue
LinkedBlockingQueue
PriorityBlockingQueue
SynchronousQueue
```

---

### 89. CountDownLatch vs CyclicBarrier vs Semaphore?

**CountDownLatch**

Wait until a counter reaches zero.

```text
one-shot
```

Example: wait until 5 services initialize.

**CyclicBarrier**

Fixed group of threads meet at a barrier.

```text
reusable
```

Example: phases of a parallel computation.

**Semaphore**

Controls number of concurrent permits.

```java
new Semaphore(10)
```

Example:

```text
allow at most 10 concurrent database operations
```

---

# 8. JVM Memory

### 90. 🔴 Explain JVM runtime memory areas

## Heap

Shared across threads.

Contains most objects/arrays.

Managed by GC.

## Java Stack

Each thread has its own stack.

Contains frames:

```text
local variables
operand stack
method execution state
references
```

## Metaspace

HotSpot implementation area for class metadata.

Stored in native memory rather than normal Java heap.

## Program Counter

Per-thread pointer/state representing the current bytecode execution position.

## Native Method Stack

Used for native/JNI execution.

---

### 91. 🔴 Heap vs stack?

Heap:

```text
shared
GC-managed
typically stores objects
larger
```

Stack:

```text
per-thread
contains method frames/local variables
automatically unwound when methods return
```

Avoid oversimplifying this as:

> “Primitives always go on stack and objects always go on heap.”

References/local primitives may be in frames, while JIT escape analysis may eliminate or scalar-replace allocations.

Think in terms of **JVM execution semantics**, not simplistic physical placement rules.

---

### 92. What is stored in Metaspace?

HotSpot Metaspace contains class metadata such as information about:

```text
loaded classes
methods
runtime constant-pool metadata
class structure
```

Since Java 8, it replaced PermGen.

It uses native memory and can grow according to configuration/system limits.

---

### 93. 🔴 Can Java leak memory despite GC?

Yes.

GC removes objects that are **unreachable**.

If an object is still reachable but no longer useful, GC cannot know it should be deleted.

Example:

```java
static final Map<String, Object> CACHE =
        new HashMap<>();
```

If entries are never removed, memory keeps growing even though GC works correctly.

---

### 94. Common Java memory leaks?

Examples:

### Unbounded static collection

```java
static Map<?, ?> cache;
```

### Listener not deregistered

Publisher retains listener references.

### ThreadLocal with thread pools

```java
threadLocal.set(bigObject);
```

but never:

```java
threadLocal.remove();
```

Pool threads live for a long time.

### Unbounded caches

No capacity/expiry.

### ClassLoader leaks

Old application classloaders remain referenced during redeploys.

### Unclosed resources

Not strictly Java-heap leaks in every case, but can leak:

```text
native memory
file descriptors
connections
```

---

# 9. Garbage Collection

### 95. 🔴 How does GC determine whether an object is alive?

Java uses **reachability analysis**, not simple reference counting.

GC begins from **GC Roots**, such as:

```text
references from active thread stacks
static references
JNI references
certain JVM internal roots
```

If object A can be reached from a GC root through references:

```text
Root -> A -> B -> C
```

then A/B/C are live.

An unreachable cycle:

```text
A -> B
B -> A
```

can still be collected because neither is reachable from a GC root.

---

### 96. 🔴 Young vs old generation?

Generational collectors exploit the observation:

> Most objects die young.

Young-generation concepts traditionally include:

```text
Eden
Survivor spaces
```

New objects generally begin young.

Objects surviving enough collection activity may be promoted to:

```text
old generation
```

With G1, the heap is physically divided into regions; regions can dynamically serve roles such as:

```text
Eden
Survivor
Old
Humongous
```

rather than being one permanently contiguous young area.

---

### 97. 🔴 Minor vs Major vs Full GC?

Terminology varies by collector, so avoid treating it as perfectly universal.

Traditionally:

**Minor/Young GC**

Collects young generation.

Usually relatively frequent.

**Major/Old GC**

Term often used for old-generation collection, but its meaning is collector-specific and sometimes imprecise.

**Full GC**

Typically a stop-the-world collection/compaction involving the whole heap and often additional JVM metadata cleanup.

For G1, more precise terms include:

```text
Young GC
Concurrent Marking
Mixed GC
Full GC
```

Use collector-specific terminology when diagnosing production systems.

---

### 98. 🔴 How does G1 GC work?

G1 divides heap into many similarly sized **regions**.

Instead of fixed contiguous generations, regions dynamically represent:

```text
Eden
Survivor
Old
Humongous
```

Major ideas:

```text
young evacuation
concurrent marking
remembered sets
mixed collections
region selection based partly on reclaim value
pause-time goals
```

After concurrent marking, G1 can perform **mixed collections**, collecting young regions plus selected old regions containing significant reclaimable garbage.

G1 aims for a balance between:

```text
throughput
predictable pauses
large heap support
```

and is the default collector in modern HotSpot Java.

---

### 99. G1 vs ZGC?

## G1

Good general-purpose choice.

Optimizes for a balance of:

```text
throughput
reasonable latency
predictable pause goals
```

Suitable for many backend applications.

## ZGC

Designed for extremely low pause times, including very large heaps.

Most expensive GC work is performed concurrently.

Choose ZGC when:

```text
tail latency is extremely important
heap may be large
very short pauses matter more than maximizing raw throughput
```

Potential trade-offs:

```text
some additional CPU
memory overhead
different tuning/operational characteristics
```

Java 21 also introduced **Generational ZGC** as a Java 21 feature option, adding generational behavior to ZGC.

Don't choose based only on heap size. Measure workload latency, throughput and allocation behavior.

---

### 100. 🔴 How do you investigate long GC pauses?

First: **measure, don't guess**.

Enable GC logging:

```bash
-Xlog:gc*
```

Use:

```text
Java Flight Recorder
JDK Mission Control
jcmd
GC logs
heap histograms
heap dumps
allocation profiling
```

Questions to investigate:

```text
Is allocation rate extremely high?
Is old generation constantly near capacity?
Are objects surviving unexpectedly?
Are there humongous allocations?
Is heap too small?
Is heap unnecessarily huge?
Are Full GCs occurring?
Is Metaspace growing?
Is application retaining objects?
Are promotion/evacuation pressures high?
```

Useful commands:

```bash
jcmd <pid> GC.heap_info
```

```bash
jcmd <pid> GC.class_histogram
```

```bash
jcmd <pid> JFR.start
```

For a suspected leak, take a heap dump and inspect **retained size and GC-root paths**, not merely object counts.

The diagnostic flow should be:

```text
GC pauses high
     ↓
inspect GC logs/JFR
     ↓
allocation vs retention?
     ↓
collector pressure / heap sizing / leak?
     ↓
identify dominant object graph
     ↓
fix application or configuration
     ↓
measure again
```

---

# The 15 answers I would memorize almost word-for-word for Walmart IN4

If the interview is close, prioritize:

```text
HashMap internals
ConcurrentHashMap internals
equals/hashCode
immutability
SOLID

synchronized
volatile
happens-before
ReentrantLock
AtomicInteger/CAS
deadlock

ThreadPoolExecutor
virtual threads

JVM memory
G1 GC
```

And connect them to practical LLD examples:

```text
LRU Cache
    -> HashMap
    -> DLL
    -> ReentrantLock
    -> ConcurrentHashMap discussion

Restaurant Reservation
    -> check-then-act race
    -> per-resource locking
    -> DB locking after horizontal scaling

Payment Gateway
    -> Strategy
    -> Factory
    -> CompletableFuture
    -> computeIfAbsent/putIfAbsent
    -> idempotency
```
