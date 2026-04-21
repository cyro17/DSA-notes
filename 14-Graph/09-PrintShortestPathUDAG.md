# Shortest Path in Weighted Undirected Graph

Find the shortest path from node `1` to node `n` in a weighted undirected graph. Return the **cost** followed by the **path nodes**. Return `{-1}` if no path exists.

---

## Output Format (GFG Specific)

```
result[0]     = minimum distance (cost)
result[1...]  = path nodes from 1 to n

Example: cost=5, path=[1,4,3,5]
result = [5, 1, 4, 3, 5]
```

---

## Approach 1 — Brute Force (DFS + Backtracking)

### Idea

Explore **every possible path** from source using DFS with backtracking. Record cost and path whenever destination is reached. After full exploration — return minimum cost path.

### Implementation (C++)

```cpp
class Solution {
private:
    void dfs(int node, int dest, int cost,
             vector<int>& path,
             vector<vector<pair<int,int>>>& adj,
             vector<bool>& vis,
             int& minCost,
             vector<int>& bestPath) {

        if (node == dest) {
            if (cost < minCost) {
                minCost  = cost;
                bestPath = path;
            }
            return;
        }

        for (auto [adjnode, w] : adj[node]) {
            if (!vis[adjnode]) {
                vis[adjnode] = true;
                path.push_back(adjnode);

                dfs(adjnode, dest, cost + w, path, adj, vis, minCost, bestPath);

                // backtrack
                path.pop_back();
                vis[adjnode] = false;
            }
        }
    }

public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> adj(n + 1);
        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }

        vector<bool> vis(n + 1, false);
        vector<int> path = {1};
        vector<int> bestPath;
        int minCost = INT_MAX;

        vis[1] = true;
        dfs(1, n, 0, path, adj, vis, minCost, bestPath);

        if (minCost == INT_MAX) return {-1};

        vector<int> res = {minCost};
        res.insert(res.end(), bestPath.begin(), bestPath.end());
        return res;
    }
};
```

### Why Slow

```
Backtracking allows revisiting nodes via different paths
Number of distinct paths grows exponentially in dense graphs:

n nodes, every node connects to every node ahead:
paths = 2^(n-2)

Total = O(2^V × E)
```

### Complexity

| | Value |
|-|-------|
| **Time** | O(2^V × E) — exponential paths |
| **Space** | O(V) — recursion stack depth |

---

## Approach 2 — Dijkstra + Parent Tracking (Optimal)

### Idea

Standard Dijkstra finds shortest distances. Add a `parent[]` array to track which node each shortest path came through. After Dijkstra — trace back from destination to source using `parent[]`.

```
When dist[v] is updated via u → parent[v] = u
At end → trace: n → parent[n] → parent[parent[n]] → ... → 1
Reverse → path from 1 to n
```

### Key Details

```
dist[1] = 0        → source distance initialized
parent[1] = 1      → sentinel: stops path reconstruction at source
stale skip         → if (dis > dist[node]) continue
prepend cost       → result[0] = dist[n], then path nodes
```

### Implementation (C++)

```cpp
class Solution {
  public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
        // build adjacency list — 1 indexed
        vector<vector<pair<int,int>>> adj(n + 1);
        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }

        vector<int> dist(n + 1, 1e9);
        vector<int> parent(n + 1, -1);

        // min heap: {distance, node}
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;

        dist[1] = 0;
        parent[1] = 1;   // sentinel — stops trace at source
        pq.push({0, 1});

        while (!pq.empty()) {
            auto [dis, node] = pq.top(); pq.pop();

            if (dis > dist[node]) continue;   // stale entry — skip

            for (auto& [adjnode, w] : adj[node]) {
                if (dis + w < dist[adjnode]) {
                    dist[adjnode] = dis + w;
                    parent[adjnode] = node;   // track shortest path predecessor
                    pq.push({dist[adjnode], adjnode});
                }
            }
        }

        if (dist[n] == (int)1e9) return {-1};

        // trace path from dest back to src
        vector<int> path;
        int curr = n;
        while (curr != 1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        path.push_back(1);
        reverse(path.begin(), path.end());

        // prepend cost — GFG format: [cost, node1, node2, ...]
        path.insert(path.begin(), dist[n]);
        return path;
    }
};
```

### Dry Run

```
n=5, m=6
edges: 1-2(2), 2-5(5), 2-3(4), 1-4(1), 4-3(3), 3-5(1)

adj:
1→[(2,2),(4,1)]
2→[(1,2),(5,5),(3,4)]
3→[(2,4),(4,3),(5,1)]
4→[(1,1),(3,3)]
5→[(2,5),(3,1)]

dist   = [-, 0, INF, INF, INF, INF]
parent = [-, 1,  -1,  -1,  -1,  -1]
pq: [{0,1}]
```

| Pop | dis | node | relaxations | dist[] | parent[] |
|-----|-----|------|-------------|--------|----------|
| {0,1} | 0 | 1 | 2→2, 4→1 | [0,2,INF,1,INF] | [1,1,-1,-1,-1] |
| {1,4} | 1 | 4 | 3→4 | [0,2,4,1,INF] | [1,1,4,-1,-1] |
| {2,2} | 2 | 2 | 5→7, 3→6>4 skip | [0,2,4,1,7] | [1,1,4,2,-1] |
| {4,3} | 4 | 3 | 5→5<7 ✅ | [0,2,4,1,5] | [1,1,4,2,3] |
| {5,5} | 5 | 5 | no improvement | — | — |
| {7,5} | 7 | 5 | stale → skip | — | — |

```
dist[5] = 5

Path reconstruction:
curr=5 → push 5 → curr=parent[5]=3
curr=3 → push 3 → curr=parent[3]=4
curr=4 → push 4 → curr=parent[4]=1
curr=1 → exit loop → push 1

path = [5,3,4,1] → reverse → [1,4,3,5]
prepend cost → [5, 1, 4, 3, 5] ✅
```

### Path Reconstruction — Why `parent[1] = 1`

```
Without sentinel (parent[1] = -1 or 0):
  trace reaches node 1
  curr = parent[1] = -1 or 0
  loop continues → accesses adj[-1] or adj[0] → wrong/crash

With sentinel (parent[1] = 1):
  while (curr != 1) → exits exactly when source reached
  clean stop ✅
```

### Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O((V+E) log V) | E pushes × O(log V) per pq op |
| **Space** | O(V+E) | adj + dist + parent + pq |

---

## Comparison

| | Brute Force | Dijkstra |
|-|-------------|----------|
| **Time** | O(2^V × E) | O((V+E) log V) |
| **Space** | O(V) | O(V+E) |
| **Path tracking** | Store full path during DFS | Parent array + trace back |
| **Revisits nodes?** | Yes — backtracking | No — finalized on pop |
| **Practical** | TLE for large input | ✅ Accepted |

---

## Common Mistakes

| Mistake | Effect | Fix |
|---------|--------|-----|
| `dist[1]` not initialized to 0 | Source gets wrong distance | `dist[1] = 0` before push |
| `parent[1] = 0` or `-1` | Trace goes past source → invalid node | `parent[1] = 1` as sentinel |
| `push(parent[curr])` in reconstruction | Skips nodes, pushes grandparent | `push(curr)` then `curr = parent[curr]` |
| Missing stale skip | Wrong parent assigned from stale pop | `if (dis > dist[node]) continue` |
| Not prepending cost (GFG) | First element is path node not cost | `path.insert(path.begin(), dist[n])` |

---

## Key Takeaways

- Brute force explores all paths via backtracking — exponential time but simple to implement.
- Dijkstra finalizes each node's distance exactly once — no revisiting → O((V+E) log V).
- Parent array tracks the shortest path predecessor — updated only when a shorter distance is found.
- `parent[src] = src` is the sentinel that cleanly stops path reconstruction at source.
- GFG output format requires cost prepended to path — `result = {cost, node1, node2, ..., nodeN}`.
- Stale skip (`dis > dist[node]`) is critical — prevents wrong parent assignments from outdated queue entries.
