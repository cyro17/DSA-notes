# Longest Increasing Subsequence

> **LC 300:** [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)  
> **Pattern:** LIS  
> **Striver DP:** #41

---

## Problem

Given an integer array, return the length of the longest strictly increasing subsequence.

```
arr = [10, 9, 2, 5, 3, 7, 101, 18]
Answer: 4 ([2, 3, 7, 101] or [2, 3, 7, 18])

arr = [0, 1, 0, 3, 2, 3]
Answer: 4 ([0, 1, 2, 3])
```

---

## Gotchas

1. **Condition order matters:** check `prev == -1` before `arr[index] > arr[prev]`, otherwise `arr[-1]` is undefined behavior.
2. **`-1` as prev index:** can't use `-1` directly in a DP table. Shift to 0-indexed by using `prev + 1` as the table index.
3. **Binary search approach** gives the LIS **length** correctly, but the `tmp` array is NOT the actual LIS.

---

## M-1: Pure Recursion (Brute Force)

At each index, two choices: pick (if greater than prev) or skip.

> TC = O(2^n) — two branches per element  
> SC = O(n) — recursion depth

```cpp
class Solution {
    int f(int index, int prev, vector<int> &arr) {
        int n = arr.size();
        if (index >= n) return 0;

        int p = 0;
        if (prev == -1 || arr[index] > arr[prev])
            p = 1 + f(index + 1, index, arr);

        int np = f(index + 1, prev, arr);
        return max(p, np);
    }

public:
    int lengthOfLIS(vector<int> &arr) {
        return f(0, -1, arr);
    }
};
```

---

## M-2: Memoization (Top-Down DP)

State: `dp[index][prev + 1]` — shifted by 1 since `prev` starts at `-1`.

> TC = O(n²) — n × (n+1) states, O(1) each  
> SC = O(n²) table + O(n) stack

```cpp
class Solution {
    int f(int index, int prev, vector<int> &arr, vector<vector<int>> &dp) {
        int n = arr.size();
        if (index >= n) return 0;
        if (dp[index][prev + 1] != -1) return dp[index][prev + 1];

        int p = 0;
        if (prev == -1 || arr[index] > arr[prev])
            p = 1 + f(index + 1, index, arr, dp);

        int np = f(index + 1, prev, arr, dp);
        return dp[index][prev + 1] = max(p, np);
    }

public:
    int lengthOfLIS(vector<int> &arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return f(0, -1, arr, dp);
    }
};
```

---

## M-3: Tabulation (Bottom-Up, Classic O(n²))

`dp[i]` = length of LIS ending at index `i`.

For each `i`, check all `j < i` where `arr[j] < arr[i]`.

> TC = O(n²)  
> SC = O(n)

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int> &arr) {
        int n = arr.size();
        vector<int> dp(n, 1);  // every element is an LIS of length 1
        int ans = 1;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
```

---

## M-4: Binary Search (Patience Sorting) — O(n log n)

Maintain a sorted array `tmp`. For each element:
- If greater than `tmp.back()` → extend the LIS, append it
- Otherwise → replace the first element ≥ it (using `lower_bound`)

`tmp` stays sorted and its **length** always equals the current LIS length.

> TC = O(n log n) — n elements × O(log n) binary search each  
> SC = O(n)

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int> &arr) {
        vector<int> tmp;
        int n = arr.size();
        tmp.push_back(arr[0]);
        int len = 1;

        for (int i = 1; i < n; i++) {
            if (arr[i] > tmp.back()) {
                tmp.push_back(arr[i]);
                len++;
            } else {
                int it = lower_bound(tmp.begin(), tmp.end(), arr[i]) - tmp.begin();
                tmp[it] = arr[i];
            }
        }
        return len;
    }
};
```

---

## Why Binary Search Works — Intuition

Think of `tmp` as the **best possible tail** for each LIS length:

```
tmp[0] = smallest tail of all increasing subsequences of length 1
tmp[1] = smallest tail of all increasing subsequences of length 2
...
tmp[k] = smallest tail of all increasing subsequences of length k+1
```

By keeping tails as small as possible, you maximize the chance of extending the LIS with future elements.

---

## Dry Run (Binary Search)

```
arr = [10, 9, 2, 5, 3, 7, 101, 18]

i=0: tmp = [10]                    (start)
i=1: 9 < 10 → replace 10 with 9   tmp = [9]
i=2: 2 < 9  → replace 9 with 2    tmp = [2]
i=3: 5 > 2  → append              tmp = [2, 5]
i=4: 3 < 5  → replace 5 with 3    tmp = [2, 3]
i=5: 7 > 3  → append              tmp = [2, 3, 7]
i=6: 101 > 7 → append             tmp = [2, 3, 7, 101]
i=7: 18 < 101 → replace 101       tmp = [2, 3, 7, 18]

Length = 4 ✓
```

Notice: `tmp = [2, 3, 7, 18]` is a valid LIS, but this isn't always the case. The array maintains correct length, not necessarily the actual LIS.

---

## Dry Run (Tabulation O(n²))

```
arr = [10, 9, 2, 5, 3, 7, 101, 18]
dp  = [ 1, 1, 1, 1, 1, 1,   1,  1]  (initial)

i=1: no j < 1 with arr[j] < 9           dp[1] = 1
i=2: no j < 2 with arr[j] < 2           dp[2] = 1
i=3: arr[2]=2 < 5 → dp[3] = dp[2]+1 = 2    dp[3] = 2
i=4: arr[2]=2 < 3 → dp[4] = dp[2]+1 = 2    dp[4] = 2
i=5: arr[2]=2 < 7 → 2, arr[3]=5 < 7 → 3, arr[4]=3 < 7 → 3
                                             dp[5] = 3
i=6: arr[5]=7 < 101 → dp[5]+1 = 4           dp[6] = 4
i=7: arr[5]=7 < 18 → dp[5]+1 = 4            dp[7] = 4

dp  = [1, 1, 1, 2, 2, 3, 4, 4]
Answer = max(dp) = 4 ✓
```

---

## Printing the LIS

Use the O(n²) approach and backtrack:

```cpp
vector<int> printLIS(vector<int> &arr) {
    int n = arr.size();
    vector<int> dp(n, 1), parent(n, -1);
    int maxLen = 1, maxIdx = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
            maxIdx = i;
        }
    }

    vector<int> lis;
    for (int i = maxIdx; i != -1; i = parent[i])
        lis.push_back(arr[i]);
    reverse(lis.begin(), lis.end());
    return lis;
}
```

---

## LIS Family

| Problem | Twist | LC# |
|---------|-------|-----|
| Longest Decreasing Subsequence | Reverse the comparison | GFG |
| Longest String Chain | Sort by length, predecessor check | LC 1048 |
| Longest Bitonic Subsequence | LIS from left + LDS from right - 1 | GFG |
| Number of LIS | Track count[] alongside dp[] | LC 673 |
| Russian Doll Envelopes | Sort by w asc, h desc → LIS on h | LC 354 |
| Largest Divisible Subset | LIS with divisibility condition | LC 368 |

---

## Complexity Summary

| Approach | Time | Space |
|----------|------|-------|
| Pure Recursion | O(2^n) | O(n) |
| Memoization | O(n²) | O(n²) |
| Tabulation | O(n²) | O(n) |
| Binary Search | **O(n log n)** | O(n) |
