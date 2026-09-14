# CSES — Building Teams

Problem: [CSES Building Teams](https://cses.fi/problemset/task/1668)

## Problem statement

There are `n` pupils and `m` friendship relationships. Divide all pupils into two teams such that no two friends belong to the same team.

For every pupil, print:

- `1` if the pupil belongs to team 1.
- `2` if the pupil belongs to team 2.

If no valid assignment exists, print `IMPOSSIBLE`.

### Constraints

- `1 <= n <= 100000`
- `1 <= m <= 200000`
- Each friendship is bidirectional.

## Graph interpretation

Treat:

- Each pupil as a graph node.
- Each friendship as an undirected edge.
- Team `1` and team `2` as two different colors.

The task is therefore to determine whether the graph is **bipartite**.

A graph is bipartite if its nodes can be divided into two groups such that every edge connects nodes from different groups.

## Key observation

During BFS, if a pupil is placed in one team, every friend must be placed in the opposite team.

```text
team 1 -> team 2 -> team 1 -> team 2
```

If an edge connects two pupils already assigned to the same team, no valid division exists.

This conflict happens precisely when the graph contains an odd-length cycle.

## Approach: BFS two-coloring

Use an array named `team`:

```python
team = [0] * (n + 1)
```

Its values mean:

- `0`: not assigned yet
- `1`: assigned to team 1
- `2`: assigned to team 2

### Why iterate over every pupil?

The graph can be disconnected:

```text
1 -- 2       3 -- 4       5
```

A BFS starting only from `1` would never assign teams to pupils `3`, `4`, and `5`. Therefore, start a new BFS from every still-unassigned pupil.

```python
for start in range(1, n + 1):
    if team[start] != 0:
        continue

    team[start] = 1
    queue = deque([start])
```

An isolated pupil can safely be assigned to either team.

### Assign the opposite team

If `node` is in team `1`, its neighbor must be in team `2`, and vice versa.

```python
team[next_node] = 3 - team[node]
```

This works because:

```text
3 - 1 = 2
3 - 2 = 1
```

### Detect a conflict

When a neighbor already has a team, compare its team with the current node's team:

```python
elif team[next_node] == team[node]:
    possible = False
```

If they are friends but have the same team, the required assignment is impossible.

## Correct solution

```python
from collections import deque

if __name__ == "__main__":
    n, m = map(int, input().split())
    graph = [[] for _ in range(n + 1)]

    for _ in range(m):
        a, b = map(int, input().split())
        graph[a].append(b)
        graph[b].append(a)

    # 0 = unassigned, 1 = team 1, 2 = team 2
    team = [0] * (n + 1)
    possible = True

    for start in range(1, n + 1):
        if team[start] != 0:
            continue

        team[start] = 1
        queue = deque([start])

        while queue and possible:
            node = queue.popleft()

            for next_node in graph[node]:
                if team[next_node] == 0:
                    team[next_node] = 3 - team[node]
                    queue.append(next_node)
                elif team[next_node] == team[node]:
                    possible = False
                    break

        if not possible:
            break

    if not possible:
        print("IMPOSSIBLE")
    else:
        print(*team[1:])
```

## Example walkthrough

Input:

```text
5 3
1 2
1 3
4 5
```

The graph has two connected components:

```text
2 -- 1 -- 3       4 -- 5
```

One valid assignment is:

| Pupil | Team |
| --- | --- |
| 1 | 1 |
| 2 | 2 |
| 3 | 2 |
| 4 | 1 |
| 5 | 2 |

Output:

```text
1 2 2 1 2
```

Other valid assignments are also accepted.

## Impossible example

Consider a triangle:

```text
1 -- 2
|    |
+-- 3
```

Input:

```text
3 3
1 2
2 3
3 1
```

Suppose pupil `1` is assigned team `1`:

- Pupil `2` must be in team `2`.
- Pupil `3` must be in team `1` because pupil `3` is a friend of pupil `2`.
- But pupils `1` and `3` are friends and are now both in team `1`.

Therefore, the output is:

```text
IMPOSSIBLE
```

## Correctness argument

We prove that the algorithm prints a valid assignment exactly when one exists.

### If the algorithm prints teams, the assignment is valid

For every processed edge `(u, v)`:

- If `v` was unassigned, the algorithm assigned it the opposite team from `u`.
- If `v` was already assigned, the algorithm verified that `u` and `v` had different teams.

Therefore, every friendship connects pupils in different teams.

### If the algorithm prints `IMPOSSIBLE`, no valid assignment exists

The algorithm prints `IMPOSSIBLE` only after finding an edge `(u, v)` whose endpoints have the same team. The BFS coloring alternates teams along every path. Such a conflict means that two paths force incompatible colors, forming an odd-length cycle. An odd-length cycle cannot be divided into two teams without placing two adjacent nodes together.

Therefore, no valid assignment exists.

## Complexity

Every pupil is added to a BFS queue at most once, and every friendship is examined twice—once from each endpoint.

- Time: **`O(n + m)`**
- Space: **`O(n + m)`** for the adjacency list, team array, and BFS queue

## Common mistakes

### 1. Starting BFS only from node 1

This misses disconnected components. Start BFS from every unassigned node.

### 2. Using only a visited set

Knowing that a node was visited is insufficient. We must know which of the two teams it belongs to.

### 3. Skipping already-visited neighbors completely

An already-colored neighbor must still be checked. If it has the same team as the current node, the graph is not bipartite.

### 4. Marking nodes only after dequeueing

Assign the team before enqueueing. This prevents duplicate queue entries and ensures the first assignment is preserved.

