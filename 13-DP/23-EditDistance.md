# Edit Distance

> **LC 72:** [Edit Distance](https://leetcode.com/problems/edit-distance/)  
> **Pattern:** String DP (Two string comparison)  
> **Striver DP:** #33

---

## Problem

Given two strings `s` and `t`, return the minimum number of operations to convert `s` into `t`. Three operations allowed: insert, delete, replace — each costs 1.

```
s = "horse", t = "ros"
Answer: 3 (horse → rorse → rose → ros)

s = "intention", t = "execution"
Answer: 5
```

---

## Intuition

At each position `(i, j)`, compare `s[i]` with `t[j]`:

```
Match:     characters are same → no operation needed, move both back
Mismatch:  pick the cheapest of 3 operations:
           - Insert:  add t[j] to s → j shrinks, i stays    → (i, j-1)
           - Delete:  remove s[i]  → i shrinks, j stays     → (i-1, j)
           - Replace: change s[i] to t[j] → both shrink     → (i-1, j-1)
```

---

## M-1: Pure Recursion (Brute Force)

> TC = O(3^(n+m)) — three branches at each mismatch  
> SC = O(n + m) — recursion depth

```cpp
class Solution {
    int f(int i, int j, string &s, string &t) {
        if (i < 0) return j + 1;  // s exhausted, insert remaining t
        if (j < 0) return i + 1;  // t exhausted, delete remaining s

        if (s[i] == t[j])
            return f(i - 1, j - 1, s, t);

        return 1 + min({f(i - 1, j, s, t),      // delete
                        f(i, j - 1, s, t),        // insert
                        f(i - 1, j - 1, s, t)});  // replace
    }

public:
    int minDistance(string s, string t) {
        return f(s.size() - 1, t.size() - 1, s, t);
    }
};
```

---

## M-2: Memoization (Top-Down DP)

State: `dp[i][j]` = min operations to convert `s[0..i]` into `t[0..j]`.

> TC = O(n × m) — n × m states, O(1) each  
> SC = O(n × m) table + O(n + m) stack

```cpp
class Solution {
    int f(int i, int j, string &s, string &t, vector<vector<int>> &dp) {
        if (i < 0) return j + 1;
        if (j < 0) return i + 1;
        if (dp[i][j] != -1) return dp[i][j];

        if (s[i] == t[j])
            return dp[i][j] = f(i - 1, j - 1, s, t, dp);

        return dp[i][j] = 1 + min({f(i - 1, j, s, t, dp),
                                    f(i, j - 1, s, t, dp),
                                    f(i - 1, j - 1, s, t, dp)});
    }

public:
    int minDistance(string s, string t) {
        int n = s.size(), m = t.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return f(n - 1, m - 1, s, t, dp);
    }
};
```

---

## M-3: Tabulation (Bottom-Up DP)

1-indexed: `dp[i][j]` = min operations for `s[0..i-1]` → `t[0..j-1]`.

**Base cases:**
```
dp[i][0] = i    (delete all i chars from s)
dp[0][j] = j    (insert all j chars of t)
```

**Transition:**
```
match:     dp[i][j] = dp[i-1][j-1]
mismatch:  dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
                            delete      insert       replace
```

> TC = O(n × m)  
> SC = O(n × m)

```cpp
class Solution {
public:
    int minDistance(string s, string t) {
        int n = s.size(), m = t.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 0; i <= n; i++) dp[i][0] = i;
        for (int j = 0; j <= m; j++) dp[0][j] = j;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = 1 + min({dp[i - 1][j],
                                         dp[i][j - 1],
                                         dp[i - 1][j - 1]});
            }
        }
        return dp[n][m];
    }
};
```

---

## M-4: Space Optimized (Two Rows)

Current row depends on previous row only. Need to save `dp[i-1][j-1]` (diagonal) before overwriting.

> TC = O(n × m)  
> SC = O(m)

```cpp
class Solution {
public:
    int minDistance(string s, string t) {
        int n = s.size(), m = t.size();
        vector<int> prev(m + 1), curr(m + 1);

        for (int j = 0; j <= m; j++) prev[j] = j;

        for (int i = 1; i <= n; i++) {
            curr[0] = i;
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == t[j - 1])
                    curr[j] = prev[j - 1];
                else
                    curr[j] = 1 + min({prev[j],       // delete
                                        curr[j - 1],   // insert
                                        prev[j - 1]}); // replace
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
s = "horse", t = "ros"

      ""  r  o  s
  ""   0  1  2  3
  h    1  1  2  3
  o    2  2  1  2
  r    3  2  2  2
  s    4  3  3  2
  e    5  4  4  3

Key cells:
  (1,1): 'h'!='r' → 1 + min(dp[0][1], dp[1][0], dp[0][0])
                    = 1 + min(1, 1, 0) = 1  (replace h→r)

  (2,2): 'o'=='o' → dp[1][1] = 1  (match, no cost)

  (3,1): 'r'=='r' → dp[2][0] = 2  (match, no cost)

  (5,3): 'e'!='s' → 1 + min(dp[4][3], dp[5][2], dp[4][2])
                    = 1 + min(2, 4, 3) = 3

Answer = dp[5][3] = 3 ✓
Operations: horse → rorse (replace h) → rose (delete r) → ros (delete e)
```

---

## Understanding the Three Operations

```
dp[i-1][j]   = DELETE s[i]
               "s was longer, remove a char to catch up"
               s shrinks by 1, t stays

dp[i][j-1]   = INSERT t[j] into s
               "t has an extra char, add it to s"
               s stays, t shrinks by 1

dp[i-1][j-1] = REPLACE s[i] with t[j]
               "swap this char, both move on"
               both shrink by 1
```

Visual:
```
          t[j]
           ↑
    dp[i-1][j-1]  dp[i-1][j]
     (replace)     (delete)
           ↘          ↓
    dp[i][j-1] → dp[i][j]
     (insert)    (answer)
```

---

## Related Problems

| Problem | Relation | LC# |
|---------|----------|-----|
| Delete Operation for Two Strings | Only insert + delete (no replace) | LC 583 |
| Min Steps to Make Anagram | Frequency-based, not positional | LC 1347 |
| One Edit Distance | Check if exactly 1 operation | LC 161 |
| Wildcard Matching | Insert/match with * and ? | LC 44 |

---

## Complexity Summary

| Approach | Time | Space |
|----------|------|-------|
| Pure Recursion | O(3^(n+m)) | O(n + m) |
| Memoization | O(n × m) | O(n × m) |
| Tabulation | O(n × m) | O(n × m) |
| Space Optimized | O(n × m) | O(m) |
