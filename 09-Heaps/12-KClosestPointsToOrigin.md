# K Closest Points to Origin (LeetCode 973)

Given an array of points on the X-Y plane and an integer `k`, return the `k` closest points to the origin `(0, 0)`.

> Distance formula: `√(x² + y²)` — but since `√` is monotonic, we can compare `x² + y²` directly and skip the square root entirely. This avoids floating point and is faster.

**Example**
```
points = [[1,3],[-2,2],[5,8],[0,1]],  k = 2

distances → [1,3]=10  [-2,2]=8  [5,8]=89  [0,1]=1

2 closest → [[-2,2],[0,1]]
```

---

## Approach 1: Brute Force — O(N log N)

**Idea:** Calculate distance for every point, sort all of them by distance, return the first `k`.

```java
public int[][] kClosest(int[][] points, int k) {
    Arrays.sort(points, (a, b) -> {
        int distA = a[0]*a[0] + a[1]*a[1];
        int distB = b[0]*b[0] + b[1]*b[1];
        return distA - distB;                 // sort ascending by distance
    });

    return Arrays.copyOfRange(points, 0, k);  // first k are the closest
}
```

**Why it's suboptimal:** You sort all N points just to use `k` of them. If `k` is small, most of the sort is wasted work.

### Complexity

| | |
|---|---|
| Time | O(N log N) — sorting all N points |
| Space | O(1) — sort in place |

---

## Approach 2: Max Heap of Size k — O(N log k)

**Idea:** Maintain a max-heap of size `k` where the farthest point always sits at the top. For every new point:
- Push it into the heap
- If heap size exceeds `k`, evict the farthest point (the top)

At the end the heap contains exactly the `k` closest points.

**Why max-heap and not min-heap?**

```
min-heap → smallest distance at top
         → you'd need to push ALL N points first, then poll k times
         → O(N log N) space and time, same as brute force

max-heap of size k → farthest point always at top, ready to be evicted
                   → heap never grows beyond k
                   → each push/evict is O(log k) instead of O(log N)
```

### Dry Run

```
points = [[1,3],[-2,2],[5,8],[0,1]],  k = 2

push [1,3]   → pq={[1,3]}              dist=10   size 1 ≤ k
push [-2,2]  → pq={[1,3],[-2,2]}       dist=8    size 2 = k
push [5,8]   → pq={[5,8],[1,3],[-2,2]} dist=89   size 3 > k
               evict max [5,8] (dist=89)
               pq={[1,3],[-2,2]}
push [0,1]   → pq={[1,3],[-2,2],[0,1]} dist=1    size 3 > k
               evict max [1,3] (dist=10)
               pq={[-2,2],[0,1]}

result = [[-2,2],[0,1]] ✓
```

### Java

```java
public int[][] kClosest(int[][] points, int k) {
    // max-heap — farthest point sits at top, ready to be evicted
    PriorityQueue<int[]> pq = new PriorityQueue<>(
        (a, b) -> (b[0]*b[0] + b[1]*b[1]) - (a[0]*a[0] + a[1]*a[1])
    );

    for (int[] point : points) {
        pq.offer(point);
        if (pq.size() > k)
            pq.poll();              // evict farthest point
    }

    int[][] res = new int[k][2];
    for (int i = 0; i < k; i++)
        res[i] = pq.poll();

    return res;
}
```

### Complexity

| | |
|---|---|
| Time | O(N log k) — each of N points is pushed once, heap ops cost O(log k) |
| Space | O(k) — heap never grows beyond k |

---

## Complexity Comparison

| Approach | Time | Space |
|---|---|---|
| Brute Force (sort all) | O(N log N) | O(1) |
| Max Heap size k | **O(N log k)** | O(k) |

Since `k ≤ N`, log k ≤ log N — the heap is strictly better. The gap widens significantly when `k` is small relative to `N` (e.g. find the 5 closest points out of 1 million).
