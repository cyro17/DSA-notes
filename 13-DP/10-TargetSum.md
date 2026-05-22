# Target Sum (Count Subsets with Given Difference)

Given an array of non-negative integers and a target, assign `+` or `-` to each element such that the total equals `target`. Return the number of ways.

**Key Reduction:** Instead of brute-forcing +/- assignments, reduce to a subset sum counting problem.

```
s1 - s2 = target
s1 + s2 = total
→ s2 = (total - target) / 2
```

Count subsets summing to `s2`. Two early exits:
- `total - target < 0` → impossible
- `(total - target)` is odd → can't split evenly

---

## Approach 1 — Brute Force (Recursive)

Pick or skip each element, count how many times we hit `s2`.

**Time:** O(2^n) &nbsp;|&nbsp; **Space:** O(n) recursion stack

```cpp
class Solution {
    int f(int index, int sum, int k, vector<int>& arr) {
        if (index == arr.size()) {
            return sum == k;
        }

        int pick = 0;
        if (sum + arr[index] <= k)
            pick = f(index + 1, sum + arr[index], k, arr);
        int skip = f(index + 1, sum, k, arr);

        return pick + skip;
    }

public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total - target < 0 || (total - target) & 1) return 0;
        int s2 = (total - target) >> 1;
        return f(0, 0, s2, nums);
    }
};
```

> **Why `pick + skip` not `pick || skip`?** We're counting ways, not checking existence.

---

## Approach 2 — Memoization (Top-Down DP)

Cache `(index, sum)` → number of ways to reach `s2` from this state.

**Time:** O(n × s2) &nbsp;|&nbsp; **Space:** O(n × s2)

```cpp
class Solution {
    int f(int index, int sum, int k, vector<int>& arr,
          vector<vector<int>>& dp) {
        if (index == arr.size()) {
            return sum == k;
        }
        if (dp[index][sum] != -1) return dp[index][sum];

        int pick = 0;
        if (sum + arr[index] <= k)
            pick = f(index + 1, sum + arr[index], k, arr, dp);
        int skip = f(index + 1, sum, k, arr, dp);

        return dp[index][sum] = pick + skip;
    }

public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total - target < 0 || (total - target) & 1) return 0;
        int s2 = (total - target) >> 1;
        vector<vector<int>> dp(nums.size(), vector<int>(s2 + 1, -1));
        return f(0, 0, s2, nums, dp);
    }
};
```

### Common bugs to avoid

| Bug | Why it breaks |
|-----|---------------|
| Using `1e9` as sentinel | Valid int value — collides with real counts. Use `-1` |
| Passing `target` instead of `s2` | Solves a different problem entirely |
| Using `count&` with memoized return | Dead variable — return value carries the answer |
| Missing return when `sum != k` at base | Undefined behavior — `return sum == k` handles both cases |

---

## Approach 3 — Tabulation (Bottom-Up DP)

`dp[i][j]` = number of ways to form sum `j` using elements `0..i`.

**Time:** O(n × s2) &nbsp;|&nbsp; **Space:** O(n × s2)

```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total - target < 0 || (total - target) & 1) return 0;
        int s2 = (total - target) >> 1;
        int n = nums.size();

        vector<vector<int>> dp(n + 1, vector<int>(s2 + 1, 0));
        dp[0][0] = 1;  // one way to make sum 0 with 0 elements

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= s2; j++) {
                int skip = dp[i - 1][j];
                int pick = 0;
                if (nums[i - 1] <= j)
                    pick = dp[i - 1][j - nums[i - 1]];
                dp[i][j] = pick + skip;
            }
        }
        return dp[n][s2];
    }
};
```

> **Note:** Inner loop starts at `j = 0` (not `j = 1`) because `nums[i-1]` can be `0`, and we need to count those ways.

---

## Approach 4 — Space Optimized (1D DP)

**Time:** O(n × s2) &nbsp;|&nbsp; **Space:** O(s2)

```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total - target < 0 || (total - target) & 1) return 0;
        int s2 = (total - target) >> 1;

        vector<int> dp(s2 + 1, 0);
        dp[0] = 1;

        for (int num : nums) {
            // right-to-left: 0/1 knapsack
            for (int j = s2; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }
        return dp[s2];
    }
};
```

### Edge case: zeros in array

If `num = 0`, the inner loop `for (j = s2; j >= 0; j--)` runs and `dp[j] += dp[j]`, effectively doubling the count. This is correct — each zero can go in either set.

---

## Summary

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Brute force | O(2^n) | O(n) | TLE for n > ~20 |
| Memoized | O(n·s2) | O(n·s2) | Top-down, clean |
| Tabulation | O(n·s2) | O(n·s2) | Bottom-up |
| 1D optimized | O(n·s2) | O(s2) | Best for interviews |

### Reduction Chain

```
Target Sum (+/- assignment)
  → Count Subsets with Difference = target
    → Count Subsets with Sum = (total - target) / 2
      → 0/1 Knapsack (counting variant)
```
