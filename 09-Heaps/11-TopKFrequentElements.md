# 🔢 Top K Frequent Elements — Leetcode 347

## Problem Statement

Given an integer array `nums` and an integer `k`, return the `k` most frequent elements.  
You may return the answer in **any order**.

**Constraints:** The answer is guaranteed to be unique.

---

## Approach 1 — Brute Force with Frequency List

### Intuition

Manually count frequencies using a `visited[]` array to avoid re-processing duplicates. After building the frequency list, sort it by count in descending order and extract the top `k` elements.

### Code

```java
class Solution {
    public int[] topKFrequent(int[] nums, int k) {
        List<int[]> freqList = new ArrayList<>();
        boolean[] visited = new boolean[nums.length];

        for (int i = 0; i < nums.length; i++) {
            if (visited[i]) continue;

            int count = 0;
            for (int j = 0; j < nums.length; j++) {
                if (nums[i] == nums[j]) {
                    count++;
                    visited[j] = true;
                }
            }
            freqList.add(new int[]{nums[i], count});
        }

        freqList.sort((a, b) -> b[1] - a[1]);

        int[] res = new int[k];
        for (int i = 0; i < k; i++) {
            res[i] = freqList.get(i)[0];
        }
        return res;
    }
}
```

### Step-by-step Walkthrough

Given `nums = [1, 1, 1, 2, 2, 3]`, `k = 2`:

| Step | Action | State |
|------|--------|-------|
| i=0 (val=1) | Count occurrences of 1, mark indices 0,1,2 visited | `freqList = [[1,3]]` |
| i=3 (val=2) | Count occurrences of 2, mark indices 3,4 visited | `freqList = [[1,3],[2,2]]` |
| i=5 (val=3) | Count occurrences of 3, mark index 5 visited | `freqList = [[1,3],[2,2],[3,1]]` |
| Sort | Sort by frequency descending | `[[1,3],[2,2],[3,1]]` |
| Extract | Pick top k=2 | `[1, 2]` ✅ |

### Complexity

| | Value | Reason |
|--|-------|--------|
| **Time** | O(N²) | Nested loops to count each element's frequency |
| **Space** | O(N) | `visited[]` array + `freqList` both of size N |

> ⚠️ **Drawback:** The inner loop re-scans the entire array for every unique element, making this inefficient for large inputs.

---

## Approach 2 — HashMap + Min-Heap (Priority Queue) ✅ Optimal

### Intuition

Use a `HashMap` to count frequencies in O(N). Then maintain a **min-heap of size k** — as we process each entry, we push it into the heap and evict the least frequent element whenever the heap exceeds size `k`. At the end, the heap holds exactly the top `k` most frequent elements.

### Why a Min-Heap?

A min-heap of size `k` keeps the `k` largest frequencies seen so far. Whenever a new element arrives:
- If the heap has room → push it in.
- If the heap is full → compare with the minimum (heap top). If the new element has a higher frequency, it displaces the minimum.

This avoids sorting all N elements — we only ever maintain `k` entries.

### Code

```java
class Solution {
    public int[] topKFrequent(int[] nums, int k) {
        // Step 1: Build frequency map
        Map<Integer, Integer> map = new HashMap<>();
        for (int num : nums)
            map.put(num, map.getOrDefault(num, 0) + 1);

        // Step 2: Min-heap ordered by frequency (smallest freq at top)
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[1] - b[1]);

        for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
            pq.offer(new int[]{entry.getKey(), entry.getValue()});
            if (pq.size() > k) pq.poll(); // evict least frequent
        }

        // Step 3: Extract results
        int[] res = new int[k];
        for (int i = 0; i < k; i++) res[i] = pq.poll()[0];
        return res;
    }
}
```

### Step-by-step Walkthrough

Given `nums = [1, 1, 1, 2, 2, 3]`, `k = 2`:

**After building frequency map:**
```
{ 1 → 3, 2 → 2, 3 → 1 }
```

**Processing map entries into min-heap:**

| Entry Added | Heap Before Evict | Action | Heap After |
|-------------|-------------------|--------|------------|
| [1, 3] | [[1,3]] | size=1 ≤ k, keep | [[1,3]] |
| [2, 2] | [[2,2],[1,3]] | size=2 ≤ k, keep | [[2,2],[1,3]] |
| [3, 1] | [[3,1],[1,3],[2,2]] | size=3 > k, evict min ([3,1]) | [[2,2],[1,3]] |

**Final heap:** `[[2,2],[1,3]]` → result = `[2, 1]` ✅

### Complexity

| | Value | Reason |
|--|-------|--------|
| **Time** | O(N log k) | HashMap build: O(N). Each of the M unique elements is pushed/popped from heap of size k: O(M log k) ≤ O(N log k) |
| **Space** | O(N + k) | O(N) for HashMap, O(k) for the heap |

> ✅ **Optimal for large N with small k.** When k << N, `log k` is much smaller than `log N`.

---

## Comparison

| | Approach 1 (Brute Force) | Approach 2 (HashMap + Min-Heap) |
|--|--------------------------|----------------------------------|
| **Time** | O(N²) | O(N log k) |
| **Space** | O(N) | O(N + k) |
| **Sorting** | Full sort of unique elements | No sort — heap maintains top k |
| **Use case** | Small inputs only | Large-scale, production-ready |

---

## Key Takeaway

> When the problem asks for **"top k"** of anything, your first instinct should be a **min-heap of size k**.  
> It avoids fully sorting the data and runs in **O(N log k)** instead of **O(N log N)**.

---

## Tags

`Array` `HashMap` `Heap / Priority Queue` `Sorting` `Greedy`
