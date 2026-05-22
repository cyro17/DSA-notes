# Coin Change — Minimum Coins

> **LC 322:** [Coin Change](https://leetcode.com/problems/coin-change/)  
> **Pattern:** Unbounded Knapsack  
> **Striver DP:** #20

---

## Problem

Given coins of different denominations and a total amount, return the fewest coins needed to make that amount. Each coin can be used unlimited times. Return `-1` if not possible.

```
coins = [1, 5, 11], amount = 11
Answer: 1 (use one 11-coin)

coins = [2], amount = 3
Answer: -1 (impossible)
```

---

## Gotchas

1. **Failure = infinity, not 0.** In minimization, returning 0 for invalid paths means `min()` always picks it — poisons the entire recursion. Invalid → return `1e8`.
2. **Base case `curr == k` must be standalone.** Don't embed it inside `index == n-1` check — valid paths can complete before reaching the last coin.
3. **Sentinel overflow:** `1e8` is safe inside `int` (~2×10⁹ max). Using `1e9` risks overflow when you do `1 + f(...)`.
4. **`-1` conversion:** `f()` returns `1e8` for impossible. Convert to `-1` in the wrapper.
5. **DP table sentinel:** `-1` works here since answers are always ≥ 0 (count of coins can't be negative).

---

## M-1: Pure Recursion (Brute Force)

Two choices at each index: pick coin (stay at same index, unbounded) or skip (move to next coin).

> TC = exponential — each coin reusable, branches wildly  
> SC = O(amount) — recursion depth at most amount (picking coin 1 repeatedly)

```cpp
class Solution {
    int f(int index, int curr, int k, vector<int> &arr) {
        if (curr == k) return 0;
        if (curr > k || index >= (int)arr.size()) return 1e8;

        int pick = 1 + f(index, curr + arr[index], k, arr);
        int np = f(index + 1, curr, k, arr);
        return min(pick, np);
    }

public:
    int coinChange(vector<int> &coins, int amount) {
        int ans = f(0, 0, amount, coins);
        return ans >= 1e8 ? -1 : ans;
    }
};
```

---

## M-2: Memoization (Top-Down DP)

State: `dp[index][curr]` = min coins needed using coins `[index..n-1]` with `curr` amount already accumulated.

> TC = O(n × amount) — n × (amount+1) states, O(1) each  
> SC = O(n × amount) table + O(n + amount) stack

```cpp
class Solution {
    int f(int index, long long curr, int k, vector<int> &arr,
          vector<vector<int>> &dp) {
        if (curr == k) return 0;
        if (curr > k || index >= (int)arr.size()) return 1e8;

        if (dp[index][curr] != -1) return dp[index][curr];

        int pick = 1e8;
        if (curr + arr[index] <= k)
            pick = 1 + f(index, curr + arr[index], k, arr, dp);

        int np = f(index + 1, curr, k, arr, dp);
        return dp[index][curr] = min(pick, np);
    }

public:
    int coinChange(vector<int> &coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, -1));
        int ans = f(0, 0L, amount, coins, dp);
        return ans >= 1e8 ? -1 : ans;
    }
};
```

---

## M-3: Tabulation (Bottom-Up DP)

Redefine state as remaining amount instead of accumulated amount — cleaner for bottom-up.

`dp[i][a]` = min coins using coins `[0..i]` to make amount `a`.

**Transition:**
```
not pick:  dp[i][a] = dp[i-1][a]
pick:      dp[i][a] = 1 + dp[i][a - coins[i]]     (same row → unbounded)
```

**Base case:** `dp[i][0] = 0` for all i (0 coins to make amount 0).

> TC = O(n × amount)  
> SC = O(n × amount)

```cpp
class Solution {
public:
    int coinChange(vector<int> &coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, 1e8));

        // base case: amount 0 needs 0 coins
        for (int i = 0; i < n; i++)
            dp[i][0] = 0;

        // base case: first coin only
        for (int a = 1; a <= amount; a++) {
            if (a % coins[0] == 0)
                dp[0][a] = a / coins[0];
        }

        for (int i = 1; i < n; i++) {
            for (int a = 1; a <= amount; a++) {
                int np = dp[i - 1][a];
                int p = 1e8;
                if (coins[i] <= a)
                    p = 1 + dp[i][a - coins[i]];
                dp[i][a] = min(p, np);
            }
        }

        int ans = dp[n - 1][amount];
        return ans >= 1e8 ? -1 : ans;
    }
};
```

---

## M-4: Space Optimized (1D DP)

Pick uses same row (`dp[i][a - coins[i]]`), not-pick uses prev row (`dp[i-1][a]`). Single array, left to right (same direction logic as unbounded knapsack).

> TC = O(n × amount)  
> SC = O(amount)

```cpp
class Solution {
public:
    int coinChange(vector<int> &coins, int amount) {
        vector<int> dp(amount + 1, 1e8);
        dp[0] = 0;

        for (int i = 0; i < (int)coins.size(); i++) {
            for (int a = coins[i]; a <= amount; a++) {
                dp[a] = min(dp[a], 1 + dp[a - coins[i]]);
            }
        }

        return dp[amount] >= 1e8 ? -1 : dp[amount];
    }
};
```

---

## Dry Run

```
coins = [1, 5, 11], amount = 11

--- 1D Space Optimized ---
Initial dp = [0, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞]

i=0 (coin=1):
  a=1: min(∞, 1+dp[0]) = 1
  a=2: min(∞, 1+dp[1]) = 2
  ...
  a=11: min(∞, 1+dp[10]) = 11
  dp = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

i=1 (coin=5):
  a=5:  min(5, 1+dp[0]) = 1
  a=6:  min(6, 1+dp[1]) = 2
  a=10: min(10, 1+dp[5]) = 2
  a=11: min(11, 1+dp[6]) = 3
  dp = [0, 1, 2, 3, 4, 1, 2, 3, 4, 5, 2, 3]

i=2 (coin=11):
  a=11: min(3, 1+dp[0]) = 1
  dp = [0, 1, 2, 3, 4, 1, 2, 3, 4, 5, 2, 1]

Answer = dp[11] = 1 ✓ (one 11-coin)
```

---

## Edge Case: coins = [2], amount = 3

```
dp = [0, ∞, ∞, ∞]

i=0 (coin=2):
  a=2: min(∞, 1+dp[0]) = 1
  a=3: min(∞, 1+dp[1]) = ∞   ← dp[1] is still ∞

dp = [0, ∞, 1, ∞]
dp[3] >= 1e8 → return -1 ✓
```

---

## Complexity Summary

| Approach | Time | Space |
|----------|------|-------|
| Pure Recursion | Exponential | O(amount) |
| Memoization | O(n × amount) | O(n × amount) |
| Tabulation | O(n × amount) | O(n × amount) |
| Space Optimized | O(n × amount) | O(amount) |

---

## Bugs Encountered

1. Returning 0 for invalid paths → `min()` always picks failure as best answer
2. Base case only checks last coin → misses paths that complete earlier
3. Base case `index == n-1` only tries adding one coin → misses multi-use of last coin
4. Not converting `1e8` to `-1` in wrapper → returns garbage for impossible cases
