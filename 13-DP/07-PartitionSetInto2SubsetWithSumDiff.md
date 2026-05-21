# Minimum Subset Sum Difference

Given an array of non-negative integers, partition it into two subsets such that the absolute difference of their sums is minimized. Return that minimum difference.

**Key Insight:** If one subset sums to `s1`, the other sums to `total - s1`. The difference is `|total - 2*s1|`. So the problem reduces to: find a reachable sum `s1 ≤ total/2` that is as close to `total/2` as possible.

---

## Approach 1 — Brute Force (Recursive)

At each index, put the element in subset 1 (pick) or subset 2 (skip). At the end, compute the difference.

**Time:** O(2^n) &nbsp;|&nbsp; **Space:** O(n) recursion stack

```cpp
class Solution {
    void f(int index, int s1, int total, vector<int>& arr, int& mini) {
        if (index == arr.size()) {
            mini = min(mini, abs(total - 2 * s1));
            return;
        }

        f(index + 1, s1 + arr[index], total, arr, mini);  // pick
        f(index + 1, s1, total, arr, mini);                // skip
    }

public:
    int minDifference(vector<int>& arr) {
        int mini = 1e9;
        int total = accumulate(arr.begin(), arr.end(), 0);
        f(0, 0, total, arr, mini);
        return mini;
    }
};
```

> **Why `abs(total - 2*s1)`?**
> `s2 = total - s1`, so `|s1 - s2| = |s1 - (total - s1)| = |2*s1 - total|`.

---

## Approach 2 — Memoization (Top-Down DP)

We can't memoize `mini` directly. Instead, use subset sum DP to find **all reachable sums**, then pick the best one.

`dp[index][sum]` = can we form `sum` using elements `0..index`?

**Time:** O(n × total) &nbsp;|&nbsp; **Space:** O(n × total)

```cpp
class Solution {
    bool f(int index, int sum, vector<int>& arr, int target,
           vector<vector<int>>& dp) {
        if (sum == target) return true;
        if (index == arr.size() || sum > target) return false;
        if (dp[index][sum] != -1) return dp[index][sum];

        bool pick = false;
        if (sum + arr[index] <= target)
            pick = f(index + 1, sum + arr[index], arr, target, dp);
        bool skip = f(index + 1, sum, arr, target, dp);

        return dp[index][sum] = pick || skip;
    }

public:
    int minDifference(vector<int>& arr) {
        int n = arr.size();
        int total = accumulate(arr.begin(), arr.end(), 0);

        // find all reachable sums up to total/2
        int half = total / 2;
        vector<vector<int>> dp(n, vector<int>(half + 1, -1));

        int mini = total;  // worst case: one set empty
        for (int s1 = half; s1 >= 0; s1--) {
            if (f(0, 0, arr, s1, dp)) {
                mini = total - 2 * s1;
                break;  // first hit is the closest to half
            }
        }
        return mini;
    }
};
```

> This works but calls `f()` multiple times for different targets. The tabulation approach below is cleaner.

---

## Approach 3 — Tabulation (Bottom-Up DP)

Build the subset sum table, then scan the last row for the best reachable sum ≤ `total/2`.

**Time:** O(n × total) &nbsp;|&nbsp; **Space:** O(n × total)

```cpp
class Solution {
public:
    int minDifference(vector<int>& arr) {
        int n = arr.size();
        int total = accumulate(arr.begin(), arr.end(), 0);
        vector<vector<bool>> dp(n, vector<bool>(total + 1, false));

        // base case: empty subset
        for (int i = 0; i < n; i++)
            dp[i][0] = true;

        // base case: first element alone
        if (arr[0] <= total)
            dp[0][arr[0]] = true;

        // fill table
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= total; j++) {
                bool skip = dp[i - 1][j];
                bool pick = false;
                if (arr[i] <= j)
                    pick = dp[i - 1][j - arr[i]];
                dp[i][j] = skip || pick;
            }
        }

        // find closest reachable sum to total/2
        int mini = total;
        for (int s1 = 0; s1 <= total / 2; s1++) {
            if (dp[n - 1][s1]) {
                mini = min(mini, total - 2 * s1);
            }
        }
        return mini;
    }
};
```

---

## Approach 4 — Space Optimized (1D DP)

Since each row only depends on the previous row, use a single array.

**Time:** O(n × total) &nbsp;|&nbsp; **Space:** O(total)

```cpp
class Solution {
public:
    int minDifference(vector<int>& arr) {
        int total = accumulate(arr.begin(), arr.end(), 0);
        vector<bool> dp(total + 1, false);
        dp[0] = true;

        for (int num : arr) {
            // right-to-left: 0/1 knapsack
            for (int j = total; j >= num; j--) {
                dp[j] = dp[j] || dp[j - num];
            }
        }

        int mini = total;
        for (int s1 = 0; s1 <= total / 2; s1++) {
            if (dp[s1]) {
                mini = min(mini, total - 2 * s1);
            }
        }
        return mini;
    }
};
```

---

## Summary

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Brute force | O(2^n) | O(n) | TLE for n > ~20 |
| Memoized | O(n·total) | O(n·total) | Multiple target calls, less clean |
| Tabulation | O(n·total) | O(n·total) | Cleanest 2D approach |
| 1D optimized | O(n·total) | O(total) | Best for interviews |

### Reduction Chain

```
Min Subset Difference → Subset Sum (find all reachable sums) → 0/1 Knapsack
```

### Core Formula

```
s1 + s2 = total
diff = |s1 - s2| = |total - 2*s1|
minimize diff → maximize s1 where s1 ≤ total/2
```
