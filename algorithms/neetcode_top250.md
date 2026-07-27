# NeetCode 250 — Java 21 Pattern & Solution Handbook

> **Snapshot:** NeetCode 250 list verified on **2026-07-26**. The live list contains **250 problems**: **60 Easy, 155 Medium, 35 Hard**, grouped into **18 categories**.
>
> **Scope of “all possible solutions”:** each card consolidates the standard interview-grade solution families—brute force, sorting/hash/heap alternatives, recursive and iterative variants, DP formulations, and the preferred asymptotic solution. Variants that only change syntax, container choice, or recursion style are not duplicated. Full Java code is provided for the preferred solution.

**Primary list:** <https://neetcode.io/practice/practice/neetcode250>

## How to Use This

For each problem, hide the Java block and force yourself to state: **pattern → invariant/state → complexity → failure case**. Re-code only problems where you miss one of those four. All snippets assume `import java.util.*;` and LeetCode-provided types such as `ListNode`, `TreeNode`, `Node`, `Interval`, `MountainArray`, and `GuessGame`.

## Coverage Index

| # | Category | Problems |
|---:|---|---:|
| 1 | [Arrays & Hashing](#arrays--hashing) | 22 |
| 2 | [Two Pointers](#two-pointers) | 13 |
| 3 | [Sliding Window](#sliding-window) | 9 |
| 4 | [Stack](#stack) | 14 |
| 5 | [Binary Search](#binary-search) | 14 |
| 6 | [Linked List](#linked-list) | 14 |
| 7 | [Trees](#trees) | 23 |
| 8 | [Heap / Priority Queue](#heap--priority-queue) | 12 |
| 9 | [Backtracking](#backtracking) | 17 |
| 10 | [Tries](#tries) | 4 |
| 11 | [Graphs](#graphs) | 21 |
| 12 | [Advanced Graphs](#advanced-graphs) | 10 |
| 13 | [1-D Dynamic Programming](#1-d-dynamic-programming) | 17 |
| 14 | [2-D Dynamic Programming](#2-d-dynamic-programming) | 16 |
| 15 | [Greedy](#greedy) | 14 |
| 16 | [Intervals](#intervals) | 7 |
| 17 | [Math & Geometry](#math--geometry) | 13 |
| 18 | [Bit Manipulation](#bit-manipulation) | 10 |

## Java Revision Conventions

- Prefer `ArrayDeque` over legacy `Stack`; use indices in monotonic deques/stacks.
- Use `long` for sums, products, squared distances, binary-search bounds, and delayed meeting times when overflow is plausible.
- For 0/1 knapsack, iterate capacity **descending**; for unbounded knapsack, iterate **ascending**.
- In graph shortest paths, stale heap entries must be skipped. In Bellman–Ford with an edge limit, relax from a cloned previous layer.
- For backtracking with duplicates, sort first and skip equal **siblings**, not equal values globally.

---

## Arrays & Hashing

### 1. [Concatenation of Array](https://leetcode.com/problems/concatenation-of-array/) — Easy

- [ ] **Revised**
- **Recognition cue:** Direct simulation
- **Approach ladder:** 1. Append into a dynamic list — O(n) time, O(n) space. 2. Allocate `2n` and copy twice — O(n) time, O(n) output space **(preferred)**.
- **Preferred pattern:** Direct simulation
- **Preferred complexity:** O(n) time, O(n) output space
- **Pitfall:** Output space is mandatory; do not count it as avoidable auxiliary space.

```java
class Solution {
    public int[] getConcatenation(int[] nums) {
        int n = nums.length;
        int[] ans = new int[2 * n];
        for (int i = 0; i < n; i++) ans[i] = ans[i + n] = nums[i];
        return ans;
    }
}
```

### 2. [Contains Duplicate](https://leetcode.com/problems/contains-duplicate/) — Easy

- [ ] **Revised**
- **Recognition cue:** Hash set membership
- **Approach ladder:** 1. Pairwise comparison — O(n²). 2. Sort and scan — O(n log n), O(1) extra if mutable. 3. HashSet — expected O(n) **(preferred)**.
- **Preferred pattern:** Hash set membership
- **Preferred complexity:** Expected O(n) time, O(n) space

```java
class Solution {
    public boolean containsDuplicate(int[] nums) {
        Set<Integer> seen = new HashSet<>();
        for (int x : nums) if (!seen.add(x)) return true;
        return false;
    }
}
```

### 3. [Valid Anagram](https://leetcode.com/problems/valid-anagram/) — Easy

- [ ] **Revised**
- **Recognition cue:** Compare character multisets.
- **Approach ladder:** 1. Direct enumeration/simulation — simplest baseline; may be O(n²) or use extra copies. 2. Sorting, hashing, counting, or prefix-state formulation — choose based on whether order must be preserved. 3. **Preferred:** Frequency equality — O(n) time, O(1) alphabet space.
- **Preferred pattern:** Frequency equality
- **Preferred complexity:** O(n) time, O(1) alphabet space
- **Invariant / state:** Increment for one string and decrement for the other.

```java
class Solution {
    public boolean isAnagram(String s, String t) {
        if (s.length() != t.length()) return false;
        int[] count = new int[26];
        for (int i = 0; i < s.length(); i++) {
            count[s.charAt(i) - 'a']++;
            count[t.charAt(i) - 'a']--;
        }
        for (int x : count) if (x != 0) return false;
        return true;
    }
}
```

### 4. [Two Sum](https://leetcode.com/problems/two-sum/) — Easy

- [ ] **Revised**
- **Recognition cue:** Find two indices whose values sum to target.
- **Approach ladder:** 1. Direct enumeration/simulation — simplest baseline; may be O(n²) or use extra copies. 2. Sorting, hashing, counting, or prefix-state formulation — choose based on whether order must be preserved. 3. **Preferred:** Complement lookup — O(n) time, O(n) space.
- **Preferred pattern:** Complement lookup
- **Preferred complexity:** O(n) time, O(n) space
- **Invariant / state:** Before storing x, check whether target-x was seen earlier.

```java
class Solution {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> index = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int need = target - nums[i];
            if (index.containsKey(need)) return new int[]{index.get(need), i};
            index.put(nums[i], i);
        }
        return new int[0];
    }
}
```

### 5. [Longest Common Prefix](https://leetcode.com/problems/longest-common-prefix/) — Easy

- [ ] **Revised**
- **Recognition cue:** Find the common prefix across many strings.
- **Approach ladder:** 1. Direct enumeration/simulation — simplest baseline; may be O(n²) or use extra copies. 2. Sorting, hashing, counting, or prefix-state formulation — choose based on whether order must be preserved. 3. **Preferred:** Vertical scan — O(total compared characters) time, O(1) space.
- **Preferred pattern:** Vertical scan
- **Preferred complexity:** O(total compared characters) time, O(1) space
- **Invariant / state:** Column i is valid only if every string has the same character at i.

```java
class Solution {
    public String longestCommonPrefix(String[] strs) {
        for (int i = 0; i < strs[0].length(); i++) {
            char c = strs[0].charAt(i);
            for (int j = 1; j < strs.length; j++) {
                if (i == strs[j].length() || strs[j].charAt(i) != c)
                    return strs[0].substring(0, i);
            }
        }
        return strs[0];
    }
}
```

### 6. [Group Anagrams](https://leetcode.com/problems/group-anagrams/) — Medium

- [ ] **Revised**
- **Recognition cue:** Group strings sharing the same character multiset.
- **Approach ladder:** 1. Direct enumeration/simulation — simplest baseline; may be O(n²) or use extra copies. 2. Sorting, hashing, counting, or prefix-state formulation — choose based on whether order must be preserved. 3. **Preferred:** Canonical signature — O(total characters) time, O(total characters) space.
- **Preferred pattern:** Canonical signature
- **Preferred complexity:** O(total characters) time, O(total characters) space
- **Invariant / state:** Equal anagrams produce identical frequency signatures.

```java
class Solution {
    public List<List<String>> groupAnagrams(String[] strs) {
        Map<String, List<String>> groups = new HashMap<>();
        for (String s : strs) {
            int[] freq = new int[26];
            for (char c : s.toCharArray()) freq[c - 'a']++;
            StringBuilder key = new StringBuilder();
            for (int x : freq) key.append('#').append(x);
            groups.computeIfAbsent(key.toString(), k -> new ArrayList<>()).add(s);
        }
        return new ArrayList<>(groups.values());
    }
}
```

### 7. [Remove Element](https://leetcode.com/problems/remove-element/) — Easy

- [ ] **Revised**
- **Recognition cue:** Delete selected values in-place; order may or may not matter.
- **Approach ladder:** 1. Direct enumeration/simulation — simplest baseline; may be O(n²) or use extra copies. 2. Sorting, hashing, counting, or prefix-state formulation — choose based on whether order must be preserved. 3. **Preferred:** Stable write pointer — O(n) time, O(1) space.
- **Preferred pattern:** Stable write pointer
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** [0, write) contains exactly the retained elements.

```java
class Solution {
    public int removeElement(int[] nums, int val) {
        int write = 0;
        for (int x : nums) {
            if (x != val) nums[write++] = x;
        }
        return write;
    }
}
```

### 8. [Majority Element](https://leetcode.com/problems/majority-element/) — Easy

- [ ] **Revised**
- **Recognition cue:** One value occurs more than n/2 times.
- **Approach ladder:** 1. Direct enumeration/simulation — simplest baseline; may be O(n²) or use extra copies. 2. Sorting, hashing, counting, or prefix-state formulation — choose based on whether order must be preserved. 3. **Preferred:** Boyer-Moore voting — O(n) time, O(1) space.
- **Preferred pattern:** Boyer-Moore voting
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Different values cancel; the majority cannot be fully cancelled.
- **Pitfall:** If majority existence is not guaranteed, verify candidate in a second pass.

```java
class Solution {
    public int majorityElement(int[] nums) {
        int candidate = 0, count = 0;
        for (int x : nums) {
            if (count == 0) candidate = x;
            count += (x == candidate) ? 1 : -1;
        }
        return candidate;
    }
}
```

### 9. [Design HashSet](https://leetcode.com/problems/design-hashset/) — Easy

- [ ] **Revised**
- **Recognition cue:** Direct addressing / separate chaining
- **Approach ladder:** 1. Boolean direct-address table — O(1), uses key-range memory **(preferred for LC constraints)**. 2. Separate chaining — expected O(1), general-purpose. 3. Balanced BST — O(log n).
- **Preferred pattern:** Direct addressing / separate chaining
- **Preferred complexity:** O(1) per operation, O(U) space where U is key range
- **Pitfall:** Direct addressing depends on the documented bounded key range.

```java
class MyHashSet {
    private final boolean[] present = new boolean[1_000_001];
    public void add(int key) { present[key] = true; }
    public void remove(int key) { present[key] = false; }
    public boolean contains(int key) { return present[key]; }
}
```

### 10. [Design HashMap](https://leetcode.com/problems/design-hashmap/) — Easy

- [ ] **Revised**
- **Recognition cue:** Direct addressing
- **Approach ladder:** 1. Array of key-value pairs — O(n) lookup. 2. Separate chaining — expected O(1), general-purpose. 3. Direct-address integer array — O(1) **(preferred for LC constraints)**.
- **Preferred pattern:** Direct addressing
- **Preferred complexity:** O(1) per operation, O(U) space
- **Pitfall:** The sentinel `-1` is valid only because stored values are non-negative in this problem.

```java
class MyHashMap {
    private final int[] values = new int[1_000_001];
    public MyHashMap() { Arrays.fill(values, -1); }
    public void put(int key, int value) { values[key] = value; }
    public int get(int key) { return values[key]; }
    public void remove(int key) { values[key] = -1; }
}
```

### 11. [Sort an Array](https://leetcode.com/problems/sort-an-array/) — Medium

- [ ] **Revised**
- **Recognition cue:** Merge sort
- **Approach ladder:** 1. Insertion sort — O(n²), good for tiny/nearly sorted inputs. 2. Heap sort — O(n log n), O(1). 3. Randomized quicksort — expected O(n log n). 4. Merge sort — guaranteed O(n log n) **(preferred)**.
- **Preferred pattern:** Merge sort
- **Preferred complexity:** O(n log n) time, O(n) space

```java
class Solution {
    public int[] sortArray(int[] nums) {
        int[] tmp = new int[nums.length];
        sort(nums, tmp, 0, nums.length - 1);
        return nums;
    }
    private void sort(int[] a, int[] tmp, int l, int r) {
        if (l >= r) return;
        int m = l + (r - l) / 2;
        sort(a, tmp, l, m); sort(a, tmp, m + 1, r);
        int i = l, j = m + 1, k = l;
        while (i <= m || j <= r) {
            if (j > r || (i <= m && a[i] <= a[j])) tmp[k++] = a[i++];
            else tmp[k++] = a[j++];
        }
        for (i = l; i <= r; i++) a[i] = tmp[i];
    }
}
```

### 12. [Sort Colors](https://leetcode.com/problems/sort-colors/) — Medium

- [ ] **Revised**
- **Recognition cue:** Dutch national flag
- **Approach ladder:** 1. Library sort — O(n log n). 2. Count 0/1/2 then overwrite — O(n), two passes. 3. Dutch national flag — O(n), one pass, O(1) **(preferred)**.
- **Preferred pattern:** Dutch national flag
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** [0, low) are 0s, [low, i) are 1s, and (high, n) are 2s.
- **Pitfall:** After swapping with `high`, do not increment `i`; the incoming value is unclassified.

```java
class Solution {
    public void sortColors(int[] nums) {
        int low = 0, i = 0, high = nums.length - 1;
        while (i <= high) {
            if (nums[i] == 0) swap(nums, low++, i++);
            else if (nums[i] == 2) swap(nums, i, high--);
            else i++;
        }
    }
    private void swap(int[] a, int i, int j) {
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }
}
```

### 13. [Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) — Medium

- [ ] **Revised**
- **Recognition cue:** Frequency map + buckets
- **Approach ladder:** 1. Sort by frequency — O(n log n). 2. Min-heap of size k — O(n log k). 3. Quickselect — expected O(n). 4. Frequency buckets — O(n) **(preferred)**.
- **Preferred pattern:** Frequency map + buckets
- **Preferred complexity:** O(n) time, O(n) space

```java
class Solution {
    public int[] topKFrequent(int[] nums, int k) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int x : nums) freq.merge(x, 1, Integer::sum);
        List<Integer>[] bucket = new List[nums.length + 1];
        for (var e : freq.entrySet()) {
            int f = e.getValue();
            if (bucket[f] == null) bucket[f] = new ArrayList<>();
            bucket[f].add(e.getKey());
        }
        int[] ans = new int[k];
        for (int f = nums.length, p = 0; f >= 1 && p < k; f--)
            if (bucket[f] != null)
                for (int x : bucket[f]) if (p < k) ans[p++] = x;
        return ans;
    }
}
```

### 14. [Encode and Decode Strings](https://leetcode.com/problems/encode-and-decode-strings/) — Medium

- [ ] **Revised**
- **Recognition cue:** Length-prefixed framing
- **Approach ladder:** 1. Escape a delimiter — linear but error-prone. 2. Length prefix (`len#payload`) — linear and unambiguous **(preferred)**.
- **Preferred pattern:** Length-prefixed framing
- **Preferred complexity:** O(total characters) time and output space
- **Pitfall:** The payload may contain the delimiter; only the length determines its boundary.

```java
class Codec {
    public String encode(List<String> strs) {
        StringBuilder out = new StringBuilder();
        for (String s : strs) out.append(s.length()).append('#').append(s);
        return out.toString();
    }
    public List<String> decode(String s) {
        List<String> ans = new ArrayList<>();
        for (int i = 0; i < s.length();) {
            int j = i;
            while (s.charAt(j) != '#') j++;
            int len = Integer.parseInt(s.substring(i, j));
            j++;
            ans.add(s.substring(j, j + len));
            i = j + len;
        }
        return ans;
    }
}
```

### 15. [Range Sum Query 2D Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/) — Medium

- [ ] **Revised**
- **Recognition cue:** 2-D prefix sum
- **Approach ladder:** 1. Sum every query rectangle — O(area) per query. 2. Row-prefix sums — O(rows) per query. 3. 2-D prefix sum — O(1) query **(preferred)**.
- **Preferred pattern:** 2-D prefix sum
- **Preferred complexity:** O(mn) build, O(1) query, O(mn) space

```java
class NumMatrix {
    private final int[][] pre;
    public NumMatrix(int[][] matrix) {
        int m = matrix.length, n = matrix[0].length;
        pre = new int[m + 1][n + 1];
        for (int r = 1; r <= m; r++)
            for (int c = 1; c <= n; c++)
                pre[r][c] = matrix[r - 1][c - 1] + pre[r - 1][c]
                          + pre[r][c - 1] - pre[r - 1][c - 1];
    }
    public int sumRegion(int r1, int c1, int r2, int c2) {
        r2++; c2++;
        return pre[r2][c2] - pre[r1][c2] - pre[r2][c1] + pre[r1][c1];
    }
}
```

### 16. [Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) — Medium

- [ ] **Revised**
- **Recognition cue:** Product excluding self, without division.
- **Approach ladder:** 1. Direct enumeration/simulation — simplest baseline; may be O(n²) or use extra copies. 2. Sorting, hashing, counting, or prefix-state formulation — choose based on whether order must be preserved. 3. **Preferred:** Prefix and suffix products — O(n) time, O(1) extra space excluding output.
- **Preferred pattern:** Prefix and suffix products
- **Preferred complexity:** O(n) time, O(1) extra space excluding output
- **Invariant / state:** Output first stores left products; a rolling suffix multiplies right products.

```java
class Solution {
    public int[] productExceptSelf(int[] nums) {
        int n = nums.length;
        int[] ans = new int[n];
        ans[0] = 1;
        for (int i = 1; i < n; i++) ans[i] = ans[i - 1] * nums[i - 1];
        int suffix = 1;
        for (int i = n - 1; i >= 0; i--) {
            ans[i] *= suffix;
            suffix *= nums[i];
        }
        return ans;
    }
}
```

### 17. [Valid Sudoku](https://leetcode.com/problems/valid-sudoku/) — Medium

- [ ] **Revised**
- **Recognition cue:** Validate uniqueness across rows, columns, and 3x3 boxes.
- **Approach ladder:** 1. Direct enumeration/simulation — simplest baseline; may be O(n²) or use extra copies. 2. Sorting, hashing, counting, or prefix-state formulation — choose based on whether order must be preserved. 3. **Preferred:** Constraint encoding — O(1) time and space for fixed 9x9 board.
- **Preferred pattern:** Constraint encoding
- **Preferred complexity:** O(1) time and space for fixed 9x9 board
- **Invariant / state:** Encode each seen constraint in a set; any repeated encoding is invalid.

```java
class Solution {
    public boolean isValidSudoku(char[][] board) {
        Set<String> seen = new HashSet<>();
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                char x = board[r][c];
                if (x == '.') continue;
                if (!seen.add(x + " in row " + r) ||
                    !seen.add(x + " in col " + c) ||
                    !seen.add(x + " in box " + (r / 3) + '-' + (c / 3))) return false;
            }
        }
        return true;
    }
}
```

### 18. [Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/) — Medium

- [ ] **Revised**
- **Recognition cue:** Find longest run of consecutive integers in O(n).
- **Approach ladder:** 1. Direct enumeration/simulation — simplest baseline; may be O(n²) or use extra copies. 2. Sorting, hashing, counting, or prefix-state formulation — choose based on whether order must be preserved. 3. **Preferred:** Hash-set sequence starts — O(n) expected time, O(n) space.
- **Preferred pattern:** Hash-set sequence starts
- **Preferred complexity:** O(n) expected time, O(n) space
- **Invariant / state:** Only values with no predecessor start a sequence; every value is traversed at most once as a successor.

```java
class Solution {
    public int longestConsecutive(int[] nums) {
        Set<Integer> set = new HashSet<>();
        for (int x : nums) set.add(x);
        int best = 0;
        for (int x : set) {
            if (set.contains(x - 1)) continue;
            int y = x;
            while (set.contains(y)) y++;
            best = Math.max(best, y - x);
        }
        return best;
    }
}
```

### 19. [Best Time to Buy And Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Unlimited non-overlapping transactions.
- **Approach ladder:** 1. Direct enumeration/simulation — simplest baseline; may be O(n²) or use extra copies. 2. Sorting, hashing, counting, or prefix-state formulation — choose based on whether order must be preserved. 3. **Preferred:** Greedy positive deltas — O(n) time, O(1) space.
- **Preferred pattern:** Greedy positive deltas
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Every positive adjacent increase can be collected independently.

```java
class Solution {
    public int maxProfit(int[] prices) {
        int profit = 0;
        for (int i = 1; i < prices.length; i++) {
            if (prices[i] > prices[i - 1]) profit += prices[i] - prices[i - 1];
        }
        return profit;
    }
}
```

### 20. [Majority Element II](https://leetcode.com/problems/majority-element-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Generalized Boyer-Moore voting
- **Approach ladder:** 1. Frequency map — O(n) space. 2. Sort and inspect candidates — O(n log n). 3. Two-candidate Boyer-Moore + verification — O(n), O(1) **(preferred)**.
- **Preferred pattern:** Generalized Boyer-Moore voting
- **Preferred complexity:** O(n) time, O(1) auxiliary space
- **Pitfall:** Voting yields candidates, not guaranteed winners; always verify counts.

```java
class Solution {
    public List<Integer> majorityElement(int[] nums) {
        int a = 0, b = 1, ca = 0, cb = 0;
        for (int x : nums) {
            if (x == a) ca++;
            else if (x == b) cb++;
            else if (ca == 0) { a = x; ca = 1; }
            else if (cb == 0) { b = x; cb = 1; }
            else { ca--; cb--; }
        }
        ca = cb = 0;
        for (int x : nums) { if (x == a) ca++; else if (x == b) cb++; }
        List<Integer> ans = new ArrayList<>();
        if (ca > nums.length / 3) ans.add(a);
        if (cb > nums.length / 3) ans.add(b);
        return ans;
    }
}
```

### 21. [Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) — Medium

- [ ] **Revised**
- **Recognition cue:** Prefix sum frequency map
- **Approach ladder:** 1. Enumerate all subarrays — O(n²). 2. Prefix sums + nested loops — O(n²). 3. Prefix-frequency map — expected O(n) **(preferred)**.
- **Preferred pattern:** Prefix sum frequency map
- **Preferred complexity:** Expected O(n) time, O(n) space
- **Invariant / state:** For current prefix sum `sum`, every earlier prefix `sum-k` starts a valid subarray.
- **Pitfall:** Seed prefix sum 0 with frequency 1.

```java
class Solution {
    public int subarraySum(int[] nums, int k) {
        Map<Integer, Integer> count = new HashMap<>();
        count.put(0, 1);
        int sum = 0, ans = 0;
        for (int x : nums) {
            sum += x;
            ans += count.getOrDefault(sum - k, 0);
            count.merge(sum, 1, Integer::sum);
        }
        return ans;
    }
}
```

### 22. [First Missing Positive](https://leetcode.com/problems/first-missing-positive/) — Hard

- [ ] **Revised**
- **Recognition cue:** Index placement / cyclic sort
- **Approach ladder:** 1. HashSet — O(n) time, O(n) space. 2. Sort — O(n log n). 3. Mark presence in-place. 4. Place value x at index x-1 — O(n), O(1) **(preferred)**.
- **Preferred pattern:** Index placement / cyclic sort
- **Preferred complexity:** O(n) time, O(1) space
- **Pitfall:** The duplicate check prevents an infinite swap loop.

```java
class Solution {
    public int firstMissingPositive(int[] nums) {
        int n = nums.length;
        for (int i = 0; i < n; i++) {
            while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                int j = nums[i] - 1;
                int t = nums[i]; nums[i] = nums[j]; nums[j] = t;
            }
        }
        for (int i = 0; i < n; i++) if (nums[i] != i + 1) return i + 1;
        return n + 1;
    }
}
```

---

## Two Pointers

### 23. [Reverse String](https://leetcode.com/problems/reverse-string/) — Easy

- [ ] **Revised**
- **Recognition cue:** Two pointers
- **Approach ladder:** 1. Extra reversed buffer — O(n) space. 2. Swap symmetric positions in-place — O(n), O(1) **(preferred)**.
- **Preferred pattern:** Two pointers
- **Preferred complexity:** O(n) time, O(1) space

```java
class Solution {
    public void reverseString(char[] s) {
        for (int l = 0, r = s.length - 1; l < r; l++, r--) {
            char t = s[l]; s[l] = s[r]; s[r] = t;
        }
    }
}
```

### 24. [Valid Palindrome](https://leetcode.com/problems/valid-palindrome/) — Easy

- [ ] **Revised**
- **Recognition cue:** Compare normalized characters from both ends.
- **Approach ladder:** 1. Enumerate candidate pairs/ranges — usually O(n²). 2. Use an auxiliary buffer, set, or sort-and-scan trade-off. 3. **Preferred:** Converging pointers — O(n) time, O(1) space.
- **Preferred pattern:** Converging pointers
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Everything outside [left, right] has already matched.

```java
class Solution {
    public boolean isPalindrome(String s) {
        int l = 0, r = s.length() - 1;
        while (l < r) {
            while (l < r && !Character.isLetterOrDigit(s.charAt(l))) l++;
            while (l < r && !Character.isLetterOrDigit(s.charAt(r))) r--;
            if (Character.toLowerCase(s.charAt(l++)) != Character.toLowerCase(s.charAt(r--)))
                return false;
        }
        return true;
    }
}
```

### 25. [Valid Palindrome II](https://leetcode.com/problems/valid-palindrome-ii/) — Easy

- [ ] **Revised**
- **Recognition cue:** Two pointers + one deletion branch
- **Approach ladder:** 1. Delete each position and test — O(n²). 2. On first mismatch, test skipping left or right — O(n) **(preferred)**.
- **Preferred pattern:** Two pointers + one deletion branch
- **Preferred complexity:** O(n) time, O(1) space
- **Pitfall:** Branch only once—at the first mismatch.

```java
class Solution {
    public boolean validPalindrome(String s) {
        int l = 0, r = s.length() - 1;
        while (l < r && s.charAt(l) == s.charAt(r)) { l++; r--; }
        return l >= r || pal(s, l + 1, r) || pal(s, l, r - 1);
    }
    private boolean pal(String s, int l, int r) {
        while (l < r) if (s.charAt(l++) != s.charAt(r--)) return false;
        return true;
    }
}
```

### 26. [Merge Strings Alternately](https://leetcode.com/problems/merge-strings-alternately/) — Easy

- [ ] **Revised**
- **Recognition cue:** Two read pointers
- **Approach ladder:** 1. Repeated string concatenation — potentially O(n²). 2. StringBuilder with two indices — O(m+n) **(preferred)**.
- **Preferred pattern:** Two read pointers
- **Preferred complexity:** O(m+n) time, O(m+n) output space

```java
class Solution {
    public String mergeAlternately(String a, String b) {
        StringBuilder out = new StringBuilder(a.length() + b.length());
        for (int i = 0; i < a.length() || i < b.length(); i++) {
            if (i < a.length()) out.append(a.charAt(i));
            if (i < b.length()) out.append(b.charAt(i));
        }
        return out.toString();
    }
}
```

### 27. [Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/) — Easy

- [ ] **Revised**
- **Recognition cue:** Two sorted arrays; nums1 has trailing capacity.
- **Approach ladder:** 1. Enumerate candidate pairs/ranges — usually O(n²). 2. Use an auxiliary buffer, set, or sort-and-scan trade-off. 3. **Preferred:** Reverse merge / two pointers — O(m+n) time, O(1) space.
- **Preferred pattern:** Reverse merge / two pointers
- **Preferred complexity:** O(m+n) time, O(1) space
- **Invariant / state:** Write from the back so unread nums1 values are never overwritten.
- **Pitfall:** Only nums2 leftovers must be copied; nums1 leftovers are already placed.

```java
class Solution {
    public void merge(int[] nums1, int m, int[] nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (j >= 0) {
            if (i >= 0 && nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
            else nums1[k--] = nums2[j--];
        }
    }
}
```

### 28. [Remove Duplicates From Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) — Easy

- [ ] **Revised**
- **Recognition cue:** Sorted input; retain one copy of each value.
- **Approach ladder:** 1. Enumerate candidate pairs/ranges — usually O(n²). 2. Use an auxiliary buffer, set, or sort-and-scan trade-off. 3. **Preferred:** Sorted-array write pointer — O(n) time, O(1) space.
- **Preferred pattern:** Sorted-array write pointer
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** nums[0..write] is the unique prefix.

```java
class Solution {
    public int removeDuplicates(int[] nums) {
        if (nums.length == 0) return 0;
        int write = 0;
        for (int read = 1; read < nums.length; read++) {
            if (nums[read] != nums[write]) nums[++write] = nums[read];
        }
        return write + 1;
    }
}
```

### 29. [Two Sum II Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) — Medium

- [ ] **Revised**
- **Recognition cue:** Sorted array and a target pair.
- **Approach ladder:** 1. Enumerate candidate pairs/ranges — usually O(n²). 2. Use an auxiliary buffer, set, or sort-and-scan trade-off. 3. **Preferred:** Opposite-direction pointers — O(n) time, O(1) space.
- **Preferred pattern:** Opposite-direction pointers
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** A sum below target requires a larger left value; above target requires a smaller right value.

```java
class Solution {
    public int[] twoSum(int[] numbers, int target) {
        int l = 0, r = numbers.length - 1;
        while (l < r) {
            int sum = numbers[l] + numbers[r];
            if (sum == target) return new int[]{l + 1, r + 1};
            if (sum < target) l++; else r--;
        }
        return new int[0];
    }
}
```

### 30. [3Sum](https://leetcode.com/problems/3sum/) — Medium

- [ ] **Revised**
- **Recognition cue:** Find unique triples meeting a sum target.
- **Approach ladder:** 1. Enumerate candidate pairs/ranges — usually O(n²). 2. Use an auxiliary buffer, set, or sort-and-scan trade-off. 3. **Preferred:** Sort + fixed element + two pointers — O(n^2) time, O(log n) sort stack.
- **Preferred pattern:** Sort + fixed element + two pointers
- **Preferred complexity:** O(n^2) time, O(log n) sort stack
- **Invariant / state:** After fixing i, the sorted suffix supports monotonic pointer movement.

```java
class Solution {
    public List<List<Integer>> threeSum(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> ans = new ArrayList<>();
        for (int i = 0; i < nums.length - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            if (nums[i] > 0) break;
            int l = i + 1, r = nums.length - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum < 0) l++;
                else if (sum > 0) r--;
                else {
                    ans.add(List.of(nums[i], nums[l], nums[r]));
                    int left = nums[l], right = nums[r];
                    while (l < r && nums[l] == left) l++;
                    while (l < r && nums[r] == right) r--;
                }
            }
        }
        return ans;
    }
}
```

### 31. [4Sum](https://leetcode.com/problems/4sum/) — Medium

- [ ] **Revised**
- **Recognition cue:** Sort + fixed pair + two pointers
- **Approach ladder:** 1. Four loops — O(n⁴). 2. Pair-sum hash map — O(n²) space with duplicate complexity. 3. Sort, fix two values, two-pointer remainder — O(n³) **(preferred)**.
- **Preferred pattern:** Sort + fixed pair + two pointers
- **Preferred complexity:** O(n³) time, O(log n) sorting stack excluding output
- **Pitfall:** Use `long` for the four-value sum.

```java
class Solution {
    public List<List<Integer>> fourSum(int[] nums, int target) {
        Arrays.sort(nums);
        List<List<Integer>> ans = new ArrayList<>();
        int n = nums.length;
        for (int i = 0; i < n - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                int l = j + 1, r = n - 1;
                while (l < r) {
                    long sum = (long) nums[i] + nums[j] + nums[l] + nums[r];
                    if (sum < target) l++;
                    else if (sum > target) r--;
                    else {
                        ans.add(List.of(nums[i], nums[j], nums[l], nums[r]));
                        int x = nums[l], y = nums[r];
                        while (l < r && nums[l] == x) l++;
                        while (l < r && nums[r] == y) r--;
                    }
                }
            }
        }
        return ans;
    }
}
```

### 32. [Rotate Array](https://leetcode.com/problems/rotate-array/) — Medium

- [ ] **Revised**
- **Recognition cue:** Rotate an array right by k in-place.
- **Approach ladder:** 1. Enumerate candidate pairs/ranges — usually O(n²). 2. Use an auxiliary buffer, set, or sort-and-scan trade-off. 3. **Preferred:** Three reversals — O(n) time, O(1) space.
- **Preferred pattern:** Three reversals
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Reverse all, then reverse the first k and remaining n-k elements.
- **Pitfall:** Normalize k with modulo; guard empty arrays outside LeetCode constraints.

```java
class Solution {
    public void rotate(int[] nums, int k) {
        int n = nums.length;
        k %= n;
        reverse(nums, 0, n - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, n - 1);
    }
    private void reverse(int[] a, int l, int r) {
        while (l < r) {
            int t = a[l]; a[l++] = a[r]; a[r--] = t;
        }
    }
}
```

### 33. [Container With Most Water](https://leetcode.com/problems/container-with-most-water/) — Medium

- [ ] **Revised**
- **Recognition cue:** Maximize width * min(boundary heights).
- **Approach ladder:** 1. Enumerate candidate pairs/ranges — usually O(n²). 2. Use an auxiliary buffer, set, or sort-and-scan trade-off. 3. **Preferred:** Greedy two pointers — O(n) time, O(1) space.
- **Preferred pattern:** Greedy two pointers
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Moving the taller side cannot improve the limiting height; move the shorter side.

```java
class Solution {
    public int maxArea(int[] height) {
        int l = 0, r = height.length - 1, best = 0;
        while (l < r) {
            best = Math.max(best, (r - l) * Math.min(height[l], height[r]));
            if (height[l] <= height[r]) l++; else r--;
        }
        return best;
    }
}
```

### 34. [Boats to Save People](https://leetcode.com/problems/boats-to-save-people/) — Medium

- [ ] **Revised**
- **Recognition cue:** Sort + greedy pairing
- **Approach ladder:** 1. Search all pairings — exponential. 2. Sort; always place heaviest, pair with lightest when possible — O(n log n) **(preferred)**.
- **Preferred pattern:** Sort + greedy pairing
- **Preferred complexity:** O(n log n) time, O(log n) sorting stack
- **Invariant / state:** The current heaviest person must consume one boat; only the lightest can be the best feasible partner.

```java
class Solution {
    public int numRescueBoats(int[] people, int limit) {
        Arrays.sort(people);
        int l = 0, r = people.length - 1, boats = 0;
        while (l <= r) {
            if (people[l] + people[r] <= limit) l++;
            r--; boats++;
        }
        return boats;
    }
}
```

### 35. [Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) — Hard

- [ ] **Revised**
- **Recognition cue:** Water above index is bounded by min(maxLeft, maxRight).
- **Approach ladder:** 1. Enumerate candidate pairs/ranges — usually O(n²). 2. Use an auxiliary buffer, set, or sort-and-scan trade-off. 3. **Preferred:** Two pointers with boundary maxima — O(n) time, O(1) space.
- **Preferred pattern:** Two pointers with boundary maxima
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** The lower boundary side can be finalized without knowing future values on the higher side.

```java
class Solution {
    public int trap(int[] height) {
        int l = 0, r = height.length - 1, leftMax = 0, rightMax = 0, water = 0;
        while (l < r) {
            if (height[l] <= height[r]) {
                leftMax = Math.max(leftMax, height[l]);
                water += leftMax - height[l++];
            } else {
                rightMax = Math.max(rightMax, height[r]);
                water += rightMax - height[r--];
            }
        }
        return water;
    }
}
```

---

## Sliding Window

### 36. [Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/) — Easy

- [ ] **Revised**
- **Recognition cue:** Equal values must occur within index distance k.
- **Approach ladder:** 1. Recompute every substring/window — usually O(n²) or O(nk). 2. Prefix counts or ordered structures when the window is fixed/offline. 3. **Preferred:** Last index / bounded window — O(n) time, O(n) space.
- **Preferred pattern:** Last index / bounded window
- **Preferred complexity:** O(n) time, O(n) space
- **Invariant / state:** Store the latest position; any earlier position is dominated.

```java
class Solution {
    public boolean containsNearbyDuplicate(int[] nums, int k) {
        Map<Integer, Integer> last = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            Integer prev = last.put(nums[i], i);
            if (prev != null && i - prev <= k) return true;
        }
        return false;
    }
}
```

### 37. [Best Time to Buy And Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) — Easy

- [ ] **Revised**
- **Recognition cue:** One buy followed by one sell.
- **Approach ladder:** 1. Recompute every substring/window — usually O(n²) or O(nk). 2. Prefix counts or ordered structures when the window is fixed/offline. 3. **Preferred:** Running minimum — O(n) time, O(1) space.
- **Preferred pattern:** Running minimum
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** At each day, compute profit against the minimum price seen earlier.

```java
class Solution {
    public int maxProfit(int[] prices) {
        int minPrice = Integer.MAX_VALUE, best = 0;
        for (int p : prices) {
            minPrice = Math.min(minPrice, p);
            best = Math.max(best, p - minPrice);
        }
        return best;
    }
}
```

### 38. [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) — Medium

- [ ] **Revised**
- **Recognition cue:** Longest substring satisfying character uniqueness.
- **Approach ladder:** 1. Recompute every substring/window — usually O(n²) or O(nk). 2. Prefix counts or ordered structures when the window is fixed/offline. 3. **Preferred:** Last-position window — O(n) time, O(character set) space.
- **Preferred pattern:** Last-position window
- **Preferred complexity:** O(n) time, O(character set) space
- **Invariant / state:** left is one past the latest conflicting occurrence within the current window.

```java
class Solution {
    public int lengthOfLongestSubstring(String s) {
        Map<Character, Integer> last = new HashMap<>();
        int left = 0, best = 0;
        for (int right = 0; right < s.length(); right++) {
            char c = s.charAt(right);
            if (last.containsKey(c)) left = Math.max(left, last.get(c) + 1);
            last.put(c, right);
            best = Math.max(best, right - left + 1);
        }
        return best;
    }
}
```

### 39. [Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) — Medium

- [ ] **Revised**
- **Recognition cue:** Variable window + max frequency
- **Approach ladder:** 1. Enumerate substrings — O(n²). 2. Window with recomputed max count — O(26n). 3. Window with monotone historical max frequency — O(n) **(preferred)**.
- **Preferred pattern:** Variable window + max frequency
- **Preferred complexity:** O(n) time, O(1) space for fixed alphabet
- **Pitfall:** `maxFreq` need not decrease; it is an upper bound sufficient for maximizing window length.

```java
class Solution {
    public int characterReplacement(String s, int k) {
        int[] freq = new int[26];
        int left = 0, maxFreq = 0, ans = 0;
        for (int right = 0; right < s.length(); right++) {
            maxFreq = Math.max(maxFreq, ++freq[s.charAt(right) - 'A']);
            while (right - left + 1 - maxFreq > k)
                freq[s.charAt(left++) - 'A']--;
            ans = Math.max(ans, right - left + 1);
        }
        return ans;
    }
}
```

### 40. [Permutation In String](https://leetcode.com/problems/permutation-in-string/) — Medium

- [ ] **Revised**
- **Recognition cue:** Fixed-size frequency window
- **Approach ladder:** 1. Sort every length-m substring — O(n·m log m). 2. Compare 26-count arrays per window — O(26n). 3. Maintain matched character counts — O(n) **(preferred)**.
- **Preferred pattern:** Fixed-size frequency window
- **Preferred complexity:** O(n) time, O(1) space

```java
class Solution {
    public boolean checkInclusion(String s1, String s2) {
        if (s1.length() > s2.length()) return false;
        int[] a = new int[26], b = new int[26];
        for (int i = 0; i < s1.length(); i++) {
            a[s1.charAt(i) - 'a']++;
            b[s2.charAt(i) - 'a']++;
        }
        int matches = 0;
        for (int i = 0; i < 26; i++) if (a[i] == b[i]) matches++;
        if (matches == 26) return true;
        for (int r = s1.length(); r < s2.length(); r++) {
            int in = s2.charAt(r) - 'a', out = s2.charAt(r - s1.length()) - 'a';
            if (a[in] == b[in]) matches--; b[in]++; if (a[in] == b[in]) matches++;
            if (a[out] == b[out]) matches--; b[out]--; if (a[out] == b[out]) matches++;
            if (matches == 26) return true;
        }
        return false;
    }
}
```

### 41. [Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) — Medium

- [ ] **Revised**
- **Recognition cue:** Find the shortest contiguous window meeting a lower-bound sum.
- **Approach ladder:** 1. Recompute every substring/window — usually O(n²) or O(nk). 2. Prefix counts or ordered structures when the window is fixed/offline. 3. **Preferred:** Variable window with positive values — O(n) time, O(1) space.
- **Preferred pattern:** Variable window with positive values
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Positive values make sum monotonic when either boundary moves.
- **Pitfall:** This exact shrink rule relies on all nums being positive.

```java
class Solution {
    public int minSubArrayLen(int target, int[] nums) {
        int left = 0, sum = 0, best = Integer.MAX_VALUE;
        for (int right = 0; right < nums.length; right++) {
            sum += nums[right];
            while (sum >= target) {
                best = Math.min(best, right - left + 1);
                sum -= nums[left++];
            }
        }
        return best == Integer.MAX_VALUE ? 0 : best;
    }
}
```

### 42. [Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/) — Medium

- [ ] **Revised**
- **Recognition cue:** Binary search the answer window
- **Approach ladder:** 1. Sort by distance — O(n log n). 2. Max-heap size k — O(n log k). 3. Binary-search left boundary of sorted length-k window — O(log(n-k)+k) **(preferred)**.
- **Preferred pattern:** Binary search the answer window
- **Preferred complexity:** O(log(n-k)+k) time, O(k) output space
- **Pitfall:** Compare the two elements just outside competing windows: `arr[mid]` and `arr[mid+k]`.

```java
class Solution {
    public List<Integer> findClosestElements(int[] arr, int k, int x) {
        int lo = 0, hi = arr.length - k;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (x - arr[mid] > arr[mid + k] - x) lo = mid + 1;
            else hi = mid;
        }
        List<Integer> ans = new ArrayList<>(k);
        for (int i = lo; i < lo + k; i++) ans.add(arr[i]);
        return ans;
    }
}
```

### 43. [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) — Hard

- [ ] **Revised**
- **Recognition cue:** Smallest substring covering a character multiset.
- **Approach ladder:** 1. Recompute every substring/window — usually O(n²) or O(nk). 2. Prefix counts or ordered structures when the window is fixed/offline. 3. **Preferred:** Deficit-count sliding window — O(n) time, O(character set) space.
- **Preferred pattern:** Deficit-count sliding window
- **Preferred complexity:** O(n) time, O(character set) space
- **Invariant / state:** missing counts total required characters not yet covered; surplus characters may remain.

```java
class Solution {
    public String minWindow(String s, String t) {
        if (t.length() > s.length()) return "";
        int[] need = new int[128];
        for (char c : t.toCharArray()) need[c]++;
        int missing = t.length(), left = 0, bestStart = 0, bestLen = Integer.MAX_VALUE;
        for (int right = 0; right < s.length(); right++) {
            char c = s.charAt(right);
            if (need[c]-- > 0) missing--;
            while (missing == 0) {
                if (right - left + 1 < bestLen) {
                    bestLen = right - left + 1;
                    bestStart = left;
                }
                char drop = s.charAt(left++);
                if (++need[drop] > 0) missing++;
            }
        }
        return bestLen == Integer.MAX_VALUE ? "" : s.substring(bestStart, bestStart + bestLen);
    }
}
```

### 44. [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) — Hard

- [ ] **Revised**
- **Recognition cue:** Monotonic deque
- **Approach ladder:** 1. Scan each window — O(nk). 2. Heap with lazy expiry — O(n log n). 3. Monotonic deque of indices — O(n) **(preferred)**.
- **Preferred pattern:** Monotonic deque
- **Preferred complexity:** O(n) time, O(k) space
- **Invariant / state:** Deque indices stay in-window and values decrease from front to back.

```java
class Solution {
    public int[] maxSlidingWindow(int[] nums, int k) {
        int[] ans = new int[nums.length - k + 1];
        Deque<Integer> dq = new ArrayDeque<>();
        for (int r = 0; r < nums.length; r++) {
            while (!dq.isEmpty() && dq.peekFirst() <= r - k) dq.removeFirst();
            while (!dq.isEmpty() && nums[dq.peekLast()] <= nums[r]) dq.removeLast();
            dq.addLast(r);
            if (r >= k - 1) ans[r - k + 1] = nums[dq.peekFirst()];
        }
        return ans;
    }
}
```

---

## Stack

### 45. [Baseball Game](https://leetcode.com/problems/baseball-game/) — Easy

- [ ] **Revised**
- **Recognition cue:** Stack simulation
- **Approach ladder:** 1. Keep all valid scores in a stack/list and simulate — O(n) **(preferred)**.
- **Preferred pattern:** Stack simulation
- **Preferred complexity:** O(n) time, O(n) space

```java
class Solution {
    public int calPoints(String[] operations) {
        List<Integer> scores = new ArrayList<>();
        for (String op : operations) {
            int n = scores.size();
            switch (op) {
                case "+" -> scores.add(scores.get(n - 1) + scores.get(n - 2));
                case "D" -> scores.add(2 * scores.get(n - 1));
                case "C" -> scores.remove(n - 1);
                default -> scores.add(Integer.parseInt(op));
            }
        }
        int sum = 0; for (int x : scores) sum += x; return sum;
    }
}
```

### 46. [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/) — Easy

- [ ] **Revised**
- **Recognition cue:** Nested delimiters must close in LIFO order.
- **Approach ladder:** 1. Repeated rescans or direct simulation — can degrade to O(n²). 2. Explicit stack/deque or recursive parsing. 3. **Preferred:** Matching stack — O(n) time, O(n) space.
- **Preferred pattern:** Matching stack
- **Preferred complexity:** O(n) time, O(n) space
- **Invariant / state:** Stack contains unmatched opening delimiters.

```java
class Solution {
    public boolean isValid(String s) {
        Deque<Character> stack = new ArrayDeque<>();
        for (char c : s.toCharArray()) {
            if (c == '(') stack.push(')');
            else if (c == '[') stack.push(']');
            else if (c == '{') stack.push('}');
            else if (stack.isEmpty() || stack.pop() != c) return false;
        }
        return stack.isEmpty();
    }
}
```

### 47. [Implement Stack Using Queues](https://leetcode.com/problems/implement-stack-using-queues/) — Easy

- [ ] **Revised**
- **Recognition cue:** Queue rotation
- **Approach ladder:** 1. Two queues: costly pop or costly push. 2. One queue, rotate after each push so front is stack top — O(n) push, O(1) pop **(preferred compact design)**.
- **Preferred pattern:** Queue rotation
- **Preferred complexity:** Push O(n); pop/top O(1); O(n) space

```java
class MyStack {
    private final Queue<Integer> q = new ArrayDeque<>();
    public void push(int x) {
        q.add(x);
        for (int i = 1; i < q.size(); i++) q.add(q.remove());
    }
    public int pop() { return q.remove(); }
    public int top() { return q.element(); }
    public boolean empty() { return q.isEmpty(); }
}
```

### 48. [Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/) — Easy

- [ ] **Revised**
- **Recognition cue:** Two-stack amortization
- **Approach ladder:** 1. Move elements on every operation — O(n). 2. Input/output stacks with lazy transfer — amortized O(1) **(preferred)**.
- **Preferred pattern:** Two-stack amortization
- **Preferred complexity:** Amortized O(1) per operation, O(n) space

```java
class MyQueue {
    private final Deque<Integer> in = new ArrayDeque<>(), out = new ArrayDeque<>();
    public void push(int x) { in.push(x); }
    public int pop() { move(); return out.pop(); }
    public int peek() { move(); return out.peek(); }
    public boolean empty() { return in.isEmpty() && out.isEmpty(); }
    private void move() { if (out.isEmpty()) while (!in.isEmpty()) out.push(in.pop()); }
}
```

### 49. [Min Stack](https://leetcode.com/problems/min-stack/) — Medium

- [ ] **Revised**
- **Recognition cue:** Stack operations plus O(1) minimum query.
- **Approach ladder:** 1. Repeated rescans or direct simulation — can degrade to O(n²). 2. Explicit stack/deque or recursive parsing. 3. **Preferred:** Auxiliary monotonic state — O(1) per operation, O(n) space.
- **Preferred pattern:** Auxiliary monotonic state
- **Preferred complexity:** O(1) per operation, O(n) space
- **Invariant / state:** Each element stores the minimum at or below its depth.

```java
class MinStack {
    private final Deque<int[]> stack = new ArrayDeque<>();
    public void push(int val) {
        int min = stack.isEmpty() ? val : Math.min(val, stack.peek()[1]);
        stack.push(new int[]{val, min});
    }
    public void pop() { stack.pop(); }
    public int top() { return stack.peek()[0]; }
    public int getMin() { return stack.peek()[1]; }
}
```

### 50. [Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/) — Medium

- [ ] **Revised**
- **Recognition cue:** Postfix expression evaluation.
- **Approach ladder:** 1. Repeated rescans or direct simulation — can degrade to O(n²). 2. Explicit stack/deque or recursive parsing. 3. **Preferred:** Operand stack — O(n) time, O(n) space.
- **Preferred pattern:** Operand stack
- **Preferred complexity:** O(n) time, O(n) space
- **Invariant / state:** On an operator, pop right operand first, then left operand.

```java
class Solution {
    public int evalRPN(String[] tokens) {
        Deque<Integer> stack = new ArrayDeque<>();
        for (String t : tokens) {
            switch (t) {
                case "+" -> stack.push(stack.pop() + stack.pop());
                case "*" -> stack.push(stack.pop() * stack.pop());
                case "-" -> { int b = stack.pop(), a = stack.pop(); stack.push(a - b); }
                case "/" -> { int b = stack.pop(), a = stack.pop(); stack.push(a / b); }
                default -> stack.push(Integer.parseInt(t));
            }
        }
        return stack.pop();
    }
}
```

### 51. [Asteroid Collision](https://leetcode.com/problems/asteroid-collision/) — Medium

- [ ] **Revised**
- **Recognition cue:** Monotonic collision stack
- **Approach ladder:** 1. Repeatedly scan and erase collisions — O(n²). 2. Stack of surviving asteroids — O(n) **(preferred)**.
- **Preferred pattern:** Monotonic collision stack
- **Preferred complexity:** O(n) time, O(n) space
- **Pitfall:** Only a positive survivor followed by a negative asteroid can collide.

```java
class Solution {
    public int[] asteroidCollision(int[] asteroids) {
        Deque<Integer> st = new ArrayDeque<>();
        for (int x : asteroids) {
            boolean alive = true;
            while (alive && x < 0 && !st.isEmpty() && st.peekLast() > 0) {
                int top = st.peekLast();
                if (top < -x) st.removeLast();
                else { if (top == -x) st.removeLast(); alive = false; }
            }
            if (alive) st.addLast(x);
        }
        int[] ans = new int[st.size()]; int i = 0;
        for (int x : st) ans[i++] = x;
        return ans;
    }
}
```

### 52. [Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) — Medium

- [ ] **Revised**
- **Recognition cue:** Monotonic decreasing stack
- **Approach ladder:** 1. Scan forward from every day — O(n²). 2. Jump using previously computed answers — O(n) amortized. 3. Monotonic stack of unresolved indices — O(n) **(preferred)**.
- **Preferred pattern:** Monotonic decreasing stack
- **Preferred complexity:** O(n) time, O(n) space

```java
class Solution {
    public int[] dailyTemperatures(int[] t) {
        int[] ans = new int[t.length];
        Deque<Integer> st = new ArrayDeque<>();
        for (int i = 0; i < t.length; i++) {
            while (!st.isEmpty() && t[i] > t[st.peek()]) {
                int j = st.pop(); ans[j] = i - j;
            }
            st.push(i);
        }
        return ans;
    }
}
```

### 53. [Online Stock Span](https://leetcode.com/problems/online-stock-span/) — Medium

- [ ] **Revised**
- **Recognition cue:** Monotonic stack with compressed spans
- **Approach ladder:** 1. Scan backward through all prices — O(n) per call. 2. Stack `(price, accumulated span)` — amortized O(1) **(preferred)**.
- **Preferred pattern:** Monotonic stack with compressed spans
- **Preferred complexity:** Amortized O(1) per call, O(n) space

```java
class StockSpanner {
    private final Deque<int[]> st = new ArrayDeque<>();
    public int next(int price) {
        int span = 1;
        while (!st.isEmpty() && st.peek()[0] <= price) span += st.pop()[1];
        st.push(new int[]{price, span});
        return span;
    }
}
```

### 54. [Car Fleet](https://leetcode.com/problems/car-fleet/) — Medium

- [ ] **Revised**
- **Recognition cue:** Sort by position + monotonic arrival times
- **Approach ladder:** 1. Simulate motion/events. 2. Sort cars by position descending; count strictly increasing arrival times — O(n log n) **(preferred)**.
- **Preferred pattern:** Sort by position + monotonic arrival times
- **Preferred complexity:** O(n log n) time, O(n) space
- **Invariant / state:** A car joins the fleet ahead when its solo arrival time is no greater than that fleet’s time.

```java
class Solution {
    public int carFleet(int target, int[] position, int[] speed) {
        Integer[] idx = new Integer[position.length];
        for (int i = 0; i < idx.length; i++) idx[i] = i;
        Arrays.sort(idx, (i, j) -> Integer.compare(position[j], position[i]));
        int fleets = 0; double slowest = -1;
        for (int i : idx) {
            double time = (double) (target - position[i]) / speed[i];
            if (time > slowest) { fleets++; slowest = time; }
        }
        return fleets;
    }
}
```

### 55. [Simplify Path](https://leetcode.com/problems/simplify-path/) — Medium

- [ ] **Revised**
- **Recognition cue:** Normalize an absolute Unix path.
- **Approach ladder:** 1. Repeated rescans or direct simulation — can degrade to O(n²). 2. Explicit stack/deque or recursive parsing. 3. **Preferred:** Token stack — O(n) time, O(n) space.
- **Preferred pattern:** Token stack
- **Preferred complexity:** O(n) time, O(n) space
- **Invariant / state:** Stack stores the canonical directory sequence; '.' does nothing and '..' pops when possible.

```java
class Solution {
    public String simplifyPath(String path) {
        Deque<String> stack = new ArrayDeque<>();
        for (String part : path.split("/+")) {
            if (part.isEmpty() || part.equals(".")) continue;
            if (part.equals("..")) {
                if (!stack.isEmpty()) stack.removeLast();
            } else stack.addLast(part);
        }
        return "/" + String.join("/", stack);
    }
}
```

### 56. [Decode String](https://leetcode.com/problems/decode-string/) — Medium

- [ ] **Revised**
- **Recognition cue:** Stack / recursive descent parsing
- **Approach ladder:** 1. Recursive parser with shared index — O(output). 2. Two stacks for counts and partial strings — O(output) **(preferred iterative)**.
- **Preferred pattern:** Stack / recursive descent parsing
- **Preferred complexity:** O(decoded output length) time and space

```java
class Solution {
    public String decodeString(String s) {
        Deque<Integer> counts = new ArrayDeque<>();
        Deque<StringBuilder> parts = new ArrayDeque<>();
        StringBuilder cur = new StringBuilder(); int num = 0;
        for (char ch : s.toCharArray()) {
            if (Character.isDigit(ch)) num = num * 10 + ch - '0';
            else if (ch == '[') { counts.push(num); parts.push(cur); num = 0; cur = new StringBuilder(); }
            else if (ch == ']') {
                int repeat = counts.pop(); StringBuilder parent = parts.pop();
                while (repeat-- > 0) parent.append(cur);
                cur = parent;
            } else cur.append(ch);
        }
        return cur.toString();
    }
}
```

### 57. [Maximum Frequency Stack](https://leetcode.com/problems/maximum-frequency-stack/) — Hard

- [ ] **Revised**
- **Recognition cue:** Frequency map + stacks by frequency
- **Approach ladder:** 1. Priority queue `(frequency, timestamp)` — O(log n). 2. Map value→frequency and frequency→stack; track max frequency — O(1) **(preferred)**.
- **Preferred pattern:** Frequency map + stacks by frequency
- **Preferred complexity:** O(1) average push/pop, O(n) space

```java
class FreqStack {
    private final Map<Integer, Integer> freq = new HashMap<>();
    private final Map<Integer, Deque<Integer>> groups = new HashMap<>();
    private int maxFreq = 0;
    public void push(int val) {
        int f = freq.merge(val, 1, Integer::sum);
        maxFreq = Math.max(maxFreq, f);
        groups.computeIfAbsent(f, z -> new ArrayDeque<>()).push(val);
    }
    public int pop() {
        int val = groups.get(maxFreq).pop();
        freq.put(val, freq.get(val) - 1);
        if (groups.get(maxFreq).isEmpty()) maxFreq--;
        return val;
    }
}
```

### 58. [Largest Rectangle In Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) — Hard

- [ ] **Revised**
- **Recognition cue:** Monotonic increasing stack
- **Approach ladder:** 1. Expand from every bar — O(n²). 2. Divide and conquer — average O(n log n), worst O(n²). 3. Monotonic stack of start indices — O(n) **(preferred)**.
- **Preferred pattern:** Monotonic increasing stack
- **Preferred complexity:** O(n) time, O(n) space
- **Invariant / state:** Each stack bar stores the earliest index where its height can extend.
- **Pitfall:** Append a virtual zero-height sentinel to flush remaining bars.

```java
class Solution {
    public int largestRectangleArea(int[] heights) {
        Deque<int[]> st = new ArrayDeque<>();
        int best = 0;
        for (int i = 0; i <= heights.length; i++) {
            int h = i == heights.length ? 0 : heights[i];
            int start = i;
            while (!st.isEmpty() && st.peek()[1] > h) {
                int[] p = st.pop();
                best = Math.max(best, p[1] * (i - p[0]));
                start = p[0];
            }
            st.push(new int[]{start, h});
        }
        return best;
    }
}
```

---

## Binary Search

### 59. [Binary Search](https://leetcode.com/problems/binary-search/) — Easy

- [ ] **Revised**
- **Recognition cue:** Classic binary search
- **Approach ladder:** 1. Linear scan — O(n). 2. Iterative or recursive binary search — O(log n) **(preferred iterative)**.
- **Preferred pattern:** Classic binary search
- **Preferred complexity:** O(log n) time, O(1) space

```java
class Solution {
    public int search(int[] nums, int target) {
        int lo = 0, hi = nums.length - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) lo = mid + 1; else hi = mid - 1;
        }
        return -1;
    }
}
```

### 60. [Search Insert Position](https://leetcode.com/problems/search-insert-position/) — Easy

- [ ] **Revised**
- **Recognition cue:** Find first index whose value is >= target.
- **Approach ladder:** 1. Linear search over candidates — O(n) or O(answer range). 2. Binary search an index, boundary, or monotone feasibility predicate. 3. **Preferred:** Lower bound — O(log n) time, O(1) space.
- **Preferred pattern:** Lower bound
- **Preferred complexity:** O(log n) time, O(1) space
- **Invariant / state:** Answer remains in half-open range [left, right); discard provably smaller values.

```java
class Solution {
    public int searchInsert(int[] nums, int target) {
        int left = 0, right = nums.length;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) left = mid + 1;
            else right = mid;
        }
        return left;
    }
}
```

### 61. [Guess Number Higher Or Lower](https://leetcode.com/problems/guess-number-higher-or-lower/) — Easy

- [ ] **Revised**
- **Recognition cue:** Binary search through an oracle
- **Approach ladder:** 1. Sequential guesses — O(n). 2. Binary search using `guess(mid)` — O(log n) **(preferred)**.
- **Preferred pattern:** Binary search through an oracle
- **Preferred complexity:** O(log n) calls, O(1) space

```java
public class Solution extends GuessGame {
    public int guessNumber(int n) {
        int lo = 1, hi = n;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int g = guess(mid);
            if (g == 0) return mid;
            if (g > 0) lo = mid + 1; else hi = mid - 1;
        }
        return -1;
    }
}
```

### 62. [Sqrt(x)](https://leetcode.com/problems/sqrtx/) — Easy

- [ ] **Revised**
- **Recognition cue:** Find floor square root.
- **Approach ladder:** 1. Linear search over candidates — O(n) or O(answer range). 2. Binary search an index, boundary, or monotone feasibility predicate. 3. **Preferred:** Binary search on answer — O(log x) time, O(1) space.
- **Preferred pattern:** Binary search on answer
- **Preferred complexity:** O(log x) time, O(1) space
- **Invariant / state:** Use division comparison mid <= x/mid to avoid multiplication overflow.

```java
class Solution {
    public int mySqrt(int x) {
        if (x < 2) return x;
        int left = 1, right = x / 2, answer = 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (mid <= x / mid) { answer = mid; left = mid + 1; }
            else right = mid - 1;
        }
        return answer;
    }
}
```

### 63. [Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/) — Medium

- [ ] **Revised**
- **Recognition cue:** Rows form one globally sorted sequence.
- **Approach ladder:** 1. Linear search over candidates — O(n) or O(answer range). 2. Binary search an index, boundary, or monotone feasibility predicate. 3. **Preferred:** Flattened binary search — O(log(mn)) time, O(1) space.
- **Preferred pattern:** Flattened binary search
- **Preferred complexity:** O(log(mn)) time, O(1) space
- **Invariant / state:** Map flat index i to matrix[i/cols][i%cols].

```java
class Solution {
    public boolean searchMatrix(int[][] matrix, int target) {
        int m = matrix.length, n = matrix[0].length;
        int left = 0, right = m * n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int value = matrix[mid / n][mid % n];
            if (value == target) return true;
            if (value < target) left = mid + 1; else right = mid - 1;
        }
        return false;
    }
}
```

### 64. [Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/) — Medium

- [ ] **Revised**
- **Recognition cue:** Binary search on feasible rate
- **Approach ladder:** 1. Try every speed — O(maxPile·n). 2. Binary search minimum feasible speed — O(n log maxPile) **(preferred)**.
- **Preferred pattern:** Binary search on feasible rate
- **Preferred complexity:** O(n log M) time, O(1) space
- **Invariant / state:** Feasibility is monotone: every speed above a feasible speed is also feasible.

```java
class Solution {
    public int minEatingSpeed(int[] piles, int h) {
        int lo = 1, hi = 0;
        for (int p : piles) hi = Math.max(hi, p);
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            long hours = 0;
            for (int p : piles) hours += (p + (long) mid - 1) / mid;
            if (hours <= h) hi = mid; else lo = mid + 1;
        }
        return lo;
    }
}
```

### 65. [Capacity to Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) — Medium

- [ ] **Revised**
- **Recognition cue:** Binary search on capacity
- **Approach ladder:** 1. Test capacities linearly. 2. Binary search capacity between max weight and total weight — O(n log sum) **(preferred)**.
- **Preferred pattern:** Binary search on capacity
- **Preferred complexity:** O(n log S) time, O(1) space

```java
class Solution {
    public int shipWithinDays(int[] weights, int days) {
        int lo = 0, hi = 0;
        for (int w : weights) { lo = Math.max(lo, w); hi += w; }
        while (lo < hi) {
            int cap = lo + (hi - lo) / 2, used = 1, load = 0;
            for (int w : weights) {
                if (load + w > cap) { used++; load = 0; }
                load += w;
            }
            if (used <= days) hi = cap; else lo = cap + 1;
        }
        return lo;
    }
}
```

### 66. [Find Minimum In Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) — Medium

- [ ] **Revised**
- **Recognition cue:** Find rotation pivot in distinct sorted values.
- **Approach ladder:** 1. Linear search over candidates — O(n) or O(answer range). 2. Binary search an index, boundary, or monotone feasibility predicate. 3. **Preferred:** Binary search against right boundary — O(log n) time, O(1) space.
- **Preferred pattern:** Binary search against right boundary
- **Preferred complexity:** O(log n) time, O(1) space
- **Invariant / state:** If nums[mid] > nums[right], minimum is strictly right; otherwise it is at mid or left.

```java
class Solution {
    public int findMin(int[] nums) {
        int left = 0, right = nums.length - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) left = mid + 1;
            else right = mid;
        }
        return nums[left];
    }
}
```

### 67. [Search In Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) — Medium

- [ ] **Revised**
- **Recognition cue:** Sorted array is rotated once; values are distinct.
- **Approach ladder:** 1. Linear search over candidates — O(n) or O(answer range). 2. Binary search an index, boundary, or monotone feasibility predicate. 3. **Preferred:** Binary search with sorted half — O(log n) time, O(1) space.
- **Preferred pattern:** Binary search with sorted half
- **Preferred complexity:** O(log n) time, O(1) space
- **Invariant / state:** At least one half around mid is sorted; determine whether target lies inside it.

```java
class Solution {
    public int search(int[] nums, int target) {
        int left = 0, right = nums.length - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) right = mid - 1;
                else left = mid + 1;
            } else {
                if (nums[mid] < target && target <= nums[right]) left = mid + 1;
                else right = mid - 1;
            }
        }
        return -1;
    }
}
```

### 68. [Search In Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Modified binary search with duplicate shrink
- **Approach ladder:** 1. Linear scan — O(n). 2. Binary search while discarding equal endpoints — average O(log n), worst O(n) **(preferred)**.
- **Preferred pattern:** Modified binary search with duplicate shrink
- **Preferred complexity:** Average O(log n), worst O(n), O(1) space
- **Pitfall:** Duplicates can make the sorted half ambiguous, forcing linear degradation.

```java
class Solution {
    public boolean search(int[] nums, int target) {
        int lo = 0, hi = nums.length - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target) return true;
            if (nums[lo] == nums[mid] && nums[mid] == nums[hi]) { lo++; hi--; continue; }
            if (nums[lo] <= nums[mid]) {
                if (nums[lo] <= target && target < nums[mid]) hi = mid - 1;
                else lo = mid + 1;
            } else {
                if (nums[mid] < target && target <= nums[hi]) lo = mid + 1;
                else hi = mid - 1;
            }
        }
        return false;
    }
}
```

### 69. [Time Based Key Value Store](https://leetcode.com/problems/time-based-key-value-store/) — Medium

- [ ] **Revised**
- **Recognition cue:** Hash map of append-only timestamp lists
- **Approach ladder:** 1. TreeMap per key — O(log n) put/get. 2. Because timestamps arrive increasing, append arrays and binary-search floor timestamp — O(1) put, O(log n) get **(preferred)**.
- **Preferred pattern:** Hash map of append-only timestamp lists
- **Preferred complexity:** Put O(1); get O(log n); O(total puts) space

```java
class TimeMap {
    private static class Entry { int time; String value; Entry(int t, String v){time=t;value=v;} }
    private final Map<String, List<Entry>> map = new HashMap<>();
    public void set(String key, String value, int timestamp) {
        map.computeIfAbsent(key, k -> new ArrayList<>()).add(new Entry(timestamp, value));
    }
    public String get(String key, int timestamp) {
        List<Entry> a = map.get(key);
        if (a == null) return "";
        int lo = 0, hi = a.size() - 1, ans = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (a.get(mid).time <= timestamp) { ans = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        return ans < 0 ? "" : a.get(ans).value;
    }
}
```

### 70. [Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/) — Hard

- [ ] **Revised**
- **Recognition cue:** Binary search on answer + greedy feasibility
- **Approach ladder:** 1. Enumerate partitions — exponential. 2. DP — O(k n²). 3. Binary search maximum allowed subarray sum with greedy group count — O(n log sum) **(preferred)**.
- **Preferred pattern:** Binary search on answer + greedy feasibility
- **Preferred complexity:** O(n log S) time, O(1) space

```java
class Solution {
    public int splitArray(int[] nums, int k) {
        long lo = 0, hi = 0;
        for (int x : nums) { lo = Math.max(lo, x); hi += x; }
        while (lo < hi) {
            long cap = lo + (hi - lo) / 2, sum = 0; int parts = 1;
            for (int x : nums) {
                if (sum + x > cap) { parts++; sum = 0; }
                sum += x;
            }
            if (parts <= k) hi = cap; else lo = cap + 1;
        }
        return (int) lo;
    }
}
```

### 71. [Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/) — Hard

- [ ] **Revised**
- **Recognition cue:** Partition two sorted arrays so left halves contain half the elements.
- **Approach ladder:** 1. Linear search over candidates — O(n) or O(answer range). 2. Binary search an index, boundary, or monotone feasibility predicate. 3. **Preferred:** Binary search on partition — O(log(min(m,n))) time, O(1) space.
- **Preferred pattern:** Binary search on partition
- **Preferred complexity:** O(log(min(m,n))) time, O(1) space
- **Invariant / state:** Valid partition satisfies leftA<=rightB and leftB<=rightA; binary search the shorter array.

```java
class Solution {
    public double findMedianSortedArrays(int[] a, int[] b) {
        if (a.length > b.length) return findMedianSortedArrays(b, a);
        int m = a.length, n = b.length, half = (m + n + 1) / 2;
        int left = 0, right = m;
        while (left <= right) {
            int i = left + (right - left) / 2;
            int j = half - i;
            int aLeft = i == 0 ? Integer.MIN_VALUE : a[i - 1];
            int aRight = i == m ? Integer.MAX_VALUE : a[i];
            int bLeft = j == 0 ? Integer.MIN_VALUE : b[j - 1];
            int bRight = j == n ? Integer.MAX_VALUE : b[j];
            if (aLeft <= bRight && bLeft <= aRight) {
                if ((m + n) % 2 == 1) return Math.max(aLeft, bLeft);
                return ((double) Math.max(aLeft, bLeft) + Math.min(aRight, bRight)) / 2.0;
            }
            if (aLeft > bRight) right = i - 1; else left = i + 1;
        }
        throw new IllegalArgumentException("Inputs must be sorted");
    }
}
```

### 72. [Find in Mountain Array](https://leetcode.com/problems/find-in-mountain-array/) — Hard

- [ ] **Revised**
- **Recognition cue:** Peak search + two ordered binary searches
- **Approach ladder:** 1. Linear oracle scan — O(n) calls. 2. Binary-search peak, ascending side, then descending side — O(log n) calls **(preferred)**.
- **Preferred pattern:** Peak search + two ordered binary searches
- **Preferred complexity:** O(log n) oracle calls, O(1) space
- **Pitfall:** Search the ascending side first to return the minimum index.

```java
class Solution {
    public int findInMountainArray(int target, MountainArray a) {
        int n = a.length(), lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (a.get(mid) < a.get(mid + 1)) lo = mid + 1; else hi = mid;
        }
        int peak = lo;
        int left = bs(a, target, 0, peak, true);
        return left != -1 ? left : bs(a, target, peak + 1, n - 1, false);
    }
    private int bs(MountainArray a, int target, int lo, int hi, boolean asc) {
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2, v = a.get(mid);
            if (v == target) return mid;
            if ((v < target) == asc) lo = mid + 1; else hi = mid - 1;
        }
        return -1;
    }
}
```

---

## Linked List

### 73. [Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) — Easy

- [ ] **Revised**
- **Recognition cue:** Iterative pointer reversal
- **Approach ladder:** 1. Copy values into a new list — O(n) space. 2. Recursive reversal — O(n) stack. 3. Iterative three-pointer reversal — O(1) space **(preferred)**.
- **Preferred pattern:** Iterative pointer reversal
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** `prev` is the fully reversed processed prefix; `head` starts the untouched suffix.

```java
class Solution {
    public ListNode reverseList(ListNode head) {
        ListNode prev = null;
        while (head != null) {
            ListNode next = head.next;
            head.next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
}
```

### 74. [Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/) — Easy

- [ ] **Revised**
- **Recognition cue:** Merge two sorted linked lists.
- **Approach ladder:** 1. Copy nodes/values into an array or deque — O(n) extra space. 2. Recursive pointer manipulation — O(n) stack. 3. **Preferred:** Dummy-head merge — O(m+n) time, O(1) space.
- **Preferred pattern:** Dummy-head merge
- **Preferred complexity:** O(m+n) time, O(1) space
- **Invariant / state:** tail points to the last node of the merged prefix.

```java
class Solution {
    public ListNode mergeTwoLists(ListNode a, ListNode b) {
        ListNode dummy = new ListNode(), tail = dummy;
        while (a != null && b != null) {
            if (a.val <= b.val) { tail.next = a; a = a.next; }
            else { tail.next = b; b = b.next; }
            tail = tail.next;
        }
        tail.next = a != null ? a : b;
        return dummy.next;
    }
}
```

### 75. [Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/) — Easy

- [ ] **Revised**
- **Recognition cue:** Detect a cycle without extra memory.
- **Approach ladder:** 1. Copy nodes/values into an array or deque — O(n) extra space. 2. Recursive pointer manipulation — O(n) stack. 3. **Preferred:** Floyd slow/fast pointers — O(n) time, O(1) space.
- **Preferred pattern:** Floyd slow/fast pointers
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Inside a cycle, the relative distance changes by one per step, forcing a meeting.

```java
public class Solution {
    public boolean hasCycle(ListNode head) {
        ListNode slow = head, fast = head;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) return true;
        }
        return false;
    }
}
```

### 76. [Reorder List](https://leetcode.com/problems/reorder-list/) — Medium

- [ ] **Revised**
- **Recognition cue:** Middle + reverse + alternating merge
- **Approach ladder:** 1. Store nodes in an array/deque — O(n) space. 2. Find middle, reverse second half, weave halves — O(1) space **(preferred)**.
- **Preferred pattern:** Middle + reverse + alternating merge
- **Preferred complexity:** O(n) time, O(1) space
- **Pitfall:** Cut the first half before weaving to prevent cycles.

```java
class Solution {
    public void reorderList(ListNode head) {
        if (head == null || head.next == null) return;
        ListNode slow = head, fast = head;
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next; fast = fast.next.next;
        }
        ListNode second = slow.next; slow.next = null;
        ListNode prev = null;
        while (second != null) {
            ListNode next = second.next; second.next = prev; prev = second; second = next;
        }
        ListNode first = head; second = prev;
        while (second != null) {
            ListNode a = first.next, b = second.next;
            first.next = second; second.next = a;
            first = a; second = b;
        }
    }
}
```

### 77. [Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) — Medium

- [ ] **Revised**
- **Recognition cue:** Delete a node indexed from the tail in one pass.
- **Approach ladder:** 1. Copy nodes/values into an array or deque — O(n) extra space. 2. Recursive pointer manipulation — O(n) stack. 3. **Preferred:** Fixed-gap pointers — O(n) time, O(1) space.
- **Preferred pattern:** Fixed-gap pointers
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Advance fast n+1 steps from dummy; then slow stops before the target.

```java
class Solution {
    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode dummy = new ListNode(0, head), fast = dummy, slow = dummy;
        for (int i = 0; i <= n; i++) fast = fast.next;
        while (fast != null) { fast = fast.next; slow = slow.next; }
        slow.next = slow.next.next;
        return dummy.next;
    }
}
```

### 78. [Copy List With Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/) — Medium

- [ ] **Revised**
- **Recognition cue:** Deep-copy next and random pointers without a hash map.
- **Approach ladder:** 1. Copy nodes/values into an array or deque — O(n) extra space. 2. Recursive pointer manipulation — O(n) stack. 3. **Preferred:** Interleaving clone nodes — O(n) time, O(1) auxiliary space.
- **Preferred pattern:** Interleaving clone nodes
- **Preferred complexity:** O(n) time, O(1) auxiliary space
- **Invariant / state:** Insert clone after original; then original.random.next is the clone's random target.

```java
class Solution {
    public Node copyRandomList(Node head) {
        if (head == null) return null;
        for (Node cur = head; cur != null; cur = cur.next.next) {
            Node copy = new Node(cur.val);
            copy.next = cur.next;
            cur.next = copy;
        }
        for (Node cur = head; cur != null; cur = cur.next.next)
            cur.next.random = cur.random == null ? null : cur.random.next;
        Node copyHead = head.next;
        for (Node cur = head; cur != null;) {
            Node copy = cur.next;
            cur.next = copy.next;
            copy.next = copy.next == null ? null : copy.next.next;
            cur = cur.next;
        }
        return copyHead;
    }
}
```

### 79. [Add Two Numbers](https://leetcode.com/problems/add-two-numbers/) — Medium

- [ ] **Revised**
- **Recognition cue:** Numbers are stored least-significant digit first.
- **Approach ladder:** 1. Copy nodes/values into an array or deque — O(n) extra space. 2. Recursive pointer manipulation — O(n) stack. 3. **Preferred:** Digit-wise simulation with carry — O(max(m,n)) time, O(max(m,n)) output space.
- **Preferred pattern:** Digit-wise simulation with carry
- **Preferred complexity:** O(max(m,n)) time, O(max(m,n)) output space
- **Invariant / state:** Each output digit is (a+b+carry)%10; carry propagates forward.

```java
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(), tail = dummy;
        int carry = 0;
        while (l1 != null || l2 != null || carry != 0) {
            int sum = carry;
            if (l1 != null) { sum += l1.val; l1 = l1.next; }
            if (l2 != null) { sum += l2.val; l2 = l2.next; }
            tail.next = new ListNode(sum % 10);
            tail = tail.next;
            carry = sum / 10;
        }
        return dummy.next;
    }
}
```

### 80. [Find The Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/) — Medium

- [ ] **Revised**
- **Recognition cue:** Floyd cycle detection
- **Approach ladder:** 1. Sort — O(n log n), mutates input. 2. HashSet — O(n) space. 3. Binary search value counts — O(n log n). 4. Treat values as next pointers and use Floyd — O(n), O(1) **(preferred)**.
- **Preferred pattern:** Floyd cycle detection
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Array indices are graph nodes; the duplicate is the cycle entrance.

```java
class Solution {
    public int findDuplicate(int[] nums) {
        int slow = nums[0], fast = nums[0];
        do { slow = nums[slow]; fast = nums[nums[fast]]; } while (slow != fast);
        slow = nums[0];
        while (slow != fast) { slow = nums[slow]; fast = nums[fast]; }
        return slow;
    }
}
```

### 81. [Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Reverse positions left through right in one pass.
- **Approach ladder:** 1. Copy nodes/values into an array or deque — O(n) extra space. 2. Recursive pointer manipulation — O(n) stack. 3. **Preferred:** Head-insertion within sublist — O(n) time, O(1) space.
- **Preferred pattern:** Head-insertion within sublist
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** prev.next remains sublist head; repeatedly move the next node to the front.

```java
class Solution {
    public ListNode reverseBetween(ListNode head, int left, int right) {
        ListNode dummy = new ListNode(0, head), prev = dummy;
        for (int i = 1; i < left; i++) prev = prev.next;
        ListNode cur = prev.next;
        for (int i = 0; i < right - left; i++) {
            ListNode move = cur.next;
            cur.next = move.next;
            move.next = prev.next;
            prev.next = move;
        }
        return dummy.next;
    }
}
```

### 82. [Design Circular Queue](https://leetcode.com/problems/design-circular-queue/) — Medium

- [ ] **Revised**
- **Recognition cue:** Fixed-size ring buffer
- **Approach ladder:** 1. Shift an array on dequeue — O(n). 2. Linked list — O(1) but extra nodes. 3. Circular array with head and size — O(1) **(preferred)**.
- **Preferred pattern:** Fixed-size ring buffer
- **Preferred complexity:** O(1) per operation, O(k) space

```java
class MyCircularQueue {
    private final int[] a;
    private int head = 0, size = 0;
    public MyCircularQueue(int k) { a = new int[k]; }
    public boolean enQueue(int value) {
        if (isFull()) return false;
        a[(head + size) % a.length] = value; size++; return true;
    }
    public boolean deQueue() {
        if (isEmpty()) return false;
        head = (head + 1) % a.length; size--; return true;
    }
    public int Front() { return isEmpty() ? -1 : a[head]; }
    public int Rear() { return isEmpty() ? -1 : a[(head + size - 1) % a.length]; }
    public boolean isEmpty() { return size == 0; }
    public boolean isFull() { return size == a.length; }
}
```

### 83. [LRU Cache](https://leetcode.com/problems/lru-cache/) — Medium

- [ ] **Revised**
- **Recognition cue:** O(1) get/put with least-recently-used eviction.
- **Approach ladder:** 1. Copy nodes/values into an array or deque — O(n) extra space. 2. Recursive pointer manipulation — O(n) stack. 3. **Preferred:** Hash map + doubly linked list — O(1) average per operation, O(capacity) space.
- **Preferred pattern:** Hash map + doubly linked list
- **Preferred complexity:** O(1) average per operation, O(capacity) space
- **Invariant / state:** Map locates nodes; list orders recency with MRU near head and LRU near tail.

```java
class LRUCache {
    private static class Node {
        int key, value; Node prev, next;
        Node() {}
        Node(int k, int v) { key = k; value = v; }
    }
    private final int capacity;
    private final Map<Integer, Node> map = new HashMap<>();
    private final Node head = new Node(), tail = new Node();

    public LRUCache(int capacity) {
        this.capacity = capacity;
        head.next = tail; tail.prev = head;
    }
    public int get(int key) {
        Node node = map.get(key);
        if (node == null) return -1;
        moveToFront(node);
        return node.value;
    }
    public void put(int key, int value) {
        Node node = map.get(key);
        if (node != null) {
            node.value = value;
            moveToFront(node);
            return;
        }
        node = new Node(key, value);
        map.put(key, node);
        addFirst(node);
        if (map.size() > capacity) {
            Node lru = tail.prev;
            remove(lru);
            map.remove(lru.key);
        }
    }
    private void moveToFront(Node node) { remove(node); addFirst(node); }
    private void addFirst(Node node) {
        node.next = head.next; node.prev = head;
        head.next.prev = node; head.next = node;
    }
    private void remove(Node node) {
        node.prev.next = node.next; node.next.prev = node.prev;
    }
}
```

### 84. [LFU Cache](https://leetcode.com/problems/lfu-cache/) — Hard

- [ ] **Revised**
- **Recognition cue:** Key map + frequency buckets with LRU order
- **Approach ladder:** 1. Scan all entries on eviction — O(capacity). 2. Heap with lazy stale records — O(log n). 3. Key→node and frequency→LinkedHashSet, tracking minimum frequency — expected O(1) **(preferred)**.
- **Preferred pattern:** Key map + frequency buckets with LRU order
- **Preferred complexity:** Expected O(1) get/put, O(capacity) space
- **Pitfall:** Within the minimum-frequency bucket, evict the least recently used entry.

```java
class LFUCache {
    private static class Node {
        int key, value, freq = 1;
        Node(int k, int v) { key = k; value = v; }
    }
    private final int capacity;
    private int minFreq = 0;
    private final Map<Integer, Node> nodes = new HashMap<>();
    private final Map<Integer, LinkedHashSet<Node>> buckets = new HashMap<>();
    public LFUCache(int capacity) { this.capacity = capacity; }
    public int get(int key) {
        Node n = nodes.get(key);
        if (n == null) return -1;
        touch(n); return n.value;
    }
    public void put(int key, int value) {
        if (capacity == 0) return;
        Node n = nodes.get(key);
        if (n != null) { n.value = value; touch(n); return; }
        if (nodes.size() == capacity) {
            LinkedHashSet<Node> set = buckets.get(minFreq);
            Node victim = set.iterator().next();
            set.remove(victim); nodes.remove(victim.key);
        }
        n = new Node(key, value); nodes.put(key, n);
        buckets.computeIfAbsent(1, f -> new LinkedHashSet<>()).add(n);
        minFreq = 1;
    }
    private void touch(Node n) {
        int f = n.freq;
        LinkedHashSet<Node> old = buckets.get(f);
        old.remove(n);
        if (f == minFreq && old.isEmpty()) minFreq++;
        n.freq++;
        buckets.computeIfAbsent(n.freq, z -> new LinkedHashSet<>()).add(n);
    }
}
```

### 85. [Merge K Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) — Hard

- [ ] **Revised**
- **Recognition cue:** Repeatedly choose the smallest current list head.
- **Approach ladder:** 1. Copy nodes/values into an array or deque — O(n) extra space. 2. Recursive pointer manipulation — O(n) stack. 3. **Preferred:** Min-heap k-way merge — O(N log k) time, O(k) space.
- **Preferred pattern:** Min-heap k-way merge
- **Preferred complexity:** O(N log k) time, O(k) space
- **Invariant / state:** Heap contains at most one candidate from each list; popping exposes that list's next candidate.

```java
class Solution {
    public ListNode mergeKLists(ListNode[] lists) {
        PriorityQueue<ListNode> pq = new PriorityQueue<>(Comparator.comparingInt(n -> n.val));
        for (ListNode node : lists) if (node != null) pq.add(node);
        ListNode dummy = new ListNode(), tail = dummy;
        while (!pq.isEmpty()) {
            ListNode node = pq.remove();
            tail.next = node; tail = node;
            if (node.next != null) pq.add(node.next);
        }
        return dummy.next;
    }
}
```

### 86. [Reverse Nodes In K Group](https://leetcode.com/problems/reverse-nodes-in-k-group/) — Hard

- [ ] **Revised**
- **Recognition cue:** Reverse complete groups of k nodes; leave the remainder unchanged.
- **Approach ladder:** 1. Copy nodes/values into an array or deque — O(n) extra space. 2. Recursive pointer manipulation — O(n) stack. 3. **Preferred:** Segment reversal — O(n) time, O(1) space.
- **Preferred pattern:** Segment reversal
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Find kth boundary first, detach logically, reverse [groupStart, groupNext), reconnect.

```java
class Solution {
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode dummy = new ListNode(0, head), groupPrev = dummy;
        while (true) {
            ListNode kth = kth(groupPrev, k);
            if (kth == null) break;
            ListNode groupNext = kth.next;
            ListNode prev = groupNext, cur = groupPrev.next;
            while (cur != groupNext) {
                ListNode next = cur.next;
                cur.next = prev;
                prev = cur;
                cur = next;
            }
            ListNode oldStart = groupPrev.next;
            groupPrev.next = kth;
            groupPrev = oldStart;
        }
        return dummy.next;
    }
    private ListNode kth(ListNode node, int k) {
        while (node != null && k-- > 0) node = node.next;
        return node;
    }
}
```

---

## Trees

### 87. [Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/) — Easy

- [ ] **Revised**
- **Recognition cue:** Iterative DFS stack
- **Approach ladder:** 1. Recursive DFS — O(n) stack by height. 2. Explicit stack — O(h) **(preferred iterative)**. 3. Morris traversal — O(1) space but temporarily rewires the tree.
- **Preferred pattern:** Iterative DFS stack
- **Preferred complexity:** O(n) time, O(h) space

```java
class Solution {
    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        Deque<TreeNode> st = new ArrayDeque<>();
        while (root != null || !st.isEmpty()) {
            while (root != null) { st.push(root); root = root.left; }
            root = st.pop(); ans.add(root.val); root = root.right;
        }
        return ans;
    }
}
```

### 88. [Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/) — Easy

- [ ] **Revised**
- **Recognition cue:** Iterative DFS stack
- **Approach ladder:** 1. Recursive preorder — O(h) stack. 2. Explicit stack pushing right before left — O(h) to O(n) **(preferred iterative)**. 3. Morris preorder — O(1).
- **Preferred pattern:** Iterative DFS stack
- **Preferred complexity:** O(n) time, O(h) average / O(n) worst space

```java
class Solution {
    public List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        if (root == null) return ans;
        Deque<TreeNode> st = new ArrayDeque<>(); st.push(root);
        while (!st.isEmpty()) {
            TreeNode n = st.pop(); ans.add(n.val);
            if (n.right != null) st.push(n.right);
            if (n.left != null) st.push(n.left);
        }
        return ans;
    }
}
```

### 89. [Binary Tree Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/) — Easy

- [ ] **Revised**
- **Recognition cue:** Iterative DFS with last-visited pointer
- **Approach ladder:** 1. Recursive postorder — O(h). 2. Two stacks / reverse preorder — O(n). 3. One stack plus last-visited pointer — O(h) **(preferred)**. 4. Morris postorder — O(1), complex.
- **Preferred pattern:** Iterative DFS with last-visited pointer
- **Preferred complexity:** O(n) time, O(h) space

```java
class Solution {
    public List<Integer> postorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        Deque<TreeNode> st = new ArrayDeque<>();
        TreeNode last = null;
        while (root != null || !st.isEmpty()) {
            if (root != null) { st.push(root); root = root.left; }
            else {
                TreeNode top = st.peek();
                if (top.right != null && top.right != last) root = top.right;
                else { ans.add(top.val); last = st.pop(); }
            }
        }
        return ans;
    }
}
```

### 90. [Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/) — Easy

- [ ] **Revised**
- **Recognition cue:** Swap left and right recursively.
- **Approach ladder:** 1. Recursive DFS — usually the clearest baseline. 2. Iterative DFS/BFS — avoids recursion and may expose level order. 3. **Preferred:** Recursive structural transform — O(n) time, O(h) recursion space.
- **Preferred pattern:** Recursive structural transform
- **Preferred complexity:** O(n) time, O(h) recursion space
- **Invariant / state:** After processing a node, both subtrees are inverted and exchanged.

```java
class Solution {
    public TreeNode invertTree(TreeNode root) {
        if (root == null) return null;
        TreeNode left = invertTree(root.left);
        root.left = invertTree(root.right);
        root.right = left;
        return root;
    }
}
```

### 91. [Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/) — Easy

- [ ] **Revised**
- **Recognition cue:** Aggregate a value from child subtrees.
- **Approach ladder:** 1. Recursive DFS — usually the clearest baseline. 2. Iterative DFS/BFS — avoids recursion and may expose level order. 3. **Preferred:** Tree DFS — O(n) time, O(h) recursion space.
- **Preferred pattern:** Tree DFS
- **Preferred complexity:** O(n) time, O(h) recursion space
- **Invariant / state:** Depth(node) = 1 + max(depth(left), depth(right)).

```java
class Solution {
    public int maxDepth(TreeNode root) {
        if (root == null) return 0;
        return 1 + Math.max(maxDepth(root.left), maxDepth(root.right));
    }
}
```

### 92. [Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/) — Easy

- [ ] **Revised**
- **Recognition cue:** Postorder height aggregation
- **Approach ladder:** 1. Compute height separately at every node — O(n²) worst. 2. One postorder returning height while updating diameter — O(n) **(preferred)**.
- **Preferred pattern:** Postorder height aggregation
- **Preferred complexity:** O(n) time, O(h) recursion stack
- **Invariant / state:** At each node, the best path through it uses left height + right height edges.

```java
class Solution {
    private int diameter = 0;
    public int diameterOfBinaryTree(TreeNode root) { height(root); return diameter; }
    private int height(TreeNode n) {
        if (n == null) return 0;
        int l = height(n.left), r = height(n.right);
        diameter = Math.max(diameter, l + r);
        return 1 + Math.max(l, r);
    }
}
```

### 93. [Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/) — Easy

- [ ] **Revised**
- **Recognition cue:** Postorder with failure sentinel
- **Approach ladder:** 1. Recompute heights for each node — O(n²). 2. Postorder returning height or -1 on imbalance — O(n) **(preferred)**.
- **Preferred pattern:** Postorder with failure sentinel
- **Preferred complexity:** O(n) time, O(h) space

```java
class Solution {
    public boolean isBalanced(TreeNode root) { return height(root) != -1; }
    private int height(TreeNode n) {
        if (n == null) return 0;
        int l = height(n.left); if (l == -1) return -1;
        int r = height(n.right); if (r == -1 || Math.abs(l - r) > 1) return -1;
        return 1 + Math.max(l, r);
    }
}
```

### 94. [Same Tree](https://leetcode.com/problems/same-tree/) — Easy

- [ ] **Revised**
- **Recognition cue:** Compare structure and values of two trees.
- **Approach ladder:** 1. Recursive DFS — usually the clearest baseline. 2. Iterative DFS/BFS — avoids recursion and may expose level order. 3. **Preferred:** Synchronized DFS — O(n) time, O(h) recursion space.
- **Preferred pattern:** Synchronized DFS
- **Preferred complexity:** O(n) time, O(h) recursion space
- **Invariant / state:** Corresponding nodes must either both be null or have equal value and equal subtrees.

```java
class Solution {
    public boolean isSameTree(TreeNode p, TreeNode q) {
        if (p == null || q == null) return p == q;
        return p.val == q.val && isSameTree(p.left, q.left) && isSameTree(p.right, q.right);
    }
}
```

### 95. [Subtree of Another Tree](https://leetcode.com/problems/subtree-of-another-tree/) — Easy

- [ ] **Revised**
- **Recognition cue:** Canonical subtree interning
- **Approach ladder:** 1. Compare trees from every root — O(nm) worst. 2. Preorder serialization + substring matching. 3. Intern each `(value,leftId,rightId)` tuple and compare subtree IDs — expected O(n+m) **(preferred)**.
- **Preferred pattern:** Canonical subtree interning
- **Preferred complexity:** Expected O(n+m) time and space
- **Pitfall:** Null children must participate in the canonical structure; their ID is 0.

```java
class Solution {
    private record Key(int value, int left, int right) {}
    private final Map<Key, Integer> ids = new HashMap<>();
    private final Set<Integer> rootIds = new HashSet<>();
    private int nextId = 1;
    public boolean isSubtree(TreeNode root, TreeNode subRoot) {
        encode(root, true);
        int target = encode(subRoot, false);
        return rootIds.contains(target);
    }
    private int encode(TreeNode n, boolean collect) {
        if (n == null) return 0;
        int l = encode(n.left, collect), r = encode(n.right, collect);
        int id = ids.computeIfAbsent(new Key(n.val, l, r), k -> nextId++);
        if (collect) rootIds.add(id);
        return id;
    }
}
```

### 96. [Lowest Common Ancestor of a Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/) — Medium

- [ ] **Revised**
- **Recognition cue:** BST ordering
- **Approach ladder:** 1. General-tree root-to-node paths — O(n) space. 2. Use BST ordering and walk until values split — O(h), O(1) **(preferred)**.
- **Preferred pattern:** BST ordering
- **Preferred complexity:** O(h) time, O(1) space

```java
class Solution {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        int lo = Math.min(p.val, q.val), hi = Math.max(p.val, q.val);
        while (root != null) {
            if (root.val < lo) root = root.right;
            else if (root.val > hi) root = root.left;
            else return root;
        }
        return null;
    }
}
```

### 97. [Insert into a Binary Search Tree](https://leetcode.com/problems/insert-into-a-binary-search-tree/) — Medium

- [ ] **Revised**
- **Recognition cue:** BST descent
- **Approach ladder:** 1. Recursive descent — O(h) stack. 2. Iterative descent and attach at null child — O(h), O(1) **(preferred)**.
- **Preferred pattern:** BST descent
- **Preferred complexity:** O(h) time, O(1) space

```java
class Solution {
    public TreeNode insertIntoBST(TreeNode root, int val) {
        if (root == null) return new TreeNode(val);
        TreeNode cur = root;
        while (true) {
            if (val < cur.val) {
                if (cur.left == null) { cur.left = new TreeNode(val); break; }
                cur = cur.left;
            } else {
                if (cur.right == null) { cur.right = new TreeNode(val); break; }
                cur = cur.right;
            }
        }
        return root;
    }
}
```

### 98. [Delete Node in a BST](https://leetcode.com/problems/delete-node-in-a-bst/) — Medium

- [ ] **Revised**
- **Recognition cue:** BST recursion + inorder successor
- **Approach ladder:** 1. Flatten and rebuild — O(n). 2. Search node; for two children copy inorder successor then delete successor — O(h) **(preferred)**.
- **Preferred pattern:** BST recursion + inorder successor
- **Preferred complexity:** O(h) time and recursion space

```java
class Solution {
    public TreeNode deleteNode(TreeNode root, int key) {
        if (root == null) return null;
        if (key < root.val) root.left = deleteNode(root.left, key);
        else if (key > root.val) root.right = deleteNode(root.right, key);
        else {
            if (root.left == null) return root.right;
            if (root.right == null) return root.left;
            TreeNode s = root.right;
            while (s.left != null) s = s.left;
            root.val = s.val;
            root.right = deleteNode(root.right, s.val);
        }
        return root;
    }
}
```

### 99. [Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) — Medium

- [ ] **Revised**
- **Recognition cue:** Return values grouped by depth.
- **Approach ladder:** 1. Recursive DFS — usually the clearest baseline. 2. Iterative DFS/BFS — avoids recursion and may expose level order. 3. **Preferred:** Level-order BFS — O(n) time, O(width) space.
- **Preferred pattern:** Level-order BFS
- **Preferred complexity:** O(n) time, O(width) space
- **Invariant / state:** Process exactly the queue size captured before adding the next level.

```java
class Solution {
    public List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> ans = new ArrayList<>();
        if (root == null) return ans;
        Queue<TreeNode> q = new ArrayDeque<>();
        q.add(root);
        while (!q.isEmpty()) {
            int size = q.size();
            List<Integer> level = new ArrayList<>(size);
            for (int i = 0; i < size; i++) {
                TreeNode node = q.remove();
                level.add(node.val);
                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
            ans.add(level);
        }
        return ans;
    }
}
```

### 100. [Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/) — Medium

- [ ] **Revised**
- **Recognition cue:** Collect the visible node from the right side at each depth.
- **Approach ladder:** 1. Recursive DFS — usually the clearest baseline. 2. Iterative DFS/BFS — avoids recursion and may expose level order. 3. **Preferred:** Level-order endpoint — O(n) time, O(width) space.
- **Preferred pattern:** Level-order endpoint
- **Preferred complexity:** O(n) time, O(width) space
- **Invariant / state:** The last node dequeued in each level is the rightmost node.

```java
class Solution {
    public List<Integer> rightSideView(TreeNode root) {
        List<Integer> ans = new ArrayList<>();
        if (root == null) return ans;
        Queue<TreeNode> q = new ArrayDeque<>();
        q.add(root);
        while (!q.isEmpty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode node = q.remove();
                if (i == size - 1) ans.add(node.val);
                if (node.left != null) q.add(node.left);
                if (node.right != null) q.add(node.right);
            }
        }
        return ans;
    }
}
```

### 101. [Construct Quad Tree](https://leetcode.com/problems/construct-quad-tree/) — Medium

- [ ] **Revised**
- **Recognition cue:** Compress a binary square grid into uniform regions.
- **Approach ladder:** 1. Recursive DFS — usually the clearest baseline. 2. Iterative DFS/BFS — avoids recursion and may expose level order. 3. **Preferred:** Recursive spatial partition — O(n^2 log n) simple-check worst case, O(log n) recursion.
- **Preferred pattern:** Recursive spatial partition
- **Preferred complexity:** O(n^2 log n) simple-check worst case, O(log n) recursion
- **Invariant / state:** A region becomes a leaf if all four recursively built quadrants are equal leaves.

```java
class Solution {
    public Node construct(int[][] grid) {
        return build(grid, 0, 0, grid.length);
    }
    private Node build(int[][] g, int r, int c, int size) {
        boolean same = true;
        int value = g[r][c];
        for (int i = r; i < r + size && same; i++)
            for (int j = c; j < c + size; j++)
                if (g[i][j] != value) { same = false; break; }
        if (same) return new Node(value == 1, true);
        int h = size / 2;
        return new Node(true, false,
                build(g, r, c, h), build(g, r, c + h, h),
                build(g, r + h, c, h), build(g, r + h, c + h, h));
    }
}
```

### 102. [Count Good Nodes In Binary Tree](https://leetcode.com/problems/count-good-nodes-in-binary-tree/) — Medium

- [ ] **Revised**
- **Recognition cue:** DFS with path maximum
- **Approach ladder:** 1. For each node rescan ancestors — O(nh). 2. DFS carrying maximum value seen on path — O(n) **(preferred)**.
- **Preferred pattern:** DFS with path maximum
- **Preferred complexity:** O(n) time, O(h) space

```java
class Solution {
    public int goodNodes(TreeNode root) { return dfs(root, Integer.MIN_VALUE); }
    private int dfs(TreeNode n, int max) {
        if (n == null) return 0;
        int good = n.val >= max ? 1 : 0;
        max = Math.max(max, n.val);
        return good + dfs(n.left, max) + dfs(n.right, max);
    }
}
```

### 103. [Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/) — Medium

- [ ] **Revised**
- **Recognition cue:** Every node must obey all ancestor constraints, not only its parent.
- **Approach ladder:** 1. Recursive DFS — usually the clearest baseline. 2. Iterative DFS/BFS — avoids recursion and may expose level order. 3. **Preferred:** Range propagation — O(n) time, O(h) recursion space.
- **Preferred pattern:** Range propagation
- **Preferred complexity:** O(n) time, O(h) recursion space
- **Invariant / state:** Pass exclusive lower and upper bounds down the recursion.

```java
class Solution {
    public boolean isValidBST(TreeNode root) {
        return valid(root, Long.MIN_VALUE, Long.MAX_VALUE);
    }
    private boolean valid(TreeNode node, long low, long high) {
        if (node == null) return true;
        if (node.val <= low || node.val >= high) return false;
        return valid(node.left, low, node.val) && valid(node.right, node.val, high);
    }
}
```

### 104. [Kth Smallest Element In a Bst](https://leetcode.com/problems/kth-smallest-element-in-a-bst/) — Medium

- [ ] **Revised**
- **Recognition cue:** Select the kth value in sorted BST order.
- **Approach ladder:** 1. Recursive DFS — usually the clearest baseline. 2. Iterative DFS/BFS — avoids recursion and may expose level order. 3. **Preferred:** Iterative inorder — O(h+k) time, O(h) space.
- **Preferred pattern:** Iterative inorder
- **Preferred complexity:** O(h+k) time, O(h) space
- **Invariant / state:** Each pop from the inorder stack yields the next smallest value.

```java
class Solution {
    public int kthSmallest(TreeNode root, int k) {
        Deque<TreeNode> stack = new ArrayDeque<>();
        while (true) {
            while (root != null) { stack.push(root); root = root.left; }
            root = stack.pop();
            if (--k == 0) return root.val;
            root = root.right;
        }
    }
}
```

### 105. [Construct Binary Tree From Preorder And Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) — Medium

- [ ] **Revised**
- **Recognition cue:** Preorder reveals root; inorder separates left and right subtrees.
- **Approach ladder:** 1. Recursive DFS — usually the clearest baseline. 2. Iterative DFS/BFS — avoids recursion and may expose level order. 3. **Preferred:** Recursive partition by root index — O(n) time, O(n) map + O(h) recursion.
- **Preferred pattern:** Recursive partition by root index
- **Preferred complexity:** O(n) time, O(n) map + O(h) recursion
- **Invariant / state:** A shared preorder pointer consumes exactly one root per recursive subtree.

```java
class Solution {
    private int pre;
    private final Map<Integer, Integer> index = new HashMap<>();
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        for (int i = 0; i < inorder.length; i++) index.put(inorder[i], i);
        return build(preorder, 0, inorder.length - 1);
    }
    private TreeNode build(int[] preorder, int left, int right) {
        if (left > right) return null;
        int value = preorder[pre++];
        TreeNode root = new TreeNode(value);
        int mid = index.get(value);
        root.left = build(preorder, left, mid - 1);
        root.right = build(preorder, mid + 1, right);
        return root;
    }
}
```

### 106. [House Robber III](https://leetcode.com/problems/house-robber-iii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Tree DP: take versus skip
- **Approach ladder:** 1. Naive include/exclude recursion — exponential. 2. Memoize by node. 3. Postorder returns `[skip,take]` — O(n) **(preferred)**.
- **Preferred pattern:** Tree DP: take versus skip
- **Preferred complexity:** O(n) time, O(h) space

```java
class Solution {
    public int rob(TreeNode root) {
        int[] x = dfs(root); return Math.max(x[0], x[1]);
    }
    private int[] dfs(TreeNode n) {
        if (n == null) return new int[2];
        int[] l = dfs(n.left), r = dfs(n.right);
        int skip = Math.max(l[0], l[1]) + Math.max(r[0], r[1]);
        int take = n.val + l[0] + r[0];
        return new int[]{skip, take};
    }
}
```

### 107. [Delete Leaves With a Given Value](https://leetcode.com/problems/delete-leaves-with-a-given-value/) — Medium

- [ ] **Revised**
- **Recognition cue:** Postorder pruning
- **Approach ladder:** 1. Repeated full-tree deletion passes — O(n²). 2. Postorder: prune children first, then current leaf — O(n) **(preferred)**.
- **Preferred pattern:** Postorder pruning
- **Preferred complexity:** O(n) time, O(h) space
- **Pitfall:** Postorder is required because deleting children can turn the parent into a new target leaf.

```java
class Solution {
    public TreeNode removeLeafNodes(TreeNode root, int target) {
        if (root == null) return null;
        root.left = removeLeafNodes(root.left, target);
        root.right = removeLeafNodes(root.right, target);
        return root.left == null && root.right == null && root.val == target ? null : root;
    }
}
```

### 108. [Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/) — Hard

- [ ] **Revised**
- **Recognition cue:** Maximum path may start and end anywhere but cannot branch upward twice.
- **Approach ladder:** 1. Recursive DFS — usually the clearest baseline. 2. Iterative DFS/BFS — avoids recursion and may expose level order. 3. **Preferred:** Tree DP with global optimum — O(n) time, O(h) recursion space.
- **Preferred pattern:** Tree DP with global optimum
- **Preferred complexity:** O(n) time, O(h) recursion space
- **Invariant / state:** Return best one-arm gain; update global with left + node + right.

```java
class Solution {
    private int best = Integer.MIN_VALUE;
    public int maxPathSum(TreeNode root) {
        gain(root);
        return best;
    }
    private int gain(TreeNode node) {
        if (node == null) return 0;
        int left = Math.max(0, gain(node.left));
        int right = Math.max(0, gain(node.right));
        best = Math.max(best, node.val + left + right);
        return node.val + Math.max(left, right);
    }
}
```

### 109. [Serialize And Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) — Hard

- [ ] **Revised**
- **Recognition cue:** Preorder with null markers
- **Approach ladder:** 1. BFS level-order with null markers. 2. Preorder DFS with null markers — O(n), compact **(preferred)**.
- **Preferred pattern:** Preorder with null markers
- **Preferred complexity:** O(n) time and space
- **Pitfall:** Null markers are required; values alone cannot reconstruct arbitrary tree shape.

```java
public class Codec {
    public String serialize(TreeNode root) {
        StringBuilder out = new StringBuilder(); write(root, out); return out.toString();
    }
    private void write(TreeNode n, StringBuilder out) {
        if (n == null) { out.append("#,"); return; }
        out.append(n.val).append(','); write(n.left, out); write(n.right, out);
    }
    public TreeNode deserialize(String data) {
        Deque<String> q = new ArrayDeque<>(Arrays.asList(data.split(",")));
        return read(q);
    }
    private TreeNode read(Deque<String> q) {
        String s = q.removeFirst();
        if (s.equals("#")) return null;
        TreeNode n = new TreeNode(Integer.parseInt(s));
        n.left = read(q); n.right = read(q); return n;
    }
}
```

---

## Heap / Priority Queue

### 110. [Kth Largest Element In a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/) — Easy

- [ ] **Revised**
- **Recognition cue:** Min-heap of size k
- **Approach ladder:** 1. Keep all values sorted — O(n) insertion. 2. Max-heap of all values — O(n) query copies. 3. Min-heap containing only largest k — O(log k) add **(preferred)**.
- **Preferred pattern:** Min-heap of size k
- **Preferred complexity:** Constructor O(n log k); add O(log k); O(k) space

```java
class KthLargest {
    private final int k;
    private final PriorityQueue<Integer> heap = new PriorityQueue<>();
    public KthLargest(int k, int[] nums) { this.k = k; for (int x : nums) add(x); }
    public int add(int val) {
        heap.offer(val);
        if (heap.size() > k) heap.poll();
        return heap.peek();
    }
}
```

### 111. [Last Stone Weight](https://leetcode.com/problems/last-stone-weight/) — Easy

- [ ] **Revised**
- **Recognition cue:** Max-heap simulation
- **Approach ladder:** 1. Re-sort after each smash — O(n² log n). 2. Max-heap — O(n log n) **(preferred)**.
- **Preferred pattern:** Max-heap simulation
- **Preferred complexity:** O(n log n) time, O(n) space

```java
class Solution {
    public int lastStoneWeight(int[] stones) {
        PriorityQueue<Integer> pq = new PriorityQueue<>(Comparator.reverseOrder());
        for (int x : stones) pq.offer(x);
        while (pq.size() > 1) {
            int a = pq.poll(), b = pq.poll();
            if (a != b) pq.offer(a - b);
        }
        return pq.isEmpty() ? 0 : pq.peek();
    }
}
```

### 112. [K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/) — Medium

- [ ] **Revised**
- **Recognition cue:** Quickselect by squared distance
- **Approach ladder:** 1. Sort all points — O(n log n). 2. Max-heap size k — O(n log k). 3. Quickselect — expected O(n), in-place **(preferred)**.
- **Preferred pattern:** Quickselect by squared distance
- **Preferred complexity:** Expected O(n) time, O(log n) recursion / O(1) iterative auxiliary space
- **Pitfall:** Use squared distance and `long`; square roots are unnecessary.

```java
class Solution {
    public int[][] kClosest(int[][] points, int k) {
        int lo = 0, hi = points.length - 1;
        while (lo <= hi) {
            int p = partition(points, lo, hi);
            if (p == k - 1) break;
            if (p < k - 1) lo = p + 1; else hi = p - 1;
        }
        return Arrays.copyOf(points, k);
    }
    private int partition(int[][] a, int lo, int hi) {
        int[] pivot = a[hi]; long d = dist(pivot); int p = lo;
        for (int i = lo; i < hi; i++) if (dist(a[i]) <= d) swap(a, p++, i);
        swap(a, p, hi); return p;
    }
    private long dist(int[] p) { return (long) p[0] * p[0] + (long) p[1] * p[1]; }
    private void swap(int[][] a, int i, int j) { int[] t = a[i]; a[i] = a[j]; a[j] = t; }
}
```

### 113. [Kth Largest Element In An Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) — Medium

- [ ] **Revised**
- **Recognition cue:** Keep the k largest values seen so far.
- **Approach ladder:** 1. Fully sort all candidates — O(n log n). 2. Heap, quickselect, bucket, or streaming structure depending whether all order statistics are needed. 3. **Preferred:** Size-k min heap — O(n log k) time, O(k) space.
- **Preferred pattern:** Size-k min heap
- **Preferred complexity:** O(n log k) time, O(k) space
- **Invariant / state:** Heap root is the smallest among retained top-k values, hence the kth largest.

```java
class Solution {
    public int findKthLargest(int[] nums, int k) {
        PriorityQueue<Integer> heap = new PriorityQueue<>();
        for (int x : nums) {
            heap.add(x);
            if (heap.size() > k) heap.remove();
        }
        return heap.element();
    }
}
```

### 114. [Task Scheduler](https://leetcode.com/problems/task-scheduler/) — Medium

- [ ] **Revised**
- **Recognition cue:** Greedy frequency frame
- **Approach ladder:** 1. Simulate with max-heap and cooldown queue — O(n log 26). 2. Count the most frequent tasks and compute the minimum frame — O(n) **(preferred)**.
- **Preferred pattern:** Greedy frequency frame
- **Preferred complexity:** O(n) time, O(1) space

```java
class Solution {
    public int leastInterval(char[] tasks, int n) {
        int[] f = new int[26];
        for (char c : tasks) f[c - 'A']++;
        int max = 0, maxCount = 0;
        for (int x : f) {
            if (x > max) { max = x; maxCount = 1; }
            else if (x == max) maxCount++;
        }
        return Math.max(tasks.length, (max - 1) * (n + 1) + maxCount);
    }
}
```

### 115. [Design Twitter](https://leetcode.com/problems/design-twitter/) — Medium

- [ ] **Revised**
- **Recognition cue:** K-way merge of per-user tweet streams
- **Approach ladder:** 1. Scan all tweets globally on feed request — O(total tweets). 2. Maintain each user’s reverse-chronological linked list; heap-merge followed users — O((F+10) log F) **(preferred)**.
- **Preferred pattern:** K-way merge of per-user tweet streams
- **Preferred complexity:** Post/follow O(1); feed O((F+10) log F); O(total tweets + follows) space

```java
class Twitter {
    private static class Tweet {
        int id, time; Tweet next;
        Tweet(int id, int time, Tweet next) { this.id=id; this.time=time; this.next=next; }
    }
    private int clock = 0;
    private final Map<Integer, Tweet> tweets = new HashMap<>();
    private final Map<Integer, Set<Integer>> follows = new HashMap<>();
    public void postTweet(int userId, int tweetId) {
        tweets.put(userId, new Tweet(tweetId, clock++, tweets.get(userId)));
    }
    public List<Integer> getNewsFeed(int userId) {
        Set<Integer> users = new HashSet<>(follows.getOrDefault(userId, Set.of()));
        users.add(userId);
        PriorityQueue<Tweet> pq = new PriorityQueue<>((a,b) -> Integer.compare(b.time, a.time));
        for (int u : users) if (tweets.get(u) != null) pq.offer(tweets.get(u));
        List<Integer> ans = new ArrayList<>();
        while (!pq.isEmpty() && ans.size() < 10) {
            Tweet t = pq.poll(); ans.add(t.id); if (t.next != null) pq.offer(t.next);
        }
        return ans;
    }
    public void follow(int followerId, int followeeId) {
        if (followerId != followeeId) follows.computeIfAbsent(followerId, x -> new HashSet<>()).add(followeeId);
    }
    public void unfollow(int followerId, int followeeId) {
        Set<Integer> set = follows.get(followerId);
        if (set != null) set.remove(followeeId);
    }
}
```

### 116. [Single Threaded CPU](https://leetcode.com/problems/single-threaded-cpu/) — Medium

- [ ] **Revised**
- **Recognition cue:** Sort by enqueue time + execution heap
- **Approach ladder:** 1. Tick time one unit at a time — too slow. 2. Sort tasks by arrival and heap available tasks by `(processing,index)` — O(n log n) **(preferred)**.
- **Preferred pattern:** Sort by enqueue time + execution heap
- **Preferred complexity:** O(n log n) time, O(n) space

```java
class Solution {
    public int[] getOrder(int[][] tasks) {
        int n = tasks.length;
        int[][] a = new int[n][3];
        for (int i = 0; i < n; i++) a[i] = new int[]{tasks[i][0], tasks[i][1], i};
        Arrays.sort(a, Comparator.comparingInt(x -> x[0]));
        PriorityQueue<int[]> pq = new PriorityQueue<>((x,y) -> x[1] != y[1] ? Integer.compare(x[1],y[1]) : Integer.compare(x[2],y[2]));
        int[] ans = new int[n]; int i = 0, p = 0; long time = 0;
        while (p < n) {
            if (pq.isEmpty() && time < a[i][0]) time = a[i][0];
            while (i < n && a[i][0] <= time) pq.offer(a[i++]);
            int[] t = pq.poll(); ans[p++] = t[2]; time += t[1];
        }
        return ans;
    }
}
```

### 117. [Reorganize String](https://leetcode.com/problems/reorganize-string/) — Medium

- [ ] **Revised**
- **Recognition cue:** Greedy max-heap
- **Approach ladder:** 1. Backtracking — exponential. 2. Place most frequent chars in alternating indices. 3. Max-heap, hold previous char for one turn — O(n log alphabet) **(preferred general form)**.
- **Preferred pattern:** Greedy max-heap
- **Preferred complexity:** O(n log A) time, O(A) space

```java
class Solution {
    public String reorganizeString(String s) {
        int[] f = new int[26]; for (char c : s.toCharArray()) f[c-'a']++;
        PriorityQueue<int[]> pq = new PriorityQueue<>((a,b) -> b[1]-a[1]);
        for (int i = 0; i < 26; i++) if (f[i] > 0) pq.offer(new int[]{i,f[i]});
        StringBuilder out = new StringBuilder(); int[] prev = null;
        while (!pq.isEmpty()) {
            int[] cur = pq.poll(); out.append((char)('a'+cur[0])); cur[1]--;
            if (prev != null && prev[1] > 0) pq.offer(prev);
            prev = cur;
        }
        return out.length() == s.length() ? out.toString() : "";
    }
}
```

### 118. [Longest Happy String](https://leetcode.com/problems/longest-happy-string/) — Medium

- [ ] **Revised**
- **Recognition cue:** Greedy max-heap with local constraint
- **Approach ladder:** 1. Backtracking/DP over remaining counts. 2. Always use most frequent unless it would create three equal chars; then use second — O(total chars log 3) **(preferred)**.
- **Preferred pattern:** Greedy max-heap with local constraint
- **Preferred complexity:** O(a+b+c) time, O(1) space

```java
class Solution {
    public String longestDiverseString(int a, int b, int c) {
        PriorityQueue<int[]> pq = new PriorityQueue<>((x,y) -> y[1]-x[1]);
        if (a>0) pq.offer(new int[]{0,a}); if (b>0) pq.offer(new int[]{1,b}); if (c>0) pq.offer(new int[]{2,c});
        StringBuilder out = new StringBuilder();
        while (!pq.isEmpty()) {
            int[] first = pq.poll(); int n = out.length();
            char ch = (char)('a'+first[0]);
            if (n >= 2 && out.charAt(n-1)==ch && out.charAt(n-2)==ch) {
                if (pq.isEmpty()) break;
                int[] second = pq.poll(); out.append((char)('a'+second[0]));
                if (--second[1] > 0) pq.offer(second); pq.offer(first);
            } else {
                out.append(ch); if (--first[1] > 0) pq.offer(first);
            }
        }
        return out.toString();
    }
}
```

### 119. [Car Pooling](https://leetcode.com/problems/car-pooling/) — Medium

- [ ] **Revised**
- **Recognition cue:** Difference array / event sweep
- **Approach ladder:** 1. Simulate every passenger. 2. Sort pickup/drop events — O(n log n). 3. Difference array over bounded locations — O(n+U) **(preferred for constraints)**.
- **Preferred pattern:** Difference array / event sweep
- **Preferred complexity:** O(n+U) time, O(U) space
- **Pitfall:** Passengers exit at `to` before any capacity check for later positions; the difference sweep handles this naturally.

```java
class Solution {
    public boolean carPooling(int[][] trips, int capacity) {
        int[] delta = new int[1001];
        for (int[] t : trips) { delta[t[1]] += t[0]; delta[t[2]] -= t[0]; }
        int load = 0;
        for (int x : delta) { load += x; if (load > capacity) return false; }
        return true;
    }
}
```

### 120. [Find Median From Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) — Hard

- [ ] **Revised**
- **Recognition cue:** Maintain online median under insertions.
- **Approach ladder:** 1. Fully sort all candidates — O(n log n). 2. Heap, quickselect, bucket, or streaming structure depending whether all order statistics are needed. 3. **Preferred:** Two heaps — O(log n) add, O(1) median, O(n) space.
- **Preferred pattern:** Two heaps
- **Preferred complexity:** O(log n) add, O(1) median, O(n) space
- **Invariant / state:** Max-heap lower contains same count as or one more than min-heap upper; all lower values <= upper values.

```java
class MedianFinder {
    private final PriorityQueue<Integer> lower = new PriorityQueue<>(Comparator.reverseOrder());
    private final PriorityQueue<Integer> upper = new PriorityQueue<>();
    public void addNum(int num) {
        lower.add(num);
        upper.add(lower.remove());
        if (upper.size() > lower.size()) lower.add(upper.remove());
    }
    public double findMedian() {
        if (lower.size() > upper.size()) return lower.element();
        return ((double) lower.element() + upper.element()) / 2.0;
    }
}
```

### 121. [IPO](https://leetcode.com/problems/ipo/) — Hard

- [ ] **Revised**
- **Recognition cue:** At each step choose maximum profit among currently affordable projects.
- **Approach ladder:** 1. Fully sort all candidates — O(n log n). 2. Heap, quickselect, bucket, or streaming structure depending whether all order statistics are needed. 3. **Preferred:** Sort by constraint + max heap by reward — O(n log n + k log n) time, O(n) space.
- **Preferred pattern:** Sort by constraint + max heap by reward
- **Preferred complexity:** O(n log n + k log n) time, O(n) space
- **Invariant / state:** Sorted pointer adds every newly affordable project; heap contains exactly feasible choices.

```java
class Solution {
    public int findMaximizedCapital(int k, int w, int[] profits, int[] capital) {
        int n = profits.length;
        int[][] projects = new int[n][2];
        for (int i = 0; i < n; i++) projects[i] = new int[]{capital[i], profits[i]};
        Arrays.sort(projects, Comparator.comparingInt(a -> a[0]));
        PriorityQueue<Integer> best = new PriorityQueue<>(Comparator.reverseOrder());
        int i = 0;
        while (k-- > 0) {
            while (i < n && projects[i][0] <= w) best.add(projects[i++][1]);
            if (best.isEmpty()) break;
            w += best.remove();
        }
        return w;
    }
}
```

---

## Backtracking

### 122. [Sum of All Subsets XOR Total](https://leetcode.com/problems/sum-of-all-subsets-xor-total/) — Easy

- [ ] **Revised**
- **Recognition cue:** Include/exclude DFS
- **Approach ladder:** 1. Enumerate bitmasks — O(n·2ⁿ). 2. DFS carrying current XOR — O(2ⁿ) calls **(preferred)**. 3. Closed-form bit observation exists, but DFS is the reusable interview pattern.
- **Preferred pattern:** Include/exclude DFS
- **Preferred complexity:** O(2^n) time, O(n) recursion space

```java
class Solution {
    public int subsetXORSum(int[] nums) { return dfs(nums, 0, 0); }
    private int dfs(int[] a, int i, int xor) {
        if (i == a.length) return xor;
        return dfs(a, i + 1, xor) + dfs(a, i + 1, xor ^ a[i]);
    }
}
```

### 123. [Subsets](https://leetcode.com/problems/subsets/) — Medium

- [ ] **Revised**
- **Recognition cue:** Backtracking / iterative power set
- **Approach ladder:** 1. Bitmask enumeration — O(n·2ⁿ). 2. Iteratively duplicate existing subsets. 3. Include/exclude DFS — O(n·2ⁿ) output time **(preferred template)**.
- **Preferred pattern:** Backtracking / iterative power set
- **Preferred complexity:** O(n·2^n) time including output, O(n) recursion excluding output

```java
class Solution {
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> ans = new ArrayList<>();
        dfs(nums, 0, new ArrayList<>(), ans); return ans;
    }
    private void dfs(int[] a, int i, List<Integer> cur, List<List<Integer>> ans) {
        if (i == a.length) { ans.add(new ArrayList<>(cur)); return; }
        dfs(a, i + 1, cur, ans);
        cur.add(a[i]); dfs(a, i + 1, cur, ans); cur.remove(cur.size() - 1);
    }
}
```

### 124. [Combination Sum](https://leetcode.com/problems/combination-sum/) — Medium

- [ ] **Revised**
- **Recognition cue:** Choose numbers repeatedly to reach a target.
- **Approach ladder:** 1. Generate every state and validate at the leaf. 2. Incremental validation, sorting, symmetry pruning, or memoization. 3. **Preferred:** Reusable-choice backtracking — Exponential output-dependent time, O(target/minValue) recursion.
- **Preferred pattern:** Reusable-choice backtracking
- **Preferred complexity:** Exponential output-dependent time, O(target/minValue) recursion
- **Invariant / state:** Passing i again permits reuse; sorted candidates allow sum-based pruning.

```java
class Solution {
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        Arrays.sort(candidates);
        List<List<Integer>> ans = new ArrayList<>();
        dfs(candidates, 0, target, new ArrayList<>(), ans);
        return ans;
    }
    private void dfs(int[] a, int start, int remaining, List<Integer> path, List<List<Integer>> ans) {
        if (remaining == 0) { ans.add(new ArrayList<>(path)); return; }
        for (int i = start; i < a.length && a[i] <= remaining; i++) {
            path.add(a[i]);
            dfs(a, i, remaining - a[i], path, ans);
            path.remove(path.size() - 1);
        }
    }
}
```

### 125. [Combination Sum II](https://leetcode.com/problems/combination-sum-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Sorted backtracking with duplicate skipping
- **Approach ladder:** 1. Enumerate all subsets and deduplicate with a set. 2. Sort; choose each index once and skip equal siblings — exponential but output-sensitive **(preferred)**.
- **Preferred pattern:** Sorted backtracking with duplicate skipping
- **Preferred complexity:** O(2^n) worst-case time, O(n) recursion excluding output
- **Pitfall:** Skip equal values only at the same recursion depth (`i > start`).

```java
class Solution {
    public List<List<Integer>> combinationSum2(int[] candidates, int target) {
        Arrays.sort(candidates); List<List<Integer>> ans = new ArrayList<>();
        dfs(candidates, 0, target, new ArrayList<>(), ans); return ans;
    }
    private void dfs(int[] a, int start, int remain, List<Integer> cur, List<List<Integer>> ans) {
        if (remain == 0) { ans.add(new ArrayList<>(cur)); return; }
        for (int i = start; i < a.length && a[i] <= remain; i++) {
            if (i > start && a[i] == a[i - 1]) continue;
            cur.add(a[i]); dfs(a, i + 1, remain - a[i], cur, ans); cur.remove(cur.size() - 1);
        }
    }
}
```

### 126. [Combinations](https://leetcode.com/problems/combinations/) — Medium

- [ ] **Revised**
- **Recognition cue:** Generate all size-k selections from 1..n.
- **Approach ladder:** 1. Generate every state and validate at the leaf. 2. Incremental validation, sorting, symmetry pruning, or memoization. 3. **Preferred:** Choose/skip search with pruning — O(C(n,k) * k) output time, O(k) recursion space.
- **Preferred pattern:** Choose/skip search with pruning
- **Preferred complexity:** O(C(n,k) * k) output time, O(k) recursion space
- **Invariant / state:** Start index prevents permutations; upper bound leaves enough remaining values.

```java
class Solution {
    public List<List<Integer>> combine(int n, int k) {
        List<List<Integer>> ans = new ArrayList<>();
        dfs(1, n, k, new ArrayList<>(), ans);
        return ans;
    }
    private void dfs(int start, int n, int k, List<Integer> path, List<List<Integer>> ans) {
        if (path.size() == k) { ans.add(new ArrayList<>(path)); return; }
        int needed = k - path.size();
        for (int x = start; x <= n - needed + 1; x++) {
            path.add(x);
            dfs(x + 1, n, k, path, ans);
            path.remove(path.size() - 1);
        }
    }
}
```

### 127. [Permutations](https://leetcode.com/problems/permutations/) — Medium

- [ ] **Revised**
- **Recognition cue:** Generate every ordering of distinct values.
- **Approach ladder:** 1. Generate every state and validate at the leaf. 2. Incremental validation, sorting, symmetry pruning, or memoization. 3. **Preferred:** Used-set backtracking — O(n! * n) output time, O(n) recursion/used space.
- **Preferred pattern:** Used-set backtracking
- **Preferred complexity:** O(n! * n) output time, O(n) recursion/used space
- **Invariant / state:** used[i] means nums[i] is already in the current path.

```java
class Solution {
    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> ans = new ArrayList<>();
        dfs(nums, new boolean[nums.length], new ArrayList<>(), ans);
        return ans;
    }
    private void dfs(int[] nums, boolean[] used, List<Integer> path, List<List<Integer>> ans) {
        if (path.size() == nums.length) { ans.add(new ArrayList<>(path)); return; }
        for (int i = 0; i < nums.length; i++) {
            if (used[i]) continue;
            used[i] = true; path.add(nums[i]);
            dfs(nums, used, path, ans);
            path.remove(path.size() - 1); used[i] = false;
        }
    }
}
```

### 128. [Subsets II](https://leetcode.com/problems/subsets-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Sorted grouped backtracking
- **Approach ladder:** 1. Generate all subsets into a HashSet. 2. Sort and skip equal sibling choices — O(n·2ⁿ) **(preferred)**.
- **Preferred pattern:** Sorted grouped backtracking
- **Preferred complexity:** O(n·2^n) output time, O(n) recursion

```java
class Solution {
    public List<List<Integer>> subsetsWithDup(int[] nums) {
        Arrays.sort(nums); List<List<Integer>> ans = new ArrayList<>();
        dfs(nums, 0, new ArrayList<>(), ans); return ans;
    }
    private void dfs(int[] a, int start, List<Integer> cur, List<List<Integer>> ans) {
        ans.add(new ArrayList<>(cur));
        for (int i = start; i < a.length; i++) {
            if (i > start && a[i] == a[i - 1]) continue;
            cur.add(a[i]); dfs(a, i + 1, cur, ans); cur.remove(cur.size() - 1);
        }
    }
}
```

### 129. [Permutations II](https://leetcode.com/problems/permutations-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Sorted used-array backtracking
- **Approach ladder:** 1. Generate all permutations and deduplicate. 2. Frequency map recursion. 3. Sort + used array; skip an equal value when its previous copy is unused — O(n·n!) **(preferred)**.
- **Preferred pattern:** Sorted used-array backtracking
- **Preferred complexity:** O(n·n!) output time, O(n) auxiliary space

```java
class Solution {
    public List<List<Integer>> permuteUnique(int[] nums) {
        Arrays.sort(nums); List<List<Integer>> ans = new ArrayList<>();
        dfs(nums, new boolean[nums.length], new ArrayList<>(), ans); return ans;
    }
    private void dfs(int[] a, boolean[] used, List<Integer> cur, List<List<Integer>> ans) {
        if (cur.size() == a.length) { ans.add(new ArrayList<>(cur)); return; }
        for (int i = 0; i < a.length; i++) {
            if (used[i] || (i > 0 && a[i] == a[i - 1] && !used[i - 1])) continue;
            used[i] = true; cur.add(a[i]); dfs(a, used, cur, ans);
            cur.remove(cur.size() - 1); used[i] = false;
        }
    }
}
```

### 130. [Word Search](https://leetcode.com/problems/word-search/) — Medium

- [ ] **Revised**
- **Recognition cue:** Match a word through adjacent cells without reusing a cell.
- **Approach ladder:** 1. Generate every state and validate at the leaf. 2. Incremental validation, sorting, symmetry pruning, or memoization. 3. **Preferred:** Grid path backtracking — O(mn * 3^L) worst case, O(L) recursion space.
- **Preferred pattern:** Grid path backtracking
- **Preferred complexity:** O(mn * 3^L) worst case, O(L) recursion space
- **Invariant / state:** Mark current cell before exploring and restore it on return.

```java
class Solution {
    public boolean exist(char[][] board, String word) {
        for (int r = 0; r < board.length; r++)
            for (int c = 0; c < board[0].length; c++)
                if (dfs(board, word, 0, r, c)) return true;
        return false;
    }
    private boolean dfs(char[][] b, String w, int i, int r, int c) {
        if (i == w.length()) return true;
        if (r < 0 || r == b.length || c < 0 || c == b[0].length || b[r][c] != w.charAt(i)) return false;
        char saved = b[r][c];
        b[r][c] = '#';
        boolean found = dfs(b, w, i + 1, r + 1, c) || dfs(b, w, i + 1, r - 1, c)
                || dfs(b, w, i + 1, r, c + 1) || dfs(b, w, i + 1, r, c - 1);
        b[r][c] = saved;
        return found;
    }
}
```

### 131. [Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/) — Medium

- [ ] **Revised**
- **Recognition cue:** Backtracking over palindrome prefixes
- **Approach ladder:** 1. Try every partition and test substrings repeatedly. 2. Precompute palindrome DP then backtrack. 3. Expand/test during DFS; O(n·2ⁿ) worst and simpler **(preferred for revision)**.
- **Preferred pattern:** Backtracking over palindrome prefixes
- **Preferred complexity:** O(n·2^n) worst time, O(n) recursion excluding output

```java
class Solution {
    public List<List<String>> partition(String s) {
        List<List<String>> ans = new ArrayList<>();
        dfs(s, 0, new ArrayList<>(), ans); return ans;
    }
    private void dfs(String s, int start, List<String> cur, List<List<String>> ans) {
        if (start == s.length()) { ans.add(new ArrayList<>(cur)); return; }
        for (int end = start; end < s.length(); end++) if (pal(s, start, end)) {
            cur.add(s.substring(start, end + 1));
            dfs(s, end + 1, cur, ans); cur.remove(cur.size() - 1);
        }
    }
    private boolean pal(String s, int l, int r) {
        while (l < r) if (s.charAt(l++) != s.charAt(r--)) return false;
        return true;
    }
}
```

### 132. [Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) — Medium

- [ ] **Revised**
- **Recognition cue:** Choose one mapped character for each digit.
- **Approach ladder:** 1. Generate every state and validate at the leaf. 2. Incremental validation, sorting, symmetry pruning, or memoization. 3. **Preferred:** Cartesian-product backtracking — O(4^n * n) output time, O(n) recursion space.
- **Preferred pattern:** Cartesian-product backtracking
- **Preferred complexity:** O(4^n * n) output time, O(n) recursion space
- **Invariant / state:** Path length equals processed digit count; undo after each branch.

```java
class Solution {
    private static final String[] MAP = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    public List<String> letterCombinations(String digits) {
        List<String> ans = new ArrayList<>();
        if (digits.isEmpty()) return ans;
        dfs(digits, 0, new StringBuilder(), ans);
        return ans;
    }
    private void dfs(String digits, int i, StringBuilder path, List<String> ans) {
        if (i == digits.length()) { ans.add(path.toString()); return; }
        for (char c : MAP[digits.charAt(i) - '0'].toCharArray()) {
            path.append(c);
            dfs(digits, i + 1, path, ans);
            path.deleteCharAt(path.length() - 1);
        }
    }
}
```

### 133. [Matchsticks to Square](https://leetcode.com/problems/matchsticks-to-square/) — Medium

- [ ] **Revised**
- **Recognition cue:** Bin-packing backtracking with symmetry pruning
- **Approach ladder:** 1. Assign each matchstick to four sides — O(4ⁿ). 2. Sort descending, prune equal side states and overflow — same worst case but much faster **(preferred)**.
- **Preferred pattern:** Bin-packing backtracking with symmetry pruning
- **Preferred complexity:** O(4^n) worst time, O(n) recursion
- **Pitfall:** Descending order makes impossible branches fail early.

```java
class Solution {
    public boolean makesquare(int[] matchsticks) {
        int sum = Arrays.stream(matchsticks).sum();
        if (sum % 4 != 0) return false;
        Arrays.sort(matchsticks);
        for (int l = 0, r = matchsticks.length - 1; l < r; l++, r--) {
            int t = matchsticks[l]; matchsticks[l] = matchsticks[r]; matchsticks[r] = t;
        }
        return dfs(matchsticks, 0, new int[4], sum / 4);
    }
    private boolean dfs(int[] a, int i, int[] side, int target) {
        if (i == a.length) return side[0] == target && side[1] == target && side[2] == target;
        for (int s = 0; s < 4; s++) {
            if (side[s] + a[i] > target) continue;
            if (s > 0 && side[s] == side[s - 1]) continue;
            side[s] += a[i]; if (dfs(a, i + 1, side, target)) return true; side[s] -= a[i];
        }
        return false;
    }
}
```

### 134. [Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/) — Medium

- [ ] **Revised**
- **Recognition cue:** Bucket backtracking with symmetry pruning
- **Approach ladder:** 1. Subset DP over masks — O(n·2ⁿ), excellent when n is small. 2. Assign descending numbers to k equal buckets with symmetry pruning — O(kⁿ) worst **(preferred intuitive solution)**.
- **Preferred pattern:** Bucket backtracking with symmetry pruning
- **Preferred complexity:** O(k^n) worst time, O(n+k) space

```java
class Solution {
    public boolean canPartitionKSubsets(int[] nums, int k) {
        int sum = Arrays.stream(nums).sum();
        if (sum % k != 0) return false;
        Arrays.sort(nums);
        for (int l=0,r=nums.length-1;l<r;l++,r--){int t=nums[l];nums[l]=nums[r];nums[r]=t;}
        int target = sum / k;
        if (nums[0] > target) return false;
        return dfs(nums, 0, new int[k], target);
    }
    private boolean dfs(int[] a, int i, int[] bucket, int target) {
        if (i == a.length) return true;
        for (int b = 0; b < bucket.length; b++) {
            if (bucket[b] + a[i] > target) continue;
            if (b > 0 && bucket[b] == bucket[b - 1]) continue;
            bucket[b] += a[i]; if (dfs(a, i + 1, bucket, target)) return true; bucket[b] -= a[i];
            if (bucket[b] == 0) break;
        }
        return false;
    }
}
```

### 135. [Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) — Medium

- [ ] **Revised**
- **Recognition cue:** Generate all balanced strings with n pairs.
- **Approach ladder:** 1. Generate every state and validate at the leaf. 2. Incremental validation, sorting, symmetry pruning, or memoization. 3. **Preferred:** Validity-preserving generation — O(Catalan(n) * n) output time, O(n) recursion space.
- **Preferred pattern:** Validity-preserving generation
- **Preferred complexity:** O(Catalan(n) * n) output time, O(n) recursion space
- **Invariant / state:** May add '(' while open<n; may add ')' only when close<open.

```java
class Solution {
    public List<String> generateParenthesis(int n) {
        List<String> ans = new ArrayList<>();
        dfs(n, 0, 0, new StringBuilder(), ans);
        return ans;
    }
    private void dfs(int n, int open, int close, StringBuilder path, List<String> ans) {
        if (path.length() == 2 * n) { ans.add(path.toString()); return; }
        if (open < n) {
            path.append('('); dfs(n, open + 1, close, path, ans); path.deleteCharAt(path.length() - 1);
        }
        if (close < open) {
            path.append(')'); dfs(n, open, close + 1, path, ans); path.deleteCharAt(path.length() - 1);
        }
    }
}
```

### 136. [N Queens](https://leetcode.com/problems/n-queens/) — Hard

- [ ] **Revised**
- **Recognition cue:** Row-by-row constraint backtracking
- **Approach ladder:** 1. Validate the board after every placement. 2. Track occupied columns and both diagonals in sets/boolean arrays — O(n!) worst **(preferred)**. 3. Bitmask recursion is the fastest constant-factor variant.
- **Preferred pattern:** Row-by-row constraint backtracking
- **Preferred complexity:** O(n!) worst time, O(n²) output/board space

```java
class Solution {
    public List<List<String>> solveNQueens(int n) {
        List<List<String>> ans = new ArrayList<>();
        char[][] b = new char[n][n]; for (char[] row : b) Arrays.fill(row, '.');
        dfs(0, b, new boolean[n], new boolean[2*n], new boolean[2*n], ans);
        return ans;
    }
    private void dfs(int r, char[][] b, boolean[] col, boolean[] d1, boolean[] d2, List<List<String>> ans) {
        int n = b.length;
        if (r == n) { List<String> x = new ArrayList<>(); for (char[] row : b) x.add(new String(row)); ans.add(x); return; }
        for (int c = 0; c < n; c++) {
            int a = r - c + n, z = r + c;
            if (col[c] || d1[a] || d2[z]) continue;
            col[c] = d1[a] = d2[z] = true; b[r][c] = 'Q';
            dfs(r + 1, b, col, d1, d2, ans);
            b[r][c] = '.'; col[c] = d1[a] = d2[z] = false;
        }
    }
}
```

### 137. [N Queens II](https://leetcode.com/problems/n-queens-ii/) — Hard

- [ ] **Revised**
- **Recognition cue:** Place one queen per row without sharing columns or diagonals.
- **Approach ladder:** 1. Generate every state and validate at the leaf. 2. Incremental validation, sorting, symmetry pruning, or memoization. 3. **Preferred:** Constraint backtracking with bitsets/sets — O(n!) upper-bound time, O(n) recursion/constraint space.
- **Preferred pattern:** Constraint backtracking with bitsets/sets
- **Preferred complexity:** O(n!) upper-bound time, O(n) recursion/constraint space
- **Invariant / state:** At row r, occupied columns, r-c diagonals, and r+c diagonals define illegal positions.

```java
class Solution {
    public int totalNQueens(int n) {
        return dfs(0, n, new boolean[n], new boolean[2 * n], new boolean[2 * n]);
    }
    private int dfs(int r, int n, boolean[] col, boolean[] diag1, boolean[] diag2) {
        if (r == n) return 1;
        int count = 0;
        for (int c = 0; c < n; c++) {
            int d1 = r - c + n, d2 = r + c;
            if (col[c] || diag1[d1] || diag2[d2]) continue;
            col[c] = diag1[d1] = diag2[d2] = true;
            count += dfs(r + 1, n, col, diag1, diag2);
            col[c] = diag1[d1] = diag2[d2] = false;
        }
        return count;
    }
}
```

### 138. [Word Break II](https://leetcode.com/problems/word-break-ii/) — Hard

- [ ] **Revised**
- **Recognition cue:** Memoized suffix decomposition
- **Approach ladder:** 1. Backtrack all cuts without memoization — exponential repeated work. 2. DFS from index with memoized sentence lists — output-exponential but avoids duplicate states **(preferred)**.
- **Preferred pattern:** Memoized suffix decomposition
- **Preferred complexity:** O(n² + total output characters) typical, output-exponential worst; O(n + output) space

```java
class Solution {
    public List<String> wordBreak(String s, List<String> wordDict) {
        return dfs(s, 0, new HashSet<>(wordDict), new HashMap<>());
    }
    private List<String> dfs(String s, int i, Set<String> dict, Map<Integer,List<String>> memo) {
        if (memo.containsKey(i)) return memo.get(i);
        List<String> ans = new ArrayList<>();
        if (i == s.length()) { ans.add(""); return ans; }
        for (int j = i + 1; j <= s.length(); j++) {
            String word = s.substring(i, j);
            if (!dict.contains(word)) continue;
            for (String tail : dfs(s, j, dict, memo))
                ans.add(tail.isEmpty() ? word : word + " " + tail);
        }
        memo.put(i, ans); return ans;
    }
}
```

---

## Tries

### 139. [Implement Trie Prefix Tree](https://leetcode.com/problems/implement-trie-prefix-tree/) — Medium

- [ ] **Revised**
- **Recognition cue:** Support insert, exact search, and prefix search.
- **Approach ladder:** 1. Scan dictionary words or use a HashSet. 2. Prefix tree to share repeated prefix work. 3. **Preferred:** Trie node traversal — O(L) per operation, O(total inserted characters) space.
- **Preferred pattern:** Trie node traversal
- **Preferred complexity:** O(L) per operation, O(total inserted characters) space
- **Invariant / state:** Each path represents a prefix; terminal flag distinguishes complete words.

```java
class Trie {
    private static class Node {
        Node[] next = new Node[26];
        boolean word;
    }
    private final Node root = new Node();
    public void insert(String word) {
        Node cur = root;
        for (char c : word.toCharArray()) {
            int i = c - 'a';
            if (cur.next[i] == null) cur.next[i] = new Node();
            cur = cur.next[i];
        }
        cur.word = true;
    }
    public boolean search(String word) {
        Node node = find(word);
        return node != null && node.word;
    }
    public boolean startsWith(String prefix) { return find(prefix) != null; }
    private Node find(String s) {
        Node cur = root;
        for (char c : s.toCharArray()) {
            cur = cur.next[c - 'a'];
            if (cur == null) return null;
        }
        return cur;
    }
}
```

### 140. [Design Add And Search Words Data Structure](https://leetcode.com/problems/design-add-and-search-words-data-structure/) — Medium

- [ ] **Revised**
- **Recognition cue:** Search supports '.' matching any one character.
- **Approach ladder:** 1. Scan dictionary words or use a HashSet. 2. Prefix tree to share repeated prefix work. 3. **Preferred:** Trie + wildcard DFS — O(26^wildcards * L) worst case, O(total characters) space.
- **Preferred pattern:** Trie + wildcard DFS
- **Preferred complexity:** O(26^wildcards * L) worst case, O(total characters) space
- **Invariant / state:** Normal characters choose one edge; wildcard branches over all existing edges.

```java
class WordDictionary {
    private static class Node { Node[] next = new Node[26]; boolean word; }
    private final Node root = new Node();
    public void addWord(String word) {
        Node cur = root;
        for (char c : word.toCharArray()) {
            int i = c - 'a';
            if (cur.next[i] == null) cur.next[i] = new Node();
            cur = cur.next[i];
        }
        cur.word = true;
    }
    public boolean search(String word) { return dfs(word, 0, root); }
    private boolean dfs(String s, int i, Node node) {
        if (i == s.length()) return node.word;
        char c = s.charAt(i);
        if (c != '.') {
            Node next = node.next[c - 'a'];
            return next != null && dfs(s, i + 1, next);
        }
        for (Node next : node.next)
            if (next != null && dfs(s, i + 1, next)) return true;
        return false;
    }
}
```

### 141. [Extra Characters in a String](https://leetcode.com/problems/extra-characters-in-a-string/) — Medium

- [ ] **Revised**
- **Recognition cue:** Suffix DP + trie traversal
- **Approach ladder:** 1. DP trying every dictionary word at every index — O(n·D·L). 2. HashSet substring DP — O(n²). 3. Trie + DP, walking valid prefixes from each index — O(n·Lmax) **(preferred)**.
- **Preferred pattern:** Suffix DP + trie traversal
- **Preferred complexity:** O(n·Lmax + dictionary characters) time, O(n + dictionary characters) space

```java
class Solution {
    private static class Node { Node[] next = new Node[26]; boolean word; }
    public int minExtraChar(String s, String[] dictionary) {
        Node root = new Node();
        for (String w : dictionary) { Node p = root; for (char c : w.toCharArray()) p = p.next[c-'a'] == null ? (p.next[c-'a'] = new Node()) : p.next[c-'a']; p.word = true; }
        int n = s.length(); int[] dp = new int[n + 1];
        for (int i = n - 1; i >= 0; i--) {
            dp[i] = 1 + dp[i + 1]; Node p = root;
            for (int j = i; j < n && p.next[s.charAt(j)-'a'] != null; j++) {
                p = p.next[s.charAt(j)-'a'];
                if (p.word) dp[i] = Math.min(dp[i], dp[j + 1]);
            }
        }
        return dp[0];
    }
}
```

### 142. [Word Search II](https://leetcode.com/problems/word-search-ii/) — Hard

- [ ] **Revised**
- **Recognition cue:** Find many dictionary words in a character grid.
- **Approach ladder:** 1. Scan dictionary words or use a HashSet. 2. Prefix tree to share repeated prefix work. 3. **Preferred:** Trie-pruned grid backtracking — O(mn * branching depth) worst case, O(total dictionary chars) space.
- **Preferred pattern:** Trie-pruned grid backtracking
- **Preferred complexity:** O(mn * branching depth) worst case, O(total dictionary chars) space
- **Invariant / state:** Trie removes searches with impossible prefixes; nulling found word deduplicates output.

```java
class Solution {
    private static class TrieNode {
        TrieNode[] next = new TrieNode[26];
        String word;
    }
    public List<String> findWords(char[][] board, String[] words) {
        TrieNode root = new TrieNode();
        for (String word : words) insert(root, word);
        List<String> ans = new ArrayList<>();
        for (int r = 0; r < board.length; r++)
            for (int c = 0; c < board[0].length; c++) dfs(board, r, c, root, ans);
        return ans;
    }
    private void insert(TrieNode root, String word) {
        TrieNode cur = root;
        for (char c : word.toCharArray()) {
            int i = c - 'a';
            if (cur.next[i] == null) cur.next[i] = new TrieNode();
            cur = cur.next[i];
        }
        cur.word = word;
    }
    private void dfs(char[][] b, int r, int c, TrieNode node, List<String> ans) {
        if (r < 0 || r == b.length || c < 0 || c == b[0].length || b[r][c] == '#') return;
        char ch = b[r][c];
        TrieNode next = node.next[ch - 'a'];
        if (next == null) return;
        if (next.word != null) { ans.add(next.word); next.word = null; }
        b[r][c] = '#';
        dfs(b, r + 1, c, next, ans); dfs(b, r - 1, c, next, ans);
        dfs(b, r, c + 1, next, ans); dfs(b, r, c - 1, next, ans);
        b[r][c] = ch;
    }
}
```

---

## Graphs

### 143. [Island Perimeter](https://leetcode.com/problems/island-perimeter/) — Easy

- [ ] **Revised**
- **Recognition cue:** Local edge counting
- **Approach ladder:** 1. DFS and count water boundaries. 2. For each land cell add 4, subtract 2 for each shared top/left edge — O(mn) **(preferred)**.
- **Preferred pattern:** Local edge counting
- **Preferred complexity:** O(mn) time, O(1) space

```java
class Solution {
    public int islandPerimeter(int[][] grid) {
        int ans = 0;
        for (int r = 0; r < grid.length; r++) for (int c = 0; c < grid[0].length; c++) if (grid[r][c] == 1) {
            ans += 4;
            if (r > 0 && grid[r-1][c] == 1) ans -= 2;
            if (c > 0 && grid[r][c-1] == 1) ans -= 2;
        }
        return ans;
    }
}
```

### 144. [Verifying An Alien Dictionary](https://leetcode.com/problems/verifying-an-alien-dictionary/) — Easy

- [ ] **Revised**
- **Recognition cue:** Custom lexicographic comparator
- **Approach ladder:** 1. Transform every word into rank arrays then compare. 2. Compare adjacent words using a rank table — O(total characters) **(preferred)**.
- **Preferred pattern:** Custom lexicographic comparator
- **Preferred complexity:** O(total characters) time, O(1) space
- **Pitfall:** When one word is a prefix, the shorter word must come first.

```java
class Solution {
    public boolean isAlienSorted(String[] words, String order) {
        int[] rank = new int[26]; for (int i = 0; i < 26; i++) rank[order.charAt(i)-'a'] = i;
        for (int i = 1; i < words.length; i++) if (!le(words[i-1], words[i], rank)) return false;
        return true;
    }
    private boolean le(String a, String b, int[] rank) {
        int n = Math.min(a.length(), b.length());
        for (int i = 0; i < n; i++) if (a.charAt(i) != b.charAt(i)) return rank[a.charAt(i)-'a'] < rank[b.charAt(i)-'a'];
        return a.length() <= b.length();
    }
}
```

### 145. [Find the Town Judge](https://leetcode.com/problems/find-the-town-judge/) — Easy

- [ ] **Revised**
- **Recognition cue:** Net trust degree
- **Approach ladder:** 1. Build adjacency sets and inspect each person. 2. Score `+1` incoming and `-1` outgoing; judge score is n-1 — O(n+trust) **(preferred)**.
- **Preferred pattern:** Net trust degree
- **Preferred complexity:** O(n + trust.length) time, O(n) space

```java
class Solution {
    public int findJudge(int n, int[][] trust) {
        int[] score = new int[n + 1];
        for (int[] e : trust) { score[e[0]]--; score[e[1]]++; }
        for (int i = 1; i <= n; i++) if (score[i] == n - 1) return i;
        return -1;
    }
}
```

### 146. [Number of Islands](https://leetcode.com/problems/number-of-islands/) — Medium

- [ ] **Revised**
- **Recognition cue:** Count connected components in a binary grid.
- **Approach ladder:** 1. DFS/BFS with explicit visited state. 2. DSU, topological sort, multi-source BFS, or shortest-path formulation when structure permits. 3. **Preferred:** Grid flood fill — O(mn) time, O(mn) worst-case recursion/queue.
- **Preferred pattern:** Grid flood fill
- **Preferred complexity:** O(mn) time, O(mn) worst-case recursion/queue
- **Invariant / state:** When an unvisited land cell is found, one DFS/BFS consumes exactly that island.

```java
class Solution {
    public int numIslands(char[][] grid) {
        int count = 0;
        for (int r = 0; r < grid.length; r++)
            for (int c = 0; c < grid[0].length; c++)
                if (grid[r][c] == '1') { count++; dfs(grid, r, c); }
        return count;
    }
    private void dfs(char[][] g, int r, int c) {
        if (r < 0 || r == g.length || c < 0 || c == g[0].length || g[r][c] != '1') return;
        g[r][c] = '0';
        dfs(g, r + 1, c); dfs(g, r - 1, c); dfs(g, r, c + 1); dfs(g, r, c - 1);
    }
}
```

### 147. [Max Area of Island](https://leetcode.com/problems/max-area-of-island/) — Medium

- [ ] **Revised**
- **Recognition cue:** Grid DFS/BFS component size
- **Approach ladder:** 1. DFS recursion. 2. BFS queue. Both O(mn); DFS marking in-place is shortest **(preferred)**.
- **Preferred pattern:** Grid DFS/BFS component size
- **Preferred complexity:** O(mn) time, O(mn) worst recursion space

```java
class Solution {
    public int maxAreaOfIsland(int[][] grid) {
        int best = 0;
        for (int r=0;r<grid.length;r++) for(int c=0;c<grid[0].length;c++) best=Math.max(best,dfs(grid,r,c));
        return best;
    }
    private int dfs(int[][] g,int r,int c){
        if(r<0||c<0||r==g.length||c==g[0].length||g[r][c]==0)return 0;
        g[r][c]=0;
        return 1+dfs(g,r+1,c)+dfs(g,r-1,c)+dfs(g,r,c+1)+dfs(g,r,c-1);
    }
}
```

### 148. [Clone Graph](https://leetcode.com/problems/clone-graph/) — Medium

- [ ] **Revised**
- **Recognition cue:** Deep-copy a graph with cycles.
- **Approach ladder:** 1. DFS/BFS with explicit visited state. 2. DSU, topological sort, multi-source BFS, or shortest-path formulation when structure permits. 3. **Preferred:** DFS/BFS with original-to-clone map — O(V+E) time, O(V) space.
- **Preferred pattern:** DFS/BFS with original-to-clone map
- **Preferred complexity:** O(V+E) time, O(V) space
- **Invariant / state:** Create and memoize a clone before recursively cloning neighbors.

```java
class Solution {
    private final Map<Node, Node> copies = new HashMap<>();
    public Node cloneGraph(Node node) {
        if (node == null) return null;
        if (copies.containsKey(node)) return copies.get(node);
        Node copy = new Node(node.val);
        copies.put(node, copy);
        for (Node neighbor : node.neighbors) copy.neighbors.add(cloneGraph(neighbor));
        return copy;
    }
}
```

### 149. [Walls And Gates](https://leetcode.com/problems/walls-and-gates/) — Medium

- [ ] **Revised**
- **Recognition cue:** Multi-source BFS
- **Approach ladder:** 1. BFS from every empty room — O((mn)²). 2. Start BFS simultaneously from all gates; first visit is nearest distance — O(mn) **(preferred)**.
- **Preferred pattern:** Multi-source BFS
- **Preferred complexity:** O(mn) time, O(mn) space

```java
class Solution {
    public void wallsAndGates(int[][] rooms) {
        Queue<int[]> q = new ArrayDeque<>();
        for(int r=0;r<rooms.length;r++)for(int c=0;c<rooms[0].length;c++)if(rooms[r][c]==0)q.add(new int[]{r,c});
        int[][] d={{1,0},{-1,0},{0,1},{0,-1}};
        while(!q.isEmpty()){
            int[] x=q.remove();
            for(int[] z:d){int r=x[0]+z[0],c=x[1]+z[1];
                if(r>=0&&c>=0&&r<rooms.length&&c<rooms[0].length&&rooms[r][c]==Integer.MAX_VALUE){
                    rooms[r][c]=rooms[x[0]][x[1]]+1;q.add(new int[]{r,c});
                }}
        }
    }
}
```

### 150. [Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) — Medium

- [ ] **Revised**
- **Recognition cue:** Multi-source BFS by time layers
- **Approach ladder:** 1. Repeated grid scans per minute — O((mn)²). 2. Queue all rotten oranges and process BFS layers — O(mn) **(preferred)**.
- **Preferred pattern:** Multi-source BFS by time layers
- **Preferred complexity:** O(mn) time, O(mn) space

```java
class Solution {
    public int orangesRotting(int[][] grid) {
        Queue<int[]> q=new ArrayDeque<>();int fresh=0,minutes=0;
        for(int r=0;r<grid.length;r++)for(int c=0;c<grid[0].length;c++){if(grid[r][c]==2)q.add(new int[]{r,c});else if(grid[r][c]==1)fresh++;}
        int[][] d={{1,0},{-1,0},{0,1},{0,-1}};
        while(fresh>0&&!q.isEmpty()){
            for(int size=q.size();size>0;size--){int[] x=q.remove();for(int[] z:d){int r=x[0]+z[0],c=x[1]+z[1];
                if(r>=0&&c>=0&&r<grid.length&&c<grid[0].length&&grid[r][c]==1){grid[r][c]=2;fresh--;q.add(new int[]{r,c});}}}
            minutes++;
        }
        return fresh==0?minutes:-1;
    }
}
```

### 151. [Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/) — Medium

- [ ] **Revised**
- **Recognition cue:** Reverse reachability from boundaries
- **Approach ladder:** 1. DFS downhill from every cell — O((mn)²). 2. Reverse DFS/BFS uphill from each ocean boundary; intersect visited sets — O(mn) **(preferred)**.
- **Preferred pattern:** Reverse reachability from boundaries
- **Preferred complexity:** O(mn) time, O(mn) space
- **Invariant / state:** Reverse traversal can move only to equal-or-higher cells.

```java
class Solution {
    public List<List<Integer>> pacificAtlantic(int[][] h) {
        int m=h.length,n=h[0].length;boolean[][] p=new boolean[m][n],a=new boolean[m][n];
        for(int r=0;r<m;r++){dfs(h,r,0,p,Integer.MIN_VALUE);dfs(h,r,n-1,a,Integer.MIN_VALUE);}
        for(int c=0;c<n;c++){dfs(h,0,c,p,Integer.MIN_VALUE);dfs(h,m-1,c,a,Integer.MIN_VALUE);}
        List<List<Integer>> ans=new ArrayList<>();
        for(int r=0;r<m;r++)for(int c=0;c<n;c++)if(p[r][c]&&a[r][c])ans.add(List.of(r,c));
        return ans;
    }
    private void dfs(int[][] h,int r,int c,boolean[][] seen,int prev){
        if(r<0||c<0||r==h.length||c==h[0].length||seen[r][c]||h[r][c]<prev)return;
        seen[r][c]=true;int v=h[r][c];dfs(h,r+1,c,seen,v);dfs(h,r-1,c,seen,v);dfs(h,r,c+1,seen,v);dfs(h,r,c-1,seen,v);
    }
}
```

### 152. [Surrounded Regions](https://leetcode.com/problems/surrounded-regions/) — Medium

- [ ] **Revised**
- **Recognition cue:** Flip only regions not connected to the board boundary.
- **Approach ladder:** 1. DFS/BFS with explicit visited state. 2. DSU, topological sort, multi-source BFS, or shortest-path formulation when structure permits. 3. **Preferred:** Boundary-connected flood fill — O(mn) time, O(mn) worst-case recursion/queue.
- **Preferred pattern:** Boundary-connected flood fill
- **Preferred complexity:** O(mn) time, O(mn) worst-case recursion/queue
- **Invariant / state:** Mark boundary-reachable O cells as safe; all remaining O cells are enclosed.

```java
class Solution {
    public void solve(char[][] board) {
        int m = board.length, n = board[0].length;
        for (int r = 0; r < m; r++) { mark(board, r, 0); mark(board, r, n - 1); }
        for (int c = 0; c < n; c++) { mark(board, 0, c); mark(board, m - 1, c); }
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
                board[r][c] = board[r][c] == 'S' ? 'O' : 'X';
    }
    private void mark(char[][] b, int r, int c) {
        if (r < 0 || r == b.length || c < 0 || c == b[0].length || b[r][c] != 'O') return;
        b[r][c] = 'S';
        mark(b, r + 1, c); mark(b, r - 1, c); mark(b, r, c + 1); mark(b, r, c - 1);
    }
}
```

### 153. [Open The Lock](https://leetcode.com/problems/open-the-lock/) — Medium

- [ ] **Revised**
- **Recognition cue:** Implicit-graph BFS
- **Approach ladder:** 1. DFS — does not guarantee minimum turns. 2. Bidirectional BFS can reduce frontier. 3. Standard BFS over 10,000 states — O(10⁴) **(preferred simple)**.
- **Preferred pattern:** Implicit-graph BFS
- **Preferred complexity:** O(10^4) time and space

```java
class Solution {
    public int openLock(String[] deadends, String target) {
        Set<String> dead=new HashSet<>(Arrays.asList(deadends));
        if(dead.contains("0000"))return -1;
        Queue<String> q=new ArrayDeque<>();q.add("0000");dead.add("0000");int steps=0;
        while(!q.isEmpty()){
            for(int size=q.size();size>0;size--){String s=q.remove();if(s.equals(target))return steps;
                char[] x=s.toCharArray();for(int i=0;i<4;i++){char old=x[i];
                    for(int delta:new int[]{-1,1}){x[i]=(char)('0'+(old-'0'+delta+10)%10);String next=new String(x);if(dead.add(next))q.add(next);}x[i]=old;}}
            steps++;
        }
        return -1;
    }
}
```

### 154. [Course Schedule](https://leetcode.com/problems/course-schedule/) — Medium

- [ ] **Revised**
- **Recognition cue:** Determine whether a directed prerequisite graph is acyclic.
- **Approach ladder:** 1. DFS/BFS with explicit visited state. 2. DSU, topological sort, multi-source BFS, or shortest-path formulation when structure permits. 3. **Preferred:** Kahn topological sort — O(V+E) time, O(V+E) space.
- **Preferred pattern:** Kahn topological sort
- **Preferred complexity:** O(V+E) time, O(V+E) space
- **Invariant / state:** Nodes with indegree zero can be safely scheduled; a cycle leaves nodes unprocessed.

```java
class Solution {
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        List<Integer>[] graph = new List[numCourses];
        Arrays.setAll(graph, i -> new ArrayList<>());
        int[] indegree = new int[numCourses];
        for (int[] p : prerequisites) { graph[p[1]].add(p[0]); indegree[p[0]]++; }
        Queue<Integer> q = new ArrayDeque<>();
        for (int i = 0; i < numCourses; i++) if (indegree[i] == 0) q.add(i);
        int done = 0;
        while (!q.isEmpty()) {
            int u = q.remove(); done++;
            for (int v : graph[u]) if (--indegree[v] == 0) q.add(v);
        }
        return done == numCourses;
    }
}
```

### 155. [Course Schedule II](https://leetcode.com/problems/course-schedule-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Return one valid prerequisite order or empty if cyclic.
- **Approach ladder:** 1. DFS/BFS with explicit visited state. 2. DSU, topological sort, multi-source BFS, or shortest-path formulation when structure permits. 3. **Preferred:** Topological ordering — O(V+E) time, O(V+E) space.
- **Preferred pattern:** Topological ordering
- **Preferred complexity:** O(V+E) time, O(V+E) space
- **Invariant / state:** Kahn's processing order is topological; success requires all nodes processed.

```java
class Solution {
    public int[] findOrder(int numCourses, int[][] prerequisites) {
        List<Integer>[] graph = new List[numCourses];
        Arrays.setAll(graph, i -> new ArrayList<>());
        int[] indegree = new int[numCourses];
        for (int[] p : prerequisites) { graph[p[1]].add(p[0]); indegree[p[0]]++; }
        Queue<Integer> q = new ArrayDeque<>();
        for (int i = 0; i < numCourses; i++) if (indegree[i] == 0) q.add(i);
        int[] order = new int[numCourses];
        int size = 0;
        while (!q.isEmpty()) {
            int u = q.remove(); order[size++] = u;
            for (int v : graph[u]) if (--indegree[v] == 0) q.add(v);
        }
        return size == numCourses ? order : new int[0];
    }
}
```

### 156. [Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/) — Medium

- [ ] **Revised**
- **Recognition cue:** DSU cycle check + edge count
- **Approach ladder:** 1. DFS: connected and no parent-back-edge. 2. DSU: require exactly n-1 edges and no union cycle — near O(n) **(preferred)**.
- **Preferred pattern:** DSU cycle check + edge count
- **Preferred complexity:** O((n+e) α(n)) time, O(n) space

```java
class Solution {
    public boolean validTree(int n, int[][] edges) {
        if(edges.length!=n-1)return false;
        int[] p=new int[n],sz=new int[n];for(int i=0;i<n;i++){p[i]=i;sz[i]=1;}
        for(int[] e:edges){int a=find(p,e[0]),b=find(p,e[1]);if(a==b)return false;if(sz[a]<sz[b]){int t=a;a=b;b=t;}p[b]=a;sz[a]+=sz[b];}
        return true;
    }
    private int find(int[] p,int x){while(x!=p[x]){p[x]=p[p[x]];x=p[x];}return x;}
}
```

### 157. [Course Schedule IV](https://leetcode.com/problems/course-schedule-iv/) — Medium

- [ ] **Revised**
- **Recognition cue:** Transitive closure
- **Approach ladder:** 1. DFS/BFS for every query — O(q(V+E)). 2. DFS memoized reachability sets. 3. Floyd-Warshall boolean closure — O(n³), concise and reliable for n≤100 **(preferred)**.
- **Preferred pattern:** Transitive closure
- **Preferred complexity:** O(n^3 + q) time, O(n²) space

```java
class Solution {
    public List<Boolean> checkIfPrerequisite(int n, int[][] prerequisites, int[][] queries) {
        boolean[][] reach=new boolean[n][n];for(int[] e:prerequisites)reach[e[0]][e[1]]=true;
        for(int k=0;k<n;k++)for(int i=0;i<n;i++)if(reach[i][k])for(int j=0;j<n;j++)reach[i][j]|=reach[k][j];
        List<Boolean> ans=new ArrayList<>(queries.length);for(int[] q:queries)ans.add(reach[q[0]][q[1]]);return ans;
    }
}
```

### 158. [Number of Connected Components In An Undirected Graph](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/) — Medium

- [ ] **Revised**
- **Recognition cue:** Disjoint set union
- **Approach ladder:** 1. DFS/BFS each unvisited node — O(V+E). 2. DSU, decrement component count on successful union — near O(V+E) **(preferred)**.
- **Preferred pattern:** Disjoint set union
- **Preferred complexity:** O((V+E) α(V)) time, O(V) space

```java
class Solution {
    public int countComponents(int n, int[][] edges) {
        int[] p=new int[n],sz=new int[n];for(int i=0;i<n;i++){p[i]=i;sz[i]=1;}
        int count=n;
        for(int[] e:edges){int a=find(p,e[0]),b=find(p,e[1]);if(a==b)continue;if(sz[a]<sz[b]){int t=a;a=b;b=t;}p[b]=a;sz[a]+=sz[b];count--;}
        return count;
    }
    private int find(int[] p,int x){if(p[x]!=x)p[x]=find(p,p[x]);return p[x];}
}
```

### 159. [Redundant Connection](https://leetcode.com/problems/redundant-connection/) — Medium

- [ ] **Revised**
- **Recognition cue:** DSU first cycle edge
- **Approach ladder:** 1. For each edge, DFS whether endpoints are already connected — O(n²). 2. DSU; first edge whose endpoints share a root closes a cycle — near O(n) **(preferred)**.
- **Preferred pattern:** DSU first cycle edge
- **Preferred complexity:** O(n α(n)) time, O(n) space

```java
class Solution {
    public int[] findRedundantConnection(int[][] edges) {
        int[] p=new int[edges.length+1];for(int i=0;i<p.length;i++)p[i]=i;
        for(int[] e:edges){int a=find(p,e[0]),b=find(p,e[1]);if(a==b)return e;p[a]=b;}
        return new int[0];
    }
    private int find(int[] p,int x){return p[x]==x?x:(p[x]=find(p,p[x]));}
}
```

### 160. [Accounts Merge](https://leetcode.com/problems/accounts-merge/) — Medium

- [ ] **Revised**
- **Recognition cue:** DSU over email ownership
- **Approach ladder:** 1. Build email graph and DFS components. 2. DSU account indices sharing an email, then group/sort emails — near-linear plus sorting **(preferred)**.
- **Preferred pattern:** DSU over email ownership
- **Preferred complexity:** O(E α(A) + E log E) time, O(E+A) space

```java
class Solution {
    public List<List<String>> accountsMerge(List<List<String>> accounts) {
        int n=accounts.size();int[] p=new int[n];for(int i=0;i<n;i++)p[i]=i;
        Map<String,Integer> owner=new HashMap<>();
        for(int i=0;i<n;i++)for(int j=1;j<accounts.get(i).size();j++){String mail=accounts.get(i).get(j);Integer old=owner.putIfAbsent(mail,i);if(old!=null)union(p,i,old);}
        Map<Integer,List<String>> groups=new HashMap<>();
        for(String mail:owner.keySet())groups.computeIfAbsent(find(p,owner.get(mail)),x->new ArrayList<>()).add(mail);
        List<List<String>> ans=new ArrayList<>();
        for(var e:groups.entrySet()){Collections.sort(e.getValue());List<String> row=new ArrayList<>();row.add(accounts.get(e.getKey()).get(0));row.addAll(e.getValue());ans.add(row);}return ans;
    }
    private int find(int[] p,int x){return p[x]==x?x:(p[x]=find(p,p[x]));}
    private void union(int[] p,int a,int b){p[find(p,a)]=find(p,b);}
}
```

### 161. [Evaluate Division](https://leetcode.com/problems/evaluate-division/) — Medium

- [ ] **Revised**
- **Recognition cue:** Ratios form directed weighted edges; answer queries by finding a path.
- **Approach ladder:** 1. DFS/BFS with explicit visited state. 2. DSU, topological sort, multi-source BFS, or shortest-path formulation when structure permits. 3. **Preferred:** Weighted graph path product — O(E) per query worst case, O(V+E) space.
- **Preferred pattern:** Weighted graph path product
- **Preferred complexity:** O(E) per query worst case, O(V+E) space
- **Invariant / state:** Product of edge weights along a path equals the composed ratio.

```java
class Solution {
    public double[] calcEquation(List<List<String>> equations, double[] values,
                                 List<List<String>> queries) {
        Map<String, List<Edge>> graph = new HashMap<>();
        for (int i = 0; i < equations.size(); i++) {
            String a = equations.get(i).get(0), b = equations.get(i).get(1);
            graph.computeIfAbsent(a, k -> new ArrayList<>()).add(new Edge(b, values[i]));
            graph.computeIfAbsent(b, k -> new ArrayList<>()).add(new Edge(a, 1.0 / values[i]));
        }
        double[] ans = new double[queries.size()];
        for (int i = 0; i < queries.size(); i++) {
            String a = queries.get(i).get(0), b = queries.get(i).get(1);
            ans[i] = dfs(a, b, 1.0, graph, new HashSet<>());
        }
        return ans;
    }
    private double dfs(String cur, String target, double product,
                       Map<String, List<Edge>> graph, Set<String> seen) {
        if (!graph.containsKey(cur) || !seen.add(cur)) return -1.0;
        if (cur.equals(target)) return product;
        for (Edge e : graph.get(cur)) {
            double found = dfs(e.to, target, product * e.weight, graph, seen);
            if (found >= 0) return found;
        }
        return -1.0;
    }
    private record Edge(String to, double weight) {}
}
```

### 162. [Minimum Height Trees](https://leetcode.com/problems/minimum-height-trees/) — Medium

- [ ] **Revised**
- **Recognition cue:** Topological leaf peeling
- **Approach ladder:** 1. Compute height from every root — O(n²). 2. Repeatedly remove leaves until one/two centroids remain — O(n) **(preferred)**.
- **Preferred pattern:** Topological leaf peeling
- **Preferred complexity:** O(n) time, O(n) space
- **Invariant / state:** A tree has one or two centers; peeling equal-distance outer layers exposes them.

```java
class Solution {
    public List<Integer> findMinHeightTrees(int n, int[][] edges) {
        if(n==1)return List.of(0);
        List<Integer>[] g=new List[n];int[] deg=new int[n];for(int i=0;i<n;i++)g[i]=new ArrayList<>();
        for(int[] e:edges){g[e[0]].add(e[1]);g[e[1]].add(e[0]);deg[e[0]]++;deg[e[1]]++;}
        Queue<Integer> q=new ArrayDeque<>();for(int i=0;i<n;i++)if(deg[i]==1)q.add(i);
        int remain=n;
        while(remain>2){int size=q.size();remain-=size;while(size-->0){int u=q.remove();for(int v:g[u])if(--deg[v]==1)q.add(v);}}
        return new ArrayList<>(q);
    }
}
```

### 163. [Word Ladder](https://leetcode.com/problems/word-ladder/) — Hard

- [ ] **Revised**
- **Recognition cue:** Shortest sequence of one-letter transformations through a dictionary.
- **Approach ladder:** 1. DFS/BFS with explicit visited state. 2. DSU, topological sort, multi-source BFS, or shortest-path formulation when structure permits. 3. **Preferred:** Bidirectional BFS — O(N * L * alphabet) time, O(N) space.
- **Preferred pattern:** Bidirectional BFS
- **Preferred complexity:** O(N * L * alphabet) time, O(N) space
- **Invariant / state:** Always expand the smaller frontier; removing visited words prevents cycles.

```java
class Solution {
    public int ladderLength(String beginWord, String endWord, List<String> wordList) {
        Set<String> dict = new HashSet<>(wordList);
        if (!dict.contains(endWord)) return 0;
        Set<String> front = new HashSet<>(Set.of(beginWord));
        Set<String> back = new HashSet<>(Set.of(endWord));
        dict.remove(beginWord);
        int length = 1;
        while (!front.isEmpty() && !back.isEmpty()) {
            if (front.size() > back.size()) { Set<String> t = front; front = back; back = t; }
            Set<String> nextFront = new HashSet<>();
            for (String word : front) {
                char[] a = word.toCharArray();
                for (int i = 0; i < a.length; i++) {
                    char old = a[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        a[i] = c;
                        String next = new String(a);
                        if (back.contains(next)) return length + 1;
                        if (dict.remove(next)) nextFront.add(next);
                    }
                    a[i] = old;
                }
            }
            front = nextFront;
            length++;
        }
        return 0;
    }
}
```

---

## Advanced Graphs

### 164. [Path with Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/) — Medium

- [ ] **Revised**
- **Recognition cue:** Minimax Dijkstra
- **Approach ladder:** 1. Binary-search an effort threshold + BFS — O(mn log W). 2. Kruskal until endpoints connect — O(mn log mn). 3. Dijkstra where path cost is maximum edge effort — O(mn log mn) **(preferred reusable)**.
- **Preferred pattern:** Minimax Dijkstra
- **Preferred complexity:** O(mn log(mn)) time, O(mn) space
- **Invariant / state:** The distance label is the minimum possible maximum edge effort to reach a cell.

```java
class Solution {
    public int minimumEffortPath(int[][] h) {
        int m=h.length,n=h[0].length;int[][] dist=new int[m][n];for(int[] row:dist)Arrays.fill(row,Integer.MAX_VALUE);dist[0][0]=0;
        PriorityQueue<int[]> pq=new PriorityQueue<>(Comparator.comparingInt(a->a[0]));pq.offer(new int[]{0,0,0});
        int[][] d={{1,0},{-1,0},{0,1},{0,-1}};
        while(!pq.isEmpty()){
            int[] x=pq.poll();int effort=x[0],r=x[1],c=x[2];if(effort!=dist[r][c])continue;if(r==m-1&&c==n-1)return effort;
            for(int[] z:d){int nr=r+z[0],nc=c+z[1];if(nr<0||nc<0||nr==m||nc==n)continue;int nd=Math.max(effort,Math.abs(h[r][c]-h[nr][nc]));if(nd<dist[nr][nc]){dist[nr][nc]=nd;pq.offer(new int[]{nd,nr,nc});}}
        }
        return 0;
    }
}
```

### 165. [Network Delay Time](https://leetcode.com/problems/network-delay-time/) — Medium

- [ ] **Revised**
- **Recognition cue:** Dijkstra shortest paths
- **Approach ladder:** 1. Bellman-Ford — O(VE), handles negative edges. 2. Floyd-Warshall — O(V³). 3. Adjacency list + Dijkstra because weights are non-negative — O(E log V) **(preferred)**.
- **Preferred pattern:** Dijkstra shortest paths
- **Preferred complexity:** O(E log V) time, O(V+E) space

```java
class Solution {
    public int networkDelayTime(int[][] times, int n, int k) {
        List<int[]>[] g=new List[n+1];for(int i=1;i<=n;i++)g[i]=new ArrayList<>();for(int[] e:times)g[e[0]].add(new int[]{e[1],e[2]});
        int[] dist=new int[n+1];Arrays.fill(dist,Integer.MAX_VALUE);dist[k]=0;
        PriorityQueue<int[]> pq=new PriorityQueue<>(Comparator.comparingInt(a->a[0]));pq.offer(new int[]{0,k});
        while(!pq.isEmpty()){int[] x=pq.poll();int d=x[0],u=x[1];if(d!=dist[u])continue;for(int[] e:g[u])if((long)d+e[1]<dist[e[0]]){dist[e[0]]=d+e[1];pq.offer(new int[]{dist[e[0]],e[0]});}}
        int ans=0;for(int i=1;i<=n;i++){if(dist[i]==Integer.MAX_VALUE)return -1;ans=Math.max(ans,dist[i]);}return ans;
    }
}
```

### 166. [Reconstruct Itinerary](https://leetcode.com/problems/reconstruct-itinerary/) — Hard

- [ ] **Revised**
- **Recognition cue:** Lexicographic Eulerian path / Hierholzer
- **Approach ladder:** 1. Backtracking over ticket permutations — exponential. 2. Sort adjacency and use Hierholzer, consuming smallest destination first — O(E log E) **(preferred)**.
- **Preferred pattern:** Lexicographic Eulerian path / Hierholzer
- **Preferred complexity:** O(E log E) time, O(E) space
- **Invariant / state:** Postorder insertion records vertices only after all outgoing tickets are consumed.

```java
class Solution {
    public List<String> findItinerary(List<List<String>> tickets) {
        Map<String,PriorityQueue<String>> g=new HashMap<>();
        for(List<String> e:tickets)g.computeIfAbsent(e.get(0),x->new PriorityQueue<>()).offer(e.get(1));
        LinkedList<String> route=new LinkedList<>();dfs("JFK",g,route);return route;
    }
    private void dfs(String u,Map<String,PriorityQueue<String>> g,LinkedList<String> route){
        PriorityQueue<String> q=g.get(u);while(q!=null&&!q.isEmpty())dfs(q.poll(),g,route);route.addFirst(u);
    }
}
```

### 167. [Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/) — Medium

- [ ] **Revised**
- **Recognition cue:** Dense Prim MST
- **Approach ladder:** 1. Generate all O(n²) edges and Kruskal — O(n² log n). 2. Prim with heap — O(n² log n). 3. Dense-array Prim without materializing edges — O(n²), O(n) **(preferred)**.
- **Preferred pattern:** Dense Prim MST
- **Preferred complexity:** O(n²) time, O(n) space

```java
class Solution {
    public int minCostConnectPoints(int[][] p) {
        int n=p.length,ans=0;int[] min=new int[n];Arrays.fill(min,Integer.MAX_VALUE);min[0]=0;boolean[] used=new boolean[n];
        for(int step=0;step<n;step++){
            int u=-1;for(int i=0;i<n;i++)if(!used[i]&&(u==-1||min[i]<min[u]))u=i;
            used[u]=true;ans+=min[u];
            for(int v=0;v<n;v++)if(!used[v])min[v]=Math.min(min[v],Math.abs(p[u][0]-p[v][0])+Math.abs(p[u][1]-p[v][1]));
        }
        return ans;
    }
}
```

### 168. [Swim In Rising Water](https://leetcode.com/problems/swim-in-rising-water/) — Hard

- [ ] **Revised**
- **Recognition cue:** Minimax Dijkstra
- **Approach ladder:** 1. Binary search time + reachability DFS — O(n² log n²). 2. Union cells by height. 3. Dijkstra minimizing maximum elevation seen — O(n² log n) **(preferred reusable)**.
- **Preferred pattern:** Minimax Dijkstra
- **Preferred complexity:** O(n² log n) time, O(n²) space

```java
class Solution {
    public int swimInWater(int[][] grid) {
        int n=grid.length;boolean[][] seen=new boolean[n][n];PriorityQueue<int[]> pq=new PriorityQueue<>(Comparator.comparingInt(a->a[0]));pq.offer(new int[]{grid[0][0],0,0});
        int[][] d={{1,0},{-1,0},{0,1},{0,-1}};
        while(!pq.isEmpty()){int[] x=pq.poll();int t=x[0],r=x[1],c=x[2];if(seen[r][c])continue;seen[r][c]=true;if(r==n-1&&c==n-1)return t;
            for(int[] z:d){int nr=r+z[0],nc=c+z[1];if(nr>=0&&nc>=0&&nr<n&&nc<n&&!seen[nr][nc])pq.offer(new int[]{Math.max(t,grid[nr][nc]),nr,nc});}}
        return -1;
    }
}
```

### 169. [Alien Dictionary](https://leetcode.com/problems/alien-dictionary/) — Hard

- [ ] **Revised**
- **Recognition cue:** Constraint graph + topological sort
- **Approach ladder:** 1. Compare every pair of words unnecessarily. 2. Compare adjacent words, add first differing-character edge, then Kahn topological sort — O(total chars + alphabet²) **(preferred)**.
- **Preferred pattern:** Constraint graph + topological sort
- **Preferred complexity:** O(total characters + V+E) time, O(V+E) space
- **Pitfall:** An earlier longer word that starts with a later shorter word is invalid immediately.

```java
class Solution {
    public String alienOrder(String[] words) {
        Map<Character,Set<Character>> g=new HashMap<>();Map<Character,Integer> indeg=new HashMap<>();
        for(String w:words)for(char c:w.toCharArray()){g.putIfAbsent(c,new HashSet<>());indeg.putIfAbsent(c,0);}
        for(int i=1;i<words.length;i++){
            String a=words[i-1],b=words[i];if(a.length()>b.length()&&a.startsWith(b))return "";
            int n=Math.min(a.length(),b.length());for(int j=0;j<n;j++)if(a.charAt(j)!=b.charAt(j)){char u=a.charAt(j),v=b.charAt(j);if(g.get(u).add(v))indeg.put(v,indeg.get(v)+1);break;}
        }
        Queue<Character> q=new ArrayDeque<>();for(char c:indeg.keySet())if(indeg.get(c)==0)q.add(c);StringBuilder out=new StringBuilder();
        while(!q.isEmpty()){char u=q.remove();out.append(u);for(char v:g.get(u))if(indeg.merge(v,-1,Integer::sum)==0)q.add(v);}
        return out.length()==indeg.size()?out.toString():"";
    }
}
```

### 170. [Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/) — Medium

- [ ] **Revised**
- **Recognition cue:** Bounded Bellman-Ford
- **Approach ladder:** 1. DFS over paths — exponential. 2. Dijkstra on `(node,stops)` states. 3. Bellman-Ford with exactly k+1 relaxation rounds using a copy — O(kE) **(preferred concise)**.
- **Preferred pattern:** Bounded Bellman-Ford
- **Preferred complexity:** O(kE) time, O(V) space
- **Pitfall:** Use the previous-round array for every relaxation; in-place updates would allow too many edges.

```java
class Solution {
    public int findCheapestPrice(int n, int[][] flights, int src, int dst, int k) {
        int INF=1_000_000_000;int[] dist=new int[n];Arrays.fill(dist,INF);dist[src]=0;
        for(int step=0;step<=k;step++){
            int[] next=dist.clone();
            for(int[] e:flights)if(dist[e[0]]!=INF)next[e[1]]=Math.min(next[e[1]],dist[e[0]]+e[2]);
            dist=next;
        }
        return dist[dst]==INF?-1:dist[dst];
    }
}
```

### 171. [Find Critical and Pseudo Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/) — Hard

- [ ] **Revised**
- **Recognition cue:** Kruskal by weight groups + bridge detection
- **Approach ladder:** 1. Recompute MST while excluding/forcing every edge — O(E² α(V)), common accepted solution. 2. Within each equal-weight group, compress current DSU components and find graph bridges; bridges are critical, other usable edges pseudo-critical — O(E log E) **(preferred optimal)**.
- **Preferred pattern:** Kruskal by weight groups + bridge detection
- **Preferred complexity:** O(E log E + E α(V)) time, O(V+E) space
- **Pitfall:** Parallel equal-weight edges must be distinguished by edge ID; skipping by parent vertex misclassifies them as bridges.

```java
class Solution {
    private static class DSU {
        int[] p,sz;DSU(int n){p=new int[n];sz=new int[n];for(int i=0;i<n;i++){p[i]=i;sz[i]=1;}}
        int find(int x){return p[x]==x?x:(p[x]=find(p[x]));}
        void union(int a,int b){a=find(a);b=find(b);if(a==b)return;if(sz[a]<sz[b]){int t=a;a=b;b=t;}p[b]=a;sz[a]+=sz[b];}
    }
    public List<List<Integer>> findCriticalAndPseudoCriticalEdges(int n, int[][] edges) {
        int m=edges.length;int[][] e=new int[m][4];for(int i=0;i<m;i++)e[i]=new int[]{edges[i][0],edges[i][1],edges[i][2],i};
        Arrays.sort(e,Comparator.comparingInt(x->x[2]));DSU dsu=new DSU(n);Set<Integer> critical=new HashSet<>(),pseudo=new HashSet<>();
        for(int i=0;i<m;){int j=i;while(j<m&&e[j][2]==e[i][2])j++;
            Map<Integer,Integer> id=new HashMap<>();List<int[]> usable=new ArrayList<>();
            for(int k=i;k<j;k++){int a=dsu.find(e[k][0]),b=dsu.find(e[k][1]);if(a==b)continue;id.putIfAbsent(a,id.size());id.putIfAbsent(b,id.size());usable.add(new int[]{id.get(a),id.get(b),e[k][3]});}
            List<int[]>[] g=new List[id.size()];for(int k=0;k<g.length;k++)g[k]=new ArrayList<>();
            for(int[] x:usable){g[x[0]].add(new int[]{x[1],x[2]});g[x[1]].add(new int[]{x[0],x[2]});pseudo.add(x[2]);}
            int[] disc=new int[g.length],low=new int[g.length];int[] time={1};
            for(int v=0;v<g.length;v++)if(disc[v]==0)bridges(v,-1,g,disc,low,time,critical);
            for(int k=i;k<j;k++)dsu.union(e[k][0],e[k][1]);i=j;
        }
        pseudo.removeAll(critical);return List.of(new ArrayList<>(critical),new ArrayList<>(pseudo));
    }
    private void bridges(int u,int parentEdge,List<int[]>[] g,int[] disc,int[] low,int[] time,Set<Integer> critical){
        disc[u]=low[u]=time[0]++;
        for(int[] x:g[u]){int v=x[0],edge=x[1];if(edge==parentEdge)continue;
            if(disc[v]==0){bridges(v,edge,g,disc,low,time,critical);low[u]=Math.min(low[u],low[v]);if(low[v]>disc[u])critical.add(edge);}
            else low[u]=Math.min(low[u],disc[v]);
        }
    }
}
```

### 172. [Build a Matrix With Conditions](https://leetcode.com/problems/build-a-matrix-with-conditions/) — Hard

- [ ] **Revised**
- **Recognition cue:** Two independent topological orders
- **Approach ladder:** 1. Backtracking permutations — factorial. 2. Topologically sort row constraints and column constraints separately; map values to positions — O(k+conditions) **(preferred)**.
- **Preferred pattern:** Two independent topological orders
- **Preferred complexity:** O(k + R + C) time, O(k + R + C) space

```java
class Solution {
    public int[][] buildMatrix(int k, int[][] rowConditions, int[][] colConditions) {
        int[] row=topo(k,rowConditions),col=topo(k,colConditions);if(row.length==0||col.length==0)return new int[0][0];
        int[] rp=new int[k+1],cp=new int[k+1];for(int i=0;i<k;i++){rp[row[i]]=i;cp[col[i]]=i;}
        int[][] ans=new int[k][k];for(int v=1;v<=k;v++)ans[rp[v]][cp[v]]=v;return ans;
    }
    private int[] topo(int k,int[][] edges){
        List<Integer>[] g=new List[k+1];for(int i=1;i<=k;i++)g[i]=new ArrayList<>();int[] in=new int[k+1];
        for(int[] e:edges){g[e[0]].add(e[1]);in[e[1]]++;}Queue<Integer> q=new ArrayDeque<>();for(int i=1;i<=k;i++)if(in[i]==0)q.add(i);
        int[] order=new int[k];int p=0;while(!q.isEmpty()){int u=q.remove();order[p++]=u;for(int v:g[u])if(--in[v]==0)q.add(v);}return p==k?order:new int[0];
    }
}
```

### 173. [Greatest Common Divisor Traversal](https://leetcode.com/problems/greatest-common-divisor-traversal/) — Hard

- [ ] **Revised**
- **Recognition cue:** DSU by shared prime factors
- **Approach ladder:** 1. Build all pairwise gcd edges — O(n² log M). 2. Factor each number; union indices that share a prime factor — O(n√M α(n)) **(preferred)**.
- **Preferred pattern:** DSU by shared prime factors
- **Preferred complexity:** O(n√M + n α(n)) time, O(n + number of factors) space

```java
class Solution {
    public boolean canTraverseAllPairs(int[] nums) {
        int n=nums.length;if(n==1)return true;for(int x:nums)if(x==1)return false;
        int[] p=new int[n],sz=new int[n];for(int i=0;i<n;i++){p[i]=i;sz[i]=1;}Map<Integer,Integer> first=new HashMap<>();
        for(int i=0;i<n;i++){int x=nums[i];for(int f=2;(long)f*f<=x;f++)if(x%f==0){connect(first,f,i,p,sz);while(x%f==0)x/=f;}if(x>1)connect(first,x,i,p,sz);}
        int root=find(p,0);for(int i=1;i<n;i++)if(find(p,i)!=root)return false;return true;
    }
    private void connect(Map<Integer,Integer> first,int factor,int i,int[] p,int[] sz){Integer j=first.putIfAbsent(factor,i);if(j!=null)union(p,sz,i,j);}
    private int find(int[] p,int x){return p[x]==x?x:(p[x]=find(p,p[x]));}
    private void union(int[] p,int[] sz,int a,int b){a=find(p,a);b=find(p,b);if(a==b)return;if(sz[a]<sz[b]){int t=a;a=b;b=t;}p[b]=a;sz[a]+=sz[b];}
}
```

---

## 1-D Dynamic Programming

### 174. [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) — Easy

- [ ] **Revised**
- **Recognition cue:** Ways to reach step i from i-1 or i-2.
- **Approach ladder:** 1. Brute recursive choice tree. 2. Memoized recursion. 3. Bottom-up table. 4. **Preferred:** Fibonacci state compression — O(n) time, O(1) space.
- **Preferred pattern:** Fibonacci state compression
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** dp[i]=dp[i-1]+dp[i-2]; retain only the previous two states.

```java
class Solution {
    public int climbStairs(int n) {
        int a = 1, b = 1;
        for (int i = 2; i <= n; i++) {
            int next = a + b;
            a = b; b = next;
        }
        return b;
    }
}
```

### 175. [Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/) — Easy

- [ ] **Revised**
- **Recognition cue:** Rolling DP
- **Approach ladder:** 1. Exponential recursion. 2. Memoized recursion / DP array — O(n) space. 3. Keep only previous two costs — O(n), O(1) **(preferred)**.
- **Preferred pattern:** Rolling DP
- **Preferred complexity:** O(n) time, O(1) space

```java
class Solution {
    public int minCostClimbingStairs(int[] cost) {
        int two = 0, one = 0;
        for (int i = 2; i <= cost.length; i++) {
            int cur = Math.min(one + cost[i - 1], two + cost[i - 2]);
            two = one; one = cur;
        }
        return one;
    }
}
```

### 176. [N-th Tribonacci Number](https://leetcode.com/problems/n-th-tribonacci-number/) — Easy

- [ ] **Revised**
- **Recognition cue:** Rolling recurrence
- **Approach ladder:** 1. Naive recursion — exponential. 2. Memo/array DP — O(n) space. 3. Three rolling values — O(n), O(1) **(preferred)**. 4. Matrix exponentiation — O(log n), useful only for huge n.
- **Preferred pattern:** Rolling recurrence
- **Preferred complexity:** O(n) time, O(1) space

```java
class Solution {
    public int tribonacci(int n) {
        if (n == 0) return 0;
        if (n <= 2) return 1;
        int a = 0, b = 1, c = 1;
        for (int i = 3; i <= n; i++) { int d = a + b + c; a = b; b = c; c = d; }
        return c;
    }
}
```

### 177. [House Robber](https://leetcode.com/problems/house-robber/) — Medium

- [ ] **Revised**
- **Recognition cue:** Choose non-adjacent values maximizing sum.
- **Approach ladder:** 1. Brute recursive choice tree. 2. Memoized recursion. 3. Bottom-up table. 4. **Preferred:** Take/skip DP — O(n) time, O(1) space.
- **Preferred pattern:** Take/skip DP
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Current optimum is max(skip current, take current + optimum two positions back).

```java
class Solution {
    public int rob(int[] nums) {
        int prev2 = 0, prev1 = 0;
        for (int x : nums) {
            int cur = Math.max(prev1, prev2 + x);
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }
}
```

### 178. [House Robber II](https://leetcode.com/problems/house-robber-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Circular DP split into two linear ranges
- **Approach ladder:** 1. Enumerate subsets. 2. Memoized state `(index, firstTaken)`. 3. Maximum of robbing ranges `[0,n-2]` and `[1,n-1]` with rolling DP — O(n), O(1) **(preferred)**.
- **Preferred pattern:** Circular DP split into two linear ranges
- **Preferred complexity:** O(n) time, O(1) space

```java
class Solution {
    public int rob(int[] nums) {
        if (nums.length == 1) return nums[0];
        return Math.max(rob(nums, 0, nums.length - 2), rob(nums, 1, nums.length - 1));
    }
    private int rob(int[] a, int l, int r) {
        int two = 0, one = 0;
        for (int i = l; i <= r; i++) { int cur = Math.max(one, two + a[i]); two = one; one = cur; }
        return one;
    }
}
```

### 179. [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) — Medium

- [ ] **Revised**
- **Recognition cue:** Every palindrome has one character or one gap as its center.
- **Approach ladder:** 1. Brute recursive choice tree. 2. Memoized recursion. 3. Bottom-up table. 4. **Preferred:** Expand around centers — O(n^2) time, O(1) space.
- **Preferred pattern:** Expand around centers
- **Preferred complexity:** O(n^2) time, O(1) space
- **Invariant / state:** Expand while endpoints match and retain the widest interval.

```java
class Solution {
    public String longestPalindrome(String s) {
        int start = 0, end = 0;
        for (int i = 0; i < s.length(); i++) {
            int odd = expand(s, i, i);
            int even = expand(s, i, i + 1);
            int len = Math.max(odd, even);
            if (len > end - start + 1) {
                start = i - (len - 1) / 2;
                end = i + len / 2;
            }
        }
        return s.substring(start, end + 1);
    }
    private int expand(String s, int l, int r) {
        while (l >= 0 && r < s.length() && s.charAt(l) == s.charAt(r)) { l--; r++; }
        return r - l - 1;
    }
}
```

### 180. [Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/) — Medium

- [ ] **Revised**
- **Recognition cue:** Expand around centers
- **Approach ladder:** 1. Test all O(n²) substrings in O(n) — O(n³). 2. DP table — O(n²) space. 3. Expand from 2n-1 centers — O(n²), O(1) **(preferred)**. 4. Manacher can count in O(n).
- **Preferred pattern:** Expand around centers
- **Preferred complexity:** O(n²) time, O(1) space

```java
class Solution {
    public int countSubstrings(String s) {
        int ans = 0;
        for (int center = 0; center < 2 * s.length() - 1; center++) {
            int l = center / 2, r = l + center % 2;
            while (l >= 0 && r < s.length() && s.charAt(l--) == s.charAt(r++)) ans++;
        }
        return ans;
    }
}
```

### 181. [Decode Ways](https://leetcode.com/problems/decode-ways/) — Medium

- [ ] **Revised**
- **Recognition cue:** Rolling prefix DP
- **Approach ladder:** 1. Enumerate all decodings — exponential. 2. Memoized recursion / DP array — O(n) space. 3. Keep ways for previous two prefixes — O(n), O(1) **(preferred)**.
- **Preferred pattern:** Rolling prefix DP
- **Preferred complexity:** O(n) time, O(1) space
- **Pitfall:** `0` cannot stand alone; it is valid only as part of 10 or 20.

```java
class Solution {
    public int numDecodings(String s) {
        if (s.charAt(0) == '0') return 0;
        int two = 1, one = 1;
        for (int i = 1; i < s.length(); i++) {
            int cur = s.charAt(i) == '0' ? 0 : one;
            int value = (s.charAt(i - 1) - '0') * 10 + s.charAt(i) - '0';
            if (value >= 10 && value <= 26) cur += two;
            two = one; one = cur;
        }
        return one;
    }
}
```

### 182. [Coin Change](https://leetcode.com/problems/coin-change/) — Medium

- [ ] **Revised**
- **Recognition cue:** Minimum number of reusable coins reaching an amount.
- **Approach ladder:** 1. Brute recursive choice tree. 2. Memoized recursion. 3. Bottom-up table. 4. **Preferred:** Unbounded minimum-count DP — O(amount * coins) time, O(amount) space.
- **Preferred pattern:** Unbounded minimum-count DP
- **Preferred complexity:** O(amount * coins) time, O(amount) space
- **Invariant / state:** dp[a] is minimum coins for amount a; transition from dp[a-coin]+1.

```java
class Solution {
    public int coinChange(int[] coins, int amount) {
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, amount + 1);
        dp[0] = 0;
        for (int a = 1; a <= amount; a++)
            for (int coin : coins)
                if (coin <= a) dp[a] = Math.min(dp[a], dp[a - coin] + 1);
        return dp[amount] > amount ? -1 : dp[amount];
    }
}
```

### 183. [Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/) — Medium

- [ ] **Revised**
- **Recognition cue:** Track maximum and minimum ending products
- **Approach ladder:** 1. Enumerate all subarrays — O(n²). 2. Prefix/suffix scans. 3. DP carrying both max and min product because a negative swaps roles — O(n), O(1) **(preferred)**.
- **Preferred pattern:** Track maximum and minimum ending products
- **Preferred complexity:** O(n) time, O(1) space

```java
class Solution {
    public int maxProduct(int[] nums) {
        int max = nums[0], min = nums[0], ans = nums[0];
        for (int i = 1; i < nums.length; i++) {
            int x = nums[i];
            if (x < 0) { int t = max; max = min; min = t; }
            max = Math.max(x, max * x);
            min = Math.min(x, min * x);
            ans = Math.max(ans, max);
        }
        return ans;
    }
}
```

### 184. [Word Break](https://leetcode.com/problems/word-break/) — Medium

- [ ] **Revised**
- **Recognition cue:** Segment a string into dictionary words.
- **Approach ladder:** 1. Brute recursive choice tree. 2. Memoized recursion. 3. Bottom-up table. 4. **Preferred:** Prefix feasibility DP — O(n^2) substring checks, O(n) space.
- **Preferred pattern:** Prefix feasibility DP
- **Preferred complexity:** O(n^2) substring checks, O(n) space
- **Invariant / state:** dp[i] is true if prefix [0,i) is segmentable; transition from valid j with dictionary substring [j,i).

```java
class Solution {
    public boolean wordBreak(String s, List<String> wordDict) {
        Set<String> dict = new HashSet<>(wordDict);
        int maxLen = wordDict.stream().mapToInt(String::length).max().orElse(0);
        boolean[] dp = new boolean[s.length() + 1];
        dp[0] = true;
        for (int i = 1; i <= s.length(); i++) {
            for (int j = Math.max(0, i - maxLen); j < i; j++) {
                if (dp[j] && dict.contains(s.substring(j, i))) { dp[i] = true; break; }
            }
        }
        return dp[s.length()];
    }
}
```

### 185. [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) — Medium

- [ ] **Revised**
- **Recognition cue:** Find LIS length in O(n log n).
- **Approach ladder:** 1. Brute recursive choice tree. 2. Memoized recursion. 3. Bottom-up table. 4. **Preferred:** Patience sorting tails — O(n log n) time, O(n) space.
- **Preferred pattern:** Patience sorting tails
- **Preferred complexity:** O(n log n) time, O(n) space
- **Invariant / state:** tails[len-1] is the smallest possible tail of an increasing subsequence of length len.
- **Pitfall:** tails is not necessarily an actual subsequence; it is an optimal frontier.

```java
class Solution {
    public int lengthOfLIS(int[] nums) {
        int[] tails = new int[nums.length];
        int size = 0;
        for (int x : nums) {
            int l = 0, r = size;
            while (l < r) {
                int m = l + (r - l) / 2;
                if (tails[m] < x) l = m + 1; else r = m;
            }
            tails[l] = x;
            if (l == size) size++;
        }
        return size;
    }
}
```

### 186. [Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) — Medium

- [ ] **Revised**
- **Recognition cue:** 0/1 subset-sum DP
- **Approach ladder:** 1. Backtracking — O(2ⁿ). 2. Memoized `(index,sum)`. 3. Boolean 1-D knapsack updated descending — O(n·sum), O(sum) **(preferred)**. 4. Bitset shifting improves constants.
- **Preferred pattern:** 0/1 subset-sum DP
- **Preferred complexity:** O(n·sum) time, O(sum) space
- **Pitfall:** Descending sum order enforces using each number at most once.

```java
class Solution {
    public boolean canPartition(int[] nums) {
        int sum = Arrays.stream(nums).sum();
        if ((sum & 1) == 1) return false;
        int target = sum / 2; boolean[] dp = new boolean[target + 1]; dp[0] = true;
        for (int x : nums) for (int s = target; s >= x; s--) dp[s] |= dp[s - x];
        return dp[target];
    }
}
```

### 187. [Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/) — Medium

- [ ] **Revised**
- **Recognition cue:** Ordered-composition DP
- **Approach ladder:** 1. Recursive enumeration — exponential. 2. Memoized target. 3. `dp[sum]` with sum outer loop and numbers inner loop counts ordered sequences — O(target·n) **(preferred)**.
- **Preferred pattern:** Ordered-composition DP
- **Preferred complexity:** O(target·n) time, O(target) space
- **Pitfall:** Loop order matters: sum outer counts permutations; number outer counts combinations.

```java
class Solution {
    public int combinationSum4(int[] nums, int target) {
        long[] dp = new long[target + 1]; dp[0] = 1;
        for (int sum = 1; sum <= target; sum++)
            for (int x : nums) if (x <= sum) dp[sum] += dp[sum - x];
        return (int) dp[target];
    }
}
```

### 188. [Perfect Squares](https://leetcode.com/problems/perfect-squares/) — Medium

- [ ] **Revised**
- **Recognition cue:** Number theory: four-square theorem
- **Approach ladder:** 1. BFS or DP — O(n√n). 2. Number theory: perfect square→1; sum of two squares→2; Legendre form→4; otherwise 3 — O(√n) **(preferred optimal)**.
- **Preferred pattern:** Number theory: four-square theorem
- **Preferred complexity:** O(√n) time, O(1) space

```java
class Solution {
    public int numSquares(int n) {
        if (square(n)) return 1;
        while (n % 4 == 0) n /= 4;
        if (n % 8 == 7) return 4;
        for (int a = 1; (long) a * a <= n; a++) if (square(n - a * a)) return 2;
        return 3;
    }
    private boolean square(int x) { int r = (int) Math.sqrt(x); return r * r == x; }
}
```

### 189. [Integer Break](https://leetcode.com/problems/integer-break/) — Medium

- [ ] **Revised**
- **Recognition cue:** Greedy maximize factors of 3
- **Approach ladder:** 1. Partition recursion. 2. O(n²) DP. 3. Mathematical optimum: use as many 3s as possible, except replace remainder 1 with 2+2 — O(n/3), O(1) **(preferred)**.
- **Preferred pattern:** Greedy maximize factors of 3
- **Preferred complexity:** O(n) simple loop / O(1) formula time, O(1) space

```java
class Solution {
    public int integerBreak(int n) {
        if (n <= 3) return n - 1;
        int product = 1;
        while (n > 4) { product *= 3; n -= 3; }
        return product * n;
    }
}
```

### 190. [Stone Game III](https://leetcode.com/problems/stone-game-iii/) — Hard

- [ ] **Revised**
- **Recognition cue:** Suffix score-difference DP
- **Approach ladder:** 1. Minimax recursion — exponential. 2. Memoized minimax. 3. Bottom-up `dp[i] = best current score minus opponent score` considering 1–3 stones — O(n) **(preferred)**.
- **Preferred pattern:** Suffix score-difference DP
- **Preferred complexity:** O(n) time, O(n) space; O(1) rolling is possible

```java
class Solution {
    public String stoneGameIII(int[] stoneValue) {
        int n = stoneValue.length; int[] dp = new int[n + 1];
        for (int i = n - 1; i >= 0; i--) {
            dp[i] = Integer.MIN_VALUE; int take = 0;
            for (int k = 0; k < 3 && i + k < n; k++) {
                take += stoneValue[i + k]; dp[i] = Math.max(dp[i], take - dp[i + k + 1]);
            }
        }
        return dp[0] > 0 ? "Alice" : dp[0] < 0 ? "Bob" : "Tie";
    }
}
```

---

## 2-D Dynamic Programming

### 191. [Unique Paths](https://leetcode.com/problems/unique-paths/) — Medium

- [ ] **Revised**
- **Recognition cue:** Binomial coefficient
- **Approach ladder:** 1. Recursive grid paths — exponential. 2. 2-D/1-D DP — O(mn). 3. Choose positions of moves: C(m+n-2, min(m-1,n-1)) — O(min(m,n)) **(preferred)**.
- **Preferred pattern:** Binomial coefficient
- **Preferred complexity:** O(min(m,n)) time, O(1) space

```java
class Solution {
    public int uniquePaths(int m, int n) {
        int total = m + n - 2, choose = Math.min(m - 1, n - 1);
        long ans = 1;
        for (int i = 1; i <= choose; i++) ans = ans * (total - choose + i) / i;
        return (int) ans;
    }
}
```

### 192. [Unique Paths II](https://leetcode.com/problems/unique-paths-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Count right/down paths avoiding blocked cells.
- **Approach ladder:** 1. Brute recursive state exploration. 2. Memoized state graph. 3. Bottom-up table, then compress dimensions where dependencies allow. 4. **Preferred:** Grid counting DP with obstacles — O(mn) time, O(n) space.
- **Preferred pattern:** Grid counting DP with obstacles
- **Preferred complexity:** O(mn) time, O(n) space
- **Invariant / state:** Obstacle resets dp[c] to zero; otherwise add ways from left into ways from top.

```java
class Solution {
    public int uniquePathsWithObstacles(int[][] obstacleGrid) {
        int n = obstacleGrid[0].length;
        int[] dp = new int[n];
        dp[0] = 1;
        for (int[] row : obstacleGrid) {
            for (int c = 0; c < n; c++) {
                if (row[c] == 1) dp[c] = 0;
                else if (c > 0) dp[c] += dp[c - 1];
            }
        }
        return dp[n - 1];
    }
}
```

### 193. [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) — Medium

- [ ] **Revised**
- **Recognition cue:** Minimum cost from top-left to bottom-right moving right/down.
- **Approach ladder:** 1. Brute recursive state exploration. 2. Memoized state graph. 3. Bottom-up table, then compress dimensions where dependencies allow. 4. **Preferred:** Grid DP with row compression — O(mn) time, O(n) space.
- **Preferred pattern:** Grid DP with row compression
- **Preferred complexity:** O(mn) time, O(n) space
- **Invariant / state:** dp[c] is min cost to current cell from top (old dp[c]) or left (new dp[c-1]).

```java
class Solution {
    public int minPathSum(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[] dp = new int[n];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                int fromLeft = c > 0 ? dp[c - 1] : Integer.MAX_VALUE;
                dp[c] = grid[r][c] + Math.min(dp[c], fromLeft);
            }
        }
        return dp[n - 1];
    }
}
```

### 194. [Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/) — Medium

- [ ] **Revised**
- **Recognition cue:** Two-row / one-row sequence DP
- **Approach ladder:** 1. Enumerate subsequences — exponential. 2. Memoized recursion. 3. O(mn) table. 4. One-row DP using saved diagonal — O(mn), O(min(m,n)) **(preferred)**.
- **Preferred pattern:** Two-row / one-row sequence DP
- **Preferred complexity:** O(mn) time, O(min(m,n)) space

```java
class Solution {
    public int longestCommonSubsequence(String a, String b) {
        if (a.length() < b.length()) { String t = a; a = b; b = t; }
        int[] dp = new int[b.length() + 1];
        for (int i = 1; i <= a.length(); i++) {
            int diag = 0;
            for (int j = 1; j <= b.length(); j++) {
                int old = dp[j];
                if (a.charAt(i - 1) == b.charAt(j - 1)) dp[j] = diag + 1;
                else dp[j] = Math.max(dp[j], dp[j - 1]);
                diag = old;
            }
        }
        return dp[b.length()];
    }
}
```

### 195. [Last Stone Weight II](https://leetcode.com/problems/last-stone-weight-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Subset sum closest to half
- **Approach ladder:** 1. Simulate all smash orders — exponential. 2. Assign ± signs / memo. 3. 0/1 knapsack maximizing reachable sum ≤ total/2 — O(n·sum) **(preferred)**.
- **Preferred pattern:** Subset sum closest to half
- **Preferred complexity:** O(n·sum) time, O(sum) space

```java
class Solution {
    public int lastStoneWeightII(int[] stones) {
        int total = Arrays.stream(stones).sum(), half = total / 2;
        boolean[] dp = new boolean[half + 1]; dp[0] = true;
        for (int x : stones) for (int s = half; s >= x; s--) dp[s] |= dp[s - x];
        for (int s = half; ; s--) if (dp[s]) return total - 2 * s;
    }
}
```

### 196. [Best Time to Buy And Sell Stock With Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/) — Medium

- [ ] **Revised**
- **Recognition cue:** Finite-state DP
- **Approach ladder:** 1. Recursion over day/holding/cooldown. 2. Memoized DP. 3. Roll three states: hold, sold today, rest — O(n), O(1) **(preferred)**.
- **Preferred pattern:** Finite-state DP
- **Preferred complexity:** O(n) time, O(1) space

```java
class Solution {
    public int maxProfit(int[] prices) {
        int hold = -prices[0], sold = Integer.MIN_VALUE / 2, rest = 0;
        for (int i = 1; i < prices.length; i++) {
            int oldHold = hold, oldSold = sold, oldRest = rest;
            hold = Math.max(oldHold, oldRest - prices[i]);
            sold = oldHold + prices[i];
            rest = Math.max(oldRest, oldSold);
        }
        return Math.max(sold, rest);
    }
}
```

### 197. [Coin Change II](https://leetcode.com/problems/coin-change-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Unbounded knapsack combinations
- **Approach ladder:** 1. Recursive include/exclude. 2. 2-D DP. 3. One-dimensional DP with coins outermost so order is ignored — O(amount·coins) **(preferred)**.
- **Preferred pattern:** Unbounded knapsack combinations
- **Preferred complexity:** O(amount·coins) time, O(amount) space

```java
class Solution {
    public int change(int amount, int[] coins) {
        long[] dp = new long[amount + 1]; dp[0] = 1;
        for (int coin : coins) for (int sum = coin; sum <= amount; sum++) dp[sum] += dp[sum - coin];
        return (int) dp[amount];
    }
}
```

### 198. [Target Sum](https://leetcode.com/problems/target-sum/) — Medium

- [ ] **Revised**
- **Recognition cue:** Transform signs into subset sum
- **Approach ladder:** 1. Enumerate ± assignments — O(2ⁿ). 2. Memoized `(index,sum)`. 3. Let positive subset sum be `(total+target)/2`; run 0/1 counting DP — O(n·sum) **(preferred)**.
- **Preferred pattern:** Transform signs into subset sum
- **Preferred complexity:** O(n·sum) time, O(sum) space
- **Pitfall:** Zeros correctly double every reachable count when the descending loop includes `s == x == 0`.

```java
class Solution {
    public int findTargetSumWays(int[] nums, int target) {
        int total = Arrays.stream(nums).sum();
        if (Math.abs(target) > total || ((total + target) & 1) != 0) return 0;
        int goal = (total + target) / 2; if (goal < 0) return 0;
        int[] dp = new int[goal + 1]; dp[0] = 1;
        for (int x : nums) for (int s = goal; s >= x; s--) dp[s] += dp[s - x];
        return dp[goal];
    }
}
```

### 199. [Interleaving String](https://leetcode.com/problems/interleaving-string/) — Medium

- [ ] **Revised**
- **Recognition cue:** Form s3 while preserving order within s1 and s2.
- **Approach ladder:** 1. Brute recursive state exploration. 2. Memoized state graph. 3. Bottom-up table, then compress dimensions where dependencies allow. 4. **Preferred:** 2D prefix DP compressed to 1D — O(mn) time, O(n) space.
- **Preferred pattern:** 2D prefix DP compressed to 1D
- **Preferred complexity:** O(mn) time, O(n) space
- **Invariant / state:** dp[j] means s1 prefix i and s2 prefix j form s3 prefix i+j.

```java
class Solution {
    public boolean isInterleave(String s1, String s2, String s3) {
        if (s1.length() + s2.length() != s3.length()) return false;
        boolean[] dp = new boolean[s2.length() + 1];
        dp[0] = true;
        for (int i = 0; i <= s1.length(); i++) {
            for (int j = 0; j <= s2.length(); j++) {
                if (i == 0 && j == 0) continue;
                int k = i + j - 1;
                boolean from1 = i > 0 && dp[j] && s1.charAt(i - 1) == s3.charAt(k);
                boolean from2 = j > 0 && dp[j - 1] && s2.charAt(j - 1) == s3.charAt(k);
                dp[j] = from1 || from2;
            }
        }
        return dp[s2.length()];
    }
}
```

### 200. [Stone Game](https://leetcode.com/problems/stone-game/) — Medium

- [ ] **Revised**
- **Recognition cue:** Parity strategy theorem
- **Approach ladder:** 1. Minimax / interval DP — O(n²), generalizable. 2. Under this problem’s even-pile and odd-total guarantees, Alice can commit to the better index parity — O(1) **(preferred optimal)**.
- **Preferred pattern:** Parity strategy theorem
- **Preferred complexity:** O(1) time and space
- **Pitfall:** The O(1) theorem relies on this problem’s exact guarantees; use interval DP for variants.

```java
class Solution {
    public boolean stoneGame(int[] piles) { return true; }
}
```

### 201. [Stone Game II](https://leetcode.com/problems/stone-game-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Suffix sums + minimax memoization
- **Approach ladder:** 1. Exponential minimax. 2. Memoize `(index,M)` and choose x maximizing current suffix minus opponent optimum — O(n³) **(preferred standard)**.
- **Preferred pattern:** Suffix sums + minimax memoization
- **Preferred complexity:** O(n^3) time, O(n²) space

```java
class Solution {
    private int[][] memo; private int[] suffix; private int n;
    public int stoneGameII(int[] piles) {
        n = piles.length; suffix = new int[n + 1]; memo = new int[n][n + 1];
        for (int i = n - 1; i >= 0; i--) suffix[i] = suffix[i + 1] + piles[i];
        return dfs(0, 1);
    }
    private int dfs(int i, int m) {
        if (i >= n) return 0;
        if (2 * m >= n - i) return suffix[i];
        if (memo[i][m] != 0) return memo[i][m];
        int best = 0;
        for (int x = 1; x <= 2 * m; x++) best = Math.max(best, suffix[i] - dfs(i + x, Math.max(m, x)));
        return memo[i][m] = best;
    }
}
```

### 202. [Longest Increasing Path In a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/) — Hard

- [ ] **Revised**
- **Recognition cue:** DAG DFS + memoization
- **Approach ladder:** 1. DFS from every cell without memo — exponential. 2. Sort cells/topological levels. 3. DFS where each cell memoizes longest increasing suffix — O(mn) **(preferred)**.
- **Preferred pattern:** DAG DFS + memoization
- **Preferred complexity:** O(mn) time, O(mn) space

```java
class Solution {
    private int[][] a, memo; private int m, n;
    public int longestIncreasingPath(int[][] matrix) {
        a = matrix; m = a.length; n = a[0].length; memo = new int[m][n]; int best = 0;
        for (int r = 0; r < m; r++) for (int c = 0; c < n; c++) best = Math.max(best, dfs(r, c));
        return best;
    }
    private int dfs(int r, int c) {
        if (memo[r][c] != 0) return memo[r][c];
        int best = 1; int[][] d = {{1,0},{-1,0},{0,1},{0,-1}};
        for (int[] z : d) { int nr=r+z[0],nc=c+z[1]; if(nr>=0&&nc>=0&&nr<m&&nc<n&&a[nr][nc]>a[r][c]) best=Math.max(best,1+dfs(nr,nc)); }
        return memo[r][c] = best;
    }
}
```

### 203. [Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/) — Hard

- [ ] **Revised**
- **Recognition cue:** One-row subsequence-count DP
- **Approach ladder:** 1. Enumerate all subsequences — exponential. 2. 2-D DP. 3. One row updated right-to-left when source char matches target char — O(mn), O(n) **(preferred)**.
- **Preferred pattern:** One-row subsequence-count DP
- **Preferred complexity:** O(mn) time, O(n) space

```java
class Solution {
    public int numDistinct(String s, String t) {
        long[] dp = new long[t.length() + 1]; dp[0] = 1;
        for (char c : s.toCharArray())
            for (int j = t.length(); j >= 1; j--)
                if (c == t.charAt(j - 1)) dp[j] += dp[j - 1];
        return (int) dp[t.length()];
    }
}
```

### 204. [Edit Distance](https://leetcode.com/problems/edit-distance/) — Medium

- [ ] **Revised**
- **Recognition cue:** Minimum insertions, deletions, and replacements between two strings.
- **Approach ladder:** 1. Brute recursive state exploration. 2. Memoized state graph. 3. Bottom-up table, then compress dimensions where dependencies allow. 4. **Preferred:** String transformation DP — O(mn) time, O(n) space.
- **Preferred pattern:** String transformation DP
- **Preferred complexity:** O(mn) time, O(n) space
- **Invariant / state:** If chars match, take diagonal; otherwise 1 + min(delete, insert, replace).

```java
class Solution {
    public int minDistance(String word1, String word2) {
        int n = word2.length();
        int[] dp = new int[n + 1];
        for (int j = 0; j <= n; j++) dp[j] = j;
        for (int i = 1; i <= word1.length(); i++) {
            int diagonal = dp[0];
            dp[0] = i;
            for (int j = 1; j <= n; j++) {
                int top = dp[j];
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) dp[j] = diagonal;
                else dp[j] = 1 + Math.min(diagonal, Math.min(top, dp[j - 1]));
                diagonal = top;
            }
        }
        return dp[n];
    }
}
```

### 205. [Burst Balloons](https://leetcode.com/problems/burst-balloons/) — Hard

- [ ] **Revised**
- **Recognition cue:** Interval DP choosing the last balloon
- **Approach ladder:** 1. Try every bursting order — O(n!). 2. Memoized interval or bottom-up interval DP; choose the final balloon in each interval — O(n³) **(preferred)**.
- **Preferred pattern:** Interval DP choosing the last balloon
- **Preferred complexity:** O(n^3) time, O(n²) space
- **Invariant / state:** When k is last in interval [l,r], its surviving neighbors are fixed at l-1 and r+1.

```java
class Solution {
    public int maxCoins(int[] nums) {
        int n = nums.length; int[] a = new int[n + 2]; a[0] = a[n + 1] = 1;
        for (int i = 0; i < n; i++) a[i + 1] = nums[i];
        int[][] dp = new int[n + 2][n + 2];
        for (int len = 1; len <= n; len++) for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            for (int k = l; k <= r; k++) dp[l][r] = Math.max(dp[l][r], dp[l][k-1] + a[l-1]*a[k]*a[r+1] + dp[k+1][r]);
        }
        return dp[1][n];
    }
}
```

### 206. [Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/) — Hard

- [ ] **Revised**
- **Recognition cue:** String/pattern DP
- **Approach ladder:** 1. Backtracking — exponential. 2. Memoized recursion. 3. DP over prefixes; `*` either removes preceding token or consumes one matching character — O(mn) **(preferred)**.
- **Preferred pattern:** String/pattern DP
- **Preferred complexity:** O(mn) time, O(mn) space; reducible to O(n)

```java
class Solution {
    public boolean isMatch(String s, String p) {
        int m=s.length(),n=p.length();boolean[][] dp=new boolean[m+1][n+1];dp[0][0]=true;
        for(int j=2;j<=n;j++)if(p.charAt(j-1)=='*')dp[0][j]=dp[0][j-2];
        for(int i=1;i<=m;i++)for(int j=1;j<=n;j++){
            char pc=p.charAt(j-1);
            if(pc=='*'){
                dp[i][j]=dp[i][j-2];char prev=p.charAt(j-2);
                if(prev=='.'||prev==s.charAt(i-1))dp[i][j]|=dp[i-1][j];
            }else if(pc=='.'||pc==s.charAt(i-1))dp[i][j]=dp[i-1][j-1];
        }
        return dp[m][n];
    }
}
```

---

## Greedy

### 207. [Lemonade Change](https://leetcode.com/problems/lemonade-change/) — Easy

- [ ] **Revised**
- **Recognition cue:** Greedy cash inventory
- **Approach ladder:** 1. State search over possible change choices. 2. Track counts of $5 and $10 bills; for $20 prefer $10+$5 over three $5 bills — O(n) **(preferred)**.
- **Preferred pattern:** Greedy cash inventory
- **Preferred complexity:** O(n) time, O(1) space
- **Pitfall:** Preserve $5 bills by using a $10 bill whenever possible for $20 change.

```java
class Solution {
    public boolean lemonadeChange(int[] bills) {
        int five = 0, ten = 0;
        for (int b : bills) {
            if (b == 5) five++;
            else if (b == 10) { if (five-- == 0) return false; ten++; }
            else if (ten > 0 && five > 0) { ten--; five--; }
            else if (five >= 3) five -= 3;
            else return false;
        }
        return true;
    }
}
```

### 208. [Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) — Medium

- [ ] **Revised**
- **Recognition cue:** Maximum sum over a non-empty contiguous segment.
- **Approach ladder:** 1. Backtracking or DP to prove the optimum. 2. Sort/sweep or maintain a frontier after establishing an exchange argument. 3. **Preferred:** Kadane local/global optimum — O(n) time, O(1) space.
- **Preferred pattern:** Kadane local/global optimum
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** bestEndingHere either extends the previous segment or restarts at current value.

```java
class Solution {
    public int maxSubArray(int[] nums) {
        int ending = nums[0], best = nums[0];
        for (int i = 1; i < nums.length; i++) {
            ending = Math.max(nums[i], ending + nums[i]);
            best = Math.max(best, ending);
        }
        return best;
    }
}
```

### 209. [Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/) — Medium

- [ ] **Revised**
- **Recognition cue:** Maximum subarray may wrap around the array boundary.
- **Approach ladder:** 1. Backtracking or DP to prove the optimum. 2. Sort/sweep or maintain a frontier after establishing an exchange argument. 3. **Preferred:** Dual Kadane — O(n) time, O(1) space.
- **Preferred pattern:** Dual Kadane
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Wrapped maximum = total sum - minimum subarray; exclude the all-negative empty-complement case.

```java
class Solution {
    public int maxSubarraySumCircular(int[] nums) {
        int total = nums[0];
        int maxEnd = nums[0], maxSum = nums[0];
        int minEnd = nums[0], minSum = nums[0];
        for (int i = 1; i < nums.length; i++) {
            int x = nums[i];
            maxEnd = Math.max(x, maxEnd + x); maxSum = Math.max(maxSum, maxEnd);
            minEnd = Math.min(x, minEnd + x); minSum = Math.min(minSum, minEnd);
            total += x;
        }
        return maxSum < 0 ? maxSum : Math.max(maxSum, total - minSum);
    }
}
```

### 210. [Longest Turbulent Subarray](https://leetcode.com/problems/longest-turbulent-subarray/) — Medium

- [ ] **Revised**
- **Recognition cue:** Rolling alternating-comparison DP
- **Approach ladder:** 1. Check every subarray — O(n²). 2. Sliding window reset at equal or broken comparisons. 3. Track lengths ending with up/down relation — O(n), O(1) **(preferred)**.
- **Preferred pattern:** Rolling alternating-comparison DP
- **Preferred complexity:** O(n) time, O(1) space

```java
class Solution {
    public int maxTurbulenceSize(int[] arr) {
        int up = 1, down = 1, best = 1;
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > arr[i - 1]) { up = down + 1; down = 1; }
            else if (arr[i] < arr[i - 1]) { down = up + 1; up = 1; }
            else up = down = 1;
            best = Math.max(best, Math.max(up, down));
        }
        return best;
    }
}
```

### 211. [Jump Game](https://leetcode.com/problems/jump-game/) — Medium

- [ ] **Revised**
- **Recognition cue:** Each index gives maximum forward jump; ask whether the end is reachable.
- **Approach ladder:** 1. Backtracking or DP to prove the optimum. 2. Sort/sweep or maintain a frontier after establishing an exchange argument. 3. **Preferred:** Greedy farthest reach — O(n) time, O(1) space.
- **Preferred pattern:** Greedy farthest reach
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Every processed index is reachable; farthest is the maximum reachable boundary.

```java
class Solution {
    public boolean canJump(int[] nums) {
        int farthest = 0;
        for (int i = 0; i < nums.length; i++) {
            if (i > farthest) return false;
            farthest = Math.max(farthest, i + nums[i]);
        }
        return true;
    }
}
```

### 212. [Jump Game II](https://leetcode.com/problems/jump-game-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Minimum jumps to reach the end; reachability is guaranteed.
- **Approach ladder:** 1. Backtracking or DP to prove the optimum. 2. Sort/sweep or maintain a frontier after establishing an exchange argument. 3. **Preferred:** Greedy layer expansion — O(n) time, O(1) space.
- **Preferred pattern:** Greedy layer expansion
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** [current layer] represents positions reachable with the current jump count.
- **Pitfall:** Stop at n-2; otherwise a needless final jump can be counted.

```java
class Solution {
    public int jump(int[] nums) {
        int jumps = 0, layerEnd = 0, farthest = 0;
        for (int i = 0; i < nums.length - 1; i++) {
            farthest = Math.max(farthest, i + nums[i]);
            if (i == layerEnd) {
                jumps++;
                layerEnd = farthest;
            }
        }
        return jumps;
    }
}
```

### 213. [Jump Game VII](https://leetcode.com/problems/jump-game-vii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Sliding count of reachable predecessors
- **Approach ladder:** 1. From every reachable index mark all next jumps — O(n·range). 2. Prefix sum / sliding window count of reachable indices — O(n) **(preferred)**.
- **Preferred pattern:** Sliding count of reachable predecessors
- **Preferred complexity:** O(n) time, O(n) space
- **Invariant / state:** `reachable` counts true DP indices in the legal predecessor window.

```java
class Solution {
    public boolean canReach(String s, int minJump, int maxJump) {
        int n = s.length(), reachable = 0; boolean[] dp = new boolean[n]; dp[0] = true;
        for (int i = 1; i < n; i++) {
            if (i - minJump >= 0 && dp[i - minJump]) reachable++;
            if (i - maxJump - 1 >= 0 && dp[i - maxJump - 1]) reachable--;
            dp[i] = s.charAt(i) == '0' && reachable > 0;
        }
        return dp[n - 1];
    }
}
```

### 214. [Gas Station](https://leetcode.com/problems/gas-station/) — Medium

- [ ] **Revised**
- **Recognition cue:** Circular route; determine a feasible start.
- **Approach ladder:** 1. Backtracking or DP to prove the optimum. 2. Sort/sweep or maintain a frontier after establishing an exchange argument. 3. **Preferred:** Greedy reset — O(n) time, O(1) space.
- **Preferred pattern:** Greedy reset
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** If running fuel becomes negative at i, no start in the failed segment can work.

```java
class Solution {
    public int canCompleteCircuit(int[] gas, int[] cost) {
        int total = 0, tank = 0, start = 0;
        for (int i = 0; i < gas.length; i++) {
            int delta = gas[i] - cost[i];
            total += delta;
            tank += delta;
            if (tank < 0) {
                start = i + 1;
                tank = 0;
            }
        }
        return total >= 0 ? start : -1;
    }
}
```

### 215. [Hand of Straights](https://leetcode.com/problems/hand-of-straights/) — Medium

- [ ] **Revised**
- **Recognition cue:** Ordered frequency map greedy
- **Approach ladder:** 1. Backtracking group construction. 2. Sort all cards and repeatedly consume sequences. 3. TreeMap counts; always start at current minimum card — O(n log n) **(preferred)**.
- **Preferred pattern:** Ordered frequency map greedy
- **Preferred complexity:** O(n log n) time, O(n) space
- **Invariant / state:** The globally smallest remaining card cannot appear anywhere except as the first card of its group.

```java
class Solution {
    public boolean isNStraightHand(int[] hand, int groupSize) {
        if (hand.length % groupSize != 0) return false;
        TreeMap<Integer,Integer> count = new TreeMap<>();
        for (int x : hand) count.merge(x, 1, Integer::sum);
        while (!count.isEmpty()) {
            int start = count.firstKey();
            for (int x = start; x < start + groupSize; x++) {
                Integer c = count.get(x); if (c == null) return false;
                if (c == 1) count.remove(x); else count.put(x, c - 1);
            }
        }
        return true;
    }
}
```

### 216. [Dota2 Senate](https://leetcode.com/problems/dota2-senate/) — Medium

- [ ] **Revised**
- **Recognition cue:** Queues of future voting indices
- **Approach ladder:** 1. Repeated string simulation — O(n²). 2. Queue indices for each party; earlier senator bans later one and re-enters at index+n — O(n) amortized **(preferred)**.
- **Preferred pattern:** Queues of future voting indices
- **Preferred complexity:** O(n) time, O(n) space

```java
class Solution {
    public String predictPartyVictory(String senate) {
        int n = senate.length(); Queue<Integer> r = new ArrayDeque<>(), d = new ArrayDeque<>();
        for (int i = 0; i < n; i++) (senate.charAt(i) == 'R' ? r : d).add(i);
        while (!r.isEmpty() && !d.isEmpty()) {
            int ri = r.remove(), di = d.remove();
            if (ri < di) r.add(ri + n); else d.add(di + n);
        }
        return r.isEmpty() ? "Dire" : "Radiant";
    }
}
```

### 217. [Merge Triplets to Form Target Triplet](https://leetcode.com/problems/merge-triplets-to-form-target-triplet/) — Medium

- [ ] **Revised**
- **Recognition cue:** Coordinate-wise feasibility
- **Approach ladder:** 1. Try subsets of triplets — exponential. 2. Ignore any triplet exceeding target in any coordinate; OR coverage of exact target coordinates — O(n) **(preferred)**.
- **Preferred pattern:** Coordinate-wise feasibility
- **Preferred complexity:** O(n) time, O(1) space

```java
class Solution {
    public boolean mergeTriplets(int[][] triplets, int[] target) {
        boolean a = false, b = false, c = false;
        for (int[] t : triplets) {
            if (t[0] > target[0] || t[1] > target[1] || t[2] > target[2]) continue;
            a |= t[0] == target[0]; b |= t[1] == target[1]; c |= t[2] == target[2];
        }
        return a && b && c;
    }
}
```

### 218. [Partition Labels](https://leetcode.com/problems/partition-labels/) — Medium

- [ ] **Revised**
- **Recognition cue:** Greedy close at last occurrence
- **Approach ladder:** 1. Try every partition. 2. Precompute each character’s last index; extend current segment end and cut when scan reaches it — O(n) **(preferred)**.
- **Preferred pattern:** Greedy close at last occurrence
- **Preferred complexity:** O(n) time, O(1) space

```java
class Solution {
    public List<Integer> partitionLabels(String s) {
        int[] last = new int[26]; for (int i = 0; i < s.length(); i++) last[s.charAt(i)-'a'] = i;
        List<Integer> ans = new ArrayList<>(); int start = 0, end = 0;
        for (int i = 0; i < s.length(); i++) {
            end = Math.max(end, last[s.charAt(i)-'a']);
            if (i == end) { ans.add(end - start + 1); start = i + 1; }
        }
        return ans;
    }
}
```

### 219. [Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/) — Medium

- [ ] **Revised**
- **Recognition cue:** Greedy range of possible open counts
- **Approach ladder:** 1. Backtracking each `*` as three choices — O(3ⁿ). 2. DP/set of possible open counts — O(n²). 3. Track minimum and maximum possible opens — O(n), O(1) **(preferred)**.
- **Preferred pattern:** Greedy range of possible open counts
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Every feasible open-count lies within [low, high].

```java
class Solution {
    public boolean checkValidString(String s) {
        int low = 0, high = 0;
        for (char c : s.toCharArray()) {
            if (c == '(') { low++; high++; }
            else if (c == ')') { low = Math.max(0, low - 1); high--; }
            else { low = Math.max(0, low - 1); high++; }
            if (high < 0) return false;
        }
        return low == 0;
    }
}
```

### 220. [Candy](https://leetcode.com/problems/candy/) — Hard

- [ ] **Revised**
- **Recognition cue:** Assign minimum positive rewards under local rating inequalities.
- **Approach ladder:** 1. Backtracking or DP to prove the optimum. 2. Sort/sweep or maintain a frontier after establishing an exchange argument. 3. **Preferred:** Two directional constraints — O(n) time, O(n) space.
- **Preferred pattern:** Two directional constraints
- **Preferred complexity:** O(n) time, O(n) space
- **Invariant / state:** Left pass satisfies increasing-from-left; right pass satisfies increasing-from-right.

```java
class Solution {
    public int candy(int[] ratings) {
        int n = ratings.length;
        int[] candy = new int[n];
        Arrays.fill(candy, 1);
        for (int i = 1; i < n; i++)
            if (ratings[i] > ratings[i - 1]) candy[i] = candy[i - 1] + 1;
        for (int i = n - 2; i >= 0; i--)
            if (ratings[i] > ratings[i + 1])
                candy[i] = Math.max(candy[i], candy[i + 1] + 1);
        int sum = 0;
        for (int x : candy) sum += x;
        return sum;
    }
}
```

---

## Intervals

### 221. [Insert Interval](https://leetcode.com/problems/insert-interval/) — Medium

- [ ] **Revised**
- **Recognition cue:** Insert one interval into an already sorted, disjoint list.
- **Approach ladder:** 1. Compare every pair — O(n²). 2. Sort by start/end, sweep events, or maintain active intervals in a heap. 3. **Preferred:** Three-phase interval sweep — O(n) time, O(n) output space.
- **Preferred pattern:** Three-phase interval sweep
- **Preferred complexity:** O(n) time, O(n) output space
- **Invariant / state:** Emit intervals before, merge overlaps, then emit intervals after.

```java
class Solution {
    public int[][] insert(int[][] intervals, int[] newInterval) {
        List<int[]> ans = new ArrayList<>();
        int i = 0;
        while (i < intervals.length && intervals[i][1] < newInterval[0]) ans.add(intervals[i++]);
        while (i < intervals.length && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = Math.min(newInterval[0], intervals[i][0]);
            newInterval[1] = Math.max(newInterval[1], intervals[i][1]);
            i++;
        }
        ans.add(newInterval);
        while (i < intervals.length) ans.add(intervals[i++]);
        return ans.toArray(int[][]::new);
    }
}
```

### 222. [Merge Intervals](https://leetcode.com/problems/merge-intervals/) — Medium

- [ ] **Revised**
- **Recognition cue:** Combine overlapping intervals.
- **Approach ladder:** 1. Compare every pair — O(n²). 2. Sort by start/end, sweep events, or maintain active intervals in a heap. 3. **Preferred:** Sort by start + sweep — O(n log n) time, O(n) output space.
- **Preferred pattern:** Sort by start + sweep
- **Preferred complexity:** O(n log n) time, O(n) output space
- **Invariant / state:** The output's last interval is the merged union of all processed overlaps.

```java
class Solution {
    public int[][] merge(int[][] intervals) {
        Arrays.sort(intervals, Comparator.comparingInt(a -> a[0]));
        List<int[]> merged = new ArrayList<>();
        for (int[] cur : intervals) {
            if (merged.isEmpty() || merged.get(merged.size() - 1)[1] < cur[0])
                merged.add(cur);
            else {
                int[] last = merged.get(merged.size() - 1);
                last[1] = Math.max(last[1], cur[1]);
            }
        }
        return merged.toArray(int[][]::new);
    }
}
```

### 223. [Non Overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/) — Medium

- [ ] **Revised**
- **Recognition cue:** Earliest-finish greedy
- **Approach ladder:** 1. DP for maximum compatible subset — O(n²). 2. Sort by end; keep intervals ending earliest and remove overlaps — O(n log n) **(preferred)**.
- **Preferred pattern:** Earliest-finish greedy
- **Preferred complexity:** O(n log n) time, O(log n) sorting stack

```java
class Solution {
    public int eraseOverlapIntervals(int[][] intervals) {
        Arrays.sort(intervals, Comparator.comparingInt(a -> a[1]));
        int removed = 0, end = Integer.MIN_VALUE;
        for (int[] in : intervals) {
            if (in[0] < end) removed++;
            else end = in[1];
        }
        return removed;
    }
}
```

### 224. [Meeting Rooms](https://leetcode.com/problems/meeting-rooms/) — Easy

- [ ] **Revised**
- **Recognition cue:** Sort by start time
- **Approach ladder:** 1. Compare every pair — O(n²). 2. Sort by start and check adjacent overlap — O(n log n) **(preferred)**.
- **Preferred pattern:** Sort by start time
- **Preferred complexity:** O(n log n) time, O(log n) sorting stack

```java
class Solution {
    public boolean canAttendMeetings(List<Interval> intervals) {
        intervals.sort(Comparator.comparingInt(a -> a.start));
        for (int i = 1; i < intervals.size(); i++) if (intervals.get(i).start < intervals.get(i - 1).end) return false;
        return true;
    }
}
```

### 225. [Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/) — Medium

- [ ] **Revised**
- **Recognition cue:** Chronological start/end sweep
- **Approach ladder:** 1. Min-heap of end times — O(n log n). 2. Sort starts and ends separately; sweep active room count — O(n log n), smaller constants **(preferred)**.
- **Preferred pattern:** Chronological start/end sweep
- **Preferred complexity:** O(n log n) time, O(n) space

```java
class Solution {
    public int minMeetingRooms(List<Interval> intervals) {
        int n = intervals.size(); if (n == 0) return 0;
        int[] start = new int[n], end = new int[n];
        for (int i = 0; i < n; i++) { start[i] = intervals.get(i).start; end[i] = intervals.get(i).end; }
        Arrays.sort(start); Arrays.sort(end);
        int s = 0, e = 0, active = 0, best = 0;
        while (s < n) {
            if (start[s] < end[e]) { active++; best = Math.max(best, active); s++; }
            else { active--; e++; }
        }
        return best;
    }
}
```

### 226. [Meeting Rooms III](https://leetcode.com/problems/meeting-rooms-iii/) — Hard

- [ ] **Revised**
- **Recognition cue:** Available-room and busy-room heaps
- **Approach ladder:** 1. Simulate each room scan — O(meetings·rooms). 2. Min-heap of available room IDs and min-heap of busy `(end,room)`; delay when none free — O(m log n) **(preferred)**.
- **Preferred pattern:** Available-room and busy-room heaps
- **Preferred complexity:** O(m log n + m log m) time including sorting, O(n) space
- **Pitfall:** When delaying, release every room becoming free at the same earliest time so the smallest ID wins.

```java
class Solution {
    public int mostBooked(int n, int[][] meetings) {
        Arrays.sort(meetings, Comparator.comparingInt(a -> a[0]));
        PriorityQueue<Integer> free = new PriorityQueue<>(); for (int i = 0; i < n; i++) free.offer(i);
        PriorityQueue<long[]> busy = new PriorityQueue<>((a,b) -> a[0] != b[0] ? Long.compare(a[0],b[0]) : Long.compare(a[1],b[1]));
        int[] used = new int[n];
        for (int[] mt : meetings) {
            long start = mt[0], duration = mt[1] - mt[0];
            while (!busy.isEmpty() && busy.peek()[0] <= start) free.offer((int) busy.poll()[1]);
            if (free.isEmpty()) { long[] x = busy.poll(); start = x[0]; free.offer((int) x[1]); while (!busy.isEmpty() && busy.peek()[0] == start) free.offer((int) busy.poll()[1]); }
            int room = free.poll(); used[room]++; busy.offer(new long[]{start + duration, room});
        }
        int ans = 0; for (int i = 1; i < n; i++) if (used[i] > used[ans]) ans = i; return ans;
    }
}
```

### 227. [Minimum Interval to Include Each Query](https://leetcode.com/problems/minimum-interval-to-include-each-query/) — Hard

- [ ] **Revised**
- **Recognition cue:** Offline sort + min-heap
- **Approach ladder:** 1. Test every interval for every query — O(IQ). 2. Sort queries; add intervals whose start≤query to heap by length, discard ended intervals — O((I+Q) log I) **(preferred)**.
- **Preferred pattern:** Offline sort + min-heap
- **Preferred complexity:** O((I+Q) log I) time, O(I+Q) space

```java
class Solution {
    public int[] minInterval(int[][] intervals, int[] queries) {
        Arrays.sort(intervals, Comparator.comparingInt(a -> a[0]));
        int[][] q = new int[queries.length][2]; for (int i = 0; i < q.length; i++) q[i] = new int[]{queries[i], i};
        Arrays.sort(q, Comparator.comparingInt(a -> a[0]));
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        int[] ans = new int[q.length]; Arrays.fill(ans, -1); int i = 0;
        for (int[] query : q) {
            int x = query[0];
            while (i < intervals.length && intervals[i][0] <= x) { int[] in = intervals[i++]; pq.offer(new int[]{in[1]-in[0]+1, in[1]}); }
            while (!pq.isEmpty() && pq.peek()[1] < x) pq.poll();
            if (!pq.isEmpty()) ans[query[1]] = pq.peek()[0];
        }
        return ans;
    }
}
```

---

## Math & Geometry

### 228. [Excel Sheet Column Title](https://leetcode.com/problems/excel-sheet-column-title/) — Easy

- [ ] **Revised**
- **Recognition cue:** Bijective base-26 conversion
- **Approach ladder:** 1. Repeatedly map `(n-1)%26` and divide `(n-1)/26` — O(log26 n) **(preferred)**.
- **Preferred pattern:** Bijective base-26 conversion
- **Preferred complexity:** O(log n) time and output space
- **Pitfall:** This is bijective base 26: subtract one before taking each digit.

```java
class Solution {
    public String convertToTitle(int columnNumber) {
        StringBuilder out = new StringBuilder();
        while (columnNumber > 0) {
            columnNumber--;
            out.append((char) ('A' + columnNumber % 26));
            columnNumber /= 26;
        }
        return out.reverse().toString();
    }
}
```

### 229. [Greatest Common Divisor of Strings](https://leetcode.com/problems/greatest-common-divisor-of-strings/) — Easy

- [ ] **Revised**
- **Recognition cue:** Concatenation compatibility + numeric gcd
- **Approach ladder:** 1. Try every prefix divisor. 2. Strings share a primitive base iff `a+b == b+a`; answer length is gcd of lengths — O(m+n) **(preferred)**.
- **Preferred pattern:** Concatenation compatibility + numeric gcd
- **Preferred complexity:** O(m+n) time, O(m+n) temporary concatenation space

```java
class Solution {
    public String gcdOfStrings(String str1, String str2) {
        if (!(str1 + str2).equals(str2 + str1)) return "";
        return str1.substring(0, gcd(str1.length(), str2.length()));
    }
    private int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
}
```

### 230. [Insert Greatest Common Divisors in Linked List](https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/) — Medium

- [ ] **Revised**
- **Recognition cue:** Single linked-list pass
- **Approach ladder:** 1. Build a new list. 2. Traverse adjacent original nodes and splice a gcd node between them — O(n), O(1) auxiliary **(preferred)**.
- **Preferred pattern:** Single linked-list pass
- **Preferred complexity:** O(n log V) time from gcd operations, O(1) auxiliary space

```java
class Solution {
    public ListNode insertGreatestCommonDivisors(ListNode head) {
        for (ListNode cur = head; cur != null && cur.next != null; cur = cur.next.next) {
            cur.next = new ListNode(gcd(cur.val, cur.next.val), cur.next);
        }
        return head;
    }
    private int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
}
```

### 231. [Transpose Matrix](https://leetcode.com/problems/transpose-matrix/) — Easy

- [ ] **Revised**
- **Recognition cue:** Direct index swap into output
- **Approach ladder:** 1. Allocate n×m output and assign `ans[c][r] = matrix[r][c]` — O(mn) **(preferred)**. In-place is possible only for square matrices.
- **Preferred pattern:** Direct index swap into output
- **Preferred complexity:** O(mn) time and output space

```java
class Solution {
    public int[][] transpose(int[][] matrix) {
        int m = matrix.length, n = matrix[0].length; int[][] ans = new int[n][m];
        for (int r = 0; r < m; r++) for (int c = 0; c < n; c++) ans[c][r] = matrix[r][c];
        return ans;
    }
}
```

### 232. [Rotate Image](https://leetcode.com/problems/rotate-image/) — Medium

- [ ] **Revised**
- **Recognition cue:** Rotate a square matrix 90 degrees clockwise in-place.
- **Approach ladder:** 1. Direct simulation. 2. Algebraic reduction, number theory, coordinate transformation, or digit arithmetic. 3. **Preferred:** Transpose + reverse rows — O(n^2) time, O(1) space.
- **Preferred pattern:** Transpose + reverse rows
- **Preferred complexity:** O(n^2) time, O(1) space
- **Invariant / state:** Transpose maps (r,c) to (c,r); row reversal completes clockwise rotation.

```java
class Solution {
    public void rotate(int[][] matrix) {
        int n = matrix.length;
        for (int r = 0; r < n; r++)
            for (int c = r + 1; c < n; c++) {
                int t = matrix[r][c]; matrix[r][c] = matrix[c][r]; matrix[c][r] = t;
            }
        for (int[] row : matrix) {
            for (int l = 0, r = n - 1; l < r; l++, r--) {
                int t = row[l]; row[l] = row[r]; row[r] = t;
            }
        }
    }
}
```

### 233. [Spiral Matrix](https://leetcode.com/problems/spiral-matrix/) — Medium

- [ ] **Revised**
- **Recognition cue:** Traverse a rectangular matrix layer by layer.
- **Approach ladder:** 1. Direct simulation. 2. Algebraic reduction, number theory, coordinate transformation, or digit arithmetic. 3. **Preferred:** Shrinking boundaries — O(mn) time, O(1) extra space.
- **Preferred pattern:** Shrinking boundaries
- **Preferred complexity:** O(mn) time, O(1) extra space
- **Invariant / state:** top, bottom, left, right delimit the unvisited rectangle.
- **Pitfall:** Guard the bottom and left traversals to avoid duplicates in single rows/columns.

```java
class Solution {
    public List<Integer> spiralOrder(int[][] matrix) {
        List<Integer> ans = new ArrayList<>();
        int top = 0, bottom = matrix.length - 1, left = 0, right = matrix[0].length - 1;
        while (top <= bottom && left <= right) {
            for (int c = left; c <= right; c++) ans.add(matrix[top][c]);
            top++;
            for (int r = top; r <= bottom; r++) ans.add(matrix[r][right]);
            right--;
            if (top <= bottom) {
                for (int c = right; c >= left; c--) ans.add(matrix[bottom][c]);
                bottom--;
            }
            if (left <= right) {
                for (int r = bottom; r >= top; r--) ans.add(matrix[r][left]);
                left++;
            }
        }
        return ans;
    }
}
```

### 234. [Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/) — Medium

- [ ] **Revised**
- **Recognition cue:** Zero entire rows and columns containing an original zero, in-place.
- **Approach ladder:** 1. Direct simulation. 2. Algebraic reduction, number theory, coordinate transformation, or digit arithmetic. 3. **Preferred:** First row/column as markers — O(mn) time, O(1) space.
- **Preferred pattern:** First row/column as markers
- **Preferred complexity:** O(mn) time, O(1) space
- **Invariant / state:** Interior zeros mark their row in col0 and column in row0; separate flag preserves col0 state.
- **Pitfall:** Iterate backward during mutation so marker cells remain usable.

```java
class Solution {
    public void setZeroes(int[][] matrix) {
        int m = matrix.length, n = matrix[0].length;
        boolean firstColZero = false;
        for (int r = 0; r < m; r++) {
            if (matrix[r][0] == 0) firstColZero = true;
            for (int c = 1; c < n; c++) {
                if (matrix[r][c] == 0) {
                    matrix[r][0] = 0;
                    matrix[0][c] = 0;
                }
            }
        }
        for (int r = m - 1; r >= 0; r--) {
            for (int c = n - 1; c >= 1; c--)
                if (matrix[r][0] == 0 || matrix[0][c] == 0) matrix[r][c] = 0;
            if (firstColZero) matrix[r][0] = 0;
        }
    }
}
```

### 235. [Happy Number](https://leetcode.com/problems/happy-number/) — Easy

- [ ] **Revised**
- **Recognition cue:** Repeatedly transform a number; determine whether it reaches 1 or cycles.
- **Approach ladder:** 1. Direct simulation. 2. Algebraic reduction, number theory, coordinate transformation, or digit arithmetic. 3. **Preferred:** Cycle detection in state transformation — O(log n) per transformation sequence, O(1) space.
- **Preferred pattern:** Cycle detection in state transformation
- **Preferred complexity:** O(log n) per transformation sequence, O(1) space
- **Invariant / state:** Floyd's pointers detect the non-1 cycle without storing all states.

```java
class Solution {
    public boolean isHappy(int n) {
        int slow = n, fast = next(n);
        while (fast != 1 && slow != fast) {
            slow = next(slow);
            fast = next(next(fast));
        }
        return fast == 1;
    }
    private int next(int x) {
        int sum = 0;
        while (x > 0) {
            int d = x % 10;
            sum += d * d;
            x /= 10;
        }
        return sum;
    }
}
```

### 236. [Plus One](https://leetcode.com/problems/plus-one/) — Easy

- [ ] **Revised**
- **Recognition cue:** Increment a big integer stored as digits.
- **Approach ladder:** 1. Direct simulation. 2. Algebraic reduction, number theory, coordinate transformation, or digit arithmetic. 3. **Preferred:** Carry propagation — O(n) time, O(n) only when length grows.
- **Preferred pattern:** Carry propagation
- **Preferred complexity:** O(n) time, O(n) only when length grows
- **Invariant / state:** Walk from the end; first digit below 9 absorbs carry and terminates.

```java
class Solution {
    public int[] plusOne(int[] digits) {
        for (int i = digits.length - 1; i >= 0; i--) {
            if (digits[i] < 9) { digits[i]++; return digits; }
            digits[i] = 0;
        }
        int[] ans = new int[digits.length + 1];
        ans[0] = 1;
        return ans;
    }
}
```

### 237. [Roman to Integer](https://leetcode.com/problems/roman-to-integer/) — Easy

- [ ] **Revised**
- **Recognition cue:** Subtractive pairs make a smaller symbol before a larger symbol negative.
- **Approach ladder:** 1. Direct simulation. 2. Algebraic reduction, number theory, coordinate transformation, or digit arithmetic. 3. **Preferred:** Look-ahead parsing — O(n) time, O(1) space.
- **Preferred pattern:** Look-ahead parsing
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** Add current value unless the next value is larger; then subtract it.

```java
class Solution {
    public int romanToInt(String s) {
        int total = 0;
        for (int i = 0; i < s.length(); i++) {
            int cur = value(s.charAt(i));
            int next = i + 1 < s.length() ? value(s.charAt(i + 1)) : 0;
            total += cur < next ? -cur : cur;
        }
        return total;
    }
    private int value(char c) {
        return switch (c) {
            case 'I' -> 1; case 'V' -> 5; case 'X' -> 10; case 'L' -> 50;
            case 'C' -> 100; case 'D' -> 500; default -> 1000;
        };
    }
}
```

### 238. [Pow(x, n)](https://leetcode.com/problems/powx-n/) — Medium

- [ ] **Revised**
- **Recognition cue:** Compute powers in logarithmic multiplications, including negative exponent.
- **Approach ladder:** 1. Direct simulation. 2. Algebraic reduction, number theory, coordinate transformation, or digit arithmetic. 3. **Preferred:** Binary exponentiation — O(log |n|) time, O(1) space.
- **Preferred pattern:** Binary exponentiation
- **Preferred complexity:** O(log |n|) time, O(1) space
- **Invariant / state:** At each bit of exponent, square base; multiply result when the bit is set.
- **Pitfall:** Convert n to long before negating to handle Integer.MIN_VALUE.

```java
class Solution {
    public double myPow(double x, int n) {
        long exp = n;
        if (exp < 0) { x = 1.0 / x; exp = -exp; }
        double result = 1.0;
        while (exp > 0) {
            if ((exp & 1) == 1) result *= x;
            x *= x;
            exp >>= 1;
        }
        return result;
    }
}
```

### 239. [Multiply Strings](https://leetcode.com/problems/multiply-strings/) — Medium

- [ ] **Revised**
- **Recognition cue:** Grade-school digit accumulation
- **Approach ladder:** 1. Parse into numeric types — overflow / forbidden. 2. Repeated addition — too slow. 3. Multiply every digit pair into an m+n array with carry normalization — O(mn) **(preferred)**.
- **Preferred pattern:** Grade-school digit accumulation
- **Preferred complexity:** O(mn) time, O(m+n) space

```java
class Solution {
    public String multiply(String num1, String num2) {
        if (num1.equals("0") || num2.equals("0")) return "0";
        int m = num1.length(), n = num2.length(); int[] a = new int[m + n];
        for (int i = m - 1; i >= 0; i--) for (int j = n - 1; j >= 0; j--) {
            int product = (num1.charAt(i)-'0') * (num2.charAt(j)-'0');
            int low = i + j + 1, high = i + j;
            int sum = a[low] + product; a[low] = sum % 10; a[high] += sum / 10;
        }
        StringBuilder out = new StringBuilder(); int i = a[0] == 0 ? 1 : 0;
        for (; i < a.length; i++) out.append(a[i]); return out.toString();
    }
}
```

### 240. [Detect Squares](https://leetcode.com/problems/detect-squares/) — Medium

- [ ] **Revised**
- **Recognition cue:** Point-frequency map + enumerate same-row partners
- **Approach ladder:** 1. Enumerate all point triples — O(P³). 2. For query `(x,y)`, enumerate points `(x2,y)` and test two vertical corners with counts — O(number of distinct x on row) **(preferred)**.
- **Preferred pattern:** Point-frequency map + enumerate same-row partners
- **Preferred complexity:** Add O(1); count O(number of stored distinct points), O(P) space

```java
class DetectSquares {
    private final Map<Integer, Map<Integer, Integer>> rows = new HashMap<>();
    public void add(int[] point) { rows.computeIfAbsent(point[1], y -> new HashMap<>()).merge(point[0], 1, Integer::sum); }
    public int count(int[] point) {
        int x = point[0], y = point[1], ans = 0;
        Map<Integer,Integer> row = rows.get(y); if (row == null) return 0;
        for (var e : row.entrySet()) {
            int x2 = e.getKey(); if (x2 == x) continue; int side = Math.abs(x2 - x);
            for (int y2 : new int[]{y - side, y + side})
                ans += e.getValue() * rows.getOrDefault(y2, Map.of()).getOrDefault(x, 0)
                     * rows.getOrDefault(y2, Map.of()).getOrDefault(x2, 0);
        }
        return ans;
    }
}
```

---

## Bit Manipulation

### 241. [Single Number](https://leetcode.com/problems/single-number/) — Easy

- [ ] **Revised**
- **Recognition cue:** Every value appears twice except one.
- **Approach ladder:** 1. Arithmetic/string/set formulation. 2. XOR, masks, shifts, low-bit identities, or bit-deposit logic. 3. **Preferred:** XOR cancellation — O(n) time, O(1) space.
- **Preferred pattern:** XOR cancellation
- **Preferred complexity:** O(n) time, O(1) space
- **Invariant / state:** x^x=0 and XOR is associative/commutative.

```java
class Solution {
    public int singleNumber(int[] nums) {
        int answer = 0;
        for (int x : nums) answer ^= x;
        return answer;
    }
}
```

### 242. [Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/) — Easy

- [ ] **Revised**
- **Recognition cue:** Count set bits.
- **Approach ladder:** 1. Arithmetic/string/set formulation. 2. XOR, masks, shifts, low-bit identities, or bit-deposit logic. 3. **Preferred:** Brian Kernighan bit clearing — O(number of set bits) time, O(1) space.
- **Preferred pattern:** Brian Kernighan bit clearing
- **Preferred complexity:** O(number of set bits) time, O(1) space
- **Invariant / state:** n & (n-1) clears the lowest set bit each iteration.

```java
class Solution {
    public int hammingWeight(int n) {
        int count = 0;
        while (n != 0) {
            n &= n - 1;
            count++;
        }
        return count;
    }
}
```

### 243. [Counting Bits](https://leetcode.com/problems/counting-bits/) — Easy

- [ ] **Revised**
- **Recognition cue:** Lowest-set-bit DP
- **Approach ladder:** 1. Count bits independently per number — O(n log n). 2. `bits[i] = bits[i >> 1] + (i & 1)` or `bits[i&(i-1)]+1` — O(n) **(preferred)**.
- **Preferred pattern:** Lowest-set-bit DP
- **Preferred complexity:** O(n) time and O(n) output space

```java
class Solution {
    public int[] countBits(int n) {
        int[] bits = new int[n + 1];
        for (int i = 1; i <= n; i++) bits[i] = bits[i >> 1] + (i & 1);
        return bits;
    }
}
```

### 244. [Add Binary](https://leetcode.com/problems/add-binary/) — Easy

- [ ] **Revised**
- **Recognition cue:** Add binary strings without integer conversion.
- **Approach ladder:** 1. Arithmetic/string/set formulation. 2. XOR, masks, shifts, low-bit identities, or bit-deposit logic. 3. **Preferred:** Manual addition — O(max(m,n)) time, O(max(m,n)) space.
- **Preferred pattern:** Manual addition
- **Preferred complexity:** O(max(m,n)) time, O(max(m,n)) space
- **Invariant / state:** Process from right to left with carry; append low bit and shift carry.

```java
class Solution {
    public String addBinary(String a, String b) {
        StringBuilder out = new StringBuilder();
        int i = a.length() - 1, j = b.length() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry != 0) {
            int sum = carry;
            if (i >= 0) sum += a.charAt(i--) - '0';
            if (j >= 0) sum += b.charAt(j--) - '0';
            out.append(sum & 1);
            carry = sum >> 1;
        }
        return out.reverse().toString();
    }
}
```

### 245. [Reverse Bits](https://leetcode.com/problems/reverse-bits/) — Easy

- [ ] **Revised**
- **Recognition cue:** Reverse all 32 bits of an integer.
- **Approach ladder:** 1. Arithmetic/string/set formulation. 2. XOR, masks, shifts, low-bit identities, or bit-deposit logic. 3. **Preferred:** Fixed-width bit accumulation — O(32) time, O(1) space.
- **Preferred pattern:** Fixed-width bit accumulation
- **Preferred complexity:** O(32) time, O(1) space
- **Invariant / state:** Shift result left and append n's least-significant bit; use unsigned shift on n.

```java
public class Solution {
    public int reverseBits(int n) {
        int result = 0;
        for (int i = 0; i < 32; i++) {
            result = (result << 1) | (n & 1);
            n >>>= 1;
        }
        return result;
    }
}
```

### 246. [Missing Number](https://leetcode.com/problems/missing-number/) — Easy

- [ ] **Revised**
- **Recognition cue:** XOR cancellation
- **Approach ladder:** 1. Sort — O(n log n). 2. HashSet — O(n) space. 3. Arithmetic sum — O(n), overflow concern. 4. XOR indices and values — O(n), O(1) **(preferred)**.
- **Preferred pattern:** XOR cancellation
- **Preferred complexity:** O(n) time, O(1) space

```java
class Solution {
    public int missingNumber(int[] nums) {
        int x = nums.length;
        for (int i = 0; i < nums.length; i++) x ^= i ^ nums[i];
        return x;
    }
}
```

### 247. [Sum of Two Integers](https://leetcode.com/problems/sum-of-two-integers/) — Medium

- [ ] **Revised**
- **Recognition cue:** Bitwise full-adder loop
- **Approach ladder:** 1. Use arithmetic operators — disallowed. 2. XOR gives sum without carry; shifted AND gives carry; repeat until carry is zero — O(word size) **(preferred)**.
- **Preferred pattern:** Bitwise full-adder loop
- **Preferred complexity:** O(1) time for 32-bit ints, O(1) space

```java
class Solution {
    public int getSum(int a, int b) {
        while (b != 0) {
            int carry = (a & b) << 1;
            a ^= b;
            b = carry;
        }
        return a;
    }
}
```

### 248. [Reverse Integer](https://leetcode.com/problems/reverse-integer/) — Medium

- [ ] **Revised**
- **Recognition cue:** Digit extraction with pre-overflow checks
- **Approach ladder:** 1. Convert to string. 2. Pop decimal digits and verify bounds before `result*10+digit` — O(log |x|), O(1) **(preferred)**.
- **Preferred pattern:** Digit extraction with pre-overflow checks
- **Preferred complexity:** O(log |x|) time, O(1) space

```java
class Solution {
    public int reverse(int x) {
        int ans = 0;
        while (x != 0) {
            int digit = x % 10; x /= 10;
            if (ans > Integer.MAX_VALUE / 10 || (ans == Integer.MAX_VALUE / 10 && digit > 7)) return 0;
            if (ans < Integer.MIN_VALUE / 10 || (ans == Integer.MIN_VALUE / 10 && digit < -8)) return 0;
            ans = ans * 10 + digit;
        }
        return ans;
    }
}
```

### 249. [Bitwise AND of Numbers Range](https://leetcode.com/problems/bitwise-and-of-numbers-range/) — Medium

- [ ] **Revised**
- **Recognition cue:** AND every integer in [left, right].
- **Approach ladder:** 1. Arithmetic/string/set formulation. 2. XOR, masks, shifts, low-bit identities, or bit-deposit logic. 3. **Preferred:** Common binary prefix — O(log maxValue) time, O(1) space.
- **Preferred pattern:** Common binary prefix
- **Preferred complexity:** O(log maxValue) time, O(1) space
- **Invariant / state:** All differing suffix bits become zero; shift until endpoints share a prefix.

```java
class Solution {
    public int rangeBitwiseAnd(int left, int right) {
        int shifts = 0;
        while (left < right) {
            left >>= 1;
            right >>= 1;
            shifts++;
        }
        return left << shifts;
    }
}
```

### 250. [Minimum Array End](https://leetcode.com/problems/minimum-array-end/) — Medium

- [ ] **Revised**
- **Recognition cue:** Deposit bits of n-1 into zero bits of x
- **Approach ladder:** 1. Generate valid numbers incrementally — can be enormous. 2. Every array value must contain all set bits of x; map binary bits of n-1 into x’s zero positions — O(word size) **(preferred)**.
- **Preferred pattern:** Deposit bits of n-1 into zero bits of x
- **Preferred complexity:** O(log n + word size) time, O(1) space
- **Invariant / state:** All set bits of x remain set; free zero positions encode the sequence index.

```java
class Solution {
    public long minEnd(int n, int x) {
        long ans = x, bits = n - 1L;
        for (int pos = 0; bits != 0; pos++) {
            if (((ans >> pos) & 1L) == 0) {
                if ((bits & 1L) != 0) ans |= 1L << pos;
                bits >>= 1;
            }
        }
        return ans;
    }
}
```

---

## Final Recall Checklist

- [ ] I can identify the category before reading the solution.
- [ ] I can state the loop invariant, DFS return value, DP state, or greedy exchange argument.
- [ ] I know which solutions rely on expected hash-table performance or randomized partitioning.
- [ ] I check integer overflow, duplicate handling, empty inputs, and inclusive/exclusive boundaries.
- [ ] I can derive the preferred solution without memorizing variable names.

## Source and Maintenance Note

Problem titles and category counts follow the linked NeetCode 250 study plan. Problem statements are intentionally omitted. Solutions and explanations in this handbook are original condensed implementations intended for revision. Because curated lists can change, re-check the live list when using this file much later than the snapshot date.
