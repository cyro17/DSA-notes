# Celebrity Problem

A **celebrity** is someone who:
- Is **known by everyone** else in the room
- **Knows nobody** else in the room

Given an `n×n` matrix `arr` where `arr[i][j] = 1` means person `i` knows person `j`, find the celebrity. Return `-1` if none exists.

---

## Key Observations

```
Celebrity conditions:
  arr[celebrity][i] == 0  for all i ≠ celebrity  (knows nobody)
  arr[i][celebrity] == 1  for all i ≠ celebrity  (known by everyone)

At most ONE celebrity can exist.
Why? If A and B are both celebrities:
  A must know nobody → A doesn't know B
  But B is celebrity → everyone knows B → A knows B
  Contradiction ❌
```

---

## Approach 1 — Brute Force (Count indegree/outdegree)

### Idea

For every person, count:
- `knowMe[j]` — how many people know person `j` (indegree)
- `Iknow[i]` — how many people person `i` knows (outdegree)

Celebrity = person with `knowMe == n-1` and `Iknow == 0`.

### Implementation (C++)

```cpp
class Solution {
public:
    int celebrity(vector<vector<int>>& arr) {
        int n = arr.size();
        vector<int> knowMe(n, 0);   // indegree
        vector<int> Iknow(n, 0);    // outdegree

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && arr[i][j] == 1) {
                    knowMe[j]++;    // j is known by i
                    Iknow[i]++;     // i knows j
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (knowMe[i] == n - 1 && Iknow[i] == 0)
                return i;
        }

        return -1;
    }
};
```

### Dry Run

```
arr = [[0,1,0],
       [0,0,0],
       [1,1,0]]
n = 3
```

Matrix scan:
```
i=0,j=1: arr[0][1]=1 → knowMe[1]++, Iknow[0]++
i=0,j=2: arr[0][2]=0 → skip
i=1,j=0: arr[1][0]=0 → skip
i=1,j=2: arr[1][2]=0 → skip
i=2,j=0: arr[2][0]=1 → knowMe[0]++, Iknow[2]++
i=2,j=1: arr[2][1]=1 → knowMe[1]++, Iknow[2]++

knowMe = [1, 2, 0]
Iknow  = [1, 0, 2]

check i=0: knowMe[0]=1 ≠ 2 → no
check i=1: knowMe[1]=2 == n-1, Iknow[1]=0 → ✅ celebrity
check i=2: knowMe[2]=0 ≠ 2 → no
```

**Answer: 1 ✅**

### Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O(n²) | Two nested loops over matrix |
| **Space** | O(n) | Two arrays of size n |

---

## Approach 2 — Two Pointer Elimination (Optimal)

### Idea

Use two pointers `l` and `r` converging from both ends. At each step, use one matrix lookup to **eliminate** one candidate:

```
arr[l][r] == 1 → l knows r → l CANNOT be celebrity → l++
arr[l][r] == 0 → l doesn't know r → r CANNOT be celebrity → r--
```

After elimination, one candidate remains at `l`. Then **verify** it satisfies both celebrity conditions.

### Why This Works

Every step eliminates exactly one candidate using one lookup. After `n-1` eliminations, one person remains — the only possible celebrity. Verification confirms it.

```
arr[l][r] == 1:
  l knows someone → l is not celebrity → safely eliminate l

arr[l][r] == 0:
  r is not known by l → r is not celebrity → safely eliminate r

Both can't be celebrity simultaneously:
  if arr[l][r]==0 AND arr[r][l]==0 → eliminate either (both gone)
  if arr[l][r]==1 AND arr[r][l]==1 → eliminate either (both know someone)
```

### Three Cases During Elimination

| `arr[l][r]` | `arr[r][l]` | Meaning | Action |
|-------------|-------------|---------|--------|
| 1 | - | l knows r → l not celebrity | `l++` |
| 0 | 1 | r knows l → r not celebrity | `r--` |
| 0 | 0 | neither knows other → both out | `l++, r--` |

### Implementation (C++)

```cpp
class Solution {
public:
    int celebrity(vector<vector<int>>& arr) {
        int n = arr.size();
        int l = 0, r = n - 1;

        // elimination phase
        while (l < r) {
            if (arr[l][r] == 1) {
                l++;           // l knows r → l not celebrity
                continue;
            } else if (arr[r][l] == 1) {
                r--;           // r knows l → r not celebrity
                continue;
            } else {
                l++; r--;      // neither knows other → both eliminated
            }
        }

        // verification phase — confirm l is actually celebrity
        for (int i = 0; i < n; i++) {
            if (arr[i][l] != 1 ||              // someone doesn't know l
               (i != l && arr[l][i] == 1))     // l knows someone
                return -1;
        }

        return l;
    }
};
```

### Dry Run

```
arr = [[0,1,0],
       [0,0,0],
       [1,1,0]]
n=3, l=0, r=2
```

**Elimination phase:**

| l | r | arr[l][r] | arr[r][l] | action |
|---|---|-----------|-----------|--------|
| 0 | 2 | arr[0][2]=0 | arr[2][0]=1 | r-- |
| 0 | 1 | arr[0][1]=1 | — | l++ |
| 1 | 1 | l==r → exit | | |

Candidate = `l = 1`

**Verification (i=0,1,2):**
```
i=0: arr[0][1]=1 ✅ (0 knows 1), arr[1][0]=0 ✅ (1 doesn't know 0)
i=1: skip (i==l)
i=2: arr[2][1]=1 ✅ (2 knows 1), arr[1][2]=0 ✅ (1 doesn't know 2)
```

**Answer: 1 ✅**

---

```
arr = [[0,1],    no celebrity case
       [1,0]]
n=2, l=0, r=1
```

**Elimination:**
```
arr[0][1]=1 → l++ → l=1, r=1 → exit
candidate = l=1
```

**Verification:**
```
i=0: arr[0][1]=1 ✅, arr[1][0]=1 ❌ (celebrity knows someone)
→ return -1
```

**Answer: -1 ✅**

### Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O(n) | Elimination: O(n) steps. Verification: O(n) pass |
| **Space** | O(1) | Only two pointers |

---

## Comparison

| | Brute Force | Two Pointer |
|-|-------------|-------------|
| **Time** | O(n²) | O(n) |
| **Space** | O(n) | O(1) |
| **Matrix lookups** | n² | ≤ 2n |
| **Approach** | Count indegree/outdegree | Eliminate + verify |
| **Intuition** | Straightforward | Requires insight |

---

## Key Takeaways

- At most one celebrity can exist — proven by contradiction.
- **Brute force** counts indegree (knowMe) and outdegree (Iknow) for every person — celebrity has indegree `n-1` and outdegree `0`.
- **Two pointer** uses the elimination insight — every lookup eliminates at least one candidate. After `n-1` eliminations, one candidate remains.
- Verification is mandatory after elimination — the last surviving candidate isn't guaranteed to be a celebrity, just the only possible one.
- Two pointer reduces matrix lookups from O(n²) to O(n) — same matrix, dramatically fewer accesses.
