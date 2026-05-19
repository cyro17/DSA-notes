# Ninja Training / Maximum Points

> **GFG:** [Geek's Training](https://www.geeksforgeeks.org/problems/geeks-training/1)  
> **Pattern:** 2D DP (Grid with constraint)  
> **Striver DP:** #7

---

## Problem

Given a `n x m` matrix where each row represents a day and each column represents an activity. `mat[i][j]` = points for activity `j` on day `i`. Maximize total points such that **no two consecutive days have the same activity**.

---

## M-1: Pure Recursion (Brute Force)

For each day, try all activities except the one picked on the previous day. Track which column was last picked.

> TC = O(m^n) — at each of n rows, we branch into (m-1) choices  
> SC = O(n) — recursion stack depth

```cpp
class Solution {
    int rec(int r, int c, vector<vector<int>> &arr) {
        int n = arr.size(), m = arr[0].size();
        if (r > n - 1) return 0;

        int max_ = -1e8;
        for (int j = 0; j < m; ++j) {
            if (j != c) {
                max_ = max(max_, arr[r][c] + rec(r + 1, j, arr));
            }
        }
        return max_;
    }

public:
    int maximumPoints(vector<vector<int>> &mat) {
        int n = mat.size(), m = mat[0].size();
        int max_ = -1e8;
        for (int i = 0; i < m; i++) {
            max_ = max(max_, rec(0, i, mat));
        }
        return max_;
    }
};
```

---

## M-2: Memoization (Top-Down DP)

State: `dp[r][c]` = max points starting from row `r` when we pick column `c` at row `r`.

Overlapping subproblems: `rec(2, 1)` can be called from `rec(1, 0)` and `rec(1, 2)` — same subproblem recomputed.

> TC = O(n × m × m) = O(n × m²) — n×m states, each does O(m) work  
> SC = O(n × m) table + O(n) stack

```cpp
class Solution {
    int rec(int r, int c, vector<vector<int>> &arr, vector<vector<int>> &dp) {
        int n = arr.size(), m = arr[0].size();
        if (r > n - 1) return 0;
        if (dp[r][c] != -1) return dp[r][c];

        int max_ = -1e8;
        for (int j = 0; j < m; ++j) {
            if (j != c) {
                max_ = max(max_, arr[r][c] + rec(r + 1, j, arr, dp));
            }
        }
        return dp[r][c] = max_;
    }

public:
    int maximumPoints(vector<vector<int>> &mat) {
        int n = mat.size(), m = mat[0].size();
        int max_ = -1e8;
        vector<vector<int>> dp(n, vector<int>(m, -1));
        for (int i = 0; i < m; i++) {
            max_ = max(max_, rec(0, i, mat, dp));
        }
        return max_;
    }
};
```

---

## M-3: Tabulation (Bottom-Up DP)

Build from last day → first day. `dp[i][j]` = max points from day `i` to day `n-1` if we pick activity `j` on day `i`.

**Transition:**
```
dp[i][j] = mat[i][j] + max(dp[i+1][k]) for all k != j
```

**Base case:** Last row → `dp[n-1][j] = mat[n-1][j]`

> TC = O(n × m²)  
> SC = O(n × m)

```cpp
class Solution {
public:
    int maximumPoints(vector<vector<int>> &mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));

        // base case: last row
        for (int j = 0; j < m; j++)
            dp[n - 1][j] = mat[n - 1][j];

        // fill bottom-up
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j < m; j++) {
                dp[i][j] = -1e8;
                for (int k = 0; k < m; k++) {
                    if (k != j) {
                        dp[i][j] = max(dp[i][j], mat[i][j] + dp[i + 1][k]);
                    }
                }
            }
        }

        return *max_element(dp[0].begin(), dp[0].end());
    }
};
```

---

## M-4: Space Optimized

Only need the next row to compute current row. Replace 2D table with a single `prev` array.

> TC = O(n × m²)  
> SC = O(m)

```cpp
class Solution {
public:
    int maximumPoints(vector<vector<int>> &mat) {
        int n = mat.size(), m = mat[0].size();
        vector<int> prev(m);

        for (int j = 0; j < m; j++)
            prev[j] = mat[n - 1][j];

        for (int i = n - 2; i >= 0; i--) {
            vector<int> curr(m);
            for (int j = 0; j < m; j++) {
                curr[j] = -1e8;
                for (int k = 0; k < m; k++) {
                    if (k != j)
                        curr[j] = max(curr[j], mat[i][j] + prev[k]);
                }
            }
            prev = curr;
        }

        return *max_element(prev.begin(), prev.end());
    }
};
```

---

## Dry Run

```
mat = [[10, 40, 70],
       [20, 50, 30],
       [60, 10, 40]]

--- Base case (row 2) ---
prev = [60, 10, 40]

--- Row 1 ---
j=0: mat[1][0] + max(prev[1], prev[2]) = 20 + 40 = 60
j=1: mat[1][1] + max(prev[0], prev[2]) = 50 + 60 = 110
j=2: mat[1][2] + max(prev[0], prev[1]) = 30 + 60 = 90
prev = [60, 110, 90]

--- Row 0 ---
j=0: mat[0][0] + max(prev[1], prev[2]) = 10 + 110 = 120
j=1: mat[0][1] + max(prev[0], prev[2]) = 40 + 90  = 130
j=2: mat[0][2] + max(prev[0], prev[1]) = 70 + 110 = 180
prev = [120, 130, 180]

Answer = max(120, 130, 180) = 180
Path: day0→activity2(70) + day1→activity1(50) + day2→activity0(60) = 180 ✓
```

---

## Complexity Summary

| Approach | Time | Space |
|----------|------|-------|
| Pure Recursion | O(m^n) | O(n) |
| Memoization | O(n × m²) | O(n × m) |
| Tabulation | O(n × m²) | O(n × m) |
| Space Optimized | O(n × m²) | O(m) |

---

## Key Insight

The inner loop `max(dp[i+1][k]) for k != j` can be optimized to O(1) per cell by precomputing the **first and second maximum** of the next row. If `j` equals the index of the first max, use second max. Otherwise use first max. This brings total time to **O(n × m)**.

```cpp
// O(1) max-excluding-j trick
int max1 = -1e8, max2 = -1e8, idx1 = -1;
for (int k = 0; k < m; k++) {
    if (prev[k] >= max1) { max2 = max1; max1 = prev[k]; idx1 = k; }
    else if (prev[k] > max2) { max2 = prev[k]; }
}
// For column j: best_next = (j == idx1) ? max2 : max1;
```
