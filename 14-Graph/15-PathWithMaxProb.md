# 1514. Path with Maximum Probability

**Difficulty:** Medium
**Topics:** Graph, Shortest Path, Dijkstra, DFS, Backtracking

---

## Problem Statement

You are given an **undirected weighted graph** of `n` nodes (0-indexed), represented by an edge list where `edges[i] = [a, b]` is an undirected edge connecting nodes `a` and `b` with a success probability of `succProb[i]`.

Given two nodes `start_node` and `end_node`, find the path with the **maximum probability** of success and return it.

If there is no path, return `0`. Answer is accepted if it differs from the correct answer by at most `1e-5`.

**Constraints:**
- `2 <= n <= 10^4`
- `0 <= edges.length <= 2 * 10^4`
- `0 <= succProb[i] <= 1`
- At most one edge between every two nodes

---

## Examples

```
Input:  n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5, 0.5, 0.2], start = 0, end = 2
Output: 0.25000
Reason: Path 0→1→2 = 0.5 * 0.5 = 0.25 > direct 0→2 = 0.2
```

```
Input:  n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
Output: 0.00000
Reason: No path exists from 0 to 2
```

---

## Approach 1 — Brute Force DFS + Backtracking

### Intuition

Explore **every possible simple path** from `start_node` to `end_node`.
At each step, multiply the current probability by the edge weight.
Track the global maximum probability across all paths that reach the destination.

Use a `visited` array to avoid revisiting nodes in the current path (prevents cycles in the undirected graph). Backtrack after each recursive call to allow the node to be part of other paths.

### Dry Run

```
Graph: 0 --0.5-- 1 --0.5-- 2
       |                   |
       +--------0.2--------+

start = 0, end = 2

DFS from 0 (prob = 1.0):
  → visit 1 (prob = 1.0 * 0.5 = 0.5):
      → visit 2 (prob = 0.5 * 0.5 = 0.25) ✓ res = 0.25
      ← backtrack 2
  ← backtrack 1
  → visit 2 (prob = 1.0 * 0.2 = 0.2) → 0.2 < 0.25, res unchanged
  ← backtrack 2

Final: res = 0.25
```

### Code (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    void dfs(int node, int end_node, double curr_prob,
             vector<bool> &vis,
             vector<vector<pair<int, double>>> &adj,
             double &res) {

        if (node == end_node) {
            res = max(res, curr_prob);
            return;
        }

        vis[node] = true;

        for (auto &[adjnode, w] : adj[node]) {
            if (!vis[adjnode]) {
                dfs(adjnode, end_node, curr_prob * w, vis, adj, res);
            }
        }

        vis[node] = false; // backtrack
    }

public:
    double maxProbability(int n, vector<vector<int>>& edges,
                          vector<double>& succProb,
                          int start_node, int end_node) {

        double res = 0.0;
        vector<vector<pair<int, double>>> adj(n);

        for (int i = 0; i < (int)edges.size(); ++i) {
            int u = edges[i][0], v = edges[i][1];
            double w = succProb[i];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w}); // undirected
        }

        vector<bool> vis(n, false);
        dfs(start_node, end_node, 1.0, vis, adj, res);
        return res;
    }
};
```

### Complexity Analysis

| | Complexity |
|---|---|
| **Time** | O(V!) worst case (complete graph — V-1 choices at node 1, V-2 at node 2, ...) |
| **Time** | O(2^V) for sparse/tree-like graphs |
| **Space** | O(V) — recursion stack + visited array |

> **Why TLE?** No memoization — overlapping subpaths are recomputed from scratch every time. DFS has no memory of "best probability to reach node X already known."

---

## Approach 2 — Modified Dijkstra (Optimal)

### Intuition

This is a **single-source shortest path** problem with a twist:
- Standard Dijkstra **minimizes** cost (addition of weights)
- Here we **maximize** probability (multiplication of weights)

Two key adaptations:
1. Use a **max-heap** instead of min-heap
2. Relaxation condition: update if `p * w > prob[neighbor]` (instead of `dist[u] + w < dist[v]`)

**Greedy correctness:** When a node is popped from the max-heap, the probability stored for it is already the global maximum — no future path can improve it (all probabilities ≤ 1, so multiplying more edges can only decrease or maintain, never increase past the current best).

### Dry Run

```
Graph: 0 --0.5-- 1 --0.5-- 2
       |                   |
       +--------0.2--------+

prob[] = [1.0, 0.0, 0.0]
pq = [(1.0, 0)]

Step 1: pop (1.0, 0)
  → neighbor 1: 1.0 * 0.5 = 0.5 > prob[1]=0.0 → update, push (0.5, 1)
  → neighbor 2: 1.0 * 0.2 = 0.2 > prob[2]=0.0 → update, push (0.2, 2)
  prob[] = [1.0, 0.5, 0.2]

Step 2: pop (0.5, 1)   ← max-heap picks highest prob
  → neighbor 0: 0.5 * 0.5 = 0.25 > prob[0]=1.0? No
  → neighbor 2: 0.5 * 0.5 = 0.25 > prob[2]=0.2? Yes → update, push (0.25, 2)
  prob[] = [1.0, 0.5, 0.25]

Step 3: pop (0.25, 2)
  → neighbor 1: 0.25 * 0.5 = 0.125 > prob[1]=0.5? No
  → neighbor 0: 0.25 * 0.2 = 0.05  > prob[0]=1.0? No

Step 4: pop (0.2, 2)  ← stale entry, prob[2] already 0.25, skip relaxations

pq empty. Return prob[end_node=2] = 0.25 ✓
```

### Code (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges,
                          vector<double>& succProb,
                          int start_node, int end_node) {

        // Build adjacency list
        vector<vector<pair<int, double>>> adj(n);
        for (int i = 0; i < (int)edges.size(); ++i) {
            int u = edges[i][0], v = edges[i][1];
            double w = succProb[i];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w}); // undirected
        }

        // Max-heap: {probability, node}
        priority_queue<pair<double, int>> pq;
        pq.push({1.0, start_node});

        vector<double> prob(n, 0.0);
        prob[start_node] = 1.0;

        while (!pq.empty()) {
            auto [p, node] = pq.top();
            pq.pop();

            for (auto &[adjnode, w] : adj[node]) {
                if (p * w > prob[adjnode]) {
                    prob[adjnode] = p * w;
                    pq.push({prob[adjnode], adjnode});
                }
            }
        }

        return prob[end_node];
    }
};
```

### Complexity Analysis

| | Complexity |
|---|---|
| **Time** | O((V + E) log V) |
| **Space** | O(V + E) — adj list + prob array + heap |

> Each node/edge is processed a bounded number of times. The heap has at most E entries (one per relaxation). Each push/pop is O(log E) = O(log V) since E ≤ V².

---

## Comparison

| | Brute Force DFS | Dijkstra |
|---|---|---|
| Time (dense) | O(V!) | O((V+E) log V) |
| Time (sparse) | O(2^V) | O((V+E) log V) |
| Space | O(V) | O(V + E) |
| Revisits nodes? | Yes (backtracking) | No (greedy) |
| Handles cycles? | Via `visited[]` | Via stale-entry skip |
| Interview verdict | TLE on large graphs | ✅ Optimal |

---

## Key Insight

> Standard Dijkstra: `dist[u] + w < dist[v]` → minimize sum
> This problem: `prob[u] * w > prob[v]` → maximize product
>
> The structure is identical — just flip the heap and the relaxation operator.

---

## Related Problems

| Problem | Connection |
|---|---|
| [743. Network Delay Time](https://leetcode.com/problems/network-delay-time/) | Classic Dijkstra (minimize sum) |
| [787. Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/) | Dijkstra with constraint (Bellman-Ford variant) |
| [1631. Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/) | Dijkstra on grid (minimize max edge) |
