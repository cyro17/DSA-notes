# Prim's Algorithm — Minimum Spanning Tree

## Problem Statement

Given a weighted, undirected, connected graph with `n` nodes and `m` edges, find the **sum of edge weights in the Minimum Spanning Tree (MST)**.

> A **Minimum Spanning Tree** is a subset of edges that connects all vertices with the minimum possible total edge weight and no cycles.

---

## Intuition

Prim's algorithm builds the MST **greedily** — one vertex at a time.

Start from any source node (node `0`). At every step, pick the **cheapest edge** that connects a visited node to an unvisited node, and "grow" the MST by pulling that node in.

This is similar to Dijkstra's but instead of tracking cumulative shortest distance, we track the **minimum edge weight to reach a node**.

---

## Approach — Lazy Prim's with Min-Heap

1. Use a **min-heap** (priority queue) storing `{edge_weight, node}`.
2. Push `{0, 0}` (cost 0 to start at node 0).
3. While the heap is non-empty:
   - Pop the minimum cost entry `{w, node}`.
   - If `node` is already visited → **skip** (lazy deletion).
   - Mark `node` as visited, add `w` to MST sum.
   - Push all unvisited neighbors with their edge weights.
4. Return the total MST sum.

**Why skip visited nodes?**  
When we push a node multiple times (via different edges), the heap may contain stale entries. We skip them once the node is finalized — this is the "lazy" variant.

---

## Dry Run

**Graph (0-indexed, 4 nodes):**
```
0 --2-- 1
|       |
6       3
|       |
3 --1-- 2
```

**Edges:** `(0,1,2), (0,3,6), (1,2,3), (3,2,1)`

| Step | Heap (top)  | Visited       | MST Sum | Action                          |
|------|-------------|---------------|---------|---------------------------------|
| Init | {0,0}       | []            | 0       | Start                           |
| 1    | {0,0}       | [0]           | 0       | Visit 0, push {2,1}, {6,3}      |
| 2    | {2,1}       | [0,1]         | 2       | Visit 1, push {3,2}             |
| 3    | {3,2}       | [0,1,2]       | 5       | Visit 2, push {1,3}             |
| 4    | {1,3}       | [0,1,2,3]     | 6       | Visit 3 (cheaper path via 2)    |
| 5    | {6,3}       | —             | 6       | Skip 3 (already visited, lazy)  |

**MST Sum = 6** ✅

---

## Complexity Analysis

| Factor        | Value        | Reason                                                     |
|---------------|--------------|------------------------------------------------------------|
| Time          | O(E log E)   | Each edge is pushed to the heap once; heap ops are O(log E)|
| Space         | O(V + E)     | Adjacency list O(V+E) + heap O(E) + visited array O(V)    |

> For dense graphs (E ≈ V²), this becomes O(V² log V). In such cases, an indexed priority queue or Fibonacci heap reduces time to O(E + V log V).

---

## Code

### C++

```cpp
class Solution {
  public:
    int spanningTree(int n, vector<vector<int>>& edges) {
        vector<pair<int, int>> adj[n];
        for (auto it : edges) {
            int u = it[0], v = it[1], w = it[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        vector<int> vis(n, 0);
        // min-heap: {edge_weight, node}
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;

        pq.push({0, 0});
        int sum = 0;

        while (!pq.empty()) {
            auto [w, node] = pq.top(); pq.pop();
            if (vis[node]) continue;   // lazy skip
            vis[node] = 1;
            sum += w;
            for (auto [adjnode, wt] : adj[node]) {
                if (!vis[adjnode])
                    pq.push({wt, adjnode});
            }
        }
        return sum;
    }
};
```

### Java

```java
import java.util.*;

class Solution {
    public int spanningTree(int n, int[][] edges) {
        List<int[]>[] adj = new ArrayList[n];
        for (int i = 0; i < n; i++) adj[i] = new ArrayList<>();

        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            adj[u].add(new int[]{v, w});
            adj[v].add(new int[]{u, w});
        }

        boolean[] vis = new boolean[n];
        // min-heap: {edge_weight, node}
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        pq.offer(new int[]{0, 0});
        int sum = 0;

        while (!pq.isEmpty()) {
            int[] top = pq.poll();
            int w = top[0], node = top[1];
            if (vis[node]) continue;   // lazy skip
            vis[node] = true;
            sum += w;
            for (int[] neighbor : adj[node]) {
                int adjNode = neighbor[0], wt = neighbor[1];
                if (!vis[adjNode])
                    pq.offer(new int[]{wt, adjNode});
            }
        }
        return sum;
    }
}
```

---

## Key Observations

- **Prim's vs Kruskal's:** Prim's grows the MST vertex-by-vertex from a source; Kruskal's sorts all edges and uses DSU to add edges without forming cycles. Prim's is generally better for **dense graphs**; Kruskal's is better for **sparse graphs**.
- **Prim's vs Dijkstra's:** The structure is identical — only the priority changes. Dijkstra minimizes **cumulative distance** (sum of edge weights on path); Prim's minimizes **individual edge weight** to add to the MST.
- **Lazy vs Eager:** This implementation is "lazy" — stale heap entries are skipped via the `vis` check. An eager variant using a decrease-key structure is more space-efficient but harder to implement.
- **Works on undirected graphs only** — MST is defined for undirected graphs.

---

## Related Problems

| Problem                          | Concept                          |
|----------------------------------|----------------------------------|
| Kruskal's MST (DSU)              | Alternative MST algorithm        |
| Dijkstra's Shortest Path         | Same heap pattern, different goal|
| Number of Operations to Make Network Connected | MST + DSU hybrid |
| Connecting Cities With Minimum Cost | Direct MST application       |
