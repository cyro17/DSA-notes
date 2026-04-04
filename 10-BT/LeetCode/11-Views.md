# Binary Tree Views

A collection of **Top View**, **Bottom View**, **Left View**, and **Right View** traversals of a Binary Tree — each in Java and C++.

---

## Table of Contents
- [Core Intuition](#core-intuition)
- [Top View](#1-top-view)
- [Bottom View](#2-bottom-view)
- [Left View](#3-left-view)
- [Right View](#4-right-view)
- [Comparison Summary](#comparison-summary)

---

## Core Intuition

All four view problems share the same coordinate system:

```
         1          (vertical=0,  level=0)
        / \
       2   3        (vertical=-1, level=1) and (vertical=+1, level=1)
      / \ / \
     4  5 6  7      (vertical=-2,level=2) ... (vertical=+2,level=2)
```

- **Vertical** (column) — root is `0`, left child is `v-1`, right child is `v+1`
- **Level** (row) — root is `0`, every child is `parent_level + 1`

| View | Axis used | Keep |
|------|-----------|------|
| Top View | vertical | shallowest node per vertical |
| Bottom View | vertical | deepest node per vertical |
| Left View | level | leftmost node per level |
| Right View | level | rightmost node per level |

---

## 1. Top View

> Return the first node visible at each vertical column when viewed from above.

**Key idea:** BFS processes nodes top-down. The **first time** a vertical is seen = the shallowest node at that vertical. Use `putIfAbsent` / `mp.find() == mp.end()` to never overwrite.

### Java

```java
class Tuple {
    Node node;
    int y; // vertical
    int x; // level

    Tuple(Node node, int y, int x) {
        this.node = node;
        this.y = y;
        this.x = x;
    }
}

class Solution {

    private TreeMap<Integer, Node> bfs(Node root) {
        Queue<Tuple> q = new LinkedList<>();
        q.offer(new Tuple(root, 0, 0));

        TreeMap<Integer, Node> map = new TreeMap<>();

        while (!q.isEmpty()) {
            Tuple t = q.poll();
            Node node = t.node;
            int y = t.y;

            map.putIfAbsent(y, node);      // first seen = topmost

            if (node.left != null)  q.offer(new Tuple(node.left,  y - 1, t.x + 1));
            if (node.right != null) q.offer(new Tuple(node.right, y + 1, t.x + 1));
        }
        return map;
    }

    public ArrayList<Integer> topView(Node root) {
        ArrayList<Integer> list = new ArrayList<>();
        TreeMap<Integer, Node> map = this.bfs(root);
        map.forEach((v, node) -> list.add(node.data));
        return list;
    }
}
```

### C++

```cpp
vector<int> topView(Node* root) {
    vector<int> res;
    if (!root) return res;

    map<int, int> mp;
    queue<pair<Node*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        auto it = q.front();
        q.pop();
        Node* node = it.first;
        int line = it.second;

        if (mp.find(line) == mp.end())   // first seen = topmost
            mp[line] = node->data;

        if (node->left)  q.push({node->left,  line - 1});
        if (node->right) q.push({node->right, line + 1});
    }

    for (auto it : mp)
        res.push_back(it.second);

    return res;
}
```

### Complexity

| | Time | Space |
|--|------|-------|
| BFS | O(N) | O(N) |
| Map ops | O(N log N) | O(N) |
| **Total** | **O(N log N)** | **O(N)** |

---

## 2. Bottom View

> Return the last node visible at each vertical column when viewed from below.

**Key idea:** Same BFS as top view, but **always overwrite** with `put` / `mp[line] = val`. Since BFS goes top-down, the last write to any vertical = the deepest node at that vertical.

### Java

```java
class Solution {

    private TreeMap<Integer, Node> bfs_bottom(Node root) {
        Queue<Tuple> q = new LinkedList<>();
        q.offer(new Tuple(root, 0, 0));

        TreeMap<Integer, Node> map = new TreeMap<>();

        while (!q.isEmpty()) {
            Tuple t = q.poll();
            Node node = t.node;
            int y = t.y;

            map.put(y, node);              // always overwrite = deepest

            if (node.left != null)  q.offer(new Tuple(node.left,  y - 1, t.x + 1));
            if (node.right != null) q.offer(new Tuple(node.right, y + 1, t.x + 1));
        }
        return map;
    }

    public ArrayList<Integer> bottomView(Node root) {
        ArrayList<Integer> list = new ArrayList<>();
        TreeMap<Integer, Node> map = this.bfs_bottom(root);
        map.forEach((v, node) -> list.add(node.data));
        return list;
    }
}
```

### C++

```cpp
vector<int> bottomView(Node* root) {
    vector<int> res;
    if (!root) return res;

    map<int, int> mp;
    queue<pair<Node*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        auto it = q.front();
        q.pop();
        Node* node = it.first;
        int line = it.second;

        mp[line] = node->data;             // always overwrite = deepest

        if (node->left)  q.push({node->left,  line - 1});
        if (node->right) q.push({node->right, line + 1});
    }

    for (auto it : mp)
        res.push_back(it.second);

    return res;
}
```

### Complexity

| | Time | Space |
|--|------|-------|
| **Total** | **O(N log N)** | **O(N)** |

> Top view vs Bottom view is a **single method change**: `putIfAbsent` → `put`.

---

## 3. Left View

> Return the first node visible at each level when viewed from the left.

**Key idea:** The first node at each level is the leftmost. Two approaches:

- **BFS:** Pick the first node in each level's batch (`i == 0`)
- **DFS:** Pre-order traversal (root → left → right). The first time `list.size() == level`, that node is the leftmost at that level — add it and never overwrite

### Java — BFS

```java
class Solution {

    private void bfs(Node root, ArrayList<Integer> list) {
        if (root == null) return;

        Queue<Node> q = new LinkedList<>();
        q.offer(root);

        while (!q.isEmpty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                Node node = q.poll();

                if (i == 0) list.add(node.data);    // first in level = leftmost

                if (node.left != null)  q.offer(node.left);
                if (node.right != null) q.offer(node.right);
            }
        }
    }

    public ArrayList<Integer> leftView(Node root) {
        ArrayList<Integer> list = new ArrayList<>();
        this.bfs(root, list);
        return list;
    }
}
```

### Java — DFS

```java
class Solution {

    private void dfs(Node node, int level, ArrayList<Integer> list) {
        if (node == null) return;

        if (list.size() == level)          // first visit at this level = leftmost
            list.add(node.data);

        dfs(node.left,  level + 1, list);
        dfs(node.right, level + 1, list);
    }

    public ArrayList<Integer> leftView(Node root) {
        ArrayList<Integer> list = new ArrayList<>();
        this.dfs(root, 0, list);
        return list;
    }
}
```

### C++ — DFS

```cpp
void utilLeft(Node* root, int level, vector<int>& res) {
    if (!root) return;

    if (res.size() == level)               // first visit at this level = leftmost
        res.push_back(root->val);

    utilLeft(root->left,  level + 1, res);
    utilLeft(root->right, level + 1, res);
}

vector<int> leftView(Node* root) {
    vector<int> res;
    utilLeft(root, 0, res);
    return res;
}
```

### Why does `list.size() == level` work?

`list` grows by exactly one entry per level, only when a new level is seen for the first time. Since DFS goes left before right, the first node to hit any unseen level is always the leftmost node at that level.

### Complexity

| Approach | Time | Space |
|----------|------|-------|
| BFS | O(N) | O(N) queue |
| DFS | O(N) | O(H) stack — H = height |

> DFS is more space-efficient on balanced trees: O(log N) vs O(N).

---

## 4. Right View

> Return the last node visible at each level when viewed from the right.

**Key idea:** Mirror of left view.

- **BFS:** Pick the **last** node in each level's batch (`i == size - 1`) or `row.back()`
- **DFS:** Go **right before left**. The first time `list.size() == level` now captures the rightmost node

### C++ — BFS

```cpp
vector<int> rightSideView(TreeNode* root) {
    vector<int> right;
    if (!root) return right;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        vector<int> level;

        while (size--) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }

        right.push_back(level.back());     // last in level = rightmost
    }
    return right;
}
```

### C++ — DFS

```cpp
void utilRight(Node* root, int level, vector<int>& res) {
    if (!root) return;

    if (res.size() == level)               // first visit at this level = rightmost
        res.push_back(root->val);          // because we go right before left

    utilRight(root->right, level + 1, res);
    utilRight(root->left,  level + 1, res);
}

vector<int> rightView(Node* root) {
    vector<int> res;
    utilRight(root, 0, res);
    return res;
}
```

### Complexity

| Approach | Time | Space |
|----------|------|-------|
| BFS | O(N) | O(N) |
| DFS | O(N) | O(H) |

---

## Comparison Summary

| Problem | BFS pick | DFS traversal order | One-liner difference |
|---------|----------|---------------------|----------------------|
| Top View | `putIfAbsent` on vertical | — | First per vertical |
| Bottom View | `put` (overwrite) on vertical | — | Last per vertical |
| Left View | First node per level (`i == 0`) | Root → Left → Right | First per level |
| Right View | Last node per level (`i == size-1`) | Root → Right → Left | Last per level |

> Top/Bottom view use a **vertical axis** with a `TreeMap`.
> Left/Right view use a **level axis** — BFS batch or DFS pre-order trick.
