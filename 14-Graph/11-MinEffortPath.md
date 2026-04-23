# Path With Minimum Effort

Find a path from `(0,0)` to `(n-1,m-1)` in a height grid such that the **maximum absolute difference** between consecutive cells on the path is minimized.

> **Effort of a path** = maximum absolute difference between adjacent cells on that path.  
> Find the path with **minimum effort**.

---

## Key Insight

```
This is NOT minimize sum of weights (classic Dijkstra)
This IS minimize MAX weight on path

effort[v] = min over all paths of (max diff on that path)
          = max(effort[u], abs(heights[v] - heights[u]))
```

---

## Approach 1 — Brute Force (DFS + Backtracking)

### Idea

Explore every path from `(0,0)` using DFS. Track the running maximum difference on the current path. When destination reached — record if minimum effort. Backtrack to explore all paths.

```cpp
class Solution {
private:
    int minEffort;
    int drow[4] = {0, 1, 0, -1};
    int dcol[4] = {1, 0, -1, 0};

    void dfs(int r, int c, int maxDiff,
             vector<vector<int>>& heights,
             vector<vector<bool>>& vis) {

        int n = heights.size(), m = heights[0].size();

        if (r == n-1 && c == m-1) {
            minEffort = min(minEffort, maxDiff);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + drow[i];
            int nc = c + dcol[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc]) {
                int diff       = abs(heights[nr][nc] - heights[r][c]);
                int newMaxDiff = max(maxDiff, diff);

                // pruning — skip if already worse than best found
                if (newMaxDiff < minEffort) {
                    vis[nr][nc] = true;
                    dfs(nr, nc, newMaxDiff, heights, vis);
                    vis[nr][nc] = false;   // backtrack
                }
            }
        }
    }

public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        minEffort = INT_MAX;

        vis[0][0] = true;
        dfs(0, 0, 0, heights, vis);

        return minEffort;
    }
};
```

### Complexity

| | Value |
|-|-------|
| **Time** | O(4^(n×m)) — exponential paths |
| **Space** | O(n×m) — vis + recursion stack |

---

## Approach 2 — Dijkstra (Optimal)

### Why Dijkstra

Dijkstra works because:

```
Greedy insight:
  when (r,c) is popped with effort e from min-heap
  → e is the minimum possible effort to reach (r,c)
  → any other path to (r,c) has effort ≥ e
  → effort[r][c] finalized ✅

Same guarantee as standard Dijkstra because:
  all diffs are non-negative (absolute value)
  processing minimum effort first
  → can never find better path later
```

### Standard Dijkstra vs This Problem

| | Standard Dijkstra | Minimum Effort |
|-|------------------|----------------|
| Combination | `dist[u] + weight` | `max(effort[u], diff)` |
| Minimizes | Sum of weights | Max weight on path |
| Heap key | distance | effort |
| Relaxation | `dist[u]+w < dist[v]` | `max(e,diff) < effort[v]` |

### Implementation (C++)

```cpp
class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();

        // min heap: {effort, {row, col}}
        priority_queue<pair<int, pair<int,int>>,
                       vector<pair<int, pair<int,int>>>,
                       greater<pair<int, pair<int,int>>>> pq;

        pq.push({0, {0, 0}});

        vector<vector<int>> effort(n, vector<int>(m, 1e9));
        effort[0][0] = 0;   // source effort = 0

        int drow[] = {0, 1, 0, -1};
        int dcol[] = {1, 0, -1, 0};

        while (!pq.empty()) {
            int e   = pq.top().first;
            int row = pq.top().second.first;
            int col = pq.top().second.second;
            pq.pop();

            // destination popped → effort finalized
            if (row == n-1 && col == m-1) return e;

            // stale entry skip
            if (e > effort[row][col]) continue;

            for (int i = 0; i < 4; i++) {
                int nr = row + drow[i];
                int nc = col + dcol[i];

                // bounds check BEFORE array access
                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    int diff    = abs(heights[nr][nc] - heights[row][col]);
                    int newDiff = max(e, diff);   // ← key line: max not sum

                    if (newDiff < effort[nr][nc]) {
                        effort[nr][nc] = newDiff;
                        pq.push({newDiff, {nr, nc}});
                    }
                }
            }
        }

        return effort[n-1][m-1];
    }
};
```

### Dry Run

```
heights = [[1, 2, 2],
           [3, 8, 2],
           [5, 3, 5]]

source=(0,0), dest=(2,2)
effort[][] = INF, effort[0][0]=0
pq: [{0,{0,0}}]
```

| Pop | e | r,c | Neighbors | newEffort | effort[][] update |
|-----|---|-----|-----------|-----------|-------------------|
| {0,0,0} | 0 | 0,0 | (0,1):max(0,1)=1, (1,0):max(0,2)=2 | 1,2 | [0][1]=1,[1][0]=2 |
| {1,0,1} | 1 | 0,1 | (0,2):max(1,0)=1, (1,1):max(1,6)=6 | 1,6 | [0][2]=1,[1][1]=6 |
| {1,0,2} | 1 | 0,2 | (1,2):max(1,0)=1 | 1 | [1][2]=1 |
| {1,1,2} | 1 | 1,2 | (2,2):max(1,3)=3 | 3 | [2][2]=3 |
| {2,1,0} | 2 | 1,0 | (1,1):max(2,5)=5<6✅, (2,0):max(2,2)=2 | 5,2 | [1][1]=5,[2][0]=2 |
| {2,2,0} | 2 | 2,0 | (2,1):max(2,2)=2 | 2 | [2][1]=2 |
| {2,2,1} | 2 | 2,1 | (2,2):max(2,2)=2<3✅ | 2 | [2][2]=2 |
| {2,2,2} | 2 | 2,2 | **DEST** → return 2 | | |

**Answer: 2 ✅**

```
Final effort[][]:
INF  1   1
  2  5   1
  2  2   2
           ↑ answer
```

**Optimal path: (0,0)→(1,0)→(2,0)→(2,1)→(2,2)**
```
heights:  1 → 3 → 5 → 3 → 5
diffs:      2   2   2   2
max diff  = 2 ✅
```

### Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O(n×m × log(n×m)) | Each cell pushed at most once per update, heap op = O(log nm) |
| **Space** | O(n×m) | effort array + priority queue |

---

## Comparison

| | Brute Force | Dijkstra |
|-|-------------|----------|
| **Time** | O(4^(nm)) | O(nm log nm) |
| **Space** | O(nm) | O(nm) |
| **Explores all paths?** | Yes — must | No — greedy prunes |
| **Revisits cells?** | Yes — backtracking | No — finalized on pop |
| **Practical** | TLE for large input | ✅ Accepted |

---

## Common Mistakes

| Mistake | Effect | Fix |
|---------|--------|-----|
| `heights[nr][nc]` before bounds check | Out of bounds crash / UB | Bounds check first, array access inside |
| `newDiff = e + diff` (sum instead of max) | Wrong — minimizes sum not max | `newDiff = max(e, diff)` |
| `effort[0][0]` not initialized to 0 | Stale skip may cause wrong behavior | `effort[0][0] = 0` after declaration |
| Missing stale skip | Wrong effort assigned from outdated pop | `if (e > effort[row][col]) continue` |
| Using BFS (uniform steps) | Wrong — edges have different effort costs | Must use Dijkstra (weighted edges) |

---

## Key Takeaways

- Effort = max diff on path — minimize this max using Dijkstra's greedy ordering.
- The combination function changes from `+` (standard Dijkstra) to `max` — everything else is identical.
- Bounds check must come **before** array access — never compute `heights[nr][nc]` before verifying `nr`, `nc` are valid.
- Early exit when destination popped — same as standard Dijkstra, effort is finalized at that point.
- BFS doesn't work here — edges have different effort costs, so uniform exploration gives wrong answer.
