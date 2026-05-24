# Shortest Common Supersequence

> **LC 1092:** [Shortest Common Supersequence](https://leetcode.com/problems/shortest-common-supersequence/)  
> **Pattern:** String DP (LCS + Backtracking)  
> **Striver DP:** #31

---

## Problem

Given two strings `s1` and `s2`, return the shortest string that has both `s1` and `s2` as subsequences.

```
s1 = "abac", s2 = "cab"
Answer: "cabac" (length 5)

s1 = "brute", s2 = "groot"
Answer: "bgruoote" (length 8)
```

---

## Key Insight

SCS length = `n + m - LCS`. The LCS characters are shared between both strings — include them once instead of twice.

```
s1 = "abac" (4 chars)
s2 = "cab"  (3 chars)
LCS = "ab"  (2 chars)

SCS = 4 + 3 - 2 = 5

Breakdown:
  LCS chars (a, b):     included ONCE → covers both strings
  Extra from s1 (a, c): included separately
  Extra from s2 (c):    included separately
  Total: 2 + 2 + 1 = 5
```

---

## Approach: LCS Table + Backtracking

Two phases:

**Phase 1:** Build standard LCS table.

**Phase 2:** Backtrack from `(n, m)` to `(0, 0)`, deciding which character to add:

```
Match: s1[i-1] == s2[j-1]
   LCS character → add ONCE, move both: i--, j--
   "Shared character. One copy covers both strings."

UP wins: dp[i-1][j] > dp[i][j-1]
   dp[i][j] got its value from dp[i-1][j]
   → s1[i-1] was skipped during LCS → extra from s1
   → add s1[i-1], move i--

LEFT wins: dp[i][j-1] >= dp[i-1][j]
   dp[i][j] got its value from dp[i][j-1]
   → s2[j-1] was skipped during LCS → extra from s2
   → add s2[j-1], move j--
```

After the main loop, add any remaining characters from `s1` or `s2`. Reverse the result (built bottom-up).

---

## Why Direction Tells You Which String

During LCS table construction:

```cpp
dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
```

`dp[i-1][j]` = "LCS when we skip s1[i-1]" → moved UP.
`dp[i][j-1]` = "LCS when we skip s2[j-1]" → moved LEFT.

During backtracking, you reverse this: if the value came from UP, then `s1[i-1]` was skipped from LCS → it's an extra character from `s1` → must include it in the supersequence.

```
                dp[i-1][j] = 3
                    ↓  "skipped s1[i-1]"
dp[i][j-1] = 2 → dp[i][j] = 3
"skipped s2[j-1]"     ↑
                    value came from UP (3 > 2)
                    s1[i-1] is extra → add it
```

---

## Solution

> TC = O(n × m) — table construction dominates  
> SC = O(n × m) — DP table

```cpp
class Solution {
public:
    string shortestCommonSupersequence(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 0; i <= n; i++) dp[i][0] = 0;
        for (int j = 0; j <= m; j++) dp[0][j] = 0;

        // Phase 1: Build LCS table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }

        // Phase 2: Backtrack to build SCS
        int i = n, j = m;
        string res = "";

        while (i > 0 && j > 0) {
            if (s1[i - 1] == s2[j - 1]) {
                res += s1[i - 1];      // LCS char → add once
                i--; j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                res += s1[i - 1];      // extra from s1
                i--;
            } else {
                res += s2[j - 1];      // extra from s2
                j--;
            }
        }

        // remaining characters
        while (i > 0) { res += s1[i - 1]; i--; }
        while (j > 0) { res += s2[j - 1]; j--; }

        // built bottom-up, so reverse
        reverse(res.begin(), res.end());
        return res;
    }
};
```

---

## Dry Run

```
s1 = "abac", s2 = "cab"

LCS table:
      ""  c  a  b
  ""   0  0  0  0
  a    0  0  1  1
  b    0  0  1  2
  a    0  0  1  2
  c    0  1  1  2

LCS = "ab", length 2

Backtracking from (4, 3):

Step 1: i=4, j=3
  s1[3]='c' != s2[2]='b'
  dp[3][3]=2 vs dp[4][2]=1 → UP wins
  s1[3]='c' is extra from s1 → add 'c'
  i=3
  res: "c"

Step 2: i=3, j=3
  s1[2]='a' != s2[2]='b'
  dp[2][3]=2 vs dp[3][2]=1 → UP wins
  s1[2]='a' is extra from s1 → add 'a'
  i=2
  res: "ca"

Step 3: i=2, j=3
  s1[1]='b' == s2[2]='b' → MATCH (LCS char)
  add 'b' ONCE
  i=1, j=2
  res: "cab"

Step 4: i=1, j=2
  s1[0]='a' == s2[1]='a' → MATCH (LCS char)
  add 'a' ONCE
  i=0, j=1
  res: "caba"

Step 5: i=0, exit main loop
  Remaining s2: j=1 → s2[0]='c' → add 'c'
  res: "cabac"

Reverse: "cabac" → "cabac"

Verify:
  s1 = "abac" subsequence of "cabac"?
    c [a] [b] [a] [c] → ✓

  s2 = "cab" subsequence of "cabac"?
    [c] [a] [b] a c → ✓

  Length = 5 = 4 + 3 - 2 ✓
```

---

## What Went Where

```
SCS:    c   a   b   a   c
        ↑   ↑   ↑   ↑   ↑
        s2  LCS LCS s1  s1
        
LCS chars (a, b):  included once, covers both strings
Extra from s1 (a, c): included to preserve s1 as subsequence
Extra from s2 (c): included to preserve s2 as subsequence
```

---

## Related Problems

| Problem | Relation | LC# |
|---------|----------|-----|
| Longest Common Subsequence | SCS uses LCS table | LC 1143 |
| Print LCS | Same backtracking pattern, but only collect matches | LC 1143 |
| Print All LCS | Branch at ties during backtracking | GFG |
| Min Insertions/Deletions | Deletions = `n - LCS`, Insertions = `m - LCS` | GFG |

---

## Complexity Summary

| | Time | Space |
|---|------|-------|
| LCS table | O(n × m) | O(n × m) |
| Backtracking | O(n + m) | O(n + m) for result |
| Reverse | O(n + m) | — |
| **Total** | **O(n × m)** | **O(n × m)** |
