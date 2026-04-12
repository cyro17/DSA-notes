# Online Stock Span

For each day's stock price, compute the **span** — the number of consecutive days (including today) where the price was less than or equal to today's price.

---

## Key Observation

```
prices = [100, 80, 60, 70, 60, 75, 85]
spans  = [  1,  1,  1,  2,  1,  4,  6]

span = how far back you can go without seeing a price > today
     = distance to previous greater element
```

This is exactly the **Previous Greater Element** problem — applied incrementally.

---

## Approach 1 — Recompute PGE Every Call (Brute Force)

### Idea

Maintain a list of all prices seen so far. On every `next()` call, recompute the **Previous Greater Element** array for the entire list from scratch. The span = `currentIndex - prevGreaterIndex`.

### Implementation (C++)

```cpp
class StockSpanner {
    vector<int> list;

    vector<int> pge(vector<int>& arr) {
        int n = arr.size();
        vector<int> res(n);
        stack<int> st;

        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[i] >= arr[st.top()])
                st.pop();
            res[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        return res;
    }

public:
    StockSpanner() {}

    int next(int price) {
        list.push_back(price);
        vector<int> pge_ = pge(list);
        int currIndex = list.size() - 1;
        int prevG     = pge_[currIndex];
        return currIndex - prevG;
    }
};
```

### Why It Gives TLE

Every `next()` call recomputes `pge()` on the **entire list from scratch**:

```
call 1: list has 1 element  → pge runs on 1
call 2: list has 2 elements → pge runs on 2
call 3: list has 3 elements → pge runs on 3
...
call n: list has n elements → pge runs on n

Total work = 1 + 2 + 3 + ... + n = O(n²)
```

### Complexity

| | Value |
|-|-------|
| **Per call** | O(n) |
| **Total (n calls)** | O(n²) → TLE |
| **Space** | O(n) list + O(n) stack |

---

## Approach 2 — Persistent Stack (Optimal)

### Idea

Instead of recomputing from scratch — **persist the stack across calls**. Each `next()` call only processes the new price incrementally.

The stack stores `{price, span}` pairs. When you pop an element, its span is already pre-computed — just accumulate it into the current span. No need to re-examine those days.

### Why Accumulating Span Works

```
{70, 2} on stack means:
"70 and the 1 day before it were all ≤ 70"

When current price = 75 ≥ 70:
→ all those 2 days are also ≤ 75
→ span += 2 directly, no need to go back and re-examine them
```

Each element encodes the history of everything it absorbed — popping it transfers that history instantly.

### Implementation (C++)

```cpp
class StockSpanner {
    stack<pair<int,int>> st;  // {price, span}

public:
    StockSpanner() {}

    int next(int price) {
        int span = 1;

        // pop all prices <= current, accumulate their spans
        while (!st.empty() && st.top().first <= price) {
            span += st.top().second;
            st.pop();
        }

        st.push({price, span});
        return span;
    }
};
```

### Dry Run

```
prices = [100, 80, 60, 70, 60, 75, 85]
```

| call | price | pops | span | stack after |
|------|-------|------|------|-------------|
| 1 | 100 | none | 1 | [{100,1}] |
| 2 | 80 | none | 1 | [{100,1},{80,1}] |
| 3 | 60 | none | 1 | [{100,1},{80,1},{60,1}] |
| 4 | 70 | {60,1} | 1+1=2 | [{100,1},{80,1},{70,2}] |
| 5 | 60 | none | 1 | [{100,1},{80,1},{70,2},{60,1}] |
| 6 | 75 | {60,1},{70,2} | 1+1+2=4 | [{100,1},{80,1},{75,4}] |
| 7 | 85 | {75,4},{80,1} | 1+4+1=6 | [{100,1},{85,6}] |

**Output: [1, 1, 1, 2, 1, 4, 6] ✅**

### Complexity

| | Value | Why |
|-|-------|-----|
| **Per call** | O(1) amortized | Each price pushed once, popped at most once |
| **Total (n calls)** | O(n) | n pushes + at most n pops = 2n operations |
| **Space** | O(n) | Stack holds at most n pairs |

### Why O(1) Amortized — Not O(n)

The `while` loop inside `next()` looks expensive — but across all `n` calls:

```
each price → pushed exactly once
each price → popped at most once

total operations = n pushes + n pops = 2n

average per call = 2n / n = 2 = O(1)
```

Some calls are expensive (many pops), most are cheap (0 pops). The expensive calls are paid for by the cheap ones that came before — this is **amortized O(1)**.

```
prices = [1, 2, 3, 4, 5, 100]

next(1):   0 pops → cost 1
next(2):   1 pop  → cost 2
next(3):   2 pops → cost 3
next(4):   3 pops → cost 4
next(5):   4 pops → cost 5
next(100): 5 pops → cost 6   ← looks expensive

total = 1+2+3+4+5+6 = 21 for 6 calls
average = 21/6 ≈ 3.5 = O(1) amortized ✅
```

---

## Comparison

| | Approach 1 (Recompute PGE) | Approach 2 (Persistent Stack) |
|-|---------------------------|-------------------------------|
| **Per call** | O(n) | O(1) amortized |
| **Total n calls** | O(n²) | O(n) |
| **Space** | O(n) list + O(n) stack | O(n) stack only |
| **Recomputes history?** | Yes — entire list every call | No — stack encodes history |
| **LeetCode** | TLE | ✅ Accepted |

---

## Key Takeaways

- Stock Span = **Previous Greater Element** applied incrementally — the stack is the natural fit.
- Recomputing PGE from scratch every call wastes all prior work — O(n²) total.
- Persisting the stack eliminates redundant work — each element processed exactly twice (push + pop).
- Storing `{price, span}` pairs lets you absorb history in O(1) — when you pop an element, its span carries everything it had already absorbed.
- Amortized O(1) per call — individually some calls are O(k), but total across n calls is O(n).
