# Unbounded Knapsack

> **GFG:** [Knapsack with Duplicate Items](https://www.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1)  
> **Pattern:** Unbounded Knapsack  
> **Striver DP:** #23

---

## Problem

Given `n` items with weights `wt[]` and values `val[]`, and a knapsack of capacity `W`. Each item can be picked **unlimited times**. Maximize total value without exceeding capacity.

---

## Gotchas

1. **Value on not-pick:** don't add `val[index]` when skipping an item. Pick adds value, not-pick adds 0.
2. **Weight accumulation typo:** `curr + curr + wt[i]` doubles the current weight — easy to miss, hard to debug.
3. **DP table dimension:** second dimension = `capacity + 1`, not `wt_total + 1`. `curr` never exceeds capacity.
4. **0/1 vs Unbounded:** on pick, stay at `index` (unbounded) vs advance to `index + 1` (0/1). One character difference, completely different problem.

---

## M-1: Pure Recursion (Brute Force)

Two choices at each index: pick (stay at same index, add weight) or skip (move to next index).

> TC = exponential — each item can be picked up to capacity/wt[i] times  
> SC = O(n + capacity) — stack depth

```cpp
class Solution {
    int f(int index, int curr, vector<int> &val, vector<int> &wt, int k) {
        int n = wt.size();
        if (index >= n) return 0;

        int p = 0;
        if (curr + wt[index] <= k)
            p = val[index] + f(index, curr + wt[index], val, wt, k);
        int np = f(index + 1, curr, val, wt, k);
        return max(p, np);
    }

public:
    int knapSack(vector<int> &val, vector<int> &wt, int capacity) {
        return f(0, 0, val, wt, capacity);
    }
};
```

---

## M-2: Memoization (Top-Down DP)

State: `dp[index][curr]` = max value using items `[index..n-1]` with `curr` weight already used.

> TC = O(n × capacity) — n × (capacity+1) states, O(1) each  
> SC = O(n × capacity) table + O(n + capacity) stack

```cpp
class Solution {
    int f(int index, int curr, vector<int> &val, vector<int> &wt, int k,
          vector<vector<int>> &dp) {
        int n = wt.size();
        if (index >= n) return 0;

        if (dp[index][curr] != -1) return dp[index][curr];

        int p = 0;
        if (curr + wt[index] <= k)
            p = val[index] + f(index, curr + wt[index], val, wt, k, dp);
        int np = f(index + 1, curr, val, wt, k, dp);
        return dp[index][curr] = max(p, np);
    }

public:
    int knapSack(vector<int> &val, vector<int> &wt, int capacity) {
        int n = wt.size();
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, -1));
        return f(0, 0, val, wt, capacity, dp);
    }
};
```

---

## M-3: Tabulation (Bottom-Up DP)

Redefine state as remaining capacity instead of used capacity — cleaner for tabulation.

`dp[i][w]` = max value using items `[0..i]` with capacity `w`.

**Transition:**
```
not pick: dp[i][w] = dp[i-1][w]
pick:     dp[i][w] = val[i] + dp[i][w - wt[i]]    (stay at i, not i-1)
                                   ^^ this is the unbounded part
```

> TC = O(n × capacity)  
> SC = O(n × capacity)

```cpp
class Solution {
public:
    int knapSack(vector<int> &val, vector<int> &wt, int capacity) {
        int n = wt.size();
        vector<vector<int>> dp(n, vector<int>(capacity + 1, 0));

        // base case: first item only
        for (int w = 0; w <= capacity; w++) {
            dp[0][w] = (w / wt[0]) * val[0];
        }

        for (int i = 1; i < n; i++) {
            for (int w = 0; w <= capacity; w++) {
                int np = dp[i - 1][w];
                int p = 0;
                if (wt[i] <= w)
                    p = val[i] + dp[i][w - wt[i]];
                dp[i][w] = max(p, np);
            }
        }
        return dp[n - 1][capacity];
    }
};
```

---

## M-4: Space Optimized (1D DP)

Since pick uses `dp[i][w - wt[i]]` (same row), and not-pick uses `dp[i-1][w]` (prev row), we can use a single 1D array. Process **left to right** so that `dp[w - wt[i]]` reflects the current row (allowing re-picks).

> TC = O(n × capacity)  
> SC = O(capacity)

```cpp
class Solution {
public:
    int knapSack(vector<int> &val, vector<int> &wt, int capacity) {
        int n = wt.size();
        vector<int> dp(capacity + 1, 0);

        for (int i = 0; i < n; i++) {
            for (int w = wt[i]; w <= capacity; w++) {
                dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
            }
        }
        return dp[capacity];
    }
};
```

**Key difference from 0/1 knapsack:** 0/1 processes right to left (so each item is used once). Unbounded processes left to right (so `dp[w - wt[i]]` may already include item `i`).

---

## Dry Run

```
val = [1, 4, 5, 7], wt = [1, 3, 4, 5], capacity = 8

--- 1D Space Optimized ---
Initial dp = [0, 0, 0, 0, 0, 0, 0, 0, 0]

i=0 (val=1, wt=1):
  w=1: max(0, 1+dp[0]) = 1
  w=2: max(0, 1+dp[1]) = 2
  ...
  w=8: max(0, 1+dp[7]) = 8
  dp = [0, 1, 2, 3, 4, 5, 6, 7, 8]

i=1 (val=4, wt=3):
  w=3: max(3, 4+dp[0]) = 4
  w=4: max(4, 4+dp[1]) = 5
  w=5: max(5, 4+dp[2]) = 6
  w=6: max(6, 4+dp[3]) = 8
  w=7: max(7, 4+dp[4]) = 9
  w=8: max(8, 4+dp[5]) = 10
  dp = [0, 1, 2, 4, 5, 6, 8, 9, 10]

i=2 (val=5, wt=4):
  w=4: max(5, 5+dp[0]) = 5
  w=5: max(6, 5+dp[1]) = 6
  w=6: max(8, 5+dp[2]) = 8
  w=7: max(9, 5+dp[3]) = 9
  w=8: max(10, 5+dp[4]) = 10
  dp = [0, 1, 2, 4, 5, 6, 8, 9, 10]

i=3 (val=7, wt=5):
  w=5: max(6, 7+dp[0]) = 7
  w=6: max(8, 7+dp[1]) = 8
  w=7: max(9, 7+dp[2]) = 9
  w=8: max(10, 7+dp[3]) = 11
  dp = [0, 1, 2, 4, 5, 7, 8, 9, 11]

Answer = dp[8] = 11
Pick item 1 (val=4, wt=3) + item 3 (val=7, wt=5) = 11, total wt = 8 ✓
```

---

## 0/1 vs Unbounded — Key Differences

| | 0/1 Knapsack | Unbounded Knapsack |
|---|---|---|
| Pick transition | `dp[i-1][w - wt[i]]` (prev row) | `dp[i][w - wt[i]]` (same row) |
| 1D traversal | Right to left | Left to right |
| Recursion on pick | `f(index + 1, ...)` | `f(index, ...)` |
| Item usage | At most once | Unlimited |

---

## Complexity Summary

| Approach | Time | Space |
|----------|------|-------|
| Pure Recursion | Exponential | O(n + capacity) |
| Memoization | O(n × capacity) | O(n × capacity) |
| Tabulation | O(n × capacity) | O(n × capacity) |
| Space Optimized | O(n × capacity) | O(capacity) |

> Note: O(n × capacity) is **pseudo-polynomial** — polynomial in the numeric value of capacity, not input size. Fails if capacity is very large (e.g. 10^9).

---

## Bugs Encountered

1. Added `val[index]` unconditionally to both pick and not-pick → inflated answer
2. `curr + curr + wt[index]` typo → capacity fills 2x faster → misses valid picks
3. DP table sized `wt_total + 1` instead of `capacity + 1` → out of bounds when capacity > wt_total
