# Longest Common Subsequence

> **LC 1143:** [Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)  
> **Pattern:** String DP (Two string comparison)  
> **Striver DP:** #25

---

## Problem

Given two strings `s1` and `s2`, return the length of their longest common subsequence. A subsequence is a sequence that can be derived by deleting some (or no) characters without changing the order.

```
s1 = "abcde", s2 = "ace"
Answer: 3 ("ace")

s1 = "abc", s2 = "def"
Answer: 0 (no common subsequence)
```

---

## Gotchas

1. **Store on match:** `return 1 + f(...)` without storing in `dp[i][j]` → matched cells recompute every time → TLE.
2. **Pass strings by reference:** `string s1` copies the entire string on every recursive call. Use `string &s1`.
3. **Syntax:** `dp[i][j] =return expr` is invalid C++. Use `return dp[i][j] = expr`.

---

## M-1: Pure Recursion (Brute Force)

Compare characters at `i` and `j`. If they match, both advance. If not, try advancing each one separately and take the max.

> TC = O(2^(n+m)) — at each mismatch, two branches  
> SC = O(n + m) — recursion depth

```cpp
class Solution {
    int f(int i, int j, int n, int m, string &s1, string &s2) {
        if (i >= n || j >= m) return 0;

        if (s1[i] == s2[j])
            return 1 + f(i + 1, j + 1, n, m, s1, s2);

        return max(f(i, j + 1, n, m, s1, s2),
                   f(i + 1, j, n, m, s1, s2));
    }

public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.length(), m = text2.size();
        return f(0, 0, n, m, text1, text2);
    }
};
```

---

## M-2: Memoization (Top-Down DP)

State: `dp[i][j]` = LCS length of `s1[i..n-1]` and `s2[j..m-1]`.

> TC = O(n × m) — n × m states, O(1) each  
> SC = O(n × m) table + O(n + m) stack

```cpp
class Solution {
    int f(int i, int j, int n, int m, string &s1, string &s2,
          vector<vector<int>> &dp) {
        if (i >= n || j >= m) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        if (s1[i] == s2[j])
            return dp[i][j] = 1 + f(i + 1, j + 1, n, m, s1, s2, dp);

        return dp[i][j] = max(f(i, j + 1, n, m, s1, s2, dp),
                              f(i + 1, j, n, m, s1, s2, dp));
    }

public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.length(), m = text2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return f(0, 0, n, m, text1, text2, dp);
    }
};
```

---

## M-3: Tabulation (Bottom-Up DP)

`dp[i][j]` = LCS length of `s1[0..i-1]` and `s2[0..j-1]` (1-indexed for cleaner base case).

**Transition:**
```
match:     dp[i][j] = 1 + dp[i-1][j-1]
mismatch:  dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

**Base case:** `dp[0][j] = 0` and `dp[i][0] = 0` (empty string has LCS 0).

> TC = O(n × m)  
> SC = O(n × m)

```cpp
class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }
};
```

---

## M-4: Space Optimized (Two Rows)

Current row only depends on previous row. Use two 1D arrays.

> TC = O(n × m)  
> SC = O(m)

```cpp
class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<int> prev(m + 1, 0), curr(m + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1])
                    curr[j] = 1 + prev[j - 1];
                else
                    curr[j] = max(prev[j], curr[j - 1]);
            }
            prev = curr;
        }
        return prev[m];
    }
};
```

---

## Dry Run

```
s1 = "abcde", s2 = "ace"

--- Tabulation (1-indexed) ---

      ""  a  c  e
  ""   0  0  0  0
  a    0  1  1  1
  b    0  1  1  1
  c    0  1  2  2
  d    0  1  2  2
  e    0  1  2  3

Key cells:
  (1,1): s1[0]='a' == s2[0]='a' → 1 + dp[0][0] = 1
  (3,2): s1[2]='c' == s2[1]='c' → 1 + dp[2][1] = 2
  (5,3): s1[4]='e' == s2[2]='e' → 1 + dp[4][2] = 3

Answer = dp[5][3] = 3 ✓ (LCS = "ace")
```

---

## Printing the LCS

Backtrack from `dp[n][m]`:

```cpp
string printLCS(string &s1, string &s2, vector<vector<int>> &dp) {
    int i = s1.size(), j = s2.size();
    string lcs = "";

    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs = s1[i - 1] + lcs;
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    return lcs;
}
```

---

## LCS Family — Related Problems

| Problem | How it uses LCS | LC# |
|---------|----------------|-----|
| Longest Common Substring | Reset to 0 on mismatch instead of max | GFG |
| Shortest Common Supersequence | `n + m - LCS` for length, backtrack for string | LC 1092 |
| Min Insertions/Deletions to Convert | Deletions = `n - LCS`, Insertions = `m - LCS` | GFG |
| Longest Palindromic Subsequence | `LCS(s, reverse(s))` | LC 516 |
| Min Insertions for Palindrome | `n - LPS` | LC 1312 |

---

## Complexity Summary

| Approach | Time | Space |
|----------|------|-------|
| Pure Recursion | O(2^(n+m)) | O(n + m) |
| Memoization | O(n × m) | O(n × m) |
| Tabulation | O(n × m) | O(n × m) |
| Space Optimized | O(n × m) | O(m) |

---

## Bugs Encountered

1. Match branch returned without storing in `dp[i][j]` → matched cells recomputed every visit → TLE
2. Strings passed by value → full copy on every recursive call → TLE on large inputs
3. `dp[i][j] =return expr` → invalid syntax, use `return dp[i][j] = expr`
