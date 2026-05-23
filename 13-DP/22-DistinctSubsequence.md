# Distinct Subsequences

> **LC 115:** [Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)  
> **Pattern:** String DP (Two string comparison)  
> **Striver DP:** #32

---

## Problem

Given strings `s` and `t`, return the number of distinct subsequences of `s` which equals `t`.

```
s = "rabbbit", t = "rabbit"
Answer: 3

s = "babgbag", t = "bag"
Answer: 5
```

---

## Intuition

At each position `(i, j)`, compare `s[i]` with `t[j]`:

```
Match:     two choices:
           - Use s[i] to match t[j] → both move back → (i-1, j-1)
           - Skip s[i], find another match → i moves back, j stays → (i-1, j)
           Total = both paths added together

Mismatch:  s[i] can't match t[j] → skip s[i] → (i-1, j)
           Only one path
```

Key difference from LCS: we're **counting** paths, not maximizing length. So we **add** instead of taking max.

---

## Gotchas

1. **Base case order matters:** check `j < 0` before `i < 0`. If both exhaust simultaneously, that's a valid match (return 1). Checking `i < 0` first returns 0 incorrectly.
2. **Compare `s[i]` with `t[j]`**, not `s[i]` with `s[j]` — easy typo.
3. **Overflow:** answer can be very large. Problem guarantees it fits in 32-bit int, but intermediate sums can overflow with some inputs.

---

## M-1: Pure Recursion (Brute Force)

> TC = O(2^n) — at each match, two branches  
> SC = O(n + m) — recursion depth

```cpp
class Solution {
    int f(int i, int j, string &s, string &t) {
        if (j < 0) return 1;   // all of t matched
        if (i < 0) return 0;   // s exhausted, t remains

        if (s[i] == t[j])
            return f(i - 1, j - 1, s, t) + f(i - 1, j, s, t);

        return f(i - 1, j, s, t);
    }

public:
    int numDistinct(string s, string t) {
        return f(s.size() - 1, t.size() - 1, s, t);
    }
};
```

---

## M-2: Memoization (Top-Down DP)

State: `dp[i][j]` = number of ways to form `t[0..j]` from `s[0..i]`.

> TC = O(n × m) — n × m states, O(1) each  
> SC = O(n × m) table + O(n + m) stack

```cpp
class Solution {
    int f(int i, int j, string &s, string &t, vector<vector<int>> &dp) {
        if (j < 0) return 1;
        if (i < 0) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        if (s[i] == t[j])
            return dp[i][j] = f(i - 1, j - 1, s, t, dp) + f(i - 1, j, s, t, dp);

        return dp[i][j] = f(i - 1, j, s, t, dp);
    }

public:
    int numDistinct(string &s, string &t) {
        int n = s.size(), m = t.size();
        if (m > n) return 0;
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return f(n - 1, m - 1, s, t, dp);
    }
};
```

---

## M-3: Tabulation (Bottom-Up DP)

1-indexed: `dp[i][j]` = ways to form `t[0..j-1]` from `s[0..i-1]`.

**Base cases:**
```
dp[i][0] = 1    for all i (empty t = 1 way: pick nothing)
dp[0][j] = 0    for j > 0 (empty s, non-empty t = 0 ways)
```

**Transition:**
```
match:     dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
                       use s[i]       skip s[i]

mismatch:  dp[i][j] = dp[i-1][j]
                       skip s[i]
```

> TC = O(n × m)  
> SC = O(n × m)

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(m + 1, 0));

        for (int i = 0; i <= n; i++)
            dp[i][0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }
        return dp[n][m];
    }
};
```

---

## M-4: Space Optimized (Single Row)

Every cell depends on previous row only: `dp[i-1][j-1]` and `dp[i-1][j]`. Use single array, traverse **right to left** to preserve `dp[j-1]` before overwriting.

> TC = O(n × m)  
> SC = O(m)

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<unsigned long long> dp(m + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {  // right to left
                if (s[i - 1] == t[j - 1])
                    dp[j] += dp[j - 1];
                // else dp[j] stays same (= dp[i-1][j])
            }
        }
        return dp[m];
    }
};
```

---

## Dry Run

```
s = "babgbag", t = "bag"

      ""  b  a  g
  ""   1  0  0  0
  b    1  1  0  0
  a    1  1  1  0
  b    1  2  1  0
  g    1  2  1  1
  b    1  3  1  1
  a    1  3  4  1
  g    1  3  4  5

Key cells:
  (1,1): 'b'=='b' → dp[0][0]+dp[0][1] = 1+0 = 1
  (3,1): 'b'=='b' → dp[2][0]+dp[2][1] = 1+1 = 2  (two 'b's found so far)
  (5,1): 'b'=='b' → dp[4][0]+dp[4][1] = 1+2 = 3  (three 'b's found)
  (6,2): 'a'=='a' → dp[5][1]+dp[5][2] = 3+1 = 4  (3 b's × available a's)
  (7,3): 'g'=='g' → dp[6][2]+dp[6][3] = 4+1 = 5

Answer = dp[7][3] = 5 ✓

The 5 subsequences:
  ba_g_ag  → indices 0,1,3
  ba_gb_g  → indices 0,1,5 (wait, that's not right)
  
  Actually: b(0)a(1)g(3), b(0)a(1)g(6), b(0)a(5)g(6),
            b(2)a(5)g(6), b(4)a(5)g(6)
```

---

## Comparison with LCS

| | LCS | Distinct Subsequences |
|---|---|---|
| Goal | Max length | Count ways |
| Match | `1 + dp[i-1][j-1]` | `dp[i-1][j-1] + dp[i-1][j]` |
| Mismatch | `max(dp[i-1][j], dp[i][j-1])` | `dp[i-1][j]` |
| Combine | max | add |

Key insight: in LCS both strings can skip. Here only `s` can skip (we must use all of `t`). That's why mismatch only has `dp[i-1][j]` — we can skip `s[i]` but never skip `t[j]`.

---

## Complexity Summary

| Approach | Time | Space |
|----------|------|-------|
| Pure Recursion | O(2^n) | O(n + m) |
| Memoization | O(n × m) | O(n × m) |
| Tabulation | O(n × m) | O(n × m) |
| Space Optimized | O(n × m) | O(m) |

---

## Bugs Encountered

1. Compared `s[i]` with `s[j]` instead of `t[j]` → comparing string with itself
2. Checked `i < 0` before `j < 0` → simultaneous exhaustion returned 0 instead of 1
