# Triangle — Minimum Path Sum

> **LC 120:** [Triangle](https://leetcode.com/problems/triangle/)  
> **Pattern:** 2D DP (Variable-width grid)  
> **Striver DP:** #11

---

## Problem

Given a triangle array, find the minimum path sum from top to bottom. At each step from position `(r, c)`, you may move to `(r+1, c)` or `(r+1, c+1)`.

```
    2
   3 4
  6 5 7
 4 1 8 3

Min path: 2 → 3 → 5 → 1 = 11
```

---

## Gotchas

1. **Row width varies** — row `r` has `r+1` elements. Don't use `arr[0].size()` as column bound — it's always 1. Use `c > r` instead.
2. **Access before bounds check** — `int m = arr[r].size()` crashes when `r >= n`. Always check `r` first.
3. **Sentinel collision** — values can be negative. Using `-1` as "unvisited" breaks memoization when actual answers are `-1`. Use `INT_MIN`.

---

## M-1: Pure Recursion (Brute Force)

From `(r, c)`, try both moves and take the minimum.

> TC = O(2^n) — each cell branches into 2 calls, overlapping subproblems recomputed  
> SC = O(n) — recursion stack depth

```cpp
class Solution {
    int f(int r, int c, vector<vector<int>> &arr, int n) {
        if (r == n - 1) return arr[r][c];
        if (c > r) return 0;
        return arr[r][c] + min(f(r + 1, c + 1, arr, n), f(r + 1, c, arr, n));
    }

public:
    int minimumTotal(vector<vector<int>> &arr) {
        int n = arr.size();
        return f(0, 0, arr, n);
    }
};
```

---

## M-2: Memoization (Top-Down DP)

State: `dp[r][c]` = min path sum from `(r, c)` to any cell in the last row.

Why `n × n` table works: max column index is `n-1` (at the last row), so `dp[r][c]` with both dimensions `n` covers all states. Only the lower-left triangle gets filled.

```
dp[0][0]  ✓  .     .     .
dp[1][0]  ✓  [1][1] ✓  .     .
dp[2][0]  ✓  [2][1] ✓  [2][2] ✓  .
dp[3][0]  ✓  [3][1] ✓  [3][2] ✓  [3][3] ✓
```

> TC = O(n²) — n(n+1)/2 unique states, O(1) work each  
> SC = O(n²) table + O(n) stack

```cpp
class Solution {
    int f(int r, int c, vector<vector<int>> &arr, int n, vector<vector<int>> &dp) {
        if (r == n - 1) return dp[r][c] = arr[r][c];
        if (c > r) return 0;
        if (dp[r][c] != INT_MIN) return dp[r][c];
        return dp[r][c] = arr[r][c] + min(f(r + 1, c + 1, arr, n, dp),
                                           f(r + 1, c, arr, n, dp));
    }

public:
    int minimumTotal(vector<vector<int>> &arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, INT_MIN));
        return f(0, 0, arr, n, dp);
    }
};
```

---

## M-3: Tabulation (Bottom-Up DP)

Build from last row → first row.

**Base case:** `dp[n-1][c] = arr[n-1][c]` for all c in last row.

**Transition:**
```
dp[i][j] = arr[i][j] + min(dp[i+1][j], dp[i+1][j+1])
```

> TC = O(n²)  
> SC = O(n²)

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>> &arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // base case: last row
        for (int c = 0; c < n; c++)
            dp[n - 1][c] = arr[n - 1][c];

        // fill bottom-up
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                dp[i][j] = arr[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
            }
        }

        return dp[0][0];
    }
};
```

---

## M-4: Space Optimized

Only need the row below to compute current row. Single array suffices since we process left to right and `dp[j]` / `dp[j+1]` from the previous iteration are still valid.

> TC = O(n²)  
> SC = O(n)

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>> &arr) {
        int n = arr.size();
        vector<int> dp(arr[n - 1].begin(), arr[n - 1].end());

        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                dp[j] = arr[i][j] + min(dp[j], dp[j + 1]);
            }
        }

        return dp[0];
    }
};
```

---

## Dry Run

```
arr = [[2], [3,4], [6,5,7], [4,1,8,3]]

--- Base case (row 3) ---
dp = [4, 1, 8, 3]

--- Row 2 ---
j=0: arr[2][0] + min(dp[0], dp[1]) = 6 + min(4,1) = 7
j=1: arr[2][1] + min(dp[1], dp[2]) = 5 + min(1,8) = 6
j=2: arr[2][2] + min(dp[2], dp[3]) = 7 + min(8,3) = 10
dp = [7, 6, 10, 3]

--- Row 1 ---
j=0: arr[1][0] + min(dp[0], dp[1]) = 3 + min(7,6) = 9
j=1: arr[1][1] + min(dp[1], dp[2]) = 4 + min(6,10) = 10
dp = [9, 10, 10, 3]

--- Row 0 ---
j=0: arr[0][0] + min(dp[0], dp[1]) = 2 + min(9,10) = 11
dp = [11, 10, 10, 3]

Answer = dp[0] = 11 ✓
Path: 2 → 3 → 5 → 1 = 11
```

---

## Complexity Summary

| Approach | Time | Space |
|----------|------|-------|
| Pure Recursion | O(2^n) | O(n) |
| Memoization | O(n²) | O(n²) |
| Tabulation | O(n²) | O(n²) |
| Space Optimized | O(n²) | O(n) |

---

## Bugs Encountered

1. Using `arr[0].size()` as column bound → always 1 for a triangle → early termination
2. Accessing `arr[r].size()` before checking `r < n` → heap buffer overflow
3. Using `-1` sentinel when answer can be `-1` → memo never triggers → TLE
4. Returning base case without storing in `dp` → last row recomputed every time → TLE
