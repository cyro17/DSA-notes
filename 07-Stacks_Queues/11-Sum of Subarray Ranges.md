    # Sum of Subarray Ranges

For every subarray of `arr`, find the difference between the largest and smallest element. Return the **sum of all these differences**.

---

## Key Identity

```
sum of (max - min) for all subarrays
= sum of all subarray maximums
- sum of all subarray minimums
```

This splits one hard problem into two independent, well-known subproblems.

---

## Approach 1 — Brute Force

Fix every pair `(i, j)`, maintain running min and max as `j` expands.

```cpp
class Solution {
public:
    long long subArrayRanges(vector<int>& arr) {
        int n = arr.size();
        long long res = 0;

        for (int i = 0; i < n; i++) {
            int min_ = INT_MAX, max_ = INT_MIN;
            for (int j = i; j < n; j++) {
                min_ = min(min_, arr[j]);
                max_ = max(max_, arr[j]);
                res += (max_ - min_);
            }
        }

        return res;
    }
};
```

### Complexity

| | Value |
|-|-------|
| **Time** | O(n²) |
| **Space** | O(1) |

---

## Approach 2 — Monotonic Stack (Optimal)

### Contribution Technique

Instead of asking "what is the min/max of each subarray?" — ask:

> **For each element `arr[i]`, how many subarrays is it the min/max of?**

```
count = left[i] * right[i]

left[i]  = i - (index of previous smaller/greater)
right[i] = (index of next smaller/greater) - i

contribution of arr[i] = arr[i] * left[i] * right[i]
```

`left[i] * right[i]` counts all valid `(start, end)` combinations where `arr[i]` dominates — any start from `prevBoundary+1` to `i`, any end from `i` to `nextBoundary-1`.

### Handling Duplicates — Strict vs Non-Strict

To avoid double-counting when duplicates exist, one boundary uses strict comparison and the other uses non-strict:

| Function | Finds | Pop condition |
|----------|-------|---------------|
| `psee` | Previous Smaller or Equal | `arr[top] > curr` |
| `nse` | Next Smaller (strict) | `arr[top] >= curr` |
| `pgee` | Previous Greater or Equal | `arr[top] < curr` |
| `nge` | Next Greater (strict) | `arr[top] <= curr` |

This ensures each subarray is counted **exactly once**.

---

### Implementation (C++)

```cpp
class Solution {
    // Next Smaller Element (strict)
    vector<int> nse(vector<int>& arr) {
        int n = arr.size();
        vector<int> res(n);
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && arr[st.top()] >= arr[i]) st.pop();
            res[i] = st.empty() ? n : st.top();
            st.push(i);
        }
        return res;
    }

    // Previous Smaller or Equal
    vector<int> psee(vector<int>& arr) {
        int n = arr.size();
        vector<int> res(n);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[st.top()] > arr[i]) st.pop();
            res[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        return res;
    }

    long long sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        long long total = 0;
        vector<int> nse_  = nse(arr);
        vector<int> psee_ = psee(arr);
        for (int i = 0; i < n; i++) {
            long long left  = i - psee_[i];
            long long right = nse_[i] - i;
            total += left * right * arr[i];
        }
        return total;
    }

    // Next Greater Element (strict)
    vector<int> nge(vector<int>& arr) {
        int n = arr.size();
        vector<int> res(n);
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && arr[st.top()] <= arr[i]) st.pop();
            res[i] = st.empty() ? n : st.top();
            st.push(i);
        }
        return res;
    }

    // Previous Greater or Equal
    vector<int> pgee(vector<int>& arr) {
        int n = arr.size();
        vector<int> res(n);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[st.top()] < arr[i]) st.pop();
            res[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        return res;
    }

    long long sumSubarrayMaxs(vector<int>& arr) {
        int n = arr.size();
        long long total = 0;
        vector<int> nge_  = nge(arr);
        vector<int> pgee_ = pgee(arr);
        for (int i = 0; i < n; i++) {
            long long left  = i - pgee_[i];
            long long right = nge_[i] - i;
            total += left * right * arr[i];
        }
        return total;
    }

public:
    long long subArrayRanges(vector<int>& nums) {
        return sumSubarrayMaxs(nums) - sumSubarrayMins(nums);
    }
};
```

### Complexity

| | Value |
|-|-------|
| **Time** | O(n) — four stack passes, each O(n) |
| **Space** | O(n) — four result arrays + stacks |

---

## Dry Run

```
arr = [3, 1, 2]

All subarrays:
[3]      → range = 0
[1]      → range = 0
[2]      → range = 0
[3, 1]   → range = 2
[1, 2]   → range = 1
[3, 1, 2]→ range = 2
answer   = 5
```

**Sum of Mins:**

| i | arr[i] | psee | nse | left | right | contribution |
|---|--------|------|-----|------|-------|-------------|
| 0 | 3 | -1 | 1 | 1 | 1 | 3×1×1 = 3 |
| 1 | 1 | -1 | 3 | 2 | 2 | 1×2×2 = 4 |
| 2 | 2 | 1 | 3 | 1 | 1 | 2×1×1 = 2 |

`sumMins = 3 + 4 + 2 = 9`

**Sum of Maxs:**

| i | arr[i] | pgee | nge | left | right | contribution |
|---|--------|------|-----|------|-------|-------------|
| 0 | 3 | -1 | 3 | 1 | 3 | 3×1×3 = 9 |
| 1 | 1 | 0 | 2 | 1 | 1 | 1×1×1 = 1 |
| 2 | 2 | 0 | 3 | 2 | 1 | 2×2×1 = 4 |

`sumMaxs = 9 + 1 + 4 = 14`

```
answer = sumMaxs - sumMins = 14 - 9 = 5 ✅
```

---

## Common Mistakes

| Mistake | Effect | Fix |
|---------|--------|-----|
| Using `>=` in `nge` instead of `<=` | Equal elements not popped — duplicate double-counting | `arr[top] <= curr` |
| Using `>` in `pgee` instead of `<` | Equal elements not popped — duplicate double-counting | `arr[top] < curr` |
| Returning `int` from sum functions | Silent overflow on large inputs | Return `long long` |
| Applying `mod` to this problem | `sumMax % mod < sumMin % mod` → negative result | Remove mod entirely |

---

## Comparison

| | Brute Force | Monotonic Stack |
|-|-------------|-----------------|
| **Time** | O(n²) | O(n) |
| **Space** | O(1) | O(n) |
| **Approach** | Check every subarray | Contribution per element |
| **Key idea** | Running min/max | `left[i] × right[i]` counts |

---

## Key Takeaways

- `max - min` sum splits cleanly into two independent problems via the identity `sumMaxs - sumMins`.
- The contribution technique flips the question — instead of per subarray, compute per element.
- Monotonic stack finds previous/next smaller/greater for **all elements in O(n) total**.
- Strict vs non-strict pop conditions on opposite sides is **critical** for correct duplicate handling — one side strict, other non-strict ensures each subarray counted exactly once.
- Never apply modulo to `subArrayRanges` — it is not a modular arithmetic problem and modulo before subtraction can produce wrong negative results.
