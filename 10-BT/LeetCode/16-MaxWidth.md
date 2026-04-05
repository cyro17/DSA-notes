# Maximum Width of Binary Tree

> **LeetCode 662** | Difficulty: Medium | Topic: BFS, Binary Tree

---

## Problem Statement

Given the root of a binary tree, return the **maximum width** of the tree.

The width of one level is defined as the length between the **leftmost** and **rightmost** non-null nodes, including all null nodes in between.

---

## Approach — BFS with Index Tracking

Assign each node a **heap-style index**:
- Root → `0`
- Left child of node at `i` → `2*i + 1`
- Right child of node at `i` → `2*i + 2`

At each level, track the **first** and **last** index dequeued.

Width = `lastIndex - firstIndex + 1`

Since BFS processes nodes left to right, the first node dequeued at each level is always the leftmost, and the last is always the rightmost — no need to track min/max separately.

**Normalize** at each level by subtracting the base index to prevent overflow on deep trees.

---

## Complexity

| | |
|---|---|
| **Time** | O(N) — each node visited once |
| **Space** | O(W) — queue holds at most one level at a time |

---

## Java Solution

```java
class Pair {
    TreeNode node;
    long index;
    public Pair(TreeNode node, long index) {
        this.node = node;
        this.index = index;
    }
}

class Solution {
    private int bfs(TreeNode root) {
        if (root == null) return 0;

        Queue<Pair> q = new LinkedList<>();
        q.offer(new Pair(root, 0));
        int max = 0;

        while (!q.isEmpty()) {
            int size = q.size();
            long baseIndex = q.peek().index, firstIndex = 0, lastIndex = 0;

            for (int i = 0; i < size; i++) {
                Pair pair = q.poll();
                TreeNode node = pair.node;
                long index = pair.index - baseIndex;  // normalize

                if (i == 0) firstIndex = index;
                if (i == size - 1) lastIndex = index;

                if (node.left != null)  q.offer(new Pair(node.left,  2 * index + 1));
                if (node.right != null) q.offer(new Pair(node.right, 2 * index + 2));
            }

            max = (int) Math.max(lastIndex - firstIndex + 1, max);
        }

        return max;
    }

    public int widthOfBinaryTree(TreeNode root) {
        if (root == null) return 0;
        return bfs(root);
    }
}
```

---

## C++ Solution

```cpp
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;

        queue<pair<TreeNode*, long long>> q;
        q.push({root, 0});
        int max_ = 0;

        while (!q.empty()) {
            int size = q.size();
            long long base = q.front().second;
            long long l = 0, r = 0;

            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front().first;
                long long index = q.front().second - base;  // normalize
                q.pop();

                if (i == 0) l = index;
                if (i == size - 1) r = index;

                if (node->left)  q.push({node->left,  2 * index + 1});
                if (node->right) q.push({node->right, 2 * index + 2});
            }

            max_ = (int) max((long long)max_, r - l + 1);
        }

        return max_;
    }
};
```

---

## Dry Run — `[1,3,2,5,3,null,9]`

```
        1              index = 0
       / \
      3   2            3 → 1,  2 → 2
     / \    \
    5   3    9         5 → 3,  3 → 4,  9 → 6
```

| Level | baseIndex | firstIndex | lastIndex | Width |
|-------|-----------|------------|-----------|-------|
| 1     | 0         | 0          | 0         | 1     |
| 2     | 1         | 0          | 1         | 2     |
| 3     | 3         | 0          | 3         | **4** |

**Answer = 4** ✅

---

## ⚠️ Overflow — Why It Happens and How Normalization Fixes It

Without normalization, indices grow as `2^depth`. At depth 31, `2*index + 2` exceeds `Integer.MAX_VALUE` and silently wraps to a negative number.

**Normalization** subtracts the leftmost index at each level, resetting indices to start from `0` every level:

```
Without normalization — Level 30:  leftmost = 536870912, rightmost = 1073741820
With normalization    — Level 30:  leftmost = 0,         rightmost = 908
```

Width calculation is identical — `right - left + 1` gives the same result either way.

---

## Key Takeaways

- Heap indexing tracks **positional gaps** (null nodes) without storing nulls in the queue
- BFS processes left to right — `i == 0` and `i == size - 1` cleanly capture first and last index
- Always use `long long` (C++) or `long` (Java) for indices in heap-indexed tree problems
- Normalize at every level — subtract `base` before computing children's indices
