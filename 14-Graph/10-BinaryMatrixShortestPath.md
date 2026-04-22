# Shortest Path in Binary Maze

Find the shortest path from `source` to `destination` in a binary grid where `1` = passable and `0` = blocked. Move in 4 directions (up, down, left, right). Return minimum steps or `-1` if unreachable.

---

## Key Observation

```
Every move costs exactly 1 step — uniform edge weights.
Shortest path in steps = fewest cells visited.
BFS explores level by level → first reach = shortest path ✅
```

---

## Approach 1 — Brute Force (DFS + Backtracking)

### Idea

Explore every possible path from source using DFS with backtracking. Record steps when destination is reached. After full exploration — return minimum.

```cpp
class Solution {
private:
    int minSteps;
    int drow[4] = {0, 1, 0, -1};
    int dcol[4] = {1, 0, -1, 0};

    void dfs(int r, int c, int steps,
             vector<vector<int>>& grid,
             vector<vector<bool>>& vis,
             pair<int,int>& dest) {

        if (r == dest.first && c == dest.second) {
            minSteps = min(minSteps, steps);
            return;
        }

        int n = grid.size(), m = grid[0].size();
        for (int i = 0; i < 4; i++) {
            int nr = r + drow[i];
            int nc = c + dcol[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m
                && !vis[nr][nc] && grid[nr][nc] == 1) {
                vis[nr][nc] = true;
                dfs(nr, nc, steps + 1, grid, vis, dest);
                vis[nr][nc] = false;   // backtrack
            }
        }
    }

public:
    int shortestPath(vector<vector<int>>& grid,
                     pair<int,int> source, pair<int,int> dest) {
        int n = grid.size(), m = grid[0].size();
        if (grid[source.first][source.second] == 0 ||
            grid[dest.first][dest.second] == 0) return -1;

        vector<vector<bool>> vis(n, vector<bool>(m, false));
        minSteps = INT_MAX;
        vis[source.first][source.second] = true;
        dfs(source.first, source.second, 0, grid, vis, dest);
        return minSteps == INT_MAX ? -1 : minSteps;
    }
};
```

### Why Slow

```
Backtracking allows revisiting cells via different paths.
For an n×m grid with all 1s:
  4 choices per cell × n×m cells = O(4^(nm)) paths

Must explore everything to confirm minimum → TLE
```

### Complexity

| | Value |
|-|-------|
| **Time** | O(4^(n×m)) — exponential |
| **Space** | O(n×m) — recursion stack |

---

## Approach 2 — BFS (Optimal)

### Why BFS Works Perfectly Here

BFS explores **level by level** — all cells at distance 1 first, then distance 2, then distance 3...

```
The FIRST time BFS reaches destination = guaranteed shortest path.
Stop immediately — no need to explore further.
```

```
Think of BFS as ripples in water:
  source = stone dropped in water
  ripples spread uniformly in all directions
  first ripple to reach dest = shortest path ✅
```

### The Critical Rule — Mark Visited on PUSH Not POP

```
Mark on pop (WRONG):
  cell (1,1) pushed 4 times by 4 different neighbors
  all 4 sit in queue, all get processed
  each adds (1,1)'s neighbors again → exponential blowup → TLE

Mark on push (CORRECT):
  first neighbor to reach (1,1) marks it immediately
  other 3 neighbors see vis[1][1]=true → skip
  (1,1) in queue exactly once → O(nm)
```

```cpp
vis[nr][nc] = true;        // mark BEFORE pushing
q.push({dist+1, {nr, nc}});
```

### Implementation (C++)

```cpp
class Solution {
  public:
    int shortestPath(vector<vector<int>>& grid,
                     pair<int,int> source,
                     pair<int,int> destination) {

        int n = grid.size(), m = grid[0].size();

        // edge cases
        if (grid[source.first][source.second] == 0 ||
            grid[destination.first][destination.second] == 0)
            return -1;

        if (source == destination) return 0;

        int drow[] = {0, 1, 0, -1};
        int dcol[] = {1, 0, -1, 0};

        vector<vector<bool>> vis(n, vector<bool>(m, false));

        // queue: {steps, {row, col}}
        queue<pair<int, pair<int,int>>> q;
        q.push({0, {source.first, source.second}});
        vis[source.first][source.second] = true;

        while (!q.empty()) {
            int dist = q.front().first;
            int r    = q.front().second.first;
            int c    = q.front().second.second;
            q.pop();

            // reached destination → guaranteed shortest
            if (r == destination.first && c == destination.second)
                return dist;

            for (int i = 0; i < 4; i++) {
                int nr = r + drow[i];
                int nc = c + dcol[i];

                if (nr >= 0 && nr < n &&
                    nc >= 0 && nc < m &&
                    !vis[nr][nc] &&         // visited check
                    grid[nr][nc] == 1) {
                    vis[nr][nc] = true;     // mark on push
                    q.push({dist + 1, {nr, nc}});
                }
            }
        }

        return -1;   // destination unreachable
    }
};
```

### Dry Run

```
grid = [[1,1,1],
        [1,0,1],
        [1,1,1]]

source={0,0}, dest={2,2}
```

| Pop | r,c | steps | Neighbors added | vis marked |
|-----|-----|-------|-----------------|------------|
| init | — | — | — | [0][0] |
| {0,0} | 0,0 | 0 | (0,1),(1,0) | [0][1],[1][0] |
| {0,1} | 0,1 | 1 | (0,2) blocked(0,0)✓ | [0][2] |
| {1,0} | 1,0 | 1 | (2,0) | [2][0] |
| {0,2} | 0,2 | 2 | (1,2) | [1][2] |
| {2,0} | 2,0 | 2 | (2,1) | [2][1] |
| {1,2} | 1,2 | 3 | (2,2)=dest! | return 4 |

**Answer: 4 ✅**

### Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O(n×m) | Each cell visited exactly once |
| **Space** | O(n×m) | vis array + queue holds at most n×m cells |

---

## Why Not Dijkstra With Priority Queue?

### It Works — But Is Overkill

Dijkstra is designed for **weighted graphs** where edge costs differ. Here every move costs exactly `1` — all edges have **identical weight**.

```
Dijkstra's min-heap advantage:
  always process cheapest node first
  necessary when weights differ

This grid:
  every edge weight = 1
  every level of BFS has same cost
  min-heap always pops same distance as BFS queue front
  → heap provides ZERO benefit
```

### The Log Overhead Kills Performance

```
BFS queue:   push/pop = O(1)
Dijkstra pq: push/pop = O(log(n×m))

For a 1000×1000 grid:
  cells = 10^6
  BFS:      10^6 operations × O(1)      = 10^6
  Dijkstra: 10^6 operations × O(log10^6) = 10^6 × 20 = 2×10^7

20x slower for identical results — purely wasted log factor
```

### Dijkstra Code on Grid (Correct But Inefficient)

```cpp
// works but unnecessary O(nm log nm)
priority_queue<tuple<int,int,int>,
               vector<tuple<int,int,int>>,
               greater<>> pq;

vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
dist[source.first][source.second] = 0;
pq.push({0, source.first, source.second});

while (!pq.empty()) {
    auto [d, r, c] = pq.top(); pq.pop();

    if (r == dest.first && c == dest.second) return d;
    if (d > dist[r][c]) continue;   // stale skip — needed for pq

    for (int i = 0; i < 4; i++) {
        int nr = r + drow[i];
        int nc = c + dcol[i];
        if (valid bounds && grid[nr][nc] == 1 && d+1 < dist[nr][nc]) {
            dist[nr][nc] = d + 1;
            pq.push({d+1, nr, nc});
        }
    }
}
```

Note: Dijkstra also needs a stale entry skip (`d > dist[r][c]`) — extra complexity BFS avoids entirely.

### Comparison

| | BFS | Dijkstra |
|-|-----|----------|
| **Time** | O(n×m) | O(n×m × log(n×m)) |
| **Space** | O(n×m) | O(n×m) |
| **Queue op cost** | O(1) push/pop | O(log nm) push/pop |
| **Stale entries** | ❌ None — vis prevents | ✅ Exist — need skip check |
| **Works here?** | ✅ Optimal | ✅ Correct but slower |
| **Verdict** | ✅ Right tool | ❌ Overkill |

### When to Use Each

```
All edge weights equal (= 1)    → BFS
Edge weights differ             → Dijkstra
Grid with uniform move cost     → BFS always
```

---

## Topological Sort — Not Applicable

```
Topo sort requires DAG (Directed Acyclic Graph)

This grid is undirected:
  (0,0) ↔ (0,1) ← bidirectional = cycle

Undirected graphs have cycles by nature → no valid topo order ❌
```

---

## Algorithm Decision for Shortest Path

| Graph Type | Algorithm | Time |
|------------|-----------|------|
| Unweighted / uniform weight | **BFS** | O(V+E) |
| Weighted, non-negative | **Dijkstra** | O((V+E) log V) |
| Weighted, negative edges | **Bellman-Ford** | O(V×E) |
| DAG, any weights | **Topo Sort** | O(V+E) |

---

## Common Mistakes

| Mistake | Effect | Fix |
|---------|--------|-----|
| No vis array | Same cell pushed multiple times → TLE | Add `vis[][]`, mark on push |
| Mark vis on pop not push | Cell enters queue 4 times → wasted work | Mark vis BEFORE `q.push()` |
| Using Dijkstra pq | O(log nm) overhead per op | Use plain `queue` — O(1) |
| Not checking source/dest == 0 | Wrong answer for blocked cells | Check before BFS |
| Forgetting `source == dest` case | Returns -1 instead of 0 | Check before BFS |

---

## Key Takeaways

- BFS is the natural fit for shortest path in unweighted grids — explores level by level, first reach = shortest path.
- Always mark visited **when pushing** to queue — not when popping. Marking on pop causes exponential queue blowup → TLE.
- Dijkstra works but adds `O(log nm)` overhead per operation for zero benefit — BFS is strictly better when all edge weights are equal.
- Topo sort is invalid — undirected grids have cycles by nature.
- The visited array is the single most important addition — without it BFS becomes O(4^(nm)).
