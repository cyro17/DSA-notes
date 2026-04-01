# Task Scheduler (LeetCode 621)

Given a list of tasks and a cooldown interval `n`, find the minimum number of CPU intervals needed to finish all tasks.

---

## Approach 1: Brute Force — O(N²)

**Idea:** At each time unit, find all currently available tasks (not in cooldown), then greedily pick the one with the highest remaining frequency.

### C++

```cpp
int leastInterval(vector<char>& arr, int n) {
    int total = arr.size();
    int freq[26] = {};
    for (char c : arr)
        freq[c - 'A']++;

    int time = 0;
    int nextAvail[26] = {};

    while (total > 0) {
        vector<int> avail;
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0 && nextAvail[i] <= time)
                avail.push_back(i);
        }

        if (!avail.empty()) {
            int chosen = avail[0];
            for (int index : avail) {
                if (freq[index] > freq[chosen])
                    chosen = index;
            }
            freq[chosen]--;
            total--;
            nextAvail[chosen] = time + n + 1;
        }
        time++;
    }
    return time;
}
```

### Java

```java
public int leastInterval(char[] arr, int n) {
    int total = arr.length;
    int[] freq = new int[26];
    for (char c : arr) freq[c - 'A']++;

    int time = 0;
    int[] nextAvailable = new int[26];

    while (total > 0) {
        ArrayList<Integer> available = new ArrayList<>();
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0 && nextAvailable[i] <= time)
                available.add(i);
        }

        if (!available.isEmpty()) {
            int chosen = available.get(0);
            for (int index : available) {
                if (freq[index] > freq[chosen]) chosen = index;
            }
            freq[chosen]--;
            total--;
            nextAvailable[chosen] = time + n + 1;
        }
        time++;
    }
    return time;
}
```

---

## Approach 2: Greedy + Max Heap — O(N)

**Idea:** Use a max heap to always execute the most frequent available task first. Process tasks in windows of size `n + 1` (one full cooldown cycle).

### Algorithm

1. Count the frequency of each character and push all frequencies into a **max heap**.
2. While the heap is not empty, take up to `n + 1` tasks from the heap:
   - Pop the top frequency, decrement it, and store it in a temporary list.
3. After the window, push back any tasks with remaining frequency > 0.
4. Add to time:
   - `temp.size()` — if the heap is now empty (last partial window)
   - `n + 1` — otherwise (full cooldown window)

### C++

```cpp
int leastInterval(vector<char>& tasks, int n) {
    vector<int> mp(26, 0);
    for (char& ch : tasks)
        mp[ch - 'A']++;

    priority_queue<int> pq;
    for (int i = 0; i < 26; i++)
        if (mp[i] > 0) pq.push(mp[i]);

    int time = 0;
    while (!pq.empty()) {
        vector<int> tmp;

        for (int i = 1; i <= n + 1; i++) {
            if (!pq.empty()) {
                int freq = pq.top(); pq.pop();
                tmp.push_back(--freq);
            }
        }

        for (int& f : tmp)
            if (f > 0) pq.push(f);

        time += pq.empty() ? tmp.size() : n + 1;
    }
    return time;
}
```

### Java

```java
public int leastInterval(char[] arr, int n) {
    int[] freqMap = new int[26];
    for (char c : arr)
        freqMap[c - 'A']++;

    PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());
    for (int f : freqMap)
        if (f > 0) pq.offer(f);

    int time = 0;
    while (!pq.isEmpty()) {
        ArrayList<Integer> temp = new ArrayList<>();

        for (int i = 1; i <= n + 1; i++) {
            if (!pq.isEmpty()) {
                int freq = pq.poll();
                temp.add(--freq);
            }
        }

        for (int f : temp)
            if (f > 0) pq.offer(f);

        time += pq.isEmpty() ? temp.size() : n + 1;
    }
    return time;
}
```

---

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Brute Force | O(N²) | O(1) |
| Greedy + Max Heap | O(N) | O(1) |
