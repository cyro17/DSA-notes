# Equal Partition Problem

Given an array of positive integers, determine whether it can be partitioned into two subsets with equal sum.

**Key Insight:** If `totalSum` is even, the problem reduces to **Subset Sum** — find any subset summing to `totalSum / 2`. The remaining elements automatically sum to the other half.

---

## Edge Case — Odd Sum

If the total sum is odd, no equal partition is possible. Return `false` immediately.

```cpp
if (sum % 2 != 0) return false;
```

This is easy to miss — without it, integer division (`11/2 = 5`) lets the recursion find a valid subset of sum 5, incorrectly returning `true`.

---

## Approach 1 — Brute Force (Recursive)

Pick or skip each element, accumulating toward `target = sum/2`.

**Time:** O(2^n) &nbsp;|&nbsp; **Space:** O(n) recursion stack

```cpp
class Solution {
    bool f(int index, int k, vector<int>& arr, int target) {
        if (k == target) return true;
        if (index == arr.size() || k > target) return false;

        bool pick = false;
        if (arr[index] + k <= target)
            pick = f(index + 1, arr[index] + k, arr, target);
        bool skip = f(index + 1, k, arr, target);

        return pick || skip;
    }

public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        return f(0, 0, nums, sum / 2);
    }
};
```

---

## Approach 2 — Recursion + Memoization (Top-Down DP)

Cache `(index, k)` states. Since `k` ranges from `0` to `sum/2`, the table is `n × (sum/2 + 1)`.

**Time:** O(n × sum/2) &nbsp;|&nbsp; **Space:** O(n × sum/2)

```cpp
class Solution {
    bool f(int index, int k, vector<int>& arr, int target,
           vector<vector<int>>& dp) {
        if (k == target) return true;
        if (index == arr.size() || k > target) return false;
        if (dp[index][k] != -1) return dp[index][k];

        bool pick = false;
        if (arr[index] + k <= target)
            pick = f(index + 1, arr[index] + k, arr, target, dp);
        bool skip = f(index + 1, k, arr, target, dp);

        return dp[index][k] = pick || skip;
    }

public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();
        if (sum & 1) return false;
        vector<vector<int>> dp(n + 1, vector<int>(sum / 2 + 1, -1));
        return f(0, 0, nums, sum / 2, dp);
    }
};
```

> **Why `-1` sentinel works:** cached values are `0` (false) or `1` (true), so `-1` cleanly means "unvisited".

---

## Approach 3 — Bottom-Up DP (Tabulation)

`dp[j]` = can we form sum `j` from elements seen so far?

**Time:** O(n × sum/2) &nbsp;|&nbsp; **Space:** O(sum/2)

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        int target = sum / 2;

        vector<bool> dp(target + 1, false);
        dp[0] = true;  // empty subset → sum 0

        for (int num : nums) {
            // right-to-left: each element used at most once
            for (int j = target; j >= num; --j) {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        return dp[target];
    }
};
```

### Why right-to-left?

Left-to-right iteration lets `dp[j - num]` reflect the current element already being included, allowing unlimited reuse (unbounded knapsack). Right-to-left ensures each element contributes at most once (0/1 knapsack).

---

## Summary

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Brute force | O(2^n) | O(n) | TLE for n > ~20 |
| Memoized | O(n·sum/2) | O(n·sum/2) | Good when sum is moderate |
| Tabulation | O(n·sum/2) | O(sum/2) | Optimal — best for interviews |

### Reduction Chain

```
Equal Partition → Subset Sum(target = totalSum/2) → 0/1 Knapsack
```
