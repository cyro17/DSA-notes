# Minimum Window Subsequence

Find the **minimum window substring** of `s` such that `t` is a **subsequence** of that window.

> Return the minimum window. If no such window exists, return `""`.

---

## Substring vs Subsequence — Key Distinction

```
t = "AB"

Window "BA"  → ❌ not a subsequence (order matters)
Window "ACB" → ✅ subsequence (A appears before B, gaps allowed)
Window "AB"  → ✅ subsequence
```

Unlike the Minimum Window Substring problem — **order matters here**. Every character of `t` must appear in `s` in the same relative order.

---

## Is Subsequence Check

Both approaches rely on this helper — match `t` left to right inside a window `[i, j]`:

```cpp
bool isSubsequence(string& s, int i, int j, string& t) {
    int k = 0;
    while (i <= j && k < t.size()) {
        if (s[i] == t[k]) k++;
        i++;
    }
    return k == t.size();  // all chars of t matched in order
}
```

---

## Approach 1 — Brute Force

### Idea

Generate all substrings of `s`. For each, check if `t` is a subsequence. Track the minimum length valid window.

### Why `break` after first valid window per `i`?

For a fixed starting index `i`, once you find the earliest `j` where `[i,j]` is valid — any further extension of `j` only makes the window **longer**. No point continuing.

```
i=1, s="abcdebdde", t="bde"
  j=1: "b"    → ❌
  j=2: "bc"   → ❌
  j=3: "bcd"  → ❌
  j=4: "bcde" → ✅ len=4, break   ← don't check j=5,6,7...
```

### Implementation (C++)

```cpp
class Solution {
public:
    bool isSubsequence(string& s, int i, int j, string& t) {
        int k = 0;
        while (i <= j && k < t.size()) {
            if (s[i] == t[k]) k++;
            i++;
        }
        return k == t.size();
    }

    string minWindow(string s, string t) {
        int min_ = INT_MAX, start = -1;

        for (int i = 0; i < s.size(); i++) {
            for (int j = i; j < s.size(); j++) {
                if (isSubsequence(s, i, j, t)) {
                    if (j - i + 1 < min_) {
                        min_ = j - i + 1;
                        start = i;
                    }
                    break;  // earliest valid window from i found
                }
            }
        }

        return start == -1 ? "" : s.substr(start, min_);
    }
};
```

### Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O(n² × m) | n² substrings × O(m) subsequence check each |
| **Space** | O(1) | No extra storage |

---

## Approach 2 — Two Pointer (Optimal)

### The Problem With Brute Force

For every `i`, you restart the subsequence scan from scratch. Pure waste — you're rediscovering matches you already found.

```
i=0 → forward scan → valid window ends at r=4
i=1 → forward scan again from scratch → valid window ends at r=4 again
```

### Key Insight — Two Phases

For each starting position, instead of trying all `j` values:

**Phase 1 — Forward pass:** move `r` right, match `t` left to right → find where `t` ends  
**Phase 2 — Backward pass:** from that `r`, move `l` left, match `t` right to left → find the tightest left boundary

The backward pass gives you the **optimal left boundary** for the valid window ending at `r` — in one shot, without trying all possible left boundaries.

```
Phase 1 (→):   match t forward  → find r where t ends
Phase 2 (←):   match t backward → tighten l as far right as possible
Result:         [l, r] is the minimum window ending at this r
Next:           i = l + 1  (skip dead starts)
```

### Why Backward Pass?

Forward pass alone finds **a** valid window — not the shortest one.

```
s = "a b c d e b d d e"
     0 1 2 3 4 5 6 7 8
t = "bde"

Forward from i=0 → matches b(1) d(3) e(4) → r=5
Window so far: s[0..4] = "abcde", len=5

Backward from r-1=4:
  s[4]='e' matches t[2]='e' → k=1
  s[3]='d' matches t[1]='d' → k=0
  s[2]='c' no match
  s[1]='b' matches t[0]='b' → k=-1 → stop
  l = 1+1 = 2... wait l=1+1? No → l overshot, l++ → l=1

Tighter window: s[1..4] = "bcde", len=4  ✅
```

Without backward pass you'd have returned `"abcde"` — correct but not minimum.

### Implementation (C++)

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size(), m = t.size();
        int min_ = INT_MAX, start = -1;
        int i = 0;

        while (i < n) {
            // Phase 1 — forward: match t left to right
            int k = 0;
            int r = i;

            while (r < n && k < m) {
                if (s[r] == t[k]) k++;
                r++;
            }

            // t not fully matched from i onwards — no more windows possible
            if (k < m) break;

            // Phase 2 — backward: shrink from r-1 matching t right to left
            int l = r - 1;
            k = m - 1;

            while (l >= i && k >= 0) {
                if (s[l] == t[k]) k--;
                l--;
            }
            l++;  // l overshot by 1 during backward pass

            // [l, r-1] is the tightest window ending at r-1
            if (r - l < min_) {
                min_ = r - l;
                start = l;
            }

            // jump i forward — no point starting before l+1
            i = l + 1;
        }

        return start == -1 ? "" : s.substr(start, min_);
    }
};
```

### Dry Run

```
s = "abcdebdde"   (n=9)
t = "bde"         (m=3)
```

---

**Iteration 1 — i=0**

Phase 1 (forward from i=0):
```
r=0 'a' vs 'b' → no
r=1 'b' vs 'b' → match, k=1
r=2 'c' vs 'd' → no
r=3 'd' vs 'd' → match, k=2
r=4 'e' vs 'e' → match, k=3
r=5 → k==m → stop
```

Phase 2 (backward from l=4):
```
l=4 'e' vs t[2]='e' → match, k=1
l=3 'd' vs t[1]='d' → match, k=0
l=2 'c' vs t[0]='b' → no
l=1 'b' vs t[0]='b' → match, k=-1 → stop
l=0 → l++ → l=1
```

Window = `s[1..4]` = `"bcde"`, len=4 → **save, start=1**
`i = l+1 = 2`

---

**Iteration 2 — i=2**

Phase 1 (forward from i=2):
```
r=2 'c' vs 'b' → no
r=3 'd' vs 'b' → no
r=4 'e' vs 'b' → no
r=5 'b' vs 'b' → match, k=1
r=6 'd' vs 'd' → match, k=2
r=7 'd' vs 'e' → no
r=8 'e' vs 'e' → match, k=3
r=9 → stop
```

Phase 2 (backward from l=8):
```
l=8 'e' vs t[2]='e' → match, k=1
l=7 'd' vs t[1]='d' → match, k=0
l=6 'd' vs t[0]='b' → no
l=5 'b' vs t[0]='b' → match, k=-1 → stop
l=4 → l++ → l=5
```

Window = `s[5..8]` = `"bdde"`, len=4 → same as min, no update
`i = l+1 = 6`

---

**Iteration 3 — i=6**

Phase 1 (forward from i=6):
```
r=6 'd' vs 'b' → no
r=7 'd' vs 'b' → no
r=8 'e' vs 'b' → no
r=9 → k=0 < m=3 → break
```

`t` not fully matched → **exit while loop**

---

**Result:**
```
start=1, min_=4
s.substr(1, 4) = "bcde" ✅
```

### Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O(n × m) | Each position in `s` visited at most twice; subsequence check is O(m) |
| **Space** | O(1) | No extra storage |

---

## Head-to-Head Comparison

| | Brute Force | Two Pointer |
|-|-------------|-------------|
| **Time** | O(n² × m) | O(n × m) |
| **Space** | O(1) | O(1) |
| **Restarts from scratch?** | Yes — every `i` | No — `i` jumps to `l+1` |
| **Finds tightest window?** | Via break | Via backward pass |
| **LeetCode verdict** | TLE on large input | ✅ Accepted |

---

## The Mental Model

```
Brute force:   try every (i, j) pair             → O(n²) windows
Two pointer:   for each valid r, tighten l        → O(n) positions
               each position touched at most 2x   → O(n × m) total
```

The backward pass is the key insight:
> Instead of trying all possible left boundaries for a valid right boundary — **compute the optimal one directly**.

---

## Key Takeaways

- **Order matters** — this is a subsequence problem, not a substring/anagram problem. Frequency maps don't work here.
- The `break` in brute force is essential — first valid `j` for a given `i` is always the shortest window starting at `i`.
- The **backward pass** in two pointer eliminates trying all left boundaries — it finds the tightest one in O(m).
- After each valid window, `i = l + 1` skips positions that can't produce a shorter window — that's where the O(n²) → O(n) saving comes from.
- `l++` after the backward pass corrects the overshoot — the loop decrements `l` one extra time before stopping.
