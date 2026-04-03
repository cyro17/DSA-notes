# Vertical Order Traversal of a Binary Tree

## Problem Statement

Given the `root` of a binary tree, return the **vertical order traversal** of its nodes' values.

For each node at position `(row, col)`:
- The root is at `(0, 0)`
- Left child of a node at `(row, col)` is at `(row + 1, col - 1)`
- Right child of a node at `(row, col)` is at `(row + 1, col + 1)`

The vertical order traversal is a list of top-to-bottom orderings for **each column index** from leftmost to rightmost. If two nodes share the same `(row, col)`, sort them by value.

---

### Example

```
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

| Node | Vertical | Level |
|------|----------|-------|
| 1    | 0        | 0     |
| 2    | -1       | 1     |
| 3    | +1       | 1     |
| 4    | -2       | 2     |
| 5    | 0        | 2     |
| 6    | 0        | 2     |
| 7    | +2       | 2     |

> Nodes `5` and `6` collide at `(vertical=0, level=2)` → sorted by value → `5` before `6`

**Output:** `[[4], [2], [1, 5, 6], [3], [7]]`

---

## Approach — BFS + Sorted Map

### Core Idea

Assign every node a **coordinate pair `(vertical, level)`** during BFS. Then group and sort:
- By **vertical** (left column → right column)
- Within each vertical, by **level** (top → bottom)
- Within the same `(vertical, level)`, by **value** (ascending)

### Why BFS over DFS?

BFS processes nodes level by level, which aligns naturally with the `level` coordinate. While DFS also works (since `TreeMap` handles sorting), BFS avoids any risk of out-of-order insertions and is more intuitive for level-aware problems.

---

### Data Structure Breakdown

```
TreeMap<Integer,                      ← vertical (col), auto-sorted L→R
  TreeMap<Integer,                    ← level (row), auto-sorted top→bottom
    PriorityQueue<Integer>            ← node values at same (v, level), min-heap
  >
>
```

| Layer | Type | Purpose |
|-------|------|---------|
| Outer key | `TreeMap` | Sorts columns left → right automatically |
| Inner key | `TreeMap` | Sorts rows top → bottom within a column |
| Value | `PriorityQueue` | Sorts colliding node values in ascending order |

> **Why `PriorityQueue` and not `List`?**
> When two nodes land on the **same vertical AND same level**, they must appear in ascending value order. A min-heap (`PriorityQueue`) guarantees this on `poll()` without a manual sort step.

---

### Step-by-Step Dry Run

**Tree:**
```
        1         (v=0,  l=0)
       / \
      2   3       (v=-1, l=1) and (v=+1, l=1)
     / \ / \
    4  5 6  7     (v=-2,l=2), (v=0,l=2), (v=0,l=2), (v=+2,l=2)
```

**BFS Queue processing:**

| Step | Node Polled | (v, l)   | Left Child pushed      | Right Child pushed     |
|------|-------------|----------|------------------------|------------------------|
| 1    | 1           | (0, 0)   | 2 → (-1, 1)            | 3 → (+1, 1)            |
| 2    | 2           | (-1, 1)  | 4 → (-2, 2)            | 5 → (0, 2)             |
| 3    | 3           | (+1, 1)  | 6 → (0, 2)             | 7 → (+2, 2)            |
| 4    | 4           | (-2, 2)  | —                      | —                      |
| 5    | 5           | (0, 2)   | —                      | —                      |
| 6    | 6           | (0, 2)   | —                      | —                      |
| 7    | (+2, 2)     | (+2, 2)  | —                      | —                      |

**Map state after BFS:**

```
vertical -2 → { level 2 → PQ[4] }
vertical -1 → { level 1 → PQ[2] }
vertical  0 → { level 0 → PQ[1],
                level 2 → PQ[5, 6] }   ← collision, PQ sorts them
vertical +1 → { level 1 → PQ[3] }
vertical +2 → { level 2 → PQ[7] }
```

**Result construction (iterate outer → inner → poll PQ):**

```
[-2] → [4]
[-1] → [2]
[ 0] → poll level 0: 1 | poll level 2: 5, 6 → [1, 5, 6]
[+1] → [3]
[+2] → [7]
```

**Final output:** `[[4], [2], [1, 5, 6], [3], [7]]` ✅

---

## Complexity Analysis

| Phase | Time | Space |
|-------|------|-------|
| BFS traversal | O(N) | O(N) — queue |
| Map insertions | O(N log N) | O(N) — map storage |
| PriorityQueue offers | O(N log N) worst case | — |
| Result construction | O(N log N) | O(N) — output list |
| **Total** | **O(N log N)** | **O(N)** |

> The `log N` factor comes from `TreeMap` insertions (balanced BST under the hood) and `PriorityQueue` operations. In practice the constant is small since collisions at the same `(v, level)` are rare.

---

## Java Implementation

```java
class Tuple {
    TreeNode node;
    int vertical;
    int level;

    public Tuple(TreeNode node, int vertical, int level) {
        this.node = node;
        this.vertical = vertical;
        this.level = level;
    }
}

class Solution {
    public List<List<Integer>> verticalTraversal(TreeNode root) {
        List<List<Integer>> res = new ArrayList<>();
        if (root == null) return res;

        // BFS queue storing node with its (vertical, level) coordinates
        Queue<Tuple> q = new LinkedList<>();
        q.offer(new Tuple(root, 0, 0));

        // Outer TreeMap: vertical → Inner TreeMap: level → PQ of values
        TreeMap<Integer, TreeMap<Integer, PriorityQueue<Integer>>> nodes = new TreeMap<>();

        while (!q.isEmpty()) {
            Tuple t = q.poll();
            TreeNode node = t.node;
            int v = t.vertical;
            int level = t.level;

            // Lazily initialize nested maps
            nodes.putIfAbsent(v, new TreeMap<>());
            nodes.get(v).putIfAbsent(level, new PriorityQueue<>());
            nodes.get(v).get(level).offer(node.val);

            // Left child: same level + 1, vertical - 1
            if (node.left != null)
                q.offer(new Tuple(node.left, v - 1, level + 1));

            // Right child: same level + 1, vertical + 1
            if (node.right != null)
                q.offer(new Tuple(node.right, v + 1, level + 1));
        }

        // Build result: outer TreeMap iterates verticals L→R,
        // inner TreeMap iterates levels top→bottom,
        // PriorityQueue polls values in ascending order
        for (TreeMap<Integer, PriorityQueue<Integer>> mp : nodes.values()) {
            List<Integer> tmp = new ArrayList<>();
            for (PriorityQueue<Integer> pq : mp.values()) {
                while (!pq.isEmpty()) {
                    tmp.add(pq.poll());
                }
            }
            res.add(tmp);
        }

        return res;
    }
}
```

---

## Key Observations

| Detail | Why it matters |
|--------|----------------|
| `TreeMap` for vertical | Automatically iterates columns left → right, no manual sorting needed |
| `TreeMap` for level | Automatically iterates rows top → bottom within a column |
| `PriorityQueue` for values | Handles the tiebreaker: same `(vertical, level)` → ascending value order |
| `putIfAbsent` | Avoids overwriting existing entries; safe lazy initialization |
| BFS over DFS | Level coordinate increments naturally with BFS; no risk of processing a deeper node before a shallower one |

---

## Edge Cases

| Input | Expected Output |
|-------|-----------------|
| Single node | `[[root.val]]` |
| Left-skewed tree | One node per column, all in separate lists |
| Right-skewed tree | One node per column, all in separate lists |
| Two nodes at same `(v, level)` | Sorted ascending in the same column list |
| `null` root | `[]` |
