# Shortest Path in DAG

Find the shortest path from source node `0` to all other nodes in a **Directed Acyclic Graph (DAG)** with weighted edges.

> Return `INT_MAX` (or `-1`) for nodes unreachable from source.

---

## Why DAG Is Special

```
General graph → Dijkstra  O((V+E) log V)
DAG           → Topo Sort O(V+E)        ← faster, no priority queue needed
```

Topological order guarantees: when you process node `u` — **all paths to `u` are already finalized**. So each relaxation is permanent — no revisiting needed.

---

## What Does "Relax" Mean?

```cpp
if (dist[node] + weight < dist[neighbor])
    dist[neighbor] = dist[node] + weight;
```

> "Can I reach this neighbor cheaper by going through the current node? If yes — update."

`dist[neighbor]` starts at INF and **relaxes downward** toward the true shortest path — like releasing tension on a stretched rubber band.

---

## Approach 1 — Brute Force (DFS + Backtracking)

### Idea

Explore **every possible path** from source using DFS. At each node, update minimum distance if current path is shorter. Backtrack to allow revisiting nodes via different paths.

```cpp
class Solution {
private:
    void dfs(int node, int dist, vector<vector<pair<int,int>>>& adj,
             vector<int>& minDist, vector<bool>& vis) {
        vis[node] = true;
        minDist[node] = min(minDist[node], dist);

        for (auto [neighbor, weight] : adj[node])
            dfs(neighbor, dist + weight, adj, minDist, vis);

        vis[node] = false;   // backtrack — allow other paths through this node
    }

public:
    vector<int> shortestPath(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> adj(n);
        for (auto& e : edges)
            adj[e[0]].push_back({e[1], e[2]});

        vector<int> minDist(n, INT_MAX);
        vector<bool> vis(n, false);
        minDist[0] = 0;

        dfs(0, 0, adj, minDist, vis);
        return minDist;
    }
};
```

### Why So Slow

Backtracking allows revisiting nodes via different paths. Number of distinct paths in a dense DAG grows exponentially:

```
n nodes, every node connects to every node ahead:
paths from 0 to n-1 = 2^(n-2)

each path may traverse O(E) edges
→ total = O(2^V × E)
```

### Complexity

| | Value |
|-|-------|
| **Time** | O(2^V × E) — exponential paths |
| **Space** | O(V) — recursion stack depth = longest path |

---

## Approach 2 — Topological Sort (Optimal)

### Key Insight

> Topological order processes every node **after all its predecessors**. When you reach node `u` in topo order — `dist[u]` is already the shortest possible. Relax its neighbors once — done.

```
Brute force: node 2 processed via 0→1→2, 0→4→2, 0→1→4→2 ... repeatedly
Topo sort:   node 2 processed exactly ONCE — after both 1 and 4 are done
```

### The Three Guarantees

```
1. All predecessors of u processed before u  (topo order property)
2. dist[u] finalized when u is popped        (all incoming edges already relaxed)
3. Neighbors relaxed exactly once            (no revisiting needed)
```

### Algorithm

```
1. Build weighted adjacency list
2. Get topological order via DFS stack
3. Initialize dist[] = INF, dist[src] = 0
4. Pop nodes from topo stack one by one
5. Skip unreachable nodes (dist == INF)
6. Relax all neighbors
7. Return dist[]
```

### Implementation (C++)

```cpp
class Solution {
private:
    void dfs(int node, vector<vector<pair<int,int>>>& adj,
             vector<bool>& vis, stack<int>& st) {
        vis[node] = true;
        for (auto [neighbor, weight] : adj[node])
            if (!vis[neighbor])
                dfs(neighbor, adj, vis, st);
        st.push(node);   // push AFTER all neighbors — correct topo order
    }

public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
        // step 1 — build adjacency list
        vector<vector<pair<int,int>>> adj(n);
        for (auto& e : edges)
            adj[e[0]].push_back({e[1], e[2]});

        // step 2 — topological sort
        vector<bool> vis(n, false);
        stack<int> st;
        for (int i = 0; i < n; i++)
            if (!vis[i])
                dfs(i, adj, vis, st);

        // step 3 — initialize distances
        vector<int> dist(n, INT_MAX);
        dist[0] = 0;   // source

        // step 4 — relax in topological order
        while (!st.empty()) {
            int node = st.top(); st.pop();

            if (dist[node] == INT_MAX) continue;   // unreachable — skip

            for (auto [neighbor, weight] : adj[node])
                if (dist[node] + weight < dist[neighbor])
                    dist[neighbor] = dist[node] + weight;
        }

        return dist;
    }
};
```

### Dry Run

```
n=6, source=0
edges: 0→1(2), 0→4(1), 1→2(3), 2→3(6), 4→2(2), 4→5(4), 5→3(1)

adj:
0 → [{1,2},{4,1}]
1 → [{2,3}]
2 → [{3,6}]
4 → [{2,2},{5,4}]
5 → [{3,1}]
3 → []
```

**Topological Sort (DFS):**

```
dfs(0) → dfs(1) → dfs(2) → dfs(3) → push 3
                           push 2
                  push 1
         dfs(4) → dfs(2): visited
                  dfs(5) → dfs(3): visited
                           push 5
                  push 4
         push 0

topo stack (top→bottom): 0, 4, 5, 1, 2, 3
pop order:               0, 4, 5, 1, 2, 3
```

**Relaxation:**

| Pop | dist[node] | neighbor | new dist | update? | dist[] |
|-----|------------|----------|----------|---------|--------|
| 0 | 0 | 1(w=2) | 0+2=2 | ✅ | [0,2,INF,INF,INF,INF] |
| 0 | 0 | 4(w=1) | 0+1=1 | ✅ | [0,2,INF,INF,1,INF] |
| 4 | 1 | 2(w=2) | 1+2=3 | ✅ | [0,2,3,INF,1,INF] |
| 4 | 1 | 5(w=4) | 1+4=5 | ✅ | [0,2,3,INF,1,5] |
| 5 | 5 | 3(w=1) | 5+1=6 | ✅ | [0,2,3,6,1,5] |
| 1 | 2 | 2(w=3) | 2+3=5 > 3 | ❌ | [0,2,3,6,1,5] |
| 2 | 3 | 3(w=6) | 3+6=9 > 6 | ❌ | [0,2,3,6,1,5] |
| 3 | 6 | none | — | — | [0,2,3,6,1,5] |

**Final distances:**

| Node | Distance | Shortest Path |
|------|----------|---------------|
| 0 | 0 | source |
| 1 | 2 | 0→1 |
| 2 | 3 | 0→4→2 |
| 3 | 6 | 0→4→5→3 |
| 4 | 1 | 0→4 |
| 5 | 5 | 0→4→5 |

### Why `dist[node] == INT_MAX → continue`

```
Unreachable nodes have dist = INT_MAX
INT_MAX + weight → integer overflow → wrong distances for neighbors

Skip unreachable nodes entirely — their neighbors stay INF correctly
```

### Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O(V+E) | Topo sort O(V+E) + relaxation O(V+E) |
| **Space** | O(V+E) | adj list + dist + vis + stack |

---

## Brute Force vs Topo Sort

| | Brute Force | Topo Sort |
|-|-------------|-----------|
| **Time** | O(2^V × E) | O(V+E) |
| **Space** | O(V+E) | O(V+E) |
| **Each node processed** | Exponential times | Exactly once |
| **Revisits needed?** | Yes — backtracking | No — topo order finalizes dist |
| **Works on** | DAG only | DAG only |
| **Practical** | TLE for large input | ✅ Optimal for DAG |

---

## Why Not Dijkstra Here?

```
Dijkstra:  O((V+E) log V) — uses min-heap
Topo sort: O(V+E)         — no heap needed

DAG structure eliminates the need for a priority queue.
Topo order naturally gives the correct processing sequence.
Dijkstra is needed for general graphs (with cycles).
```

---

## Key Takeaways

- Topo sort is the natural fit for shortest path in DAG — processes each node once, each relaxation is permanent.
- **Relaxation** = "check if going through current node gives a shorter path to neighbor — if yes, update."
- Skip `dist[node] == INT_MAX` nodes — avoids integer overflow and correctly leaves unreachable neighbors as INF.
- Push nodes to stack AFTER all neighbors in DFS — this ensures correct topo order on pop.
- Brute force explores exponential paths because backtracking allows revisiting — topo sort eliminates this entirely.
