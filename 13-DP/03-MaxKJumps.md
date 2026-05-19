# Maximum Score from at most K Jumps

> **GFG:** [Maximum score from at most K jumps](https://www.geeksforgeeks.org/problems/maximum-score-from-at-most-k-jumps/1)  
> **LC 1696:** [Jump Game VI](https://leetcode.com/problems/jump-game-vi/) (same problem)  
> **Pattern:** DP + Sliding Window Optimization  
> **Related:** Frog Jumps (DP-3), Sliding Window Maximum (LC 239)

---

## Problem

Given an array `arr[]` and integer `k`. Start at index 0, reach index `n-1` by jumping at most `k` indices per move. Score = sum of values at all visited indices. Maximize the score.

```
arr = [1, -1, -2, 4, -7, 3], k = 2
Answer: 7
Path: 0(1) → 1(-1) → 3(4) → 5(3) = 7
```

**Constraints:** `n, k <= 10^5`

---

## M-1: Pure Recursion (Brute Force)

From index `i`, try all jumps `i+1` to `i+k` and take the max.

> TC = O(k^n) — at each index, branch into up to k choices  
> SC = O(n) — recursion stack

```cpp
class Solution {
    int f(int index, vector<int> &arr, int k) {
        int n = arr.size();
        if (index == n - 1) return arr[index];
        if (index > n - 1) return -1e8;

        int max_ = -1e8;
        for (int i = 1; i <= k; i++) {
            if (index + i < n)
                max_ = max(max_, f(index + i, arr, k));
        }
        return arr[index] + max_;
    }

public:
    int getScore(vector<int> &arr, int k) {
        return f(0, arr, k);
    }
};
```

---

## M-2: Memoization (Top-Down DP)

State: `dp[index]` = max score from `index` to `n-1`.

> TC = O(n × k) — n states, each does O(k) work  
> SC = O(n)

⚠️ **Sentinel pitfall:** values can be negative, so `-1` as "unvisited" collides with valid answers. Use `INT_MIN`.

```cpp
class Solution {
    int f(int index, vector<int> &arr, int k, vector<int> &dp) {
        int n = arr.size();
        if (index == n - 1) return arr[index];
        if (index > n - 1) return -1e8;

        if (dp[index] != INT_MIN) return dp[index];

        int max_ = -1e8;
        for (int i = 1; i <= k; i++) {
            if (index + i < n)
                max_ = max(max_, f(index + i, arr, k, dp));
        }
        return dp[index] = arr[index] + max_;
    }

public:
    int getScore(vector<int> &arr, int k) {
        int n = arr.size();
        vector<int> dp(n, INT_MIN);
        return f(0, arr, k, dp);
    }
};
```

**⛔ TLE for n, k = 10^5 → O(n × k) = 10^10 operations.**

---

## Why O(n × k) is not enough

The bottleneck is the inner loop:

```
dp[i] = arr[i] + max(dp[i+1], dp[i+2], ..., dp[i+k])
```

Scanning k elements per state is O(k). No matter how you structure the DP (recursion, tabulation), this loop remains. We need a data structure to get the max in a sliding window faster than O(k).

| Approach | Per-state work | Total |
|----------|---------------|-------|
| Recursion + memo | O(k) loop | O(n × k) = TLE |
| Tabulation | O(k) loop | O(n × k) = TLE |
| Tabulation + heap | O(log n) | O(n log n) ✓ |
| Tabulation + deque | O(1) amortized | O(n) ✓ |

---

## M-3: Tabulation + Max Heap (Left to Right)

**Intuition:** Instead of scanning k elements for the max, maintain a max-heap of all dp values computed so far. The top is always the best jump source. If it's out of range (more than k steps back), pop it.

**Key insight — lazy popping:** We don't maintain a strict window. Out-of-range elements buried in the heap are harmless — they only get popped when they reach the top. Once popped, they're never needed again (we're moving forward).

> TC = O(n log n) — each index pushed/popped once, heap ops O(log n)  
> SC = O(n)

```cpp
class Solution {
public:
    int getScore(vector<int> &arr, int k) {
        int n = arr.size();
        priority_queue<pair<int, int>> pq; // {dp value, index}
        vector<int> dp(n);
        dp[0] = arr[0];
        pq.push({dp[0], 0});

        for (int i = 1; i < n; ++i) {
            // pop elements out of jump range
            while (pq.top().second < i - k) pq.pop();

            dp[i] = arr[i] + pq.top().first;
            pq.push({dp[i], i});
        }
        return dp[n - 1];
    }
};
```

---

## M-3 Dry Run

```
arr = [1, -1, -2, 4, -7, 3], k = 2

--- i = 0 (base) ---
dp[0] = 1
heap: [(1, 0)]

--- i = 1 ---
top = (1, 0), 0 >= 1-2 = -1 ✓ (in range)
dp[1] = -1 + 1 = 0
heap: [(1,0), (0,1)]

--- i = 2 ---
top = (1, 0), 0 >= 2-2 = 0 ✓
dp[2] = -2 + 1 = -1
heap: [(1,0), (0,1), (-1,2)]

--- i = 3 ---
top = (1, 0), 0 >= 3-2 = 1? NO → pop
top = (0, 1), 1 >= 1 ✓
dp[3] = 4 + 0 = 4
heap: [(4,3), (0,1), (-1,2)]

--- i = 4 ---
top = (4, 3), 3 >= 4-2 = 2 ✓
dp[4] = -7 + 4 = -3
heap: [(4,3), (0,1), (-1,2), (-3,4)]

--- i = 5 ---
top = (4, 3), 3 >= 5-2 = 3 ✓
dp[5] = 3 + 4 = 7

Answer = dp[5] = 7 ✓
Path: 0(1) → 1(-1) → 3(4) → 5(3) = 7
```

---

## M-4: Tabulation + Monotonic Deque (Optimal)

Same idea but use a deque that maintains decreasing order of dp values. Front = max in window. O(1) amortized per lookup.

> TC = O(n) — each index pushed/popped from deque at most once  
> SC = O(n)

```cpp
class Solution {
public:
    int getScore(vector<int> &arr, int k) {
        int n = arr.size();
        vector<int> dp(n);
        dp[0] = arr[0];
        deque<int> dq; // stores indices, front = best dp in window
        dq.push_back(0);

        for (int i = 1; i < n; i++) {
            // remove out-of-window
            while (!dq.empty() && dq.front() < i - k)
                dq.pop_front();

            dp[i] = arr[i] + dp[dq.front()];

            // maintain decreasing order
            while (!dq.empty() && dp[dq.back()] <= dp[i])
                dq.pop_back();
            dq.push_back(i);
        }
        return dp[n - 1];
    }
};
```

---

## Complexity Summary

| Approach | Time | Space |
|----------|------|-------|
| Pure Recursion | O(k^n) | O(n) |
| Memoization | O(n × k) | O(n) |
| Tabulation + Heap | O(n log n) | O(n) |
| Tabulation + Deque | O(n) | O(n) |

---

## Bugs Encountered

1. **Sentinel collision:** Using `-1` as unvisited when answers can be `-1` → memoization silently breaks → TLE on negative arrays
2. **Heap range check direction:** Left-to-right traversal needs `pq.top().second < i - k` (too far behind), not `i + k` (that points forward)
