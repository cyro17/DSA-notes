# Largest Rectangle in Histogram

**Difficulty:** Hard
**Topic Tags:** Stack, Monotonic Stack, Array
**LeetCode:** [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

---

## Problem Statement

Given an array `heights` representing the heights of bars in a histogram where each bar has width `1`, return the area of the largest rectangle that can be formed within the histogram.

**Example:**
```
Input:  heights = [2, 1, 5, 6, 2, 3]
Output: 10
```
```
     _
    | |
   _| |
  | | |_
 _| | | |
| | | | |
| | | | |_
|_|_|_|_|_|_|
 2 1 5 6 2 3
```
The largest rectangle spans bars at index 2 and 3 (heights 5 and 6), giving area = 5 × 2 = **10**.

---

## Intuition

For each bar, the maximum rectangle it can contribute is bounded by:
- Its own height (since the rectangle can be at most as tall as the bar itself)
- The nearest shorter bar to its **left** (Previous Smaller Element — PSE)
- The nearest shorter bar to its **right** (Next Smaller Element — NSE)

So for every bar `i`:
```
width = NSE[i] - PSE[i] - 1
area  = heights[i] × width
```

The answer is the maximum area across all bars.

---

## Approach 1 — Explicit PSE + NSE (3-Pass)

Precompute PSE and NSE arrays separately using a monotonic stack, then calculate area in a final pass.

```cpp
class Solution {
    vector<int> pse(vector<int>& arr) {
        int n = arr.size();
        vector<int> pse_(n);
        stack<int> st;

        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[i] <= arr[st.top()])
                st.pop();
            pse_[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        return pse_;
    }

    vector<int> nse(vector<int>& arr) {
        int n = arr.size();
        vector<int> nse_(n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && arr[st.top()] > arr[i])
                st.pop();
            nse_[i] = st.empty() ? n : st.top();
            st.push(i);
        }
        return nse_;
    }

public:
    int largestRectangleArea(vector<int>& arr) {
        int n = arr.size();
        vector<int> nse_ = nse(arr);
        vector<int> pse_ = pse(arr);

        int maxArea = INT_MIN;
        for (int i = 0; i < n; i++) {
            int width = nse_[i] - pse_[i] - 1;
            maxArea = max(maxArea, arr[i] * width);
        }
        return maxArea;
    }
};
```

**Note on duplicate handling:** The asymmetry between `<=` in PSE and `>` in NSE is intentional. It attributes the full span to the rightmost duplicate, preventing double-counting of rectangles with equal heights.

**Complexity:**
- Time: `O(n)` — each index is pushed and popped at most once in each pass
- Space: `O(n)` — two result vectors + two stacks

---

## Approach 2 — Single Pass (Optimal)

Eliminate the PSE/NSE arrays entirely. Compute them **lazily** at pop time using one stack and one pass.

### Key Insight

Maintain a **monotonic increasing stack** of indices. When a shorter bar arrives at index `i`, every bar taller than it gets evicted. At the moment of eviction, we know:
- **Right boundary** = `i` (the current bar that caused eviction → NSE)
- **Left boundary** = new `stack.top()` after popping (the previous smaller bar → PSE)

PSE and NSE are computed on the fly, exactly when needed.

```
Push → "this bar might extend further right, keep it"
Pop  → "this bar's reach just ended, compute its area now"
```

### Sentinel

Bars in a strictly increasing suffix (e.g., `[1, 2, 3]`) never get evicted during traversal. A virtual bar of height `0` at index `n` acts as a sentinel — shorter than everything, it forces all remaining bars out of the stack cleanly.

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& arr) {
        int n = arr.size();
        stack<int> st;
        int maxArea = 0;

        for (int i = 0; i <= n; i++) {          // note: i <= n for sentinel
            int currHeight = (i == n) ? 0 : arr[i];

            while (!st.empty() && currHeight < arr[st.top()]) {
                int height = arr[st.top()]; st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            st.push(i);
        }
        return maxArea;
    }
};
```

**Complexity:**
- Time: `O(n)` — each index pushed and popped at most once
- Space: `O(n)` — one stack only

---

## Dry Run — `[2, 1, 5, 6, 2, 3]`

| i | currHeight | Action | Popped (h, w, area) | maxArea |
|---|---|---|---|---|
| 0 | 2 | push 0 | — | 0 |
| 1 | 1 | pop 0 → push 1 | h=2, w=1, area=2 | 2 |
| 2 | 5 | push 2 | — | 2 |
| 3 | 6 | push 3 | — | 2 |
| 4 | 2 | pop 3, pop 2 → push 4 | h=6,w=1,a=6 → h=5,w=2,a=10 | 10 |
| 5 | 3 | push 5 | — | 10 |
| 6 | 0 (sentinel) | pop 5, pop 4, pop 1 | h=3,w=1,a=3 → h=2,w=4,a=8 → h=1,w=6,a=6 | 10 |

**Answer: 10** ✓

---

## Comparison

| | Approach 1 (3-Pass) | Approach 2 (Single-Pass) |
|---|---|---|
| Time | O(n) | O(n) |
| Space | O(n) — 2 vectors + 2 stacks | O(n) — 1 stack |
| Passes | 3 | 1 |
| Readability | Higher (explicit PSE/NSE) | Moderate |
| Interview preference | Good for explanation | Expected optimal answer |

Approach 1 is excellent for understanding the concept. Approach 2 is what interviewers at product-tier companies expect as the final answer.

---

## Related Problems

- [85. Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) — apply this per row on a 2D matrix
- [907. Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/) — same PSE/NSE pattern
- [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) — next greater element variant
