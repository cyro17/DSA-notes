# Remove K Digits

Given a string `s` representing a number and an integer `k`, remove `k` digits to make the number as small as possible. Return the result as a string.

---

## Key Observations

- Removing k **individual** digits from anywhere — not a contiguous block
- To minimize the number — remove digits that create a **peak** (digit greater than the next)
- Leading zeros must be stripped from the result
- If result is empty → return `"0"`

---

## Why Not Substring Removal?

A common misconception — removing a contiguous block of `k` digits.

```
s = "1324", k = 2

Substring removal options:
  remove "13" → "24"
  remove "32" → "14"
  remove "24" → "13"   ← numerically smallest

But "13" is WRONG — you'd need to remove '2' and '4'
which are non-contiguous. Substring removal never allows that.

Correct answer = "12" (remove '3' and '4')
```

Substring removal is a **subset** of the actual solution space — it misses all non-contiguous removals.

| | Substring Removal | Actual Problem |
|-|-------------------|----------------|
| What's removed | k contiguous digits | k individual digits from anywhere |
| Solution space | n-k+1 options | C(n,k) options |
| Correct? | ❌ Sometimes by luck | ✅ Always |

---

## Approach 1 — Brute Force (Remove One Peak at a Time)

### Idea

Remove **1 digit at a time**, `k` times. Each time, find and remove the **first peak** — first digit greater than the digit after it. If no peak exists (non-decreasing), remove the last digit.

### Why First Peak?

Removing the leftmost peak gives the smallest number after one removal — greedy local choice.

```
s = "1432219"

1 < 4 → fine
4 > 3 → first peak at index 1 → remove '4' → "132219"

1 < 3 → fine
3 > 2 → peak at index 1 → remove '3' → "12219"

1 < 2 → fine
2 > 2 → fine
2 > 1 → peak at index 2 → remove '2' → "1219" ✅
```

### Implementation (C++)

```cpp
string removeKdigits(string s, int k) {
    while (k--) {
        int n = s.size();
        int idx = -1;

        // find first digit greater than next
        for (int i = 0; i < n - 1; i++) {
            if (s[i] > s[i + 1]) {
                idx = i;
                break;
            }
        }

        // no peak → number is non-decreasing → remove last digit
        if (idx == -1) idx = n - 1;

        s.erase(s.begin() + idx);
    }

    // remove leading zeros
    int i = 0;
    while (i < (int)s.size() - 1 && s[i] == '0') i++;
    s = s.substr(i);

    return s.empty() ? "0" : s;
}
```

### Dry Run

```
s = "1432219", k = 3
```

| Iteration | Scan | Peak at | Remove | Result |
|-----------|------|---------|--------|--------|
| 1 | 1<4 → 4>3 | index 1 | '4' | "132219" |
| 2 | 1<3 → 3>2 | index 1 | '3' | "12219" |
| 3 | 1<2 → 2==2 → 2>1 | index 2 | '2' | "1219" |

**Answer: "1219" ✅**

```
s = "12345", k = 2   (no peak case)
```

| Iteration | Scan | Peak? | Remove | Result |
|-----------|------|-------|--------|--------|
| 1 | 1<2<3<4<5 | None | last '5' | "1234" |
| 2 | 1<2<3<4 | None | last '4' | "123" |

**Answer: "123" ✅**

### Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O(n × k) | k iterations × O(n) scan + O(n) erase each |
| **Space** | O(1) | In-place on string |

> Note: O(n×k) degrades to **O(n²)** when k ≈ n. The "O(3n)" intuition only holds when k=3 specifically — it's not a constant in the algorithm.

| k value | Complexity |
|---------|-----------|
| k = 3 | O(3n) — coincidental |
| k = n/2 | O(n²/2) |
| k = n-1 | O(n²) worst case |
| **General** | **O(n × k)** |

---

## Approach 2 — Monotonic Stack (Optimal)

### Idea

Simulate all `k` removals in **one pass** using a monotonically increasing stack. Whenever the current digit is smaller than the stack top — the top is a peak → pop it (remove it). This is the brute force done simultaneously across all positions.

```
Brute force:  k passes × scan entire string   → O(n×k)
Stack:        one pass — pop peaks on the fly  → O(n)
```

### Three Cases After Stack Traversal

| Situation | Action |
|-----------|--------|
| `k > 0` after loop | Number was non-decreasing — remove last k digits |
| Leading zeros | Strip from front |
| Result empty | Return `"0"` |

### Common Mistakes

| Mistake | Effect | Fix |
|---------|--------|-----|
| `st.pop()` after stack drained | UB — crash | `res.pop_back()` for remaining k |
| `res.pop_back()` before reversing | Removes wrong end | Reverse first, then trim |
| `res[i]=='0'` loop reaches end | Returns empty string | Stop at `res.size()-1` |
| `res.empty` without `()` | Returns function pointer | `res.empty() ? "0" : res` |
| `k == n` guard | Misses k > n | Use `k >= n` |

### Implementation (C++)

```cpp
string removeKdigits(string s, int k) {
    int n = s.size();
    if (k >= n) return "0";

    stack<char> st;

    for (int i = 0; i < n; i++) {
        // pop stack top if it's a peak and k remains
        while (!st.empty() && st.top() > s[i] && k) {
            st.pop();
            k--;
        }
        st.push(s[i]);
    }

    // drain stack into res (comes out reversed)
    string res = "";
    while (!st.empty()) {
        res.push_back(st.top());
        st.pop();
    }

    reverse(res.begin(), res.end());           // correct order first

    res = res.substr(0, res.size() - k);       // remove remaining k from back

    // remove leading zeros — keep at least one char
    int i = 0;
    while (i < (int)res.size() - 1 && res[i] == '0') i++;
    res = res.substr(i);

    return res.empty() ? "0" : res;
}
```

### Dry Run

```
s = "1432219", k = 3
```

| i | s[i] | stack top | action | stack | k |
|---|------|-----------|--------|-------|---|
| 0 | 1 | empty | push | [1] | 3 |
| 1 | 4 | 1 | 1<4 → push | [1,4] | 3 |
| 2 | 3 | 4 | 4>3 → pop, push 3 | [1,3] | 2 |
| 3 | 2 | 3 | 3>2 → pop, push 2 | [1,2] | 1 |
| 4 | 2 | 2 | 2==2 → push | [1,2,2] | 1 |
| 5 | 1 | 2 | 2>1 → pop, push 1 | [1,2,1] | 0 |
| 6 | 9 | 1 | k=0 → push | [1,2,1,9] | 0 |

```
drain  → res = "9121" (reversed)
reverse → res = "1219"
k=0    → no trimming
no leading zeros
answer = "1219" ✅
```

```
s = "112", k = 1
```

| i | s[i] | stack top | action | stack | k |
|---|------|-----------|--------|-------|---|
| 0 | 1 | empty | push | [1] | 1 |
| 1 | 1 | 1 | 1==1 → push | [1,1] | 1 |
| 2 | 2 | 1 | 1<2 → push | [1,1,2] | 1 |

```
drain   → res = "211"
reverse → res = "112"
k=1     → res.substr(0, 3-1) = "11"  ✅
```

### Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O(n) | Each char pushed once, popped at most once — amortized |
| **Space** | O(n) | Stack holds at most n chars |

---

## All Approaches Compared

| | Brute Force | Monotonic Stack |
|-|-------------|-----------------|
| **Time** | O(n × k) → O(n²) worst | O(n) |
| **Space** | O(1) | O(n) |
| **Passes** | k passes | 1 pass |
| **Idea** | Remove one peak at a time | Remove all peaks in one pass |
| **LeetCode** | TLE for large n,k | ✅ Accepted |

---

## Key Takeaways

- **Substring removal is wrong** — the problem removes individual digits, not contiguous blocks.
- **First peak = optimal local choice** — removing the leftmost digit greater than the next always gives the smallest result for that removal.
- The stack solution is the brute force done in one pass — same greedy logic, no repeated scanning.
- **Reverse before trimming remaining k** — the stack drains in reverse order, so `res.pop_back()` before reversing removes from the wrong end.
- Amortized O(n) — each character pushed once and popped at most once, same argument as all monotonic stack problems.
