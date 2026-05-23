# Rod Cutting

> **GFG:** [Rod Cutting](https://www.geeksforgeeks.org/problems/rod-cutting0840/1)  
> **Pattern:** Unbounded Knapsack  
> **Striver DP:** #24

---

## Problem

Given a rod of length `n` and an array `price[]` where `price[i]` is the price of a piece of length `i+1`. Cut the rod into pieces to maximize total price. Each length can be used unlimited times.

```
price = [1, 5, 8, 9, 10, 17, 17, 20], n = 8
Answer: 22 (cut into lengths 2 + 6 → 5 + 17 = 22)
```

---

## Gotchas

1. **Index vs cut length:** `price` is 0-indexed but `price[i]` = value of length `i+1`. If using 1-based index, access `price[index-1]` and subtract `index` from remaining length.
2. **Pick condition:** cut length must fit in remaining rod → `index <= l` (1-based) or `index+1 <= l` (0-based).
3. **Base case:** `l == 0` (no rod left) → return 0. Going past all items with `l > 0` → return 0 (can't cut further, leftover has no value).

---

## M-1: Pure Recursion (Brute Force)

Use 1-based indexing: `index` = cut length. At each step, pick this length (stay for unbounded) or skip to next length.

> TC = exponential — each length reusable, branches wildly  
> SC = O(n) — recursion depth

```cpp
class Solution {
    int f(int index, int l, vector<int> &price) {
        int n = price.size();
        if (index == n && l == 0) return 0;
        if (index > n) return 0;

        int pick = 0;
        if (index <= l)
            pick = price[index - 1] + f(index, l - index, price);
        int np = f(index + 1, l, price);
        return max(pick, np);
    }

public:
    int cutRod(vector<int> &price) {
        int n = price.size();
        return f(1, n, price);
    }
};
```

---

## M-2: Memoization (Top-Down DP)

State: `dp[index][l]` = max price using cut lengths `[index..n]` with remaining rod length `l`.

`index` ranges `[1, n]`, `l` ranges `[0, n]` → table size `(n+1) × (n+1)`.

> TC = O(n²) — n × (n+1) states, O(1) each  
> SC = O(n²) table + O(n) stack

```cpp
class Solution {
    int f(int index, int l, vector<int> &price, vector<vector<int>> &dp) {
        int n = price.size();
        if (index == n && l == 0) return 0;
        if (index > n) return 0;

        if (dp[index][l] != -1) return dp[index][l];

        int pick = 0;
        if (index <= l)
            pick = price[index - 1] + f(index, l - index, price, dp);
        int np = f(index + 1, l, price, dp);
        return dp[index][l] = max(pick, np);
    }

public:
    int cutRod(vector<int> &price) {
        int n = price.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        return f(1, n, price, dp);
    }
};
```

---

## M-3: Tabulation (Bottom-Up DP)

Switch to 0-based. `dp[i][l]` = max price using cut lengths `[1..i+1]` with rod length `l`.

**Transition:**
```
not pick:  dp[i][l] = dp[i-1][l]
pick:      dp[i][l] = price[i] + dp[i][l - (i+1)]    (same row → unbounded)
                                      ^^^^^ cut length = i+1
```

**Base case:** `dp[0][l] = (l / 1) * price[0]` — using only length-1 pieces.

> TC = O(n²)  
> SC = O(n²)

```cpp
class Solution {
public:
    int cutRod(vector<int> &price) {
        int n = price.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));

        // base case: only length-1 cuts
        for (int l = 0; l <= n; l++)
            dp[0][l] = l * price[0];

        for (int i = 1; i < n; i++) {
            int cutLen = i + 1;
            for (int l = 0; l <= n; l++) {
                int np = dp[i - 1][l];
                int p = 0;
                if (cutLen <= l)
                    p = price[i] + dp[i][l - cutLen];
                dp[i][l] = max(p, np);
            }
        }
        return dp[n - 1][n];
    }
};
```

---

## M-4: Space Optimized (1D DP)

Pick uses same row → left to right traversal (unbounded pattern).

> TC = O(n²)  
> SC = O(n)

```cpp
class Solution {
public:
    int cutRod(vector<int> &price) {
        int n = price.size();
        vector<int> dp(n + 1, 0);

        for (int i = 0; i < n; i++) {
            int cutLen = i + 1;
            for (int l = cutLen; l <= n; l++) {
                dp[l] = max(dp[l], price[i] + dp[l - cutLen]);
            }
        }
        return dp[n];
    }
};
```

---

## Dry Run

```
price = [2, 6, 7], n = 3

--- 1D Space Optimized ---
Initial dp = [0, 0, 0, 0]

i=0 (cutLen=1, price=2):
  l=1: max(0, 2+dp[0]) = 2
  l=2: max(0, 2+dp[1]) = 4
  l=3: max(0, 2+dp[2]) = 6
  dp = [0, 2, 4, 6]       ← three length-1 pieces = 2×3 = 6

i=1 (cutLen=2, price=6):
  l=2: max(4, 6+dp[0]) = 6
  l=3: max(6, 6+dp[1]) = 8
  dp = [0, 2, 6, 8]       ← length-2 + length-1 = 6+2 = 8

i=2 (cutLen=3, price=7):
  l=3: max(8, 7+dp[0]) = 8
  dp = [0, 2, 6, 8]       ← whole rod = 7, but 6+2 = 8 is better

Answer = dp[3] = 8 ✓
Best cut: length 2 (price 6) + length 1 (price 2) = 8
```

---

## Mapping to Unbounded Knapsack

| Rod Cutting | Unbounded Knapsack |
|---|---|
| Cut length `i+1` | Item weight `wt[i]` |
| `price[i]` | Item value `val[i]` |
| Rod length `n` | Knapsack capacity `W` |
| Maximize total price | Maximize total value |
| Same length reusable | Same item reusable |

The 1D solution is identical in structure — left-to-right traversal, same-row reference for unbounded picks.

---

## Complexity Summary

| Approach | Time | Space |
|----------|------|-------|
| Pure Recursion | Exponential | O(n) |
| Memoization | O(n²) | O(n²) |
| Tabulation | O(n²) | O(n²) |
| Space Optimized | O(n²) | O(n) |

---

## Bugs Encountered

1. Using `index` as both array index and cut length without adjusting → `price[index]` off by one, subtracted wrong length from rod
2. Base case `index == n && l == 0` too strict — `index > n` with `l > 0` fell through without returning → undefined behavior
