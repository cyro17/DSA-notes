# Jump Game VI — Editorial

## Problem Statement

Given a 0-indexed integer array `nums` and an integer `k`, you start at index `0`. In one move, you can jump at most `k` steps forward. You want to reach the last index with the **maximum score**, where score is the sum of `nums[i]` for every index `i` you visit.

**Constraints:** `-10^4 <= nums[i] <= 10^4`, `1 <= k <= nums.length`

---

## Intuition

At every index `i`, you can jump to any index in `[i+1, i+k]`. The best score from index `i` is:

```
dp[i] = nums[i] + max(dp[i+1], dp[i+2], ..., dp[i+k])
```

This naturally lends itself to **top-down DP with memoization**.

---

## Approach 1 — Memoization (Top-Down DP)

### Recurrence

```
f(index) = arr[index] + max(f(index+1), f(index+2), ..., f(index+k))
f(n-1)   = arr[n-1]   (base case)
```

### Code

```cpp
class Solution {
    const int NEG_INF = INT_MIN / 2;

    int f(int index, int k, int n, vector<int>& arr, vector<int>& dp) {
        if (index == n - 1) return arr[index];
        if (dp[index] != NEG_INF) return dp[index];

        int max_ = NEG_INF;
        for (int j = 1; j <= k && index + j < n; ++j)
            max_ = max(max_, f(index + j, k, n, arr, dp));

        return dp[index] = arr[index] + max_;
    }
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n, NEG_INF);
        return f(0, k, n, nums, dp);
    }
};
```

### Why `INT_MIN / 2` and not `INT_MIN`?

Because `arr[index] + max_` can overflow if `max_` is `INT_MIN`. Dividing by 2 leaves a safe buffer.

### Why a separate sentinel works here but can break

If `arr[i]` values are extreme (e.g., ±10000) and the path is long (n up to 10^5), the accumulated sum can theoretically equal `INT_MIN/2`, causing a false cache hit. The bulletproof fix is a separate `visited[]` array:

```cpp
vector<bool> visited(n, false);
// check: if (visited[index]) return dp[index];
// set:   visited[index] = true; before return
```

### Complexity

| | Value |
|---|---|
| Time | O(n × k) |
| Space | O(n) stack + O(n) dp |

---

## Approach 2 — Bottom-Up DP

Same recurrence, iterating from right to left.

```cpp
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n, INT_MIN / 2);
        dp[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; --i) {
            for (int j = 1; j <= k && i + j < n; ++j)
                dp[i] = max(dp[i], nums[i] + dp[i + j]);
        }
        return dp[0];
    }
};
```

### Complexity

| | Value |
|---|---|
| Time | O(n × k) |
| Space | O(n) |

---

## Approach 3 — Monotonic Deque (Optimal)

### Key Observation

In the bottom-up version (iterating left to right), `dp[i]` needs `max(dp[i-k], ..., dp[i-1])` — a **sliding window maximum** of size `k`. A deque maintains this in O(1) amortized.

### Code

```cpp
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n);
        dp[0] = nums[0];

        deque<int> dq;  // indices; front = index with max dp value
        dq.push_back(0);

        for (int i = 1; i < n; ++i) {
            // evict indices outside the window [i-k, i-1]
            while (!dq.empty() && dq.front() < i - k)
                dq.pop_front();

            dp[i] = nums[i] + dp[dq.front()];

            // maintain decreasing order of dp values
            while (!dq.empty() && dp[dq.back()] <= dp[i])
                dq.pop_back();
            dq.push_back(i);
        }

        return dp[n - 1];
    }
};
```

### Dry Run (small example)

`nums = [1, -1, -2, 4, -7, 3]`, `k = 2`

| i | nums[i] | deque front | dp[i] | deque after |
|---|---------|-------------|-------|-------------|
| 0 | 1       | —           | 1     | [0]         |
| 1 | -1      | 0 → dp=1    | 0     | [0,1]       |
| 2 | -2      | 0 → dp=1    | -1    | [0,2] (1 popped since dp[1]=0 ≤ dp[2]=-1? No, keep) |
| 3 | 4       | 1 → dp=0... front=0 evicted (3-2=1), front=1 | 4 | [3] |
| 4 | -7      | 3 → dp=4    | -3    | [3,4]       |
| 5 | 3       | 3 → dp=4    | 7     | [5]         |

Result: `dp[5] = 7` ✅

### Complexity

| | Value |
|---|---|
| Time | O(n) |
| Space | O(n) |

---

## Common Bugs & Fixes

| Bug | Symptom | Fix |
|---|---|---|
| `j < k` instead of `j <= k` | Misses exactly k-step jumps | Use `j <= k` |
| Initializing `max_` with `-1e9` (double) | Silent type mismatch, corrupts comparisons | Use `NEG_INF = INT_MIN/2` or `INT_MIN/2` |
| Using value sentinel for memoization with extreme inputs | False cache hits → TLE or wrong answer | Use `visited[]` boolean array |
| Passing accumulated `sum` down the stack | Double-counting elements | Let return value carry the score |

---

## Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Memoization | O(nk) | O(n) | Intuitive; watch sentinel choice |
| Bottom-up DP | O(nk) | O(n) | Clean iterative version |
| Deque (sliding window max) | O(n) | O(n) | Optimal; interview gold standard |
