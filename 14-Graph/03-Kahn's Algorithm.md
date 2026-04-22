# Kahn's Algorithm — Topological Sort (BFS)

Find a valid **topological ordering** of a Directed Acyclic Graph (DAG) using BFS. Detects cycles as a bonus.

> For every directed edge `u → v`, vertex `u` must appear before `v` in the ordering.

---

## Core Intuition

> Always process the node that has **no remaining dependencies** first.

```
indegree == 0 → no dependencies → safe to process
After processing → remove edges → some neighbors now free
Process those next → repeat until empty
```

Think of it as **peeling layers**:
```
Layer 1: nodes with no prerequisites
Layer 2: nodes whose only prerequisites were in layer 1
Layer 3: nodes whose prerequisites were in layers 1-2
...
```

---

## Indegree — The Key Concept

**Indegree** = number of incoming edges = number of dependencies.

```
graph: 0→1, 0→2, 2→3, 3→1

indegree:
  node 0 → 0   (nothing points to 0 → process first)
  node 1 → 2   (0 and 3 point to 1)
  node 2 → 1   (0 points to 2)
  node 3 → 1   (2 points to 3)
```

---

## Algorithm — 5 Steps

```
1. Build adjacency list
2. Compute indegree for every node
3. Push all indegree-0 nodes to queue
4. BFS loop:
     pop node → add to result
     for each neighbor → indegree--
     if neighbor's indegree hits 0 → push to queue
5. result.size() == n → valid DAG (no cycle)
   result.size() <  n → cycle exists
```

---

## Implementation

### C++

```cpp
vector<int> topoSort(int n, vector<vector<int>>& adj) {
    // step 1 — compute indegrees
    vector<int> indegree(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : adj[u])
            indegree[v]++;

    // step 2 — seed queue with indegree-0 nodes
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            q.push(i);

    // step 3 — BFS
    vector<int> result;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        result.push_back(node);

        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    // step 4 — cycle check
    return result;   // result.size() < n → cycle exists
}
```

### Java

```java
int[] topoSort(int n, List<List<Integer>> adj) {
    // step 1 — compute indegrees
    int[] indegree = new int[n];
    for (int u = 0; u < n; u++)
        for (int v : adj.get(u))
            indegree[v]++;

    // step 2 — seed queue with indegree-0 nodes
    Queue<Integer> q = new LinkedList<>();
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            q.offer(i);           // ← index-based, not value

    // step 3 — BFS
    int[] result = new int[n];
    int idx = 0;
    while (!q.isEmpty()) {
        int node = q.poll();
        result[idx++] = node;

        for (int neighbor : adj.get(node)) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0)
                q.offer(neighbor);
        }
    }

    // step 4 — cycle check
    return idx == n ? result : new int[]{};
}
```

---

## Dry Run

```
graph:
5→0, 5→2, 4→0, 4→1, 2→3, 3→1

adj:
0→[], 1→[], 2→[3], 3→[1], 4→[0,1], 5→[0,2]

indegree:
node: 0  1  2  3  4  5
deg:  2  2  1  1  0  0
                     ↑  ↑
                  start here
```

| Step | Pop | Result | indegree changes | Queue after |
|------|-----|--------|-----------------|-------------|
| init | — | [] | — | [4, 5] |
| 1 | 4 | [4] | [0]:2→1, [1]:2→1 | [5] |
| 2 | 5 | [4,5] | [0]:1→0→push, [2]:1→0→push | [0,2] |
| 3 | 0 | [4,5,0] | no neighbors | [2] |
| 4 | 2 | [4,5,0,2] | [3]:1→0→push | [3] |
| 5 | 3 | [4,5,0,2,3] | [1]:1→0→push | [1] |
| 6 | 1 | [4,5,0,2,3,1] | no neighbors | [] |

```
result.size()=6 == n=6 → valid DAG ✅

verify:
5→0 ✅  5→2 ✅  4→0 ✅  4→1 ✅  2→3 ✅  3→1 ✅
```

**Result: [4, 5, 0, 2, 3, 1] ✅**

---

## Cycle Detection — How It Works

Nodes in a cycle **never reach indegree 0** — they wait on each other forever:

```
cycle: 1 → 2 → 3 → 1

indegree = [1, 1, 1]

To process 1 → need 3 first
To process 3 → need 2 first
To process 2 → need 1 first
→ circular → nobody goes first → queue empty → result.size()=0 ≠ n

cycle detected ✅
```

```cpp
// cycle check
if (result.size() != n)
    return {};  // cycle exists — no valid topological order
```

---

## Why Index-Based Loop for Seeding Queue

```cpp
// WRONG — range-based loop pushes VALUES not indices
for (int i : indegree)
    if (i == 0) q.push(i);   // pushes 0 (the value) not the node index

// Example: indegree = [0, 1, 0, 1]
// Wrong: pushes 0, 0  ← node 2 completely missed
// Right: pushes 0, 2  ← correct nodes

// CORRECT — index-based
for (int i = 0; i < n; i++)
    if (indegree[i] == 0)
        q.push(i);   // push INDEX i
```

---

## Kahn's vs DFS Topological Sort

| | Kahn's (BFS) | DFS |
|-|-------------|-----|
| **Time** | O(V+E) | O(V+E) |
| **Space** | O(V) | O(V) |
| **Cycle detection** | ✅ Built-in — result.size() check | ❌ Extra state tracking needed |
| **Iterative** | ✅ Fully iterative | ❌ Recursive by nature |
| **Stack overflow risk** | ❌ None | ✅ Yes for deep graphs |
| **Intuition** | Easier — peel dependency layers | Harder — finish order reversed |
| **Interview pick** | ✅ Preferred | Good to know |

---

## Applications

| Problem | How Kahn's Helps |
|---------|-----------------|
| Course Schedule I | Cycle detection → `result.size() == n` |
| Course Schedule II | Return topo order directly |
| Alien Dictionary | Character order graph → topo sort |
| Shortest Path in DAG | Process nodes in topo order, relax edges |
| Eventual Safe Nodes | Kahn's on reversed graph |
| Task Scheduling | Order tasks respecting dependencies |

---

## Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O(V+E) | Indegree build O(E) + BFS O(V+E) |
| **Space** | O(V) | indegree array + queue + result |

Each node enters and exits queue exactly once. Each edge traversed exactly once during neighbor processing.

---

## Common Mistakes

| Mistake | Effect | Fix |
|---------|--------|-----|
| Range-based loop for seeding | Pushes indegree values not node indices | `for(int i=0; i<n; i++)` |
| Not checking `result.size() == n` | Cycle goes undetected | Always check after BFS |
| Using `result.size() == n` in DFS topo | DFS doesn't handle cycles this way | Only valid for Kahn's |
| Decrementing before checking | Misses the 0-crossing | Decrement first, then check `== 0` |

---

## Key Takeaways

- Kahn's = BFS where the queue always holds "currently dependency-free" nodes.
- Indegree is the engine — decrementing it simulates removing processed edges.
- Cycle detection is free — cyclic nodes never reach indegree 0, never enter queue, result size < n.
- Always seed queue with **index**, not the indegree value itself.
- Multiple valid topological orderings exist — Kahn's gives one valid ordering depending on queue state.
