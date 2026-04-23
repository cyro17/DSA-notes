# Bellman-Ford Algorithm

Find shortest path from a **single source** to all nodes — handles **negative edge weights** and **detects negative cycles**.

---

## When to Use Bellman-Ford

```
Negative edge weights present   → Bellman-Ford ✅
Negative cycle detection needed → Bellman-Ford ✅
Stop/hop constraint (k stops)   → Bellman-Ford ✅
All non-negative weights        → Dijkstra (faster)
```

---

## Core Idea

> Relax **every edge**, **V-1 times**.

```
Relax edge (u, v, w):
  if dist[u] + w < dist[v]:
      dist[v] = dist[u] + w
```

**Why V-1 times?**
```
Shortest simple path in V-node graph → at most V-1 edges
After i relaxations → shortest paths using ≤ i edges are correct
After V-1 relaxations → ALL shortest paths correct ✅
```

---

## Negative Cycle Detection

After V-1 passes — if the **V-th pass still relaxes any edge** → negative cycle exists.

**Why?**
```
V-1 passes found all shortest simple paths (≤ V-1 edges)
V-th pass finds cheaper path with V edges
→ V edges, V nodes → pigeonhole → repeated node → CYCLE
→ cycle made path cheaper → NEGATIVE CYCLE
```

```
negative cycle: 1→2(-3)→3(1)→1  total = -3+1 = -2
Each loop reduces dist further → approaches -∞
→ no finite shortest path → report -1
```

---

## Implementation

### C++

```cpp
class Solution {
  public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        vector<int> dist(V, 1e8);
        dist[src] = 0;

        // step 1 — relax all edges V-1 times
        for (int i = 0; i < V - 1; i++) {
            for (auto& it : edges) {
                int u = it[0], v = it[1], w = it[2];

                // guard: only relax if u is reachable
                if (dist[u] != 1e8 && dist[u] + w < dist[v])
                    dist[v] = dist[u] + w;
            }
        }

        // step 2 — V-th pass: negative cycle check
        for (auto& it : edges) {
            if (dist[it[0]] != 1e8 && dist[it[0]] + it[2] < dist[it[1]])
                return {-1};   // negative cycle detected
        }

        return dist;
    }
};
```

### Java

```java
int[] bellmanFord(int V, int[][] edges, int src) {
    int[] dist = new int[V];
    Arrays.fill(dist, (int)1e8);
    dist[src] = 0;

    // relax V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != (int)1e8 && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // V-th pass — negative cycle check
    for (int[] edge : edges) {
        if (dist[edge[0]] != (int)1e8 && dist[edge[0]] + edge[2] < dist[edge[1]])
            return new int[]{-1};
    }

    return dist;
}
```

---

## Dry Run

```
V=5, src=0
edges: 0→1(4), 0→2(2), 2→1(-3), 1→3(5), 3→4(1)

dist = [0, 1e8, 1e8, 1e8, 1e8]
```

**Pass 1:**

| Edge | dist[u] | dist[u]+w | dist[v] before | update? | dist[v] after |
|------|---------|-----------|----------------|---------|----------------|
| 0→1(4) | 0 | 4 | 1e8 | ✅ | 4 |
| 0→2(2) | 0 | 2 | 1e8 | ✅ | 2 |
| 2→1(-3) | 2 | -1 | 4 | ✅ | -1 |
| 1→3(5) | -1 | 4 | 1e8 | ✅ | 4 |
| 3→4(1) | 4 | 5 | 1e8 | ✅ | 5 |

```
dist = [0, -1, 2, 4, 5]
```

**Pass 2:**

| Edge | dist[u]+w | dist[v] | update? |
|------|-----------|---------|---------|
| 0→1(4) | 4 | -1 | ❌ |
| 0→2(2) | 2 | 2 | ❌ |
| 2→1(-3) | -1 | -1 | ❌ |
| 1→3(5) | 4 | 4 | ❌ |
| 3→4(1) | 5 | 5 | ❌ |

No updates → converged early ✅

**V-th pass check:** no edge relaxes → no negative cycle ✅

```
dist = [0, -1, 2, 4, 5] ✅
```

---

## Why `dist[u] != 1e8` Guard Is Critical

Without guard — unreachable nodes pollute neighbors:

```
node u unreachable → dist[u] = 1e8
edge u→v, w = -50

dist[u] + w = 1e8 - 50 = 99999950 < dist[v] = 1e8
→ dist[v] wrongly updated ❌
→ V-th pass falsely reports negative cycle ❌
```

With guard:
```
dist[u] == 1e8 → skip
→ unreachable node never propagates → correct ✅
```

---

## Why `1e8` Not `INT_MAX`

```
INT_MAX + positive_w → integer overflow → becomes negative
→ comparison dist[u]+w < dist[v] behaves completely wrong

1e8 is safe:
  1e8 + 1e8 = 2e8 < INT_MAX (≈2.1e9) → no overflow ✅
  large enough to represent "unreachable" for typical constraints ✅
```

---

## K Stops Variant (Cheapest Flights Problem)

Run exactly `k+1` relaxations instead of `V-1`. **Snapshot (`temp`) is critical.**

```cpp
vector<int> dist(n, 1e8);
dist[src] = 0;

for (int i = 0; i <= k; i++) {
    vector<int> temp = dist;   // ← snapshot of current state

    for (auto& flight : flights) {
        int u = flight[0], v = flight[1], w = flight[2];
        if (dist[u] != (int)1e8 && dist[u] + w < temp[v])
            temp[v] = dist[u] + w;
    }

    dist = temp;
}

return dist[dst] == (int)1e8 ? -1 : dist[dst];
```

**Why snapshot matters:**
```
Without temp — edges chain within same pass:
  A→B relaxes B, then B→C uses updated B → 2 edges in 1 pass
  violates k stop constraint ❌

With temp — pass i uses only pass i-1 values:
  exactly 1 edge per pass → correctly counts stops ✅
```

---

## Bellman-Ford vs Dijkstra — Full Comparison

| | Bellman-Ford | Dijkstra |
|-|--------------|----------|
| **Time** | O(V×E) | O((V+E) log V) |
| **Space** | O(V) | O(V+E) |
| **Negative weights** | ✅ Yes | ❌ No |
| **Negative cycle detection** | ✅ Yes — V-th pass | ❌ Infinite loop |
| **Stop constraint (k hops)** | ✅ Natural — limit passes | ❌ Needs modification |
| **Approach** | Relax all edges V-1 times | Greedy min-heap |
| **Data structure** | Just arrays | Priority queue |
| **Early termination** | ✅ If no updates in a pass | ✅ When dest popped |
| **Dense graphs** | O(V³) worst case | O(V² log V) |
| **Sparse graphs** | O(V×E) | O((V+E) log V) ← faster |

---

## When To Use Which — Decision Guide

| Situation | Algorithm |
|-----------|-----------|
| All non-negative weights, need speed | **Dijkstra** |
| Negative edge weights | **Bellman-Ford** |
| Need to detect negative cycle | **Bellman-Ford** |
| Path with at most k stops/hops | **Bellman-Ford** (limit passes) |
| Unweighted grid shortest path | **BFS** |
| DAG with any weights | **Topo Sort + Relaxation** |

---

## Interview Cheat Sheet

```
Q: Why V-1 iterations?
A: Shortest simple path has at most V-1 edges.
   Each pass finds shortest paths with one more edge.
   After V-1 passes all simple paths are optimal.

Q: How does negative cycle detection work?
A: After V-1 passes all simple paths are optimal.
   If V-th pass still relaxes → path needs V edges → cycle exists
   → cycle reduces cost → negative cycle.

Q: Why not Dijkstra for negative weights?
A: Dijkstra's greedy assumption breaks — when node is popped
   as minimum, a negative edge elsewhere could provide shorter
   path later. Greedy finalization no longer holds.

Q: Why temp snapshot for k stops?
A: Without it — multiple edges chain in one pass,
   using more than 1 hop. Snapshot enforces exactly
   1 edge per relaxation round → correct stop count.

Q: Why 1e8 not INT_MAX?
A: INT_MAX + weight → integer overflow → wrong comparisons.
   1e8 is large enough to represent infinity safely.
```

---

## Key Takeaways

- Bellman-Ford = relax all edges V-1 times. Simple but powerful.
- V-th pass update = negative cycle (pigeonhole: V edges → repeated node → cycle → negative cost).
- Always guard `dist[u] != 1e8` — unreachable nodes with negative outgoing edges corrupt neighbor distances and cause false cycle reports.
- Use `1e8` not `INT_MAX` — avoids integer overflow during addition.
- K stops variant = limit to `k+1` passes + temp snapshot to enforce exactly one hop per pass.
- Dijkstra is faster for non-negative weights — use Bellman-Ford only when negative weights or stop constraints are involved.
