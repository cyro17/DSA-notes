# Cheapest Flights Within K Stops

Find the cheapest price from `src` to `dst` using **at most k stops** (at most k+1 edges). Return `-1` if no such route exists.

---

## Problem Mapping

```
cities     → nodes
flights    → directed weighted edges
k stops    → at most k+1 edges on path
cheapest   → minimum cost path with edge constraint
```

---

## Why Standard Dijkstra FAILS Here

This is the most important thing to understand about this problem.

### Dijkstra's Core Assumption

```
When a node is popped from the min-heap with cost C:
  C is the FINAL shortest distance to that node
  → mark visited, never process again
```

This works when edges are non-negative — no future path can improve C.

### How the Stop Constraint Breaks This

Consider:

```
src=0, dst=3, k=1 (at most 1 stop = at most 2 edges)

flights:
0→1 cost 100
0→2 cost 500
1→3 cost 100
2→3 cost 1      ← very cheap but needs 2 edges total

Direct path via 1:  0→1→3  cost=200  (1 stop, 2 edges) ✅ within k=1
Direct path via 2:  0→2→3  cost=501  (1 stop, 2 edges) ✅ within k=1
```

Dijkstra processes node 1 first (cost 100) — marks it visited.
Then finds path 0→2→3 costs 501 — higher, skip.

Answer = 200. Seems fine here.

Now change k=0 (at most 0 stops = at most 1 edge):

```
k=0: only direct flights allowed
0→3 doesn't exist
→ answer should be -1

But what if we add flight 0→3 cost 1000?
Answer = 1000

Dijkstra might find 0→1 (cost 100) first, mark 1 visited
Then try to reach 3 via 1 — but that's 2 edges, violates k=0
Dijkstra has no mechanism to track HOW MANY edges were used
→ can return wrong answer
```

### The Core Conflict

```
Standard Dijkstra optimizes: minimize COST
This problem optimizes:      minimize COST subject to EDGE COUNT ≤ k+1

These are two different optimization problems.
Dijkstra's visited marking conflates them:
  "I reached node X cheaply" ≠ "I reached node X within k stops"

A more expensive path with fewer stops
might be the only valid answer under k constraint.
```

### Concrete Failure Case

```
src=0, dst=2, k=1

flights: 0→1(1), 1→2(1), 0→2(100)

Dijkstra:
  pop {0, src=0}
  push {1, node=1} and {100, node=2}

  pop {1, node=1}
  push {2, node=2}  ← same node 2, cost 2

  pop {2, node=2} → dst reached → return 2 ✅

Okay works here. Now k=0 (only 1 edge allowed):

Dijkstra (unmodified):
  pop {0, src=0}
  push {1, node=1} stops=1 → but k=0, 1 stop not allowed!
  push {100, node=2}

  Without stop tracking → pops {1, node=1} → pushes {2, node=2}
  → returns 2 using 2 edges ❌ (violates k=0)

Correct answer = 100 (only 0→2 is valid within k=0)
```

### Summary of Why Dijkstra Fails

```
1. No mechanism to count edges/stops used
2. Visited marking prevents exploring same node via fewer stops
3. Cheaper path found first ≠ valid path within k stops
4. Can return path that uses too many edges
5. Can miss valid paths by marking nodes visited too early
```

---

## Approach 1 — Bellman-Ford (Best Fit)

### Why It's Perfect

```
k stops = k+1 edges
Bellman-Ford pass i = finds shortest paths using exactly i edges
Run k+1 passes → finds cheapest path using at most k+1 edges ✅

No visited array → naturally handles same node via different stop counts
```

### The Snapshot — Why Critical

```
Without snapshot (wrong):
  Pass i processes edge A→B → updates dist[B]
  Same pass then processes B→C → uses updated dist[B]
  = 2 edges used in 1 pass → violates k stop constraint ❌

With snapshot (correct):
  Pass i reads from dist (previous pass values)
  Writes to temp (current pass values)
  All relaxations in pass i use exactly i-1 edge paths ✅
```

### Implementation (C++)

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights,
                          int src, int dst, int k) {
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        // k stops = k+1 edges = k+1 passes
        for (int i = 0; i <= k; i++) {
            vector<int> temp = dist;   // ← snapshot of current state

            for (auto& f : flights) {
                int u = f[0], v = f[1], w = f[2];
                if (dist[u] != INT_MAX && dist[u] + w < temp[v])
                    temp[v] = dist[u] + w;
            }

            dist = temp;
        }

        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};
```

### Dry Run

```
n=4, src=0, dst=3, k=1
flights: 0→1(100), 0→2(500), 1→3(100), 2→3(1)

dist = [0, INF, INF, INF]
```

**Pass 1 (i=0, 0 stops, 1 edge):**
```
temp = [0, INF, INF, INF]

0→1(100): dist[0]=0, 0+100=100 < INF → temp[1]=100
0→2(500): dist[0]=0, 0+500=500 < INF → temp[2]=500
1→3(100): dist[1]=INF → skip (snapshot — not yet updated)
2→3(1):   dist[2]=INF → skip

dist = [0, 100, 500, INF]
```

**Pass 2 (i=1, 1 stop, 2 edges):**
```
temp = [0, 100, 500, INF]

0→1(100): 0+100=100 == 100 → skip
0→2(500): 0+500=500 == 500 → skip
1→3(100): dist[1]=100, 100+100=200 < INF → temp[3]=200
2→3(1):   dist[2]=500, 500+1=501 > 200... wait 200 already set
          501 > 200 → skip

dist = [0, 100, 500, 200]
```

**Answer: dist[3] = 200 ✅**

### Complexity

| | Value |
|-|-------|
| **Time** | O(k × E) — k+1 passes, each O(E) |
| **Space** | O(V) — dist + temp arrays |

---

## Approach 2 — Modified Dijkstra (Stop Tracking)

### The Fix for Dijkstra

Track **stops used** in the heap state. Never skip based on node alone — skip based on `(node, stops)` pair. Prune on stops not cost:

```
stops[node] = minimum stops used to reach node so far
if current stops >= stops[node] → already reached with fewer stops → skip
```

Fewer stops = more flexibility for remaining path = always preferred.

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights,
                          int src, int dst, int k) {
        vector<vector<pair<int,int>>> adj(n);
        for (auto& f : flights)
            adj[f[0]].push_back({f[1], f[2]});

        // min heap: {cost, node, stops_used}
        priority_queue<tuple<int,int,int>,
                       vector<tuple<int,int,int>>,
                       greater<>> pq;

        pq.push({0, src, 0});
        vector<int> stops(n, INT_MAX);   // min stops to reach each node

        while (!pq.empty()) {
            auto [cost, node, used] = pq.top(); pq.pop();

            if (node == dst) return cost;   // first valid reach = cheapest

            if (used > k) continue;         // exceeded stop limit → skip
            if (stops[node] < used) continue; // better stop count seen → skip

            stops[node] = used;

            for (auto& [neighbor, w] : adj[node])
                pq.push({cost + w, neighbor, used + 1});
        }

        return -1;
    }
};
```

### Why Prune on Stops Not Cost

```
Two paths to node X:
  Path A: cost=50,  stops=3
  Path B: cost=100, stops=1

Standard Dijkstra keeps A (cheaper cost)
Modified Dijkstra keeps B (fewer stops = more flexibility)

If k=2 remaining:
  Path A has used 3 stops already → might violate k
  Path B has used 1 stop → 1 more stop available → valid
```

### Complexity

| | Value |
|-|-------|
| **Time** | O(E log(V×k)) — each (node,stop) state pushed once |
| **Space** | O(V×k) — states in heap |

---

## All Approaches Compared

| | Standard Dijkstra | Bellman-Ford | Modified Dijkstra |
|-|-------------------|--------------|-------------------|
| **Correct?** | ❌ No | ✅ Yes | ✅ Yes |
| **Time** | O((V+E)logV) | O(k×E) | O(E log(Vk)) |
| **Space** | O(V) | O(V) | O(Vk) |
| **Handles k constraint** | ❌ No edge count tracking | ✅ Natural — limit passes | ✅ Via stop state |
| **Snapshot needed** | ❌ | ✅ Critical | ❌ |
| **Visited marking** | Node-based (wrong) | None | Stop-based (correct) |
| **Interview pick** | ❌ | ✅ Cleanest | ✅ Good alternative |

---

## Why Bellman-Ford Wins

```
Bellman-Ford:
  k+1 passes → naturally limits to k+1 edges
  no visited array → handles same node via different stop counts
  temp snapshot → enforces exactly 1 hop per pass
  O(k×E) clean, simple, correct

Modified Dijkstra:
  needs extra stop state in heap
  more complex pruning logic
  O(Vk) space for heap states
  harder to reason about correctness
```

---

## Common Mistakes

| Mistake | Effect | Fix |
|---------|--------|-----|
| Using standard Dijkstra | Wrong answer — no stop tracking | Use Bellman-Ford or modified Dijkstra |
| Missing temp snapshot in Bellman-Ford | Edges chain in same pass → wrong stop count | Always snapshot before each pass |
| `dist[u] == INT_MAX` not checked | Overflow: INT_MAX + w → negative | Guard `dist[u] != INT_MAX` |
| Pruning on cost in modified Dijkstra | Valid paths with fewer stops skipped | Prune on stops not cost |
| Running V-1 passes instead of k+1 | Ignores stop constraint | Run exactly `k+1` passes |

---

## Key Takeaways

- Standard Dijkstra **cannot** handle stop constraints — it has no mechanism to count edges and its visited marking is node-based not stop-based.
- Bellman-Ford is the **natural fit** — each pass corresponds to one more edge, limiting to `k+1` passes directly enforces the constraint.
- The temp **snapshot** is non-negotiable — without it edges chain within a single pass, effectively using more stops than allowed.
- Modified Dijkstra works but needs stop-based pruning, not cost-based — fewer stops always preferred over cheaper cost.
- `dist[u] != INT_MAX` guard prevents unreachable nodes from propagating wrong distances through negative or large edges.
