# Print All LCS Sequences

> **GFG:** [Print All LCS Sequences](https://www.geeksforgeeks.org/problems/print-all-lcs-sequences3413/1)  
> **Pattern:** String DP (LCS + Backtracking)  
> **Striver DP:** #26

---

## Problem

Given two strings `s1` and `s2`, return all distinct longest common subsequences in sorted order.

```
s1 = "abaaa", s2 = "baaa"
Answer: ["baaa"]

s1 = "abcbdab", s2 = "bdcab"
Answer: ["bcab", "bdab"]
```

---

## Key Insight

You already know how to find LCS length using a DP table. To find **all** LCS strings, backtrack from `(n, m)` to `(0, 0)` — but instead of making one choice at each mismatch cell, **explore all valid choices**. Multiple LCS are born when both UP and LEFT give the same dp value.

---

## Intuition — The Maze Analogy

Think of the DP table as a maze. Start at `(n, m)`, reach `(0, 0)`. Every complete path = one LCS.

```
At each cell (i, j):

Match: s1[i-1] == s2[j-1]
   Only one door → DIAGONAL
   Collect this character
   "This character is part of the LCS. Take it."

Mismatch: s1[i-1] != s2[j-1]
   Check which doors are open:
   
   dp[i-1][j] > dp[i][j-1]  →  only UP door open (one path)
   dp[i-1][j] < dp[i][j-1]  →  only LEFT door open (one path)
   dp[i-1][j] == dp[i][j-1] →  BOTH doors open → BRANCH!
                                 This is where multiple LCS come from.
```

---

## Approach

**Phase 1:** Build standard LCS table (tabulation or recursive memo).

**Phase 2:** DFS backtrack from `(n, m)`:
- Match → take character, go diagonal (no choice)
- Mismatch → branch into UP and/or LEFT (whichever preserves LCS length)
- At `(0, 0)` → reverse collected string, add to result set

`set<string>` handles deduplication automatically.

---

## Solution

> TC = O(n × m + k × L) where k = number of distinct LCS, L = LCS length  
> SC = O(n × m) for table + O(k × L) for results

```cpp
class Solution {
    void backtrack(int i, int j, string &s1, string &s2,
                   vector<vector<int>> &dp, string curr,
                   set<string> &result) {
        if (i == 0 || j == 0) {
            reverse(curr.begin(), curr.end());
            result.insert(curr);
            return;
        }

        if (s1[i - 1] == s2[j - 1]) {
            // match → must take this character, go diagonal
            curr += s1[i - 1];
            backtrack(i - 1, j - 1, s1, s2, dp, curr, result);
        } else {
            // explore all valid directions
            if (dp[i - 1][j] == dp[i][j])
                backtrack(i - 1, j, s1, s2, dp, curr, result);
            if (dp[i][j - 1] == dp[i][j])
                backtrack(i, j - 1, s1, s2, dp, curr, result);
        }
    }

public:
    vector<string> all_longest_common_subsequences(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Phase 1: Build LCS table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        // Phase 2: Backtrack to find all LCS
        set<string> result;
        backtrack(n, m, s1, s2, dp, "", result);

        return vector<string>(result.begin(), result.end());
    }
};
```

---

## Dry Run

```
s1 = "abcbdab", s2 = "bdcab"

LCS table:
      ""  b  d  c  a  b
  ""   0  0  0  0  0  0
  a    0  0  0  0  1  1
  b    0  1  1  1  1  2
  c    0  1  1  2  2  2
  b    0  1  1  2  2  3
  d    0  1  2  2  2  3
  a    0  1  2  2  3  3
  b    0  1  2  2  3  4

LCS length = 4

Backtracking from (7, 5):

(7,5): s1[6]='b' == s2[4]='b' → MATCH
       take 'b', go (6,4)

(6,4): s1[5]='a' == s2[3]='a' → MATCH
       take 'a', go (5,3)

(5,3): s1[4]='d' != s2[2]='c'
       dp[4][3] = 2 == dp[5][3] = 2 ✓ → UP valid
       dp[5][2] = 2 == dp[5][3] = 2 ✓ → LEFT valid
       BOTH equal → BRANCH!

  ┌─ Branch A (UP → (4,3)):
  │   (4,3): s1[3]='b' != s2[2]='c'
  │          dp[3][3]=2 == dp[4][3]=2 → UP valid
  │          dp[4][2]=1 != dp[4][3]=2 → LEFT blocked
  │          Go UP → (3,3)
  │   (3,3): s1[2]='c' == s2[2]='c' → MATCH
  │          take 'c', go (2,2)
  │   (2,2): s1[1]='b' != s2[1]='d'
  │          dp[1][2]=0 != dp[2][2]=1 → UP blocked
  │          dp[2][1]=1 == dp[2][2]=1 → LEFT valid
  │          Go LEFT → (2,1)
  │   (2,1): s1[1]='b' == s2[0]='b' → MATCH
  │          take 'b', go (1,0)
  │   (1,0): j=0 → base case
  │          reverse "bacb" → "bcab" ✓
  │
  └─ Branch B (LEFT → (5,2)):
      (5,2): s1[4]='d' == s2[1]='d' → MATCH
             take 'd', go (4,1)
      (4,1): s1[3]='b' == s2[0]='b' → MATCH
             take 'b', go (3,0)
      (3,0): j=0 → base case
             reverse "bdab" → "bdab" ✓

Result: ["bcab", "bdab"]
```

---

## Why Branching Happens

```
At (5,3): dp[4][3] = 2, dp[5][2] = 2

Both equal dp[5][3] = 2. This means:

  Going UP: "we can find an LCS of length 2 by skipping s1[4]='d'"
            → leads to matching 'c' then 'b' → "bcab"

  Going LEFT: "we can find an LCS of length 2 by skipping s2[2]='c'"
              → leads to matching 'd' then 'b' → "bdab"

Two equally valid paths → two different LCS strings.
```

---

## When Does Branching NOT Happen?

```
dp[i-1][j] > dp[i][j-1]  →  UP is strictly better
                              only one valid path, no branch

dp[i-1][j] < dp[i][j-1]  →  LEFT is strictly better
                              only one valid path, no branch
```

Branching only happens at **ties**. More ties in the table = more distinct LCS.

---

## Why set<string>?

Different backtracking paths can produce the same string. Example:

```
s1 = "aa", s2 = "aa"

      ""  a  a
  ""   0  0  0
  a    0  1  1
  a    0  1  2

From (2,2): match 'a' → (1,1): match 'a' → "aa" (only one LCS)

But with s1 = "ab", s2 = "ab":
Only one path → "ab"
```

For strings with repeated characters, different paths through the table can converge to the same LCS. The set deduplicates automatically.

---

## Comparison with Related Problems

| Problem | Backtracking | What to collect |
|---------|-------------|-----------------|
| Print ONE LCS | Single path (pick any valid direction) | Characters at matches |
| Print ALL LCS | Branch at ties, DFS all paths | All distinct strings |
| Shortest Common Supersequence | Single path, add ALL characters | LCS chars once + extras |
| Count distinct LCS | Can't just backtrack — need separate DP | Count, not strings |

---

## Complexity Summary

| Phase | Time | Space |
|-------|------|-------|
| LCS table | O(n × m) | O(n × m) |
| Backtracking | O(k × (n + m)) per path | O(L) recursion stack |
| Deduplication | O(k × L × log k) for set | O(k × L) |
| **Total** | **O(n × m + k × L × log k)** | **O(n × m + k × L)** |

Where k = number of distinct LCS, L = LCS length.
