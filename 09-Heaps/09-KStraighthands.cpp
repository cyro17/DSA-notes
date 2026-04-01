# Hands of Straights (LeetCode 846)

Given an array of cards and a group size `k`, check whether all cards can be rearranged into groups of `k` consecutive cards.

**Example**
```
hand = [1,2,3,6,2,3,4,7,8],  k = 3
→ [1,2,3], [2,3,4], [6,7,8]  →  true

hand = [1,2,3,4],  k = 3
→ can't form complete groups  →  false
```

---

## Approach 1: Brute Force — O(N² × K)

**Idea:** Sort the array and build a frequency map. Loop over each card — if it's still available, try to form a group of `k` consecutive cards starting from it. Decrement frequencies as cards are used.

### C++

```cpp
int straightHands(vector<int>& arr, int k) {
    int n = arr.size();
    if (n % k != 0) return 0;

    unordered_map<int, int> mp;
    for (int& i : arr) mp[i]++;

    sort(arr.begin(), arr.end());

    for (int& i : arr) {
        if (mp[i] == 0) continue;       // card already used up, skip

        for (int j = 0; j < k; j++) {
            int curr = i + j;
            if (!mp[curr]) return 0;    // consecutive card not available
            mp[curr]--;
        }
    }
    return 1;
}
```

> **Why sort first?** So we always try to start a group from the smallest available card,
> avoiding scenarios where we skip over a card that can only be a group starter.

### Complexity

| | |
|---|---|
| Time | O(N log N + N × K) — sort + for each card try forming a group of size K |
| Space | O(N) |

---

## Approach 2: Optimal — TreeMap — O(N log N)

**Bottleneck in Approach 1:** `unordered_map` has no ordering — you can't efficiently fetch the smallest available card. This forces the outer sort + scan.

**Fix:** Use a `TreeMap` which keeps keys sorted. `firstKey()` always gives the smallest available card in O(log N), and all map operations (get, put, remove) are O(log N).

### Algorithm

1. Build a frequency map using `TreeMap` (keys auto-sorted)
2. While map is not empty:
   - Pick `start = firstKey()` — smallest remaining card
   - Try to form a group `[start, start+1, ..., start+k-1]`
   - For each card needed, decrement its frequency — remove if it hits 0
   - If any consecutive card is missing → return false

### Dry Run

```
hand = [1,2,3,6,2,3,4,7,8],  k = 3

TreeMap = {1:1, 2:2, 3:2, 4:1, 6:1, 7:1, 8:1}

Round 1: start=1, need [1,2,3]
         1→0 (remove), 2→1, 3→1
         map = {2:1, 3:1, 4:1, 6:1, 7:1, 8:1}

Round 2: start=2, need [2,3,4]
         2→0 (remove), 3→0 (remove), 4→0 (remove)
         map = {6:1, 7:1, 8:1}

Round 3: start=6, need [6,7,8]
         6→0, 7→0, 8→0
         map = {}

→ true ✓

────────────────────────────────────────

hand = [1,2,3,4],  k = 3

TreeMap = {1:1, 2:1, 3:1, 4:1}

Round 1: start=1, need [1,2,3] → done
         map = {4:1}

Round 2: start=4, need [4,5,6]
         need 5 → not in map → return false ✓
```

### Java

```java
public boolean isNStraightHand(int[] hand, int groupSize) {
    if (hand.length % groupSize != 0) return false;   // early exit

    TreeMap<Integer, Integer> freq = new TreeMap<>();
    for (int card : hand)
        freq.put(card, freq.getOrDefault(card, 0) + 1);

    while (!freq.isEmpty()) {
        int start = freq.firstKey();                  // smallest available card

        for (int i = 0; i < groupSize; i++) {
            int need = start + i;

            if (!freq.containsKey(need))
                return false;                         // consecutive card missing

            int count = freq.get(need);
            if (count == 1)
                freq.remove(need);                    // exhausted, clean up
            else
                freq.put(need, count - 1);
        }
    }
    return true;
}
```

### Complexity

| | |
|---|---|
| Time | O(N log N) — each card inserted and removed from TreeMap exactly once, all operations O(log N) |
| Space | O(N) |

---

## Complexity Comparison

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N log N + N × K) | O(N) |
| TreeMap | **O(N log N)** | O(N) |
