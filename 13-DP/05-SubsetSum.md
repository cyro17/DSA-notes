# Subset Sum Problem

Given an array of non-negative integers and a target sum `k`, determine whether any subset of the array adds up to `k`.

---

## Approach 1 — Brute Force (Recursive)

At each index, either **include** the current element or **skip** it. Explore all 2^n subsets.

**Time:** O(2^n) &nbsp;|&nbsp; **Space:** O(n) recursion stack

```cpp
class Solution {
    bool f(int index, int sum, vector<int>& arr, int k) {
        if (sum == k) return true;
        if (index == arr.size()) return false;

        // include arr[index] OR exclude it
        return f(index + 1, sum + arr[index], arr, k)
            || f(index + 1, sum, arr, k);
    }

public:
    bool isSubsetSum(vector<int>& arr, int k) {
        return f(0, 0, arr, k);
    }
};
```

### Why the original code was wrong

```cpp
// ❌ Original (buggy)
bool f(int index, int sum, vector<int>& arr, int k) {
    if (sum == k) return 1;
    if (index == n - 1) return sum == k;
    for (int i = index + 1; i < n; ++i) {
        if (f(i, sum + arr[index], arr, k)) return 1;
    }
    // ⚠ missing return — undefined behavior
}

bool isSubsetSum(vector<int>& arr, int k) {
    return f(0, arr[0], arr, k);  // ⚠ forces arr[0] into every subset
}
```

| Bug | Impact |
|-----|--------|
| No `return false` at end of `f()` | Undefined behavior when no subset found |
| Starts with `sum = arr[0]` | Element 0 is always included — can never test subsets without it |
| Loop only **includes** elements | Never explores "skip this element" — misses valid subsets |
| Base case `index == n-1` doesn't add `arr[n-1]` | Last element is silently excluded |

---

## Approach 2 — Recursion + Memoization (Top-Down DP)

Cache `(index, sum)` states to avoid recomputation.

**Time:** O(n × k) &nbsp;|&nbsp; **Space:** O(n × k)

```cpp
class Solution {
    unordered_map<long long, bool> memo;

    bool f(int index, int sum, vector<int>& arr, int k) {
        if (sum == k) return true;
        if (index == arr.size() || sum > k) return false;

        long long key = (long long)index * (k + 1) + sum;
        if (memo.count(key)) return memo[key];

        memo[key] = f(index + 1, sum + arr[index], arr, k)
                  || f(index + 1, sum, arr, k);
        return memo[key];
    }

public:
    bool isSubsetSum(vector<int>& arr, int k) {
        memo.clear();
        return f(0, 0, arr, k);
    }
};
```

> **Pruning:** `sum > k` works because all elements are non-negative. If negatives are possible, remove this check.

---

## Approach 3 — Bottom-Up DP (Tabulation)

`dp[j]` = can we form sum `j` using elements seen so far?

**Time:** O(n × k) &nbsp;|&nbsp; **Space:** O(k)

```cpp
class Solution {
public:
    bool isSubsetSum(vector<int>& arr, int k) {
        vector<bool> dp(k + 1, false);
        dp[0] = true;  // empty subset → sum 0

        for (int num : arr) {
            // iterate right-to-left so each element is used at most once
            for (int j = k; j >= num; --j) {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        return dp[k];
    }
};
```

### Why right-to-left?

If we go left-to-right (`j = num` to `k`), `dp[j - num]` may already reflect the current element being used, effectively allowing unlimited reuse (that solves a different problem — unbounded knapsack). Right-to-left ensures each element contributes at most once.

---

## Summary

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Brute force | O(2^n) | O(n) | TLE for n > ~20 |
| Memoized | O(n·k) | O(n·k) | Good when k is moderate |
| Tabulation | O(n·k) | O(k) | Best for interviews — optimal space |
