# CSES — Building Roads

Problem: [CSES Building Roads](https://cses.fi/problemset/task/1666/)

## Problem statement

There are `n` cities and `m` existing bidirectional roads. Some cities may be connected indirectly through other cities, while the complete graph may consist of several disconnected groups.

Build the **minimum number of new roads** so that every city can reach every other city. Print:

1. The minimum number of roads required.
2. The endpoints of every new road.

### Constraints

- `1 <= n <= 100000`
- `1 <= m <= 200000`
- Cities are numbered from `1` to `n`.

## Key observation

Suppose the existing graph contains `k` connected components.

- At least `k - 1` roads are necessary. One road can reduce the number of disconnected components by at most one.
- Exactly `k - 1` roads are sufficient. Choose one representative city from every component and connect the representatives in a chain:

```text
root[0] -- root[1] -- root[2] -- ... -- root[k - 1]
```

Therefore:

```text
minimum roads = number of connected components - 1
```

## Approach: Disjoint Set Union

The solution uses a **Disjoint Set Union (DSU)** to group cities that are already connected.

```python
dsu = [-1] * (n + 1)
```

For a city `i`:

- `dsu[i] < 0` means that `i` is the root of a component.
- `-dsu[i]` is the number of cities in that component.
- `dsu[i] >= 0` means that `dsu[i]` is the parent of `i`.

Index `0` is unused because cities are numbered from `1`.

## Explanation of the solution

### 1. Find a component's root

```python
def parent(i):
    if dsu[i] < 0:
        return i
    return parent(dsu[i])
```

The root is the first node whose DSU value is negative.

This implementation uses union-by-size but does **not** perform path compression. Union-by-size still ensures that the tree height is at most `O(log n)`.

### 2. Merge two components

```python
def __join(parent, child):
    dsu[parent] += dsu[child]
    dsu[child] = parent
```

Both arguments are component roots. Their negative sizes are added, and the smaller component's root becomes a child of the larger component's root.

### 3. Process a road

```python
def join(u, v):
    up, vp = parent(u), parent(v)
    if up == vp:
        return
    if dsu[up] > dsu[vp]:
        up, vp = vp, up
    __join(up, vp)
```

- Find the roots of `u` and `v`.
- If they have the same root, the cities are already connected.
- Otherwise, merge the smaller component into the larger one.

Because component sizes are stored as negative values, a larger component has a more negative value. For example, size `5` is stored as `-5`, while size `2` is stored as `-2`. Therefore:

```python
if dsu[up] > dsu[vp]:
    up, vp = vp, up
```

ensures that `up` represents the larger component.

The `up == vp` check is essential. Without it, joining a root with itself would corrupt the DSU.

### 4. Collect component representatives

```python
def roots_of_cc():
    rcc = []
    for i in range(1, n + 1):
        if dsu[i] < 0:
            rcc.append(i)
    return rcc
```

After processing all existing roads, every negative DSU entry represents exactly one connected component. These roots are collected in `rcc`.

### 5. Connect the components

```python
def edge_cc(rcc):
    ercc = []
    for i in range(len(rcc) - 1):
        ercc.append([rcc[i], rcc[i + 1]])
    return ercc
```

The representatives are connected consecutively. If the roots are:

```text
[2, 5, 8, 10]
```

the new roads are:

```text
2 5
5 8
8 10
```

Four components become one using exactly three roads.

## Correctness argument

Let the graph initially contain `k` connected components.

1. The DSU merges the endpoints of every existing road, so two cities have the same DSU root exactly when they belong to the same connected component.
2. `roots_of_cc()` consequently returns one representative for each of the `k` components.
3. `edge_cc()` adds an edge between each consecutive pair of representatives. These `k - 1` edges form a chain containing every component, so the resulting graph is connected.
4. Any solution needs at least `k - 1` new roads, while this solution adds exactly `k - 1` roads.

Hence, the solution produces a valid set containing the minimum possible number of new roads.

## Complexity

With union-by-size and no path compression, each `parent()` operation takes `O(log n)` in the worst case.

- Processing roads: `O(m log n)`
- Finding all roots: `O(n)`
- Constructing the new roads: `O(n)`
- Total time: **`O(m log n + n)`**, commonly written as **`O((n + m) log n)`**
- Space: **`O(n + m)`** in this implementation because all input edges and the DSU are stored

The edges can instead be processed as they are read, reducing auxiliary space to `O(n)` excluding the output.

## Submitted solution

```python
if __name__ == "__main__":
    n, m = list(map(int, input().split()))
    edges = []
    for _ in range(m):
        edges.append(list(map(int, input().split())))

    dsu = [-1] * (n + 1)

    def parent(i):
        if dsu[i] < 0:
            return i
        return parent(dsu[i])

    def __join(parent, child):
        dsu[parent] += dsu[child]
        dsu[child] = parent

    def join(u, v):
        up, vp = parent(u), parent(v)
        if up == vp:
            return
        if dsu[up] > dsu[vp]:
            up, vp = vp, up
        __join(up, vp)

    def roots_of_cc():
        rcc = []
        for i in range(1, n + 1):
            if dsu[i] < 0:
                rcc.append(i)
        return rcc

    def edge_cc(rcc):
        ercc = []
        for i in range(len(rcc) - 1):
            ercc.append([rcc[i], rcc[i + 1]])
        return ercc

    for edge in edges:
        join(edge[0], edge[1])

    rcc = roots_of_cc()
    ercc = edge_cc(rcc)

    print(len(ercc))
    for e in ercc:
        print('{} {}'.format(e[0], e[1]))
```

## Optional improvement: path compression

`parent()` can compress the path so future root lookups become faster:

```python
def parent(i):
    if dsu[i] < 0:
        return i
    dsu[i] = parent(dsu[i])
    return dsu[i]
```

With both path compression and union-by-size, DSU operations take amortized `O(alpha(n))` time, where `alpha` is the inverse Ackermann function and is effectively constant for practical inputs.

