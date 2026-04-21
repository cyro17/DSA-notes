# Dijkstra's Algorithm — Shortest Path

Find the shortest path from a **source node** to all other nodes in a weighted graph with **non-negative edge weights**.

---

## Core Idea

> Always process the node with the **smallest known distance** first. When you process a node — its distance is finalized. Relax all its neighbors.

```
Greedy insight:
  If dis[u] is the minimum in the queue → no future path can improve it
  (all weights non-negative → future paths only get longer)
  → dis[u] is final when popped
```

---

## What "Relax" Means

```cpp
if (dis + w < dist[adjnode])
    dist[adjnode] = dis + w;
```

> "Can I reach this neighbor cheaper through the current node? If yes — update."

`dist[v]` starts at INF and relaxes downward toward the true shortest distance.

---

## Approach 1 — Priority Queue (Min Heap)

### Idea

Use a min-heap to always process the closest unvisited node. Stale entries (old distances) remain in queue but are skipped when popped.

```
Push new entry when distance improves.
Old entry stays — gets skipped via: if (dis > dist[node]) continue
```

### Implementation (C++)

```cpp
class Solution {
  public:
    vector<int> dijkstra(int n, vector<vector<int>>& edges, int src) {
        // build adjacency list
        vector<vector<pair<int,int>>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});  // remove if directed
        }

        // min heap: {distance, node}
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;

        vector<int> dist(n, 1e9);
        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [dis, node] = pq.top(); pq.pop();

            if (dis > dist[node]) continue;   // stale entry — skip

            for (auto& [adjnode, w] : adj[node]) {
                if (dis + w < dist[adjnode]) {
                    dist[adjnode] = dis + w;            // relax neighbor
                    pq.push({dist[adjnode], adjnode});   // push updated distance
                }
            }
        }

        return dist;
    }
};
```

### Stale Entry Handling

```
When shorter path found → push new entry
Old entry stays in queue

Example:
  dist[1] = 5 → push {5, 1}
  dist[1] = 3 → push {3, 1}   ← better path found
  pq: [{3,1}, {5,1}]

  pop {3,1}: process ✅ dist[1]=3 finalized
  pop {5,1}: dis=5 > dist[1]=3 → skip ✅ stale — no double processing
```

### Dry Run

```
graph: 0→1(4), 0→2(1), 2→1(2)
src = 0

pq: [{0,0}], dist = [0, INF, INF]

pop {0,0}: dis=0, node=0
  relax 1: 0+4=4 < INF → dist[1]=4, push {4,1}
  relax 2: 0+1=1 < INF → dist[2]=1, push {1,2}
  pq: [{1,2},{4,1}], dist=[0,4,1]

pop {1,2}: dis=1, node=2
  relax 1: 1+2=3 < 4 → dist[1]=3, push {3,1}
  pq: [{3,1},{4,1}], dist=[0,3,1]

pop {3,1}: dis=3, node=1
  no neighbors
  pq: [{4,1}], dist=[0,3,1]

pop {4,1}: dis=4 > dist[1]=3 → SKIP (stale)
  pq: []

dist = [0, 3, 1] ✅
```

---

## Approach 2 — Set Based

### Idea

Use an ordered `set` instead of priority queue. Set maintains sorted order automatically. **Explicitly erase** old entries when a shorter path is found — no stale entries ever exist.

```
Set always contains exactly one entry per node (the current best)
No stale entries → no skip check needed
Must erase current node after reading — otherwise infinite loop
```

### Set vs Priority Queue

| | Priority Queue | Set |
|-|----------------|-----|
| Stale entries | ✅ Exist — skipped via `dis > dist[node]` | ❌ None — explicitly erased |
| Get minimum | `pq.top()` | `*st.begin()` |
| Remove minimum | `pq.pop()` | `st.erase(st.begin())` |
| Update distance | Push new, old stays | Erase old, insert new |
| Duplicate entries | Yes | No — one entry per node |

### Implementation (C++)

```cpp
class Solution {
  public:
    vector<int> dijkstra(int n, vector<vector<int>>& edges, int src) {
        vector<vector<pair<int,int>>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }

        vector<int> dist(n, 1e9);
        set<pair<int,int>> st;   // {distance, node} — auto sorted by distance

        dist[src] = 0;
        st.insert({0, src});

        while (!st.empty()) {
            auto it = *(st.begin());
            st.erase(st.begin());        // ← CRITICAL: erase current node
            int dis  = it.first;
            int node = it.second;

            for (auto& [adjnode, w] : adj[node]) {
                if (dis + w < dist[adjnode]) {
                    // erase old entry if exists
                    if (dist[adjnode] != 1e9)
                        st.erase({dist[adjnode], adjnode});

                    dist[adjnode] = dis + w;
                    st.insert({dist[adjnode], adjnode});
                }
            }
        }

        return dist;
    }
};
```

### Critical Line

```cpp
st.erase(st.begin());   // must erase BEFORE processing neighbors
```

Without this — current node stays in set forever → processed again next iteration → infinite loop.

---

## Complexity Analysis

### Priority Queue

**How many pushes?**
```
Each edge triggers at most one push (when dist improves)
total pushes ≤ E
```

**How many pops?**
```
Every push eventually gets popped (including stale)
total pops ≤ E
```

**Cost per operation:**
```
queue size ≤ E ≤ V²
log(E) = log(V²) = 2log(V) = O(log V)

each push = O(log V)
each pop  = O(log V)
```

**Total:**
```
E pushes × O(log V) = O(E log V)
E pops   × O(log V) = O(E log V)
build adj            = O(E)
init dist            = O(V)

Total = O((V+E) log V)
```

### Set

Same asymptotic complexity — `set::insert`, `set::erase` are both O(log n):

```
each insert = O(log V)
each erase  = O(log V)
total ops   ≤ 2E (one erase + one insert per relaxation)

Total = O((V+E) log V)
```

### Space

| Structure | Cost |
|-----------|------|
| adj list | O(V+E) |
| dist array | O(V) |
| pq / set | O(E) worst case |
| **Total** | **O(V+E)** |

---

## Full Comparison

| | Priority Queue | Set |
|-|----------------|-----|
| **Time** | O((V+E) log V) | O((V+E) log V) |
| **Space** | O(V+E) | O(V+E) |
| **Stale entries** | Yes — skip check | No — explicit erase |
| **Queue size** | Up to E entries | Up to V entries |
| **Constant factor** | Slightly faster | Slightly slower (erase overhead) |
| **Interview pick** | ✅ More common | ✅ Cleaner semantics |

---

## Dijkstra vs Other Algorithms

| Algorithm | Time | Negative weights | Cycle |
|-----------|------|-----------------|-------|
| **Dijkstra** | O((V+E) log V) | ❌ No | ✅ Handles |
| Bellman-Ford | O(V×E) | ✅ Yes | ✅ Detects negative cycle |
| Topo Sort | O(V+E) | ✅ Yes | ❌ DAG only |
| BFS | O(V+E) | ❌ No | ✅ Handles |

---

## Key Takeaways

- Dijkstra is **greedy** — always process minimum distance node first. Non-negative weights guarantee this gives the globally optimal answer.
- **Priority queue version** — simpler code, stale entries skipped via `dis > dist[node]`. Total entries in queue ≤ E.
- **Set version** — no stale entries, explicit erase-before-insert for neighbors. Must erase current node (`st.erase(st.begin())`) or infinite loop.
- Both versions O((V+E) log V) — priority queue is slightly faster in practice due to lower constant factor.
- Fails on negative weights — use Bellman-Ford instead. Fails on negative cycles — Bellman-Ford detects them.
