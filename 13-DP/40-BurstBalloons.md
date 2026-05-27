# Burst Balloons

**Platform:** LeetCode 312  
**Difficulty:** Hard  
**Topic Tags:** Dynamic Programming, Divide and Conquer

---

## Problem Statement

Given `n` balloons indexed from `0` to `n-1`, each with a number on it (`nums[i]`), burst all balloons to collect maximum coins.

Bursting balloon `i` gives coins = `nums[i-1] * nums[i] * nums[i+1]`.  
Neighbors shift after each burst. If `i-1` or `i+1` is out of bounds, treat that neighbor as `1`.

Return the maximum coins collectible.

**Example:**
```
nums = [3, 1, 5, 8]
Burst order: 1 → 5 → 3 → 8
Coins:  3*1*5 + 3*5*8 + 1*3*8 + 1*8*1
      =  15   + 120   + 24    + 8    = 167

Output: 167
```

---

## Key Insight — Think in Reverse

The hard part: when you burst balloon `k`, its neighbors have already changed due to prior bursts. This makes a forward simulation messy.

**Reverse the thinking:** instead of asking *"which balloon do I burst first?"*, ask *"which balloon do I burst last?"* in the interval `[i, j]`.

If balloon `k` is the **last** to be burst in `[i, j]`, then at the moment of bursting:
- All balloons between `i` and `k` (exclusive) are already gone
- All balloons between `k` and `j` (exclusive) are already gone
- So its neighbors are exactly `arr[i-1]` and `arr[j+1]` — which are **outside** the interval and never change

This gives a clean, non-overlapping subproblem split.

**Setup:** Add sentinel `1`s at both ends — `nums = [1, ...original..., 1]` — so boundary balloons always multiply by `1`.

---

## Approach 1 — Brute Force (Pure Recursion)

### Intuition

Try every balloon as the last to burst in every interval. No caching — overlapping subproblems are recomputed repeatedly.

### Code (C++)

```cpp
class Solution {
private:
    int rec(int i, int j, vector<int>& arr) {
        if (i > j) return 0;
        int max_ = INT_MIN;
        int n = arr.size();

        for (int k = i; k <= j; k++) {
            int tmp = arr[k];
            if (j + 1 < n) tmp *= arr[j + 1];
            if (i - 1 >= 0) tmp *= arr[i - 1];
            tmp += rec(i, k - 1, arr) + rec(k + 1, j, arr);
            max_ = max(max_, tmp);
        }
        return max_;
    }
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.push_back(1);
        nums.insert(nums.begin(), 1);
        return rec(1, n, nums);
    }
};
```

### Dry Run

```
nums = [3, 1, 5, 8]
After setup: arr = [1, 3, 1, 5, 8, 1]  (indices 0..5)
rec(1, 4) — find last balloon to burst among indices 1..4

  k=1 (balloon 3 is last):
    coins = arr[0] * arr[1] * arr[5] = 1*3*1 = 3
          + rec(1, 0) + rec(2, 4)
    rec(2, 4) → last among [1, 5, 8]:
      k=3 (balloon 5 last): arr[1]*arr[3]*arr[5] = 3*5*1=15 + rec(2,2)+rec(4,4)
        rec(2,2): arr[1]*arr[2]*arr[3] = 3*1*5=15
        rec(4,4): arr[3]*arr[4]*arr[5] = 5*8*1=40
        → 15+15+40 = 70
      k=2 (balloon 1 last): arr[1]*arr[2]*arr[5]=3*1*1=3 + 0+rec(3,4)
        rec(3,4): k=3: 5*8*arr[1]=3? No: arr[2]*arr[3]*arr[5]=1*5*1=5+0+rec(4,4)=40 → 45
                  k=4: arr[2]*arr[4]*arr[5]=1*8*1=8+rec(3,3)+0
                    rec(3,3)=arr[2]*arr[3]*arr[4]=1*5*8=40 → 48
                  → 48
        → 3 + 48 = 51
      k=4 (balloon 8 last): arr[1]*arr[4]*arr[5]=3*8*1=24 + rec(2,3)+0
        rec(2,3): k=2: arr[1]*arr[2]*arr[4]=3*1*8=24+0+rec(3,3)=40 → 64
                  k=3: arr[1]*arr[3]*arr[4]=3*5*8=120+rec(2,2)+0=15 → 135
                  → 135
        → 24+135 = 159
      → rec(2,4) = max(70, 51, 159) = 159
    total k=1: 3 + 0 + 159 = 162

  k=2 (balloon 1 is last):
    coins = arr[0]*arr[2]*arr[5] = 1*1*1=1 + rec(1,1)+rec(3,4)
    rec(1,1) = arr[0]*arr[1]*arr[2] = 1*3*1 = 3
    rec(3,4) = 48  (computed above)
    → 1+3+48 = 52

  k=3 (balloon 5 is last):
    coins = arr[0]*arr[3]*arr[5] = 1*5*1=5 + rec(1,2)+rec(4,4)
    rec(1,2): k=1: arr[0]*arr[1]*arr[3]=1*3*5=15+0+rec(2,2)=15 → 30
              k=2: arr[0]*arr[2]*arr[3]=1*1*5=5+rec(1,1)+0=3 → 8
              → 30
    rec(4,4) = 40
    → 5+30+40 = 75

  k=4 (balloon 8 is last):
    coins = arr[0]*arr[4]*arr[5] = 1*8*1=8 + rec(1,3)+0
    rec(1,3): k=1: arr[0]*arr[1]*arr[4]=1*3*8=24+0+rec(2,3)=135 → 159
              k=2: arr[0]*arr[2]*arr[4]=1*1*8=8+rec(1,1)+rec(3,3)=3+40 → 51
              k=3: arr[0]*arr[3]*arr[4]=1*5*8=40+rec(1,2)+0=30 → 70
              → 159
    → 8+159 = 167

rec(1,4) = max(162, 52, 75, 167) = 167 ✓
```

### Complexity

| | Complexity |
|---|---|
| **Time** | O(4^n / n^(3/2)) — Catalan number growth |
| **Space** | O(n) — recursion stack only |

Every overlapping subproblem `rec(i, j)` is recomputed from scratch, leading to exponential blowup identical in structure to Matrix Chain Multiplication without memoization.

---

## Approach 2 — Optimized (Memoization / Top-Down DP)

### Intuition

`rec(i, j)` depends only on `i` and `j`. There are O(n²) unique intervals. Cache each result the first time it's computed — every subsequent call is O(1).

### Code (C++)

```cpp
class Solution {
private:
    int rec(int i, int j, vector<int>& arr, vector<vector<int>>& dp) {
        if (i > j) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        int max_ = INT_MIN;
        int n = arr.size();

        for (int k = i; k <= j; k++) {
            int tmp = arr[k];
            if (j + 1 < n) tmp *= arr[j + 1];
            if (i - 1 >= 0) tmp *= arr[i - 1];
            tmp += rec(i, k - 1, arr, dp) + rec(k + 1, j, arr, dp);
            max_ = max(max_, tmp);
        }
        return dp[i][j] = max_;
    }
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.push_back(1);
        nums.insert(nums.begin(), 1);
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));
        return rec(1, n, nums, dp);
    }
};
```

### State Definition

```
dp[i][j] = maximum coins collectible by bursting all balloons
           in the subarray arr[i..j],
           where arr[i-1] and arr[j+1] are fixed outer boundaries
           (they are burst outside this subproblem, or are sentinels).
```

### Recurrence

```
dp[i][j] = max over k in [i, j] of:
              arr[i-1] * arr[k] * arr[j+1]   ← coins for bursting k last
            + dp[i][k-1]                      ← best from left partition
            + dp[k+1][j]                      ← best from right partition

dp[i][j] = 0   when i > j  (empty interval)
```

The critical invariant: when `k` is the **last** balloon burst in `[i, j]`, its live neighbors are `arr[i-1]` and `arr[j+1]` — fixed boundaries, not affected by any burst inside `[i, j]`.

### Dry Run

```
nums = [3, 1, 5, 8]
arr  = [1, 3, 1, 5, 8, 1]   (n=4, working range: indices 1..4)

── length-1 intervals ──────────────────────────────────
dp[1][1]: k=1, arr[0]*arr[1]*arr[2] = 1*3*1 = 3
dp[2][2]: k=2, arr[1]*arr[2]*arr[3] = 3*1*5 = 15
dp[3][3]: k=3, arr[2]*arr[3]*arr[4] = 1*5*8 = 40
dp[4][4]: k=4, arr[3]*arr[4]*arr[5] = 5*8*1 = 40

── length-2 intervals ──────────────────────────────────
dp[1][2]:  boundaries: arr[0]=1, arr[3]=5
  k=1: 1*3*5 + dp[1][0] + dp[2][2] = 15 + 0 + 15 = 30
  k=2: 1*1*5 + dp[1][1] + dp[3][2] =  5 + 3 +  0 =  8
  → dp[1][2] = 30

dp[2][3]:  boundaries: arr[1]=3, arr[4]=8
  k=2: 3*1*8 + dp[2][1] + dp[3][3] = 24 + 0 + 40 = 64
  k=3: 3*5*8 + dp[2][2] + dp[4][3] = 120 + 15 + 0 = 135
  → dp[2][3] = 135

dp[3][4]:  boundaries: arr[2]=1, arr[5]=1
  k=3: 1*5*1 + dp[3][2] + dp[4][4] =  5 + 0 + 40 = 45
  k=4: 1*8*1 + dp[3][3] + dp[5][4] =  8 + 40 + 0 = 48
  → dp[3][4] = 48

── length-3 intervals ──────────────────────────────────
dp[1][3]:  boundaries: arr[0]=1, arr[4]=8
  k=1: 1*3*8 + dp[1][0] + dp[2][3] =  24 +   0 + 135 = 159
  k=2: 1*1*8 + dp[1][1] + dp[3][3] =   8 +   3 +  40 =  51
  k=3: 1*5*8 + dp[1][2] + dp[4][3] =  40 +  30 +   0 =  70
  → dp[1][3] = 159

dp[2][4]:  boundaries: arr[1]=3, arr[5]=1
  k=2: 3*1*1 + dp[2][1] + dp[3][4] =   3 +   0 + 48 =  51
  k=3: 3*5*1 + dp[2][2] + dp[4][4] =  15 +  15 + 40 =  70
  k=4: 3*8*1 + dp[2][3] + dp[5][4] =  24 + 135 +  0 = 159
  → dp[2][4] = 159

── length-4 interval (answer) ──────────────────────────
dp[1][4]:  boundaries: arr[0]=1, arr[5]=1
  k=1: 1*3*1 + dp[1][0] + dp[2][4] =   3 +   0 + 159 = 162
  k=2: 1*1*1 + dp[1][1] + dp[3][4] =   1 +   3 +  48 =  52
  k=3: 1*5*1 + dp[1][2] + dp[4][4] =   5 +  30 +  40 =  75
  k=4: 1*8*1 + dp[1][3] + dp[5][4] =   8 + 159 +   0 = 167
  → dp[1][4] = 167 ✓
```

### Complexity

| | Complexity |
|---|---|
| **Time** | O(n³) — O(n²) states × O(n) partition loop |
| **Space** | O(n²) dp table + O(n) recursion stack |

Where `n = nums.size()` (before adding sentinels). Since `n ≤ 300`, worst case ~27 million operations — comfortably within limits.

---

## Why Forward Simulation Fails

If you try bursting `k` first (not last), its coin formula uses current neighbors — but those neighbors change as other balloons burst. The subproblems `[i, k-1]` and `[k+1, j]` would share a moving boundary, making them **dependent**, not independent.

The "last burst" framing fixes the boundary: `arr[i-1]` and `arr[j+1]` are outside the interval and guaranteed to exist when `k` is finally burst.

---

## Comparison

| Approach | Time | Space | Verdict |
|---|---|---|---|
| Brute Force | O(4^n / n^(3/2)) | O(n) | TLE for n > ~20 |
| Memoization (Top-Down DP) | O(n³) | O(n²) | ✅ Optimal |

---

## Analogous Problems

| Problem | Why Similar |
|---|---|
| Matrix Chain Multiplication | Same interval DP skeleton, minimize cost |
| Minimum Cost to Cut a Stick (LC 1547) | Interval DP, cost = boundary difference |
| Strange Printer (LC 664) | Interval DP, split at optimal character |
| Remove Boxes (LC 546) | Interval DP with state extension |
