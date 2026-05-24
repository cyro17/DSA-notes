# Longest Palindromic Subsequence

> **LC 516:** [Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/)  
> **Pattern:** String DP (LCS reduction)  
> **Striver DP:** #28

---

## Problem

Given a string `s`, find the length of its longest palindromic subsequence.

```
s = "bbabcbcab"
Answer: 7 ("babcbab")

s = "cbbd"
Answer: 2 ("bb")
```

---

## Key Insight

A palindromic subsequence reads the same forwards and backwards. So the longest palindromic subsequence of `s` is the **LCS of `s` and `reverse(s)`**.

```
s = "bbabcbcab"
t = "bacbcbabb"  (reversed)

LCS(s, t) = "babcbab" → length 7 ✓
```

Why this works: any common subsequence between `s` and its reverse must read the same in both directions — that's a palindrome by definition.

---

## M-1: Pure Recursion (Brute Force)

Reduce to LCS of `s` and `reverse(s)`.

> TC = O(2^n) — LCS without memoization  
> SC = O(n) — recursion depth

```cpp
class Solution {
    int f(int i, int j, string &s, string &t) {
        if (i >= (int)s.size() || j >= (int)t.size()) return 0;

        if (s[i] == t[j])
            return 1 + f(i + 1, j + 1, s, t);

        return max(f(i + 1, j, s, t), f(i, j + 1, s, t));
    }

public:
    int longestPalindromeSubseq(string s) {
        string t = s;
        reverse(t.begin(), t.end());
        return f(0, 0, s, t);
    }
};
```

---

## M-2: Memoization (Top-Down DP)

State: `dp[i][j]` = LCS length of `s[i..n-1]` and `t[j..n-1]`.

> TC = O(n²) — n × n states, O(1) each  
> SC = O(n²) table + O(n) stack

```cpp
class Solution {
    int f(int i, int j, string &s, string &t, vector<vector<int>> &dp) {
        int n = s.size(), m = t.size();
        if (i >= n || j >= m) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        int match = 0;
        if (s[i] == t[j])
            match = 1 + f(i + 1, j + 1, s, t, dp);

        int nm = max(f(i + 1, j, s, t, dp), f(i, j + 1, s, t, dp));
        return dp[i][j] = max(match, nm);
    }

public:
    int longestPalindromeSubseq(string s) {
        string t = s;
        reverse(t.begin(), t.end());
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        return f(0, 0, s, t, dp);
    }
};
```

**Note on the match handling:** the code takes `max(match, nm)` which is correct but redundant — when `s[i] == t[j]`, the match path is always ≥ the skip paths. The standard LCS form with `if-else` is cleaner:

```cpp
if (s[i] == t[j])
    return dp[i][j] = 1 + f(i + 1, j + 1, s, t, dp);
return dp[i][j] = max(f(i + 1, j, s, t, dp), f(i, j + 1, s, t, dp));
```

---

## M-3: Tabulation (Bottom-Up DP)

Standard LCS table on `s` and `reverse(s)`.

> TC = O(n²)  
> SC = O(n²)

```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        string t = s;
        reverse(t.begin(), t.end());
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[n][n];
    }
};
```

---

## M-4: Space Optimized (Two Rows)

> TC = O(n²)  
> SC = O(n)

```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        string t = s;
        reverse(t.begin(), t.end());
        int n = s.size();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1])
                    curr[j] = 1 + prev[j - 1];
                else
                    curr[j] = max(prev[j], curr[j - 1]);
            }
            prev = curr;
        }
        return prev[n];
    }
};
```

---

## Dry Run

```
s = "bbabcbcab"
t = "bacbcbabb" (reversed)

      ""  b  a  c  b  c  b  a  b  b
  ""   0  0  0  0  0  0  0  0  0  0
  b    0  1  1  1  1  1  1  1  1  1
  b    0  1  1  1  2  2  2  2  2  2
  a    0  1  2  2  2  2  2  3  3  3
  b    0  1  2  2  3  3  3  3  4  4
  c    0  1  2  3  3  4  4  4  4  4
  b    0  1  2  3  4  4  5  5  5  5
  c    0  1  2  3  4  5  5  5  5  5
  a    0  1  2  3  4  5  5  6  6  6
  b    0  1  2  3  4  5  6  6  7  7

Answer = dp[9][9] = 7
LPS = "babcbab" ✓
```

---

## Direct Approach (Without Reversing)

Can also solve directly on `s` using interval DP:

`dp[i][j]` = LPS length of `s[i..j]`

```
Base:      dp[i][i] = 1 (single char is palindrome)
Match:     dp[i][j] = 2 + dp[i+1][j-1]   if s[i] == s[j]
Mismatch:  dp[i][j] = max(dp[i+1][j], dp[i][j-1])
```

```cpp
int longestPalindromeSubseq(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) dp[i][i] = 1;

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j])
                dp[i][j] = 2 + dp[i + 1][j - 1];
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    return dp[0][n - 1];
}
```

Same O(n²) complexity but avoids creating the reversed string.

---

## Related Problems

| Problem | Relation | LC# |
|---------|----------|-----|
| Longest Palindromic Substring | Contiguous, not subsequence | LC 5 |
| Min Insertions for Palindrome | `n - LPS(s)` | LC 1312 |
| Palindromic Substrings (Count) | Count all, not just longest | LC 647 |
| Longest Common Subsequence | LPS = LCS(s, rev(s)) | LC 1143 |

---

## Complexity Summary

| Approach | Time | Space |
|----------|------|-------|
| Pure Recursion | O(2^n) | O(n) |
| Memoization | O(n²) | O(n²) |
| Tabulation | O(n²) | O(n²) |
| Space Optimized | O(n²) | O(n) |
