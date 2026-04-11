# Trapping Rain Water

Given an array `height` representing an elevation map, compute how much water it can trap after raining.

---

## Core Observation

Water trapped at any index `i`:
```
water[i] = min(maxLeft, maxRight) - height[i]
```

Where `maxLeft` = tallest bar to the left of `i`, `maxRight` = tallest bar to the right of `i`.

Three approaches — all O(n) time, decreasing space complexity.

---

## Approach 1 — Precompute maxLeft / maxRight Arrays

### Idea

Precompute the maximum height to the left and right of every index. Then for each index, water = `min(maxL[i], maxR[i]) - height[i]`.

### Implementation (C++)

```cpp
class Solution {
public:
    int trap(vector<int>& arr) {
        int n = arr.size();
        vector<int> maxL(n), maxR(n);

        // max height from left up to i
        int maxi = arr[0];
        for (int i = 0; i < n; i++) {
            maxi   = max(maxi, arr[i]);
            maxL[i] = maxi;
        }

        // max height from right up to i
        maxi = arr[n - 1];
        for (int i = n - 1; i >= 0; i--) {
            maxi   = max(maxi, arr[i]);
            maxR[i] = maxi;
        }

        int count = 0;
        for (int i = 0; i < n; i++)
            count += min(maxL[i], maxR[i]) - arr[i];

        return count;
    }
};
```

### Dry Run

```
height = [3, 0, 2, 0, 4]

maxL   = [3, 3, 3, 3, 4]
maxR   = [4, 4, 4, 4, 4]

i=0: min(3,4)-3 = 0
i=1: min(3,4)-0 = 3
i=2: min(3,4)-2 = 1
i=3: min(3,4)-0 = 3
i=4: min(4,4)-4 = 0

total = 0+3+1+3+0 = 7 ✅
```

### Complexity

| | Value |
|-|-------|
| **Time** | O(n) — three linear passes |
| **Space** | O(n) — two arrays of size n |

---

## Approach 2 — Monotonic Stack

### Idea

Water is trapped in **horizontal layers** between walls. Maintain a decreasing stack of indices. When a taller bar arrives — it's the right wall. Pop the top (floor/dip). New top is the left wall. Compute water for that layer.

### The Three Roles Every Pop

```
st.pop()  → floor      (the dip that holds water)
st.top()  → left wall  (next element on stack)
i         → right wall (current bar that triggered pop)

width  = right - left - 1
height = min(arr[left], arr[right]) - arr[floor]
water += width * height
```

### Implementation (C++)

```cpp
class Solution {
public:
    int trap(vector<int>& arr) {
        int n = arr.size(), water = 0;
        stack<int> st;   // decreasing stack of indices

        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[i] > arr[st.top()]) {
                int floor = st.top(); st.pop();

                if (st.empty()) break;  // no left wall → no water

                int left  = st.top();
                int right = i;

                int width  = right - left - 1;
                int height = min(arr[left], arr[right]) - arr[floor];
                water += width * height;
            }
            st.push(i);
        }

        return water;
    }
};
```

### Dry Run

```
height = [3, 0, 2, 0, 4]
```

| i | height[i] | action | floor | left | right | width | h | water |
|---|-----------|--------|-------|------|-------|-------|---|-------|
| 0 | 3 | push | — | — | — | — | — | 0 |
| 1 | 0 | push | — | — | — | — | — | 0 |
| 2 | 2 | pop 1, push 2 | 1(h=0) | 0(h=3) | 2(h=2) | 1 | 2 | +2 |
| 3 | 0 | push | — | — | — | — | — | 2 |
| 4 | 4 | pop 3 | 3(h=0) | 2(h=2) | 4(h=4) | 1 | 2 | +2 |
| | | pop 2 | 2(h=2) | 0(h=3) | 4(h=4) | 3 | 1 | +3 |
| | | pop 0, empty → break | — | — | — | — | — | 7 |

**Total = 7 ✅**

### Layer Visualization

```
Each pop fills one horizontal layer:

Pop 1 (floor=1): fills between index 0 and 2 at height 0→2   (+2)
Pop 2 (floor=3): fills between index 2 and 4 at height 0→2   (+2)
Pop 3 (floor=2): fills above index 2, between 0 and 4        (+3)
```

### Complexity

| | Value |
|-|-------|
| **Time** | O(n) — each index pushed and popped at most once (amortized) |
| **Space** | O(n) — stack holds at most n indices |

---

## Approach 3 — Two Pointer (Optimal Space)

### Idea

Instead of precomputing both maxL and maxR arrays, maintain them **on the fly** using two pointers converging from both ends.

**Key insight:**
```
if arr[l] <= arr[r]:
    water at l is determined by leftMax alone
    (rightMax is guaranteed to be ≥ leftMax, so min = leftMax)
    process left → l++

else:
    water at r is determined by rightMax alone
    process right → r--
```

Why? If `arr[l] <= arr[r]`, the right side is at least as tall. So even without knowing the exact rightMax, you know `min(leftMax, rightMax) = leftMax` — safe to compute water on the left.

### Implementation (C++)

```cpp
class Solution {
public:
    int trap(vector<int>& arr) {
        int n = arr.size();
        int l = 0, r = n - 1, water = 0;
        int leftMax = arr[0], rightMax = arr[n - 1];

        while (l <= r) {
            if (arr[l] <= arr[r]) {
                // left side is the bottleneck
                leftMax  = max(leftMax, arr[l]);
                water   += leftMax - arr[l];
                l++;
            } else {
                // right side is the bottleneck
                rightMax  = max(rightMax, arr[r]);
                water    += rightMax - arr[r];
                r--;
            }
        }

        return water;
    }
};
```

### Dry Run

```
height   = [3, 0, 2, 0, 4]
l=0, r=4, leftMax=3, rightMax=4, water=0
```

| l | r | arr[l] | arr[r] | side | leftMax | rightMax | water added | total |
|---|---|--------|--------|------|---------|----------|-------------|-------|
| 0 | 4 | 3 | 4 | left | 3 | 4 | 3-3=0 | 0 |
| 1 | 4 | 0 | 4 | left | 3 | 4 | 3-0=3 | 3 |
| 2 | 4 | 2 | 4 | left | 3 | 4 | 3-2=1 | 4 |
| 3 | 4 | 0 | 4 | left | 3 | 4 | 3-0=3 | 7 |
| 4 | 4 | 4 | 4 | left | 4 | 4 | 4-4=0 | 7 |

**Total = 7 ✅**

### Complexity

| | Value |
|-|-------|
| **Time** | O(n) — single pass, each pointer moves at most n steps |
| **Space** | **O(1)** — only four variables |

---

## All Three Approaches Compared

| | Precompute Arrays | Monotonic Stack | Two Pointer |
|-|-------------------|-----------------|-------------|
| **Time** | O(n) | O(n) | O(n) |
| **Space** | O(n) | O(n) | **O(1)** |
| **Passes** | 3 | 1 | 1 |
| **Intuition** | Easiest | Moderate | Subtle |
| **Generalizable?** | ❌ | ✅ Stack transfers to many problems | ❌ |
| **Interview pick** | Good start | ✅ Shows pattern knowledge | ✅ Optimal |

---

## Key Takeaways

- All three approaches are O(n) time — the difference is space and intuition.
- **Precompute arrays** — most readable, easiest to derive from the formula `min(maxL, maxR) - height[i]`.
- **Monotonic stack** — fills water horizontally in layers. Most transferable pattern — same technique used in Largest Rectangle in Histogram, Sum of Subarray Minimums, Daily Temperatures.
- **Two pointer** — optimal space O(1). The key insight: whichever side is shorter determines the water level — you don't need to know the other side's exact max.
- In interviews: brute force → precompute arrays → two pointer is the natural progression. Stack solution shows deeper pattern recognition.
