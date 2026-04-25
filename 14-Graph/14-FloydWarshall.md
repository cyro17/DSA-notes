# Floyd-Warshall Algorithm

Compute **shortest paths between ALL pairs of nodes** in a weighted graph. Handles negative edges. Detects negative cycles.

> **All-Pairs Shortest Path (APSP)** — unlike Dijkstra/Bellman-Ford which solve single-source shortest path.

---

## When to Use

```
Need shortest distance between every pair of nodes  → Floyd-Warshall ✅
Graph has negative edges (no negative cycles)        → Floyd-Warshall ✅
n is small (≤ 500)                                  → Floyd-Warshall ✅
Need single-source shortest path only               → Dijkstra / Bellman-Ford
n is large                                          → Dijkstra per node (faster)
```

---

## Core Idea

> For every pair `(i, j)` — check if going through an **intermediate node `k`** gives a shorter path than the direct path.

```
dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

"Can I get from i to j cheaper by going through k?"
```

Try every possible intermediate node `k` from `0` to `n-1`.
After trying all k values — `dist[i][j]` holds the true shortest path.

---

## Why Three Nested Loops?

```
Outer loop k:   intermediate node being considered
Middle loop i:  source node
Inner loop j:   destination node

For each k → update ALL pairs (i,j) that might benefit from going through k
After k=0: shortest paths using node 0 as intermediate are optimal
After k=1: shortest paths using nodes 0,1 as intermediates are optimal
...
After k=n-1: ALL shortest paths optimal ✅
```

---

## Initialization

```
dist[i][i] = 0          → distance to self = 0
dist[i][j] = weight     → direct edge weight if edge exists
dist[i][j] = 1e8        → no direct edge (represents infinity)
```

---

## Implementation

### C++

```cpp
class Solution {
  public:
    void floydWarshall(vector<vector<int>>& dist) {
        int n = dist.size();

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    // guard: both paths must exist
                    if (dist[i][k] != 1e8 && dist[k][j] != 1e8)
                        dist[i][j] = min(dist[i][j],
                                         dist[i][k] + dist[k][j]);
                }
            }
        }
    }
};
```

### Java

```java
void floydWarshall(int[][] dist, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != (int)1e8 && dist[k][j] != (int)1e8)
                    dist[i][j] = Math.min(dist[i][j],
                                          dist[i][k] + dist[k][j]);
            }
        }
    }
}
```

---

## Dry Run

```
4 nodes, edges:
0→1(3), 0→3(7), 1→0(8), 1→2(2), 2→0(5), 2→3(1), 3→0(2)

Initial dist matrix (INF = 1e8):
      0    1    2    3
0  [  0,   3, INF,   7]
1  [  8,   0,   2, INF]
2  [  5, INF,   0,   1]
3  [  2, INF, INF,   0]
```

**k=0 (route through node 0):**

```
Check all pairs — can going through 0 help?

i=1,j=3: dist[1][0]+dist[0][3] = 8+7 = 15 < INF → dist[1][3]=15
i=2,j=1: dist[2][0]+dist[0][1] = 5+3 = 8  < INF → dist[2][1]=8
i=2,j=3: dist[2][0]+dist[0][3] = 5+7 = 12 > 1   → skip
i=3,j=1: dist[3][0]+dist[0][1] = 2+3 = 5  < INF → dist[3][1]=5
i=3,j=2: dist[3][0]+dist[0][2] = 2+INF    → skip (guard)
i=3,j=3: dist[3][0]+dist[0][3] = 2+7 = 9  > 0   → skip

After k=0:
      0    1    2    3
0  [  0,   3, INF,   7]
1  [  8,   0,   2,  15]
2  [  5,   8,   0,   1]
3  [  2,   5, INF,   0]
```

**k=1 (route through node 1):**

```
i=0,j=2: dist[0][1]+dist[1][2] = 3+2=5   < INF → dist[0][2]=5
i=0,j=3: dist[0][1]+dist[1][3] = 3+15=18 > 7   → skip
i=2,j=0: dist[2][1]+dist[1][0] = 8+8=16  > 5   → skip
i=3,j=2: dist[3][1]+dist[1][2] = 5+2=7   < INF → dist[3][2]=7

After k=1:
      0    1    2    3
0  [  0,   3,   5,   7]
1  [  8,   0,   2,  15]
2  [  5,   8,   0,   1]
3  [  2,   5,   7,   0]
```

**k=2 (route through node 2):**

```
i=0,j=3: dist[0][2]+dist[2][3] = 5+1=6   < 7  → dist[0][3]=6
i=1,j=0: dist[1][2]+dist[2][0] = 2+5=7   < 8  → dist[1][0]=7
i=1,j=3: dist[1][2]+dist[2][3] = 2+1=3   < 15 → dist[1][3]=3
i=3,j=0: dist[3][2]+dist[2][0] = 7+5=12  > 2  → skip

After k=2:
      0    1    2    3
0  [  0,   3,   5,   6]
1  [  7,   0,   2,   3]
2  [  5,   8,   0,   1]
3  [  2,   5,   7,   0]
```

**k=3 (route through node 3):**

```
i=0,j=0: dist[0][3]+dist[3][0] = 6+2=8   > 0  → skip
i=1,j=0: dist[1][3]+dist[3][0] = 3+2=5   < 7  → dist[1][0]=5
i=2,j=0: dist[2][3]+dist[3][0] = 1+2=3   < 5  → dist[2][0]=3
i=2,j=1: dist[2][3]+dist[3][1] = 1+5=6   < 8  → dist[2][1]=6

Final dist matrix:
      0    1    2    3
0  [  0,   3,   5,   6]
1  [  5,   0,   2,   3]
2  [  3,   6,   0,   1]
3  [  2,   5,   7,   0] ✅
```

---

## Why the Guard `dist[i][k] != 1e8` Is Critical

Without guard — unreachable nodes with negative edges corrupt the matrix:

```
dist[i][k] = 1e8  (no path i→k)
dist[k][j] = -50  (negative edge)

dist[i][k] + dist[k][j] = 1e8 - 50 = 99999950 < dist[i][j]=1e8
→ dist[i][j] = 99999950  ← WRONG — path i→k→j doesn't exist!
```

With guard:
```
dist[i][k] == 1e8 → skip
No phantom path created ✅
```

---

## Why `1e8` Not `INT_MAX`

```
INT_MAX + any_value → integer overflow → becomes NEGATIVE
negative < everything → wrong min always taken → catastrophic

INT_MAX = 2,147,483,647
INT_MAX + 1 = -2,147,483,648  ← overflow

1e8 is safe:
  1e8 + 1e8 = 2e8 < INT_MAX → no overflow ✅
  large enough for typical constraints ✅
```

---

## Negative Cycle Detection

After running Floyd-Warshall — check the **diagonal**:

```cpp
for (int i = 0; i < n; i++)
    if (dist[i][i] < 0)
        // negative cycle exists involving node i
```

```
Why diagonal?
  dist[i][i] = shortest path from i back to i = cycle
  if dist[i][i] < 0 → negative cycle exists
  (algorithm finds shorter path back to same node)

Without negative cycle:
  dist[i][i] = 0 always (no cycle cheaper than staying put)
```

---

## Floyd-Warshall vs Other Algorithms

| | Floyd-Warshall | Dijkstra × V | Bellman-Ford × V |
|-|---------------|--------------|-----------------|
| **Time** | O(V³) | O(V²logV + VE) | O(V²E) |
| **Space** | O(V²) | O(V+E) per run | O(V) per run |
| **Negative edges** | ✅ Yes | ❌ No | ✅ Yes |
| **Negative cycle detection** | ✅ Diagonal check | ❌ | ✅ V-th pass |
| **All pairs** | ✅ Single pass | ✅ V runs needed | ✅ V runs needed |
| **Implementation** | ✅ Simplest | Moderate | Moderate |
| **Best for** | Dense graphs, small n | Sparse, non-negative | Negative weights |

---

## Applications

| Problem | How Floyd-Warshall Helps |
|---------|--------------------------|
| Find city with min neighbors in threshold | All-pairs dist → count per city |
| Transitive closure | `dist[i][j] != INF` → reachable |
| Detect negative cycles | `dist[i][i] < 0` |
| Network routing | All-pairs shortest path |
| Arbitrage detection | Negative cycle in log-weight graph |

---

## Common Mistakes

| Mistake | Effect | Fix |
|---------|--------|-----|
| `j` not incremented in inner loop | Infinite loop | `j++` |
| Using `INT_MAX` as infinity | Overflow → wrong distances | Use `1e8` |
| Missing `dist[i][k] != 1e8` guard | Phantom paths through unreachable nodes | Guard both `dist[i][k]` and `dist[k][j]` |
| Wrong loop order (i,j,k instead of k,i,j) | Incorrect results — k must be outermost | `k` outermost always |
| Not initializing diagonal to 0 | `dist[i][i]` might be wrong | `dist[i][i] = 0` always |

---

## Key Takeaways

- Floyd-Warshall = try every node as an intermediate, update all pairs. Three nested loops, outermost is `k`.
- **`k` must be the outermost loop** — when processing pair `(i,j)` with intermediate `k`, we need all `dist[i][k]` and `dist[k][j]` values already optimal for intermediates `0..k-1`.
- Guard `dist[i][k] != 1e8` prevents phantom paths — unreachable nodes with negative edges would otherwise corrupt the matrix.
- Use `1e8` not `INT_MAX` — overflow-safe representation of infinity.
- Negative cycle detection is free — check diagonal after algorithm, any `dist[i][i] < 0` means negative cycle.
- Perfect for small dense graphs (n ≤ 500) needing all-pairs distances — use Dijkstra per node for larger sparse graphs.
