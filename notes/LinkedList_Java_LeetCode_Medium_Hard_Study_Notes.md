# Linked List Study Notes — Java
## LeetCode Medium / Hard Focus

> Goal: become strong at pointer manipulation, invariants, and recurring linked-list patterns used in medium/hard LeetCode problems.

---

# 1. Core Node Definitions

## Singly Linked List

```java
class ListNode {
    int val;
    ListNode next;

    ListNode() {}

    ListNode(int val) {
        this.val = val;
    }

    ListNode(int val, ListNode next) {
        this.val = val;
        this.next = next;
    }
}
```

## Doubly Linked List

```java
class DoublyNode {
    int val;
    DoublyNode prev;
    DoublyNode next;

    DoublyNode(int val) {
        this.val = val;
    }
}
```

---

# 2. What Makes Linked List Problems Hard

Most linked-list problems are not about data structures.

They are about:

- pointer ownership
- mutation order
- maintaining invariants
- not losing references
- handling boundaries
- identifying the right pointer pattern

The main question is usually:

> Which references must still be reachable after I change `next`?

---

# 3. Golden Rule Before Rewiring

Before doing:

```java
curr.next = something;
```

first preserve the original next node if you still need it.

```java
ListNode next = curr.next;
curr.next = prev;
prev = curr;
curr = next;
```

This principle appears everywhere.

---

# 4. Dummy Node Pattern

A dummy node removes special-case logic for head mutation.

```java
ListNode dummy = new ListNode(0);
dummy.next = head;
```

Use it when:

- deleting nodes
- inserting near head
- reversing subranges
- merging lists
- partitioning
- manipulating positions

Example:

```text
dummy -> 1 -> 2 -> 3
```

Now every real node has a predecessor.

---

# 5. Sentinel Invariant

A useful invariant:

```text
dummy.next always points to the current answer head.
```

At the end:

```java
return dummy.next;
```

---

# 6. Two-Pointer Pattern

Two pointers often solve:

- middle node
- cycle detection
- nth node from end
- intersection
- palindrome
- split list

Typical form:

```java
ListNode slow = head;
ListNode fast = head;
```

---

# 7. Fast and Slow Pointer

## Find Middle

```java
ListNode slow = head;
ListNode fast = head;

while (fast != null && fast.next != null) {
    slow = slow.next;
    fast = fast.next.next;
}
```

For:

```text
1 -> 2 -> 3 -> 4 -> 5
```

slow ends at:

```text
3
```

For:

```text
1 -> 2 -> 3 -> 4
```

slow ends at:

```text
3
```

This returns the second middle for even length.

---

# 8. First Middle vs Second Middle

## Second Middle

```java
while (fast != null && fast.next != null)
```

## First Middle

```java
while (fast.next != null && fast.next.next != null)
```

This distinction matters in merge sort.

---

# 9. Reverse Entire Linked List

## Iterative

```java
public ListNode reverseList(ListNode head) {
    ListNode prev = null;
    ListNode curr = head;

    while (curr != null) {
        ListNode next = curr.next;

        curr.next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}
```

Time:

```text
O(n)
```

Space:

```text
O(1)
```

---

# 10. Reverse List Mental Model

Initial:

```text
prev    curr
null <- 1 -> 2 -> 3
```

After one iteration:

```text
null <- 1    2 -> 3
        prev curr
```

The invariant:

```text
prev = already reversed prefix
curr = first node of unreversed suffix
```

---

# 11. Recursive Reverse

```java
public ListNode reverseList(ListNode head) {
    if (head == null || head.next == null) {
        return head;
    }

    ListNode newHead = reverseList(head.next);

    head.next.next = head;
    head.next = null;

    return newHead;
}
```

Useful for understanding recursion, but iterative is usually safer.

Space:

```text
O(n)
```

because of recursion stack.

---

# 12. Reverse a Sublist

Problem:

```text
Reverse nodes from position left to right.
```

Example:

```text
1 -> 2 -> 3 -> 4 -> 5
left = 2
right = 4
```

Result:

```text
1 -> 4 -> 3 -> 2 -> 5
```

Reusable pattern:

```java
public ListNode reverseBetween(ListNode head, int left, int right) {
    if (head == null || left == right) {
        return head;
    }

    ListNode dummy = new ListNode(0);
    dummy.next = head;

    ListNode prev = dummy;

    for (int i = 1; i < left; i++) {
        prev = prev.next;
    }

    ListNode curr = prev.next;

    for (int i = 0; i < right - left; i++) {
        ListNode next = curr.next;

        curr.next = next.next;
        next.next = prev.next;
        prev.next = next;
    }

    return dummy.next;
}
```

This uses head-insertion.

---

# 13. Head-Insertion Reversal

Suppose:

```text
prev -> 2 -> 3 -> 4 -> 5
        curr
```

Take node `3` and insert immediately after `prev`:

```text
prev -> 3 -> 2 -> 4 -> 5
             curr
```

Then move `4`:

```text
prev -> 4 -> 3 -> 2 -> 5
                  curr
```

Very useful for sublist reversal.

---

# 14. Reverse Nodes in K Group — Hard Pattern

LeetCode 25.

Example:

```text
1 -> 2 -> 3 -> 4 -> 5
k = 2
```

Result:

```text
2 -> 1 -> 4 -> 3 -> 5
```

Core idea:

1. find kth node
2. remember next group
3. reverse current k nodes
4. reconnect
5. advance group pointer

```java
public ListNode reverseKGroup(ListNode head, int k) {
    ListNode dummy = new ListNode(0);
    dummy.next = head;

    ListNode groupPrev = dummy;

    while (true) {
        ListNode kth = getKth(groupPrev, k);

        if (kth == null) {
            break;
        }

        ListNode groupNext = kth.next;

        ListNode prev = groupNext;
        ListNode curr = groupPrev.next;

        while (curr != groupNext) {
            ListNode next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        ListNode oldGroupStart = groupPrev.next;

        groupPrev.next = kth;
        groupPrev = oldGroupStart;
    }

    return dummy.next;
}

private ListNode getKth(ListNode start, int k) {
    while (start != null && k > 0) {
        start = start.next;
        k--;
    }

    return start;
}
```

---

# 15. Reverse K Group Invariant

Before each iteration:

```text
groupPrev.next = first node of next group
```

After reversal:

```text
groupPrev = old first node
```

because the old first node becomes the tail of the reversed group.

This invariant is the key to LeetCode 25.

---

# 16. Nth Node from End

Problem:

Remove nth node from end.

Use a fixed distance between pointers.

```java
public ListNode removeNthFromEnd(ListNode head, int n) {
    ListNode dummy = new ListNode(0);
    dummy.next = head;

    ListNode slow = dummy;
    ListNode fast = dummy;

    for (int i = 0; i <= n; i++) {
        fast = fast.next;
    }

    while (fast != null) {
        slow = slow.next;
        fast = fast.next;
    }

    slow.next = slow.next.next;

    return dummy.next;
}
```

---

# 17. Why Move Fast n+1 Steps?

We want:

```text
slow = node before target
```

not target itself.

Using dummy node + distance `n + 1` naturally positions slow correctly.

---

# 18. Floyd Cycle Detection

Used for:

- cycle existence
- cycle entry point
- duplicate number variation

## Detect Cycle

```java
public boolean hasCycle(ListNode head) {
    ListNode slow = head;
    ListNode fast = head;

    while (fast != null && fast.next != null) {
        slow = slow.next;
        fast = fast.next.next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}
```

---

# 19. Find Cycle Entry

LeetCode 142.

```java
public ListNode detectCycle(ListNode head) {
    ListNode slow = head;
    ListNode fast = head;

    do {
        if (fast == null || fast.next == null) {
            return null;
        }

        slow = slow.next;
        fast = fast.next.next;

    } while (slow != fast);

    slow = head;

    while (slow != fast) {
        slow = slow.next;
        fast = fast.next;
    }

    return slow;
}
```

---

# 20. Floyd Mathematics

Let:

```text
a = distance from head to cycle entry
b = distance from cycle entry to meeting point
c = remaining cycle distance
```

Fast travels twice slow:

```text
2(a + b) = a + b + k(b + c)
```

Rearranging:

```text
a = (k - 1)(b + c) + c
```

Meaning:

```text
distance head -> cycle entry
```

equals:

```text
distance meeting point -> cycle entry
```

modulo full cycles.

Therefore:

- reset one pointer to head
- move both one step
- they meet at cycle entry

---

# 21. Intersection of Two Linked Lists

LeetCode 160.

Elegant switching-pointer technique:

```java
public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
    ListNode a = headA;
    ListNode b = headB;

    while (a != b) {
        a = (a == null) ? headB : a.next;
        b = (b == null) ? headA : b.next;
    }

    return a;
}
```

Why it works:

```text
A path = lenA + lenB
B path = lenB + lenA
```

Both pointers travel equal total distance.

---

# 22. Merge Two Sorted Lists

Core building block for linked-list merge sort.

```java
public ListNode mergeTwoLists(ListNode a, ListNode b) {
    ListNode dummy = new ListNode(0);
    ListNode tail = dummy;

    while (a != null && b != null) {
        if (a.val <= b.val) {
            tail.next = a;
            a = a.next;
        } else {
            tail.next = b;
            b = b.next;
        }

        tail = tail.next;
    }

    tail.next = (a != null) ? a : b;

    return dummy.next;
}
```

---

# 23. Merge K Sorted Lists — Hard

LeetCode 23.

Best common approach:

```text
Min Heap
```

```java
public ListNode mergeKLists(ListNode[] lists) {
    PriorityQueue<ListNode> pq =
        new PriorityQueue<>((a, b) -> Integer.compare(a.val, b.val));

    for (ListNode node : lists) {
        if (node != null) {
            pq.offer(node);
        }
    }

    ListNode dummy = new ListNode(0);
    ListNode tail = dummy;

    while (!pq.isEmpty()) {
        ListNode node = pq.poll();

        tail.next = node;
        tail = tail.next;

        if (node.next != null) {
            pq.offer(node.next);
        }
    }

    return dummy.next;
}
```

Time:

```text
O(N log k)
```

where:

```text
N = total nodes
k = number of lists
```

---

# 24. Merge K Lists — Divide and Conquer

Alternative:

```text
pair lists
merge pairs
repeat
```

Complexity:

```text
O(N log k)
```

Often avoids heap overhead.

```java
public ListNode mergeKLists(ListNode[] lists) {
    if (lists == null || lists.length == 0) {
        return null;
    }

    int interval = 1;

    while (interval < lists.length) {
        for (int i = 0; i + interval < lists.length; i += interval * 2) {
            lists[i] = merge(lists[i], lists[i + interval]);
        }

        interval *= 2;
    }

    return lists[0];
}
```

---

# 25. Sort Linked List — Merge Sort

LeetCode 148.

Linked lists are naturally suited for merge sort.

Why not quicksort?

Because:

- no O(1) random access
- partitioning is awkward
- merge operation is pointer-based and efficient

Algorithm:

1. find middle
2. split
3. recursively sort halves
4. merge

```java
public ListNode sortList(ListNode head) {
    if (head == null || head.next == null) {
        return head;
    }

    ListNode slow = head;
    ListNode fast = head.next;

    while (fast != null && fast.next != null) {
        slow = slow.next;
        fast = fast.next.next;
    }

    ListNode right = slow.next;
    slow.next = null;

    ListNode leftSorted = sortList(head);
    ListNode rightSorted = sortList(right);

    return merge(leftSorted, rightSorted);
}
```

Time:

```text
O(n log n)
```

Space:

```text
O(log n)
```

recursion stack.

---

# 26. Bottom-Up Merge Sort — O(1) Extra Space

For stricter constraints, use iterative bottom-up merge sort.

Concept:

```text
size = 1
merge blocks of 1

size = 2
merge blocks of 2

size = 4
merge blocks of 4
```

This is more complex but avoids recursion stack.

Important for senior-level interviews.

---

# 27. Palindrome Linked List

LeetCode 234.

Best O(1)-extra-space approach:

1. find middle
2. reverse second half
3. compare
4. optionally restore list

```java
public boolean isPalindrome(ListNode head) {
    if (head == null || head.next == null) {
        return true;
    }

    ListNode slow = head;
    ListNode fast = head;

    while (fast != null && fast.next != null) {
        slow = slow.next;
        fast = fast.next.next;
    }

    ListNode second = reverse(slow);
    ListNode first = head;

    while (second != null) {
        if (first.val != second.val) {
            return false;
        }

        first = first.next;
        second = second.next;
    }

    return true;
}
```

---

# 28. Reorder List

LeetCode 143.

Input:

```text
1 -> 2 -> 3 -> 4 -> 5
```

Output:

```text
1 -> 5 -> 2 -> 4 -> 3
```

Pattern:

```text
find middle
+
reverse second half
+
merge alternating
```

```java
public void reorderList(ListNode head) {
    if (head == null || head.next == null) {
        return;
    }

    ListNode slow = head;
    ListNode fast = head;

    while (fast.next != null && fast.next.next != null) {
        slow = slow.next;
        fast = fast.next.next;
    }

    ListNode second = reverse(slow.next);
    slow.next = null;

    ListNode first = head;

    while (second != null) {
        ListNode next1 = first.next;
        ListNode next2 = second.next;

        first.next = second;
        second.next = next1;

        first = next1;
        second = next2;
    }
}
```

---

# 29. Partition List

LeetCode 86.

Create two lists:

```text
< x
>= x
```

Then concatenate.

```java
public ListNode partition(ListNode head, int x) {
    ListNode smallDummy = new ListNode(0);
    ListNode largeDummy = new ListNode(0);

    ListNode small = smallDummy;
    ListNode large = largeDummy;

    while (head != null) {
        if (head.val < x) {
            small.next = head;
            small = small.next;
        } else {
            large.next = head;
            large = large.next;
        }

        head = head.next;
    }

    large.next = null;
    small.next = largeDummy.next;

    return smallDummy.next;
}
```

Important:

```java
large.next = null;
```

prevents accidental cycles from old links.

---

# 30. Odd Even Linked List

LeetCode 328.

Goal:

```text
1 -> 2 -> 3 -> 4 -> 5
```

becomes:

```text
1 -> 3 -> 5 -> 2 -> 4
```

```java
public ListNode oddEvenList(ListNode head) {
    if (head == null) {
        return null;
    }

    ListNode odd = head;
    ListNode even = head.next;
    ListNode evenHead = even;

    while (even != null && even.next != null) {
        odd.next = even.next;
        odd = odd.next;

        even.next = odd.next;
        even = even.next;
    }

    odd.next = evenHead;

    return head;
}
```

---

# 31. Rotate List

LeetCode 61.

Input:

```text
1 -> 2 -> 3 -> 4 -> 5
k = 2
```

Output:

```text
4 -> 5 -> 1 -> 2 -> 3
```

Trick:

1. calculate length
2. connect tail to head
3. form cycle
4. break at correct point

```java
public ListNode rotateRight(ListNode head, int k) {
    if (head == null || head.next == null || k == 0) {
        return head;
    }

    int n = 1;
    ListNode tail = head;

    while (tail.next != null) {
        tail = tail.next;
        n++;
    }

    k %= n;

    if (k == 0) {
        return head;
    }

    tail.next = head;

    int stepsToNewTail = n - k;

    ListNode newTail = tail;

    while (stepsToNewTail-- > 0) {
        newTail = newTail.next;
    }

    ListNode newHead = newTail.next;
    newTail.next = null;

    return newHead;
}
```

---

# 32. Copy List with Random Pointer — Medium/Hard Pattern

LeetCode 138.

Each node:

```text
next
random
```

Best O(1) auxiliary-space approach:

### Step 1

Insert copy after every original.

```text
A -> A' -> B -> B' -> C -> C'
```

### Step 2

Set random pointers.

```java
copy.random = original.random.next;
```

### Step 3

Separate both lists.

```java
public Node copyRandomList(Node head) {
    if (head == null) {
        return null;
    }

    Node curr = head;

    while (curr != null) {
        Node copy = new Node(curr.val);
        copy.next = curr.next;
        curr.next = copy;
        curr = copy.next;
    }

    curr = head;

    while (curr != null) {
        if (curr.random != null) {
            curr.next.random = curr.random.next;
        }

        curr = curr.next.next;
    }

    Node dummy = new Node(0);
    Node copyTail = dummy;
    curr = head;

    while (curr != null) {
        Node copy = curr.next;
        curr.next = copy.next;

        copyTail.next = copy;
        copyTail = copy;

        curr = curr.next;
    }

    return dummy.next;
}
```

---

# 33. Flatten Multilevel Doubly Linked List

LeetCode 430.

Nodes may have:

```text
next
prev
child
```

Pattern:

```text
DFS + pointer splicing
```

Use a stack:

```java
public Node flatten(Node head) {
    if (head == null) {
        return null;
    }

    Deque<Node> stack = new ArrayDeque<>();
    stack.push(head);

    Node dummy = new Node(0);
    Node prev = dummy;

    while (!stack.isEmpty()) {
        Node curr = stack.pop();

        prev.next = curr;
        curr.prev = prev;

        if (curr.next != null) {
            stack.push(curr.next);
        }

        if (curr.child != null) {
            stack.push(curr.child);
            curr.child = null;
        }

        prev = curr;
    }

    dummy.next.prev = null;

    return dummy.next;
}
```

---

# 34. LRU Cache — Linked List + HashMap

LeetCode 146.

One of the most important linked-list design problems.

Need:

```text
O(1) get
O(1) put
O(1) eviction
```

Use:

```text
HashMap<Key, Node>
+
Doubly Linked List
```

Why doubly linked?

Because arbitrary node removal must be:

```text
O(1)
```

without searching for predecessor.

---

# 35. LRU Structure

```text
HEAD <-> most recent <-> ... <-> least recent <-> TAIL
```

Use dummy head and tail.

```java
class LRUCache {
    static class Node {
        int key;
        int value;
        Node prev;
        Node next;

        Node() {}

        Node(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }

    private final int capacity;
    private final Map<Integer, Node> map = new HashMap<>();

    private final Node head = new Node();
    private final Node tail = new Node();

    public LRUCache(int capacity) {
        this.capacity = capacity;

        head.next = tail;
        tail.prev = head;
    }

    public int get(int key) {
        Node node = map.get(key);

        if (node == null) {
            return -1;
        }

        remove(node);
        insertAfterHead(node);

        return node.value;
    }

    public void put(int key, int value) {
        if (map.containsKey(key)) {
            Node old = map.get(key);
            remove(old);
            map.remove(key);
        }

        Node node = new Node(key, value);
        map.put(key, node);
        insertAfterHead(node);

        if (map.size() > capacity) {
            Node lru = tail.prev;

            remove(lru);
            map.remove(lru.key);
        }
    }

    private void remove(Node node) {
        node.prev.next = node.next;
        node.next.prev = node.prev;
    }

    private void insertAfterHead(Node node) {
        node.next = head.next;
        node.prev = head;

        head.next.prev = node;
        head.next = node;
    }
}
```

---

# 36. LFU Cache — Hard Design

LeetCode 460.

Requirement:

- evict least frequently used key
- tie-break by least recently used

Need roughly:

```text
key -> node
frequency -> doubly linked list
minimumFrequency
```

Typical structures:

```java
Map<Integer, Node> keyToNode;
Map<Integer, DoublyLinkedList> freqToList;
int minFreq;
```

Operations must remain:

```text
O(1)
```

This is much harder than LRU because frequency changes dynamically.

---

# 37. Linked List + Heap Pattern

Useful when selecting among many current head nodes.

Typical examples:

- Merge K Sorted Lists
- smallest available node among multiple chains

Structure:

```text
PriorityQueue<ListNode>
```

Complexity:

```text
O(N log k)
```

---

# 38. Linked List + Monotonic Stack

Some problems combine linked lists with array-like preprocessing.

Example family:

- next greater node in linked list

LeetCode 1019.

Typical approach:

1. convert list values to array
2. monotonic stack over indexes

```java
public int[] nextLargerNodes(ListNode head) {
    List<Integer> values = new ArrayList<>();

    while (head != null) {
        values.add(head.val);
        head = head.next;
    }

    int[] ans = new int[values.size()];
    Deque<Integer> stack = new ArrayDeque<>();

    for (int i = 0; i < values.size(); i++) {
        while (!stack.isEmpty()
                && values.get(stack.peek()) < values.get(i)) {

            int idx = stack.pop();
            ans[idx] = values.get(i);
        }

        stack.push(i);
    }

    return ans;
}
```

---

# 39. Delete Node Without Head

LeetCode 237.

Given only:

```text
node
```

cannot actually delete it directly.

Instead copy successor value:

```java
node.val = node.next.val;
node.next = node.next.next;
```

This conceptually deletes the next node while making current node look like it.

Constraint:

```text
node must not be tail
```

---

# 40. Remove Duplicates from Sorted List II

LeetCode 82.

Delete every value appearing multiple times.

Input:

```text
1 -> 2 -> 3 -> 3 -> 4 -> 4 -> 5
```

Output:

```text
1 -> 2 -> 5
```

Dummy node is crucial.

```java
public ListNode deleteDuplicates(ListNode head) {
    ListNode dummy = new ListNode(0);
    dummy.next = head;

    ListNode prev = dummy;

    while (head != null) {
        if (head.next != null && head.val == head.next.val) {
            int duplicate = head.val;

            while (head != null && head.val == duplicate) {
                head = head.next;
            }

            prev.next = head;
        } else {
            prev = head;
            head = head.next;
        }
    }

    return dummy.next;
}
```

---

# 41. Add Two Numbers

LeetCode 2.

Pattern:

```text
linked-list digit simulation
+
carry
```

```java
public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
    ListNode dummy = new ListNode(0);
    ListNode tail = dummy;

    int carry = 0;

    while (l1 != null || l2 != null || carry != 0) {
        int x = (l1 != null) ? l1.val : 0;
        int y = (l2 != null) ? l2.val : 0;

        int sum = x + y + carry;

        carry = sum / 10;

        tail.next = new ListNode(sum % 10);
        tail = tail.next;

        if (l1 != null) {
            l1 = l1.next;
        }

        if (l2 != null) {
            l2 = l2.next;
        }
    }

    return dummy.next;
}
```

---

# 42. Add Two Numbers II

LeetCode 445.

Digits are forward order.

Example:

```text
7 -> 2 -> 4 -> 3
5 -> 6 -> 4
```

Options:

### Approach 1

Use stacks.

### Approach 2

Reverse both lists.

Stack solution avoids modifying inputs.

---

# 43. Swap Nodes in Pairs

LeetCode 24.

```text
1 -> 2 -> 3 -> 4
```

becomes:

```text
2 -> 1 -> 4 -> 3
```

```java
public ListNode swapPairs(ListNode head) {
    ListNode dummy = new ListNode(0);
    dummy.next = head;

    ListNode prev = dummy;

    while (prev.next != null && prev.next.next != null) {
        ListNode first = prev.next;
        ListNode second = first.next;

        first.next = second.next;
        second.next = first;
        prev.next = second;

        prev = first;
    }

    return dummy.next;
}
```

This is essentially:

```text
reverse groups of k = 2
```

---

# 44. Delete Middle Node

LeetCode 2095.

Need predecessor of middle.

```java
public ListNode deleteMiddle(ListNode head) {
    if (head.next == null) {
        return null;
    }

    ListNode slow = head;
    ListNode fast = head.next.next;

    while (fast != null && fast.next != null) {
        slow = slow.next;
        fast = fast.next.next;
    }

    slow.next = slow.next.next;

    return head;
}
```

Alternative:

```text
dummy + slow/fast
```

---

# 45. Split Linked List in Parts

LeetCode 725.

Need:

```text
n / k = base size
n % k = number of larger parts
```

For first `remainder` parts:

```text
size = base + 1
```

Remaining:

```text
size = base
```

This is primarily arithmetic + pointer cutting.

---

# 46. Critical Pointer Patterns

Memorize these.

## Reverse

```java
next = curr.next;
curr.next = prev;
prev = curr;
curr = next;
```

## Remove after prev

```java
prev.next = prev.next.next;
```

## Insert node after prev

```java
node.next = prev.next;
prev.next = node;
```

## Remove doubly-linked node

```java
node.prev.next = node.next;
node.next.prev = node.prev;
```

## Connect two lists

```java
tail.next = secondHead;
```

---

# 47. Pattern: Split + Reverse + Merge

One of the most important composite patterns.

Used in:

- Reorder List
- Palindrome Linked List
- some list folding problems

Template:

```text
find middle
      ↓
split list
      ↓
reverse second half
      ↓
merge / compare
```

---

# 48. Pattern: Dummy + Prev + Curr

Used in:

- deletions
- swapping
- sublist reversal
- partitioning
- group reversal

Mental model:

```text
dummy -> prev -> curr -> ...
```

`prev` usually identifies the mutation boundary.

---

# 49. Pattern: Fixed Gap

Used in:

- nth node from end
- remove nth node from end
- kth node from tail

Create:

```text
distance(fast, slow) = k
```

Then advance both.

When fast reaches end:

```text
slow is k positions from end
```

---

# 50. Pattern: Convert Temporarily to Cycle

Useful for:

- Rotate List

Process:

```text
linear list
-> connect tail to head
-> circular list
-> break at new tail
```

Very clean.

---

# 51. Pattern: Interleave Copies

Used in:

- Copy List with Random Pointer

Technique:

```text
Original nodes and copies coexist temporarily.
```

This lets each copy find the copied random target in O(1):

```text
original.random.next
```

---

# 52. Pointer Safety Checklist

Before changing a pointer, ask:

1. What node am I about to disconnect?
2. Do I still need access to it?
3. Should I save it first?
4. Is the new tail properly terminated?
5. Can this create a cycle?
6. Is head changing?
7. Would a dummy node remove edge cases?

---

# 53. Common Bugs

## Losing Remaining List

Wrong:

```java
curr.next = prev;
curr = curr.next;
```

After reassignment:

```text
curr.next
```

points backward.

You lost the remaining list.

Correct:

```java
ListNode next = curr.next;
curr.next = prev;
curr = next;
```

---

# 54. Common Bug: Forgetting Tail Null

After partitioning/reordering:

```java
tail.next = null;
```

may be necessary.

Otherwise an old link may remain and form:

- incorrect suffix
- duplicate section
- cycle

---

# 55. Common Bug: Head Edge Cases

Examples:

```text
remove first node
reverse starting from first node
swap first pair
```

Dummy node solves most of them.

---

# 56. Common Bug: Wrong Middle

For even length:

```text
1 -> 2 -> 3 -> 4
```

Depending on loop condition, slow may become:

```text
2
```

or:

```text
3
```

Know which one your algorithm requires.

Merge sort usually wants the first middle so the list splits cleanly.

---

# 57. Common Bug: Infinite Cycle

Whenever doing complex rewiring, inspect:

```java
node.next
```

after each mutation.

Particularly dangerous in:

- reverse K group
- reorder
- partition
- rotate
- merge

---

# 58. Java-Specific Notes

Use:

```java
ArrayDeque
```

instead of:

```java
Stack
```

for stack behavior.

Example:

```java
Deque<ListNode> stack = new ArrayDeque<>();
```

For priority queue:

```java
PriorityQueue<ListNode> pq =
    new PriorityQueue<>((a, b) -> Integer.compare(a.val, b.val));
```

Avoid:

```java
a.val - b.val
```

because integer subtraction may overflow.

---

# 59. Java Reference Semantics

Java variables like:

```java
ListNode a;
ListNode b;
```

store object references.

If:

```java
a = b;
```

both refer to the same object.

Changing:

```java
a.next = x;
```

changes the actual shared node.

This is why linked-list pointer manipulation works.

---

# 60. Passing Head into a Method

Java passes references by value.

Example:

```java
void f(ListNode head) {
    head = head.next;
}
```

does not change the caller's variable.

But:

```java
void f(ListNode head) {
    head.next = null;
}
```

does mutate the shared object.

Critical Java interview distinction.

---

# 61. Complexity Mental Model

For most linked-list problems:

### Traversal

```text
O(n)
```

### Reverse

```text
O(n)
```

### Find middle

```text
O(n)
```

### Merge sorted lists

```text
O(n + m)
```

### Sort list

```text
O(n log n)
```

### Merge K sorted lists

```text
O(N log k)
```

### Random access

```text
O(n)
```

Unlike arrays:

```text
O(1)
```

---

# 62. Must-Do Medium Problems

Recommended order:

1. **LeetCode 2 — Add Two Numbers**
2. **LeetCode 19 — Remove Nth Node From End**
3. **LeetCode 24 — Swap Nodes in Pairs**
4. **LeetCode 61 — Rotate List**
5. **LeetCode 82 — Remove Duplicates from Sorted List II**
6. **LeetCode 86 — Partition List**
7. **LeetCode 92 — Reverse Linked List II**
8. **LeetCode 138 — Copy List with Random Pointer**
9. **LeetCode 142 — Linked List Cycle II**
10. **LeetCode 143 — Reorder List**
11. **LeetCode 146 — LRU Cache**
12. **LeetCode 148 — Sort List**
13. **LeetCode 328 — Odd Even Linked List**
14. **LeetCode 430 — Flatten a Multilevel Doubly Linked List**
15. **LeetCode 445 — Add Two Numbers II**
16. **LeetCode 725 — Split Linked List in Parts**
17. **LeetCode 1019 — Next Greater Node In Linked List**

---

# 63. Must-Do Hard Problems

Priority order:

## 1. LeetCode 25 — Reverse Nodes in k-Group

Tests:

- pointer control
- group boundaries
- invariants

## 2. LeetCode 23 — Merge k Sorted Lists

Tests:

- heap
- divide-and-conquer
- linked list merging

## 3. LeetCode 460 — LFU Cache

Tests:

- HashMap
- doubly linked lists
- frequency buckets
- O(1) system design

---

# 64. High-Value Interview Problems

If time is limited, master these:

```text
19  Remove Nth From End
23  Merge K Sorted Lists
25  Reverse K Group
92  Reverse Linked List II
138 Copy Random Pointer
142 Cycle II
143 Reorder List
146 LRU Cache
148 Sort List
234 Palindrome Linked List
460 LFU Cache
```

---

# 65. Pattern-to-Problem Mapping

| Pattern | Problems |
|---|---|
| Basic reversal | 206 |
| Sublist reversal | 92 |
| K-group reversal | 25 |
| Fast/slow | 19, 142, 143, 234 |
| Dummy node | 19, 24, 82, 92 |
| Merge | 21, 23, 148 |
| Heap + list | 23 |
| Split/reverse/merge | 143, 234 |
| HashMap + DLL | 146, 460 |
| Cycle trick | 61 |
| Interleaving copies | 138 |
| DFS/stack + DLL | 430 |

---

# 66. How to Approach a New Linked List Problem

## Step 1

Draw 4-6 nodes.

Example:

```text
A -> B -> C -> D -> E
```

## Step 2

Mark pointers.

```text
prev
curr
next
fast
slow
```

## Step 3

Identify structural pattern.

Ask:

```text
reverse?
delete?
split?
merge?
cycle?
fixed gap?
cache?
```

## Step 4

State invariant before coding.

Example:

```text
prev points to reversed prefix tail.
curr points to next unreversed node.
```

## Step 5

Code mutation only after saving needed references.

---

# 67. Senior-Level Interview Explanation

Do not narrate individual syntax.

Explain the invariant.

Weak explanation:

> I move curr here, then prev there, then next here.

Better:

> I maintain `prev` as the head of the already-reversed prefix and `curr` as the first node of the untouched suffix. Before reversing `curr.next`, I preserve the suffix pointer so I never lose access to the rest of the list.

This demonstrates actual reasoning.

---

# 68. Reverse K Group — Interview Explanation

A concise explanation:

> I use a dummy node so group reversal also works when the first group changes the head. For each iteration, I locate the kth node from `groupPrev`. If fewer than k nodes remain, I stop. Otherwise I remember `kth.next` as the next group's boundary, reverse the current group using that boundary as the initial `prev`, reconnect the reversed group, and move `groupPrev` to the old group head, which is now its tail.

---

# 69. LRU Cache — Interview Explanation

> A HashMap gives O(1) key lookup, but it cannot maintain recency efficiently. A doubly linked list maintains nodes in recency order and supports O(1) arbitrary removal because each node knows both neighbors. On every get or put, I move the node to the front. When capacity is exceeded, I evict the node just before the dummy tail.

---

# 70. Why Doubly Linked List for LRU?

With singly linked list:

```text
remove arbitrary node
```

requires finding predecessor:

```text
O(n)
```

With doubly linked list:

```java
node.prev.next = node.next;
node.next.prev = node.prev;
```

is:

```text
O(1)
```

---

# 71. Why Merge Sort for Linked Lists?

Merge sort fits linked lists because:

- splitting can use slow/fast pointers
- merging sorted lists requires only pointer changes
- no random access required
- guaranteed O(n log n)

Array merge sort needs auxiliary arrays.

Linked-list merge can reuse existing nodes.

---

# 72. Why Binary Search Is Usually Bad on Linked Lists

Even if you know the middle index:

```text
access middle node = O(n)
```

So binary search loses its main advantage.

Linked lists lack:

```text
O(1) random access
```

---

# 73. Recursive vs Iterative

Prefer iterative for:

- reverse
- K-group
- production code
- very large lists

Why?

Recursion may cause:

```text
StackOverflowError
```

For elegant divide-and-conquer like merge sort, recursion is acceptable if constraints allow it.

---

# 74. Memory Characteristics

A linked-list node typically contains:

```text
object header
value
reference to next
padding/alignment
```

A linked list has worse cache locality than an array because nodes may be scattered in memory.

So although insertion can be O(1), traversal can be slower in practice than arrays.

This matters in real system design.

---

# 75. Linked List vs ArrayList

| Operation | Linked List | ArrayList |
|---|---|---|
| Random access | O(n) | O(1) |
| Append | O(1) with tail | amortized O(1) |
| Insert at known node | O(1) | O(n) |
| Delete known node | O(1) if predecessor/prev known | O(n) |
| Cache locality | Poor | Excellent |
| Memory overhead | High | Lower |
| Binary search | Bad | Good |

In practical Java backend code:

> `ArrayList` is often preferable unless linked-list-specific behavior is genuinely needed.

---

# 76. Java LinkedList Class

Java:

```java
java.util.LinkedList
```

implements:

```text
List
Deque
Queue
```

But for LeetCode linked-list questions, you usually manipulate:

```java
ListNode
```

directly.

Do not confuse the two.

---

# 77. ArrayDeque vs LinkedList for Queue

For most Java production code:

Prefer:

```java
ArrayDeque
```

over:

```java
LinkedList
```

for queue/stack usage.

Reasons:

- better cache locality
- fewer allocations
- lower memory overhead
- typically faster

---

# 78. Dry-Run Template

When debugging, make a table:

| Step | prev | curr | next | list |
|---|---|---|---|---|
| 0 | null | 1 | 2 | 1→2→3 |
| 1 | 1 | 2 | 3 | 1←2? |
| 2 | 2 | 3 | null | 1←2, 3 |

The exact table can expose pointer loss immediately.

---

# 79. Edge Cases Checklist

Always test:

```text
null
1 node
2 nodes
even length
odd length
mutation at head
mutation at tail
k = 1
k = n
k > n if allowed
duplicate values
cycle
```

---

# 80. One-Page Revision Sheet

Memorize:

```java
// reverse
ListNode prev = null;
ListNode curr = head;

while (curr != null) {
    ListNode next = curr.next;
    curr.next = prev;
    prev = curr;
    curr = next;
}
```

```java
// middle
ListNode slow = head;
ListNode fast = head;

while (fast != null && fast.next != null) {
    slow = slow.next;
    fast = fast.next.next;
}
```

```java
// dummy
ListNode dummy = new ListNode(0);
dummy.next = head;
```

```java
// merge
while (a != null && b != null) {
    if (a.val <= b.val) {
        tail.next = a;
        a = a.next;
    } else {
        tail.next = b;
        b = b.next;
    }

    tail = tail.next;
}
```

```java
// DLL remove
node.prev.next = node.next;
node.next.prev = node.prev;
```

---

# 81. Final Mental Model

Most medium/hard linked-list problems reduce to a combination of:

```text
dummy node
+
fast/slow
+
reverse
+
split
+
merge
+
fixed pointer gap
+
HashMap
+
doubly linked list
+
heap
```

The difficult part is not remembering solutions.

The difficult part is preserving the correct invariant while mutating references.

If you can clearly state:

```text
what each pointer represents before and after every iteration
```

then most linked-list problems become manageable.
