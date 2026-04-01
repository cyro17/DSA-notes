# K-Sorted Array

Given an array and an integer `k`, check whether the array is k-sorted.  
An array is k-sorted if every element is **at most `k` positions away** from its correct (sorted) position.

**Example**
```
arr = [3, 2, 1, 5, 4, 7, 6, 5],  k = 2  →  "Yes"
arr = [3, 2, 1, 5, 4, 7, 6, 5],  k = 1  →  "No"
```

---

## Approach 1: Brute Force — O(N²)

**Idea:** Sort a copy of the array. For each element in the original array, scan the sorted array to find its correct index and check if the distance exceeds `k`.

```java
public String isKSortedArray(int[] arr, int n, int k) {
    int[] sorted = Arrays.copyOf(arr, n);
    Arrays.sort(sorted);

    for (int i = 0; i < arr.length; i++) {
        for (int j = 0; j < sorted.length; j++) {
            if (sorted[j] == arr[i]) {
                if (Math.abs(j - i) > k)
                    return "No";
            }
        }
    }
    return "Yes";
}
```

> ⚠️ Fails silently for duplicates — the inner loop matches the first occurrence
> every time, so displaced duplicates may not be caught correctly.

---

## Approach 2: Sort + HashMap — O(N log N)

**Idea:** Sort a copy to know the correct position of each element. Store sorted positions in a map (using a queue per value to handle duplicates), then verify each element's displacement.

```java
static String isKSortedArray(int[] arr, int n, int k) {
    int[] sorted = Arrays.copyOf(arr, n);
    Arrays.sort(sorted);

    // Map each value → queue of its correct sorted positions (handles duplicates)
    Map<Integer, Queue<Integer>> posMap = new HashMap<>();
    for (int i = 0; i < n; i++) {
        posMap.computeIfAbsent(sorted[i], x -> new LinkedList<>()).offer(i);
    }

    for (int i = 0; i < n; i++) {
        int sortedIndex = posMap.get(arr[i]).poll();  // expected position of arr[i]
        if (Math.abs(sortedIndex - i) > k)
            return "No";
    }
    return "Yes";
}
```

---

## Approach 3: Sort + Min Heap (Sliding Window) — O(N log N)

**Idea:** In a k-sorted array, the correct element for index `i` must lie within the window `arr[i .. i+k]`. A min-heap of size `k+1` always holds the current window — its minimum must match `sorted[i]` at every step.

### Why window size `k+1`?

The correct element for position `i` can be at most `k` steps away, so it sits somewhere in `arr[i], arr[i+1], ..., arr[i+k]` — that's `k+1` elements.

### Why `i + k + 1`?

After verifying index `i`, the window slides forward by one. The new element entering the window is at index `i + k + 1` — the right edge of the next window.

```
i=0, k=2 → window [0..2], next element to add = arr[3] = i+k+1
i=1, k=2 → window [1..3], next element to add = arr[4] = i+k+1
```

The `if (next < n)` guard prevents `ArrayIndexOutOfBoundsException` when the window slides past the end of the array.

### Java

```java
static String isKSortedArray(int[] arr, int n, int k) {
    int[] sorted = Arrays.copyOf(arr, n);
    Arrays.sort(sorted);

    PriorityQueue<Integer> pq = new PriorityQueue<>(); // min-heap of size k+1

    // Load first window
    for (int i = 0; i <= k && i < n; i++)
        pq.offer(arr[i]);

    for (int i = 0; i < n; i++) {
        // Min of current window must equal the expected sorted element
        if (pq.peek() != sorted[i])
            return "No";

        pq.poll();

        // Slide window: bring in the next unseen element
        int next = i + k + 1;
        if (next < n) pq.offer(arr[next]);
    }
    return "Yes";
}
```

### Dry Run

```
arr    = [3, 2, 1, 5, 4, 7, 6, 5],  k = 2
sorted = [1, 2, 3, 4, 5, 5, 6, 7]

Initial heap (i = 0..2): {3,2,1} → heap = {1,2,3}

i=0: peek=1, sorted[0]=1 ✓  poll 1, add arr[3]=5 → heap={2,3,5}
i=1: peek=2, sorted[1]=2 ✓  poll 2, add arr[4]=4 → heap={3,4,5}
i=2: peek=3, sorted[2]=3 ✓  poll 3, add arr[5]=7 → heap={4,5,7}
i=3: peek=4, sorted[3]=4 ✓  poll 4, add arr[6]=6 → heap={5,6,7}
i=4: peek=5, sorted[4]=5 ✓  poll 5, add arr[7]=5 → heap={5,6,7}
i=5: peek=5, sorted[5]=5 ✓  poll 5, next=8 ≥ n, skip
i=6: peek=6, sorted[6]=6 ✓  poll 6
i=7: peek=7, sorted[7]=7 ✓  poll 7

→ "Yes" ✓
```

---

## Complexity Summary

| Approach | Time | Space | Handles Duplicates |
|---|---|---|---|
| Brute Force | O(N²) | O(N) | ❌ |
| Sort + HashMap | O(N log N) | O(N) | ✅ |
| Sort + Min Heap | O(N log N) | O(N) | ✅ |

> **Note:** The heap approach is O(N log k) for the heap operations themselves, but `Arrays.sort()` dominates at O(N log N), making all three approaches equivalent in overall time complexity. The O(N log k) heap advantage only applies to the classic **"sort a k-sorted array"** problem where no reference sorted array is needed.
