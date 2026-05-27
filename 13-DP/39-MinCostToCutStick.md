# 🔗 Matrix Chain Multiplication

> **Topic:** Interval DP · Memoization  
> **Difficulty:** Medium-Hard  
> **Pattern:** Partition DP (`dp[i][j]` = optimal cost for subarray `[i..j]`)

---

## 📌 Problem Statement

Given an array `arr[]` of size `N`, where `arr[i-1]` and `arr[i]` are the dimensions of the `i-th` matrix, find the **minimum number of scalar multiplications** needed to multiply the chain of matrices.

**Example:**
```
arr = [40, 20, 30, 10, 30]
Matrices: A(40×20), B(20×30), C(30×10), D(10×30)
Output: 26000
```

---

## 💡 Intuition

Every parenthesization corresponds to picking a **split point `k`** in the chain `[i..j]`:

```
(A_i ... A_k) × (A_{k+1} ... A_j)
```

The cost of multiplying the two resulting sub-products is:
```
arr[i-1] * arr[k] * arr[j]
```

We try all valid `k` from `i` to `j-1` and recurse on the two halves.  
This is classic **"try all cuts"** interval DP.

---

## 🧠 Recurrence

```
rec(i, j) = 0                                          if i == j  (single matrix)
rec(i, j) = min over k in [i, j-1] of:
              arr[i-1] * arr[k] * arr[j]
            + rec(i, k)
            + rec(k+1, j)
```

**Index Convention (1-indexed matrices):**
- Matrix `i` has dimensions `arr[i-1] × arr[i]`
- Entry call: `rec(1, N-1)` where `N = arr.size()`

---

## ✅ Solution (Top-Down DP / Memoization)

```cpp
class Solution {
private:
    int rec(int i, int j, vector<int>& arr, vector<vector<int>>& dp) {
        if (i == j) return 0;                   // base case: single matrix
        if (dp[i][j] != -1) return dp[i][j];    // already computed

        int min_ = 1e9;
        for (int k = i; k < j; ++k) {
            int steps = arr[i-1] * arr[k] * arr[j]
                      + rec(i, k, arr, dp)
                      + rec(k+1, j, arr, dp);
            if (steps < min_) min_ = steps;
        }
        return dp[i][j] = min_;
    }

public:
    int matrixMultiplication(vector<int>& arr) {
        int N = arr.size();
        vector<vector<int>> dp(N, vector<int>(N, -1));
        return rec(1, N-1, arr, dp);
    }
};
```

---

## 🔍 Dry Run

```
arr = [10, 20, 30]  →  Matrices: A(10×20), B(20×30)

rec(1, 2):
  k=1: arr[0]*arr[1]*arr[2] + rec(1,1) + rec(2,2)
      = 10*20*30 + 0 + 0 = 6000

Output: 6000
```

---

## 📊 Complexity

| | Value |
|---|---|
| **Time** | O(N³) — N² states × N choices per state |
| **Space** | O(N²) for dp table + O(N) recursion stack |

---

## ⚠️ Key Observations & Gotchas

| Point | Detail |
|---|---|
| **1-indexed matrices** | Matrix `i` ↔ dimensions `arr[i-1] × arr[i]`. Entry call is `rec(1, N-1)`, **not** `rec(0, N-1)`. |
| **Cost formula** | `arr[i-1] * arr[k] * arr[j]` — left boundary is `i-1`, split is `k`, right boundary is `j`. |
| **Base case** | `i == j` means single matrix → 0 multiplications needed. |
| **dp size** | Allocated as `N × N`; only upper triangle `dp[i][j]` with `i ≤ j` is ever filled. |
| **Overflow risk** | For very large arrays, consider `long long` instead of `int`. |

---

## 🔄 Bottom-Up Equivalent

For reference — iterates by **chain length**:

```cpp
int matrixMultiplication(vector<int>& arr) {
    int N = arr.size();
    vector<vector<int>> dp(N, vector<int>(N, 0));

    // len = chain length (2 to N-1)
    for (int len = 2; len < N; ++len) {
        for (int i = 1; i < N - len + 1; ++i) {
            int j = i + len - 1;
            dp[i][j] = 1e9;
            for (int k = i; k < j; ++k) {
                int cost = arr[i-1] * arr[k] * arr[j]
                         + dp[i][k] + dp[k+1][j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[1][N-1];
}
```

---

## 🗺️ DP Table Pattern

```
For arr = [A, B, C, D, E]  (4 matrices, indices 1..4)

     1    2    3    4
1  [ 0 ] [  ] [  ] [  ]
2       [ 0 ] [  ] [  ]
3            [ 0 ] [  ]
4                 [ 0 ]

Fill diagonals left→right, bottom→top.
Answer is dp[1][4].
```

---

## 🔗 Related Problems

| Problem | Pattern |
|---|---|
| Burst Balloons | Interval DP — cost on merging |
| Minimum Cost to Cut a Stick | Interval DP — partition cost |
| Strange Printer | Interval DP — reduce operations |
| Palindrome Partitioning II | Partition DP — linear index |
| Boolean Parenthesization | Interval DP — count ways |

---

## 📝 Quick Revision Checklist

- [ ] Entry call is `rec(1, N-1)` — matrices are **1-indexed**
- [ ] Cost = `arr[i-1] * arr[k] * arr[j]`
- [ ] Loop: `for k in [i, j)` — k is the last matrix in the **left** group
- [ ] Base: `i == j → 0`
- [ ] dp table size = `N × N` where `N = arr.size()`
