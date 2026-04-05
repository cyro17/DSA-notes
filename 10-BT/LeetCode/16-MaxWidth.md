# Maximum Width of Binary Tree

> **LeetCode 662** | Difficulty: Medium | Topic: BFS, Binary Tree

---

## Problem Statement

Given the root of a binary tree, return the **maximum width** of the tree.

The width of one level is defined as the length between the **leftmost** and **rightmost** non-null nodes, including all null nodes in between.

---

## Core Idea — Heap-Style Index Tracking

Assign each node a positional index:
- Root → `0`
- Left child of node at `i` → `2*i + 1`
- Right child of node at `i` → `2*i + 2`

This captures **null gaps** between nodes without storing nulls explicitly.

Width at any level = `rightmostIndex - leftmostIndex + 1`

> ⚠️ **Always use `long`/`long long` for indices and normalize at every level** — without normalization, indices grow as `2^depth` and overflow beyond depth 30.

---

## Approach 1 — BFS

Process nodes level by level. First node dequeued at each level = leftmost, last = rightmost.
Normalize by subtracting the leftmost index before pushing children.

### Complexity

| | |
|---|---|
| **Time** | O(N) |
| **Space** | O(W) — max width of the tree |

### Java

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
    public int widthOfBinaryTree(TreeNode root) {
        if (root == null) return 0;

        Queue<Pair> q = new LinkedList<>();
        q.offer(new Pair(root, 0));
        int max = 0;

        while (!q.isEmpty()) {
            int size = q.size();
            long base = q.peek().index;
            long first = 0, last = 0;

            for (int i = 0; i < size; i++) {
                Pair pair = q.poll();
                TreeNode node = pair.node;
                long index = pair.index - base;  // normalize

                if (i == 0) first = index;
                if (i == size - 1) last = index;

                if (node.left != null)  q.offer(new Pair(node.left,  2 * index + 1));
                if (node.right != null) q.offer(new Pair(node.right, 2 * index + 2));
            }

            max = (int) Math.max(last - first + 1, max);
        }

        return max;
    }
}
```

### C++

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

### Dry Run — `[1,3,2,5,3,null,9]`

```
        1              index = 0
       / \
      3   2            3 → 1,  2 → 2
     / \    \
    5   3    9         5 → 3,  3 → 4,  9 → 6
```

| Level | base | first | last | Width |
|-------|------|-------|------|-------|
| 1     | 0    | 0     | 0    | 1     |
| 2     | 1    | 0     | 1    | 2     |
| 3     | 3    | 0     | 3    | **4** |

**Answer = 4** ✅

---

## Approach 2 — DFS (Optimized Space)

Use **preorder DFS** (root → left → right). Since preorder always visits left before right, the first time we reach any depth it's always the leftmost node — store that index in a map.

Every subsequent visit to that depth computes width = `normalizedIndex + 1`.

### Complexity

| | |
|---|---|
| **Time** | O(N) |
| **Space** | O(H) — recursion stack (better than BFS for balanced trees) |

### C++

```cpp
using ll = long long;

class Solution {
private:
    void dfs(TreeNode* node, int depth, ll index,
        unordered_map<int, ll>& mp, ll& max_) {

        if (!node) return;

        if (mp.find(depth) == mp.end())
            mp[depth] = index;              // first visit = leftmost, save it

        ll nindex = index - mp[depth];      // normalize
        max_ = max(max_, nindex + 1);       // width = normalized index + 1

        dfs(node->left,  depth + 1, 2 * nindex + 1, mp, max_);
        dfs(node->right, depth + 1, 2 * nindex + 2, mp, max_);
    }

public:
    int widthOfBinaryTree(TreeNode* root) {
        unordered_map<int, ll> mp;
        ll max_ = 0;
        dfs(root, 0, 0LL, mp, max_);
        return (int) max_;
    }
};
```

### Dry Run — `[1,3,2,5,3,null,9]`

| Call | Node | depth | raw index | mp[depth] | nindex | max_ |
|------|------|-------|-----------|-----------|--------|------|
| 1    | 1    | 0     | 0         | 0 (saved) | 0      | 1    |
| 2    | 3    | 1     | 1         | 1 (saved) | 0      | 1    |
| 3    | 5    | 2     | 1         | 1 (saved) | 0      | 1    |
| 4    | 3    | 2     | 2         | 1 (skip)  | 1      | 2    |
| 5    | 2    | 1     | 2         | 1 (skip)  | 1      | 2    |
| 6    | 9    | 2     | 4         | 1 (skip)  | 3      | **4**|

**Answer = 4** ✅

---

## BFS vs DFS

| | BFS | DFS |
|---|---|---|
| Time | O(N) | O(N) |
| Space | O(W) — max level width | O(H) — recursion stack |
| Normalization | Subtract base at level start | Subtract `mp[depth]` before children |
| Better for | Skewed trees | Balanced trees |

---

## Key Takeaways

- Heap indexing captures null gaps without storing nulls in the queue
- BFS: use `i == 0` and `i == size - 1` to grab leftmost and rightmost index per level
- DFS: `putIfAbsent` / `mp.find` ensures only the leftmost index per depth is saved
- Always use `long`/`long long` + normalize — overflow is a silent bug that only surfaces on deep trees
