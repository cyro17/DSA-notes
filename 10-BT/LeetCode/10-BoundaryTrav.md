# Boundary Traversal of Binary Tree

## Problem Statement

Given the root of a binary tree, return its **boundary traversal** in **anti-clockwise** order starting from the root.

The boundary consists of three parts:
1. **Left boundary** — nodes on the leftmost path from root to the leftmost leaf (excluding the leaf itself)
2. **Leaf nodes** — all leaf nodes from left to right
3. **Right boundary** — nodes on the rightmost path from root to the rightmost leaf (excluding the leaf), added in **bottom-up** order

> A node is a leaf if it has no left or right child.

**Note:** The root itself is included once. If the root is a leaf, it is added only as a leaf.

---

### Example

```
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

**Output:** `[1, 2, 4, 5, 6, 7, 3]`

**Breakdown:**
- Root → `1`
- Left boundary (excl. leaf) → `2`
- Leaves (L to R) → `4, 5, 6, 7`
- Right boundary (excl. leaf, bottom-up) → `3`

---

## Approach — Simulation (Three-Pass)

**Idea:** Break the problem into three independent traversals — left boundary, leaf nodes, and right boundary — and merge them.

### Why three separate passes?

Each part of the boundary has a different traversal direction and exclusion rule:
- Left boundary: **top-down**, skip leaves
- Leaves: **in-order DFS**, all leaves
- Right boundary: **top-down collected, then reversed** (bottom-up), skip leaves

This separation avoids complex conditional logic in a single traversal.

---

### Step-by-Step Dry Run

**Tree:**
```
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

**Step 1 — Add root:** `res = [1]`

**Step 2 — Left boundary** (start at `root.left = 2`, top-down, exclude leaves):
- Node `2`: not a leaf → add `2`, has left child → go to `4`
- Node `4`: is a leaf → stop

`res = [1, 2]`

**Step 3 — Leaf nodes** (DFS over full tree):
- `1` → not leaf, go left
- `2` → not leaf, go left
- `4` → leaf → add `4`
- back to `2`, go right
- `5` → leaf → add `5`
- back to `1`, go right
- `3` → not leaf, go left
- `6` → leaf → add `6`
- back to `3`, go right
- `7` → leaf → add `7`

`res = [1, 2, 4, 5, 6, 7]`

**Step 4 — Right boundary** (start at `root.right = 3`, top-down collected, then reversed):
- Node `3`: not a leaf → collect `3`, has right child → go to `7`
- Node `7`: is a leaf → stop

Collected: `[3]` → reversed: `[3]` → append

`res = [1, 2, 4, 5, 6, 7, 3]`

---

### Complexity

| | Time | Space |
|---|---|---|
| Left boundary | O(H) | O(H) recursion stack |
| Leaf nodes | O(N) | O(H) recursion stack |
| Right boundary | O(H) | O(H) recursion stack |
| **Total** | **O(N)** | **O(H)** |

Where `N` = number of nodes, `H` = height of tree (O(log N) balanced, O(N) skewed).

---

## Java Implementation

```java
class Solution {

    private boolean isLeaf(Node node) {
        return node.left == null && node.right == null;
    }

    // Top-down, exclude leaves, prefer left child
    public void addLeftBoundary(Node node, List<Integer> res) {
        if (node == null || isLeaf(node)) return;
        res.add(node.data);
        if (node.left != null)  addLeftBoundary(node.left, res);
        else                    addLeftBoundary(node.right, res);
    }

    // Top-down collected, exclude leaves, prefer right child → added in reverse (bottom-up)
    public void addRightBoundary(Node node, List<Integer> res) {
        if (node == null || isLeaf(node)) return;
        if (node.right != null) addRightBoundary(node.right, res);
        else                    addRightBoundary(node.left, res);
        res.add(node.data);   // add AFTER recursion = bottom-up
    }

    // In-order DFS, add all leaves
    public void addLeaves(Node root, List<Integer> res) {
        if (root == null) return;
        if (isLeaf(root)) {
            res.add(root.data);
            return;
        }
        addLeaves(root.left, res);
        addLeaves(root.right, res);
    }

    ArrayList<Integer> boundaryTraversal(Node root) {
        ArrayList<Integer> res = new ArrayList<>();
        if (root == null) return res;

        if (!isLeaf(root)) res.add(root.data); // root added once, only if not a leaf

        addLeftBoundary(root.left, res);
        addLeaves(root, res);
        addRightBoundary(root.right, res);

        return res;
    }
}
```

---

## C++ Implementation

> ⚠️ **Bug Fix:** The iterative `LeftBoundary` and `RightBoundary` in the naive version below had a missing `else` before the `curr->right` assignment, causing **both** branches to execute on every iteration. This makes the pointer advance twice per loop, skipping nodes and producing wrong results. Fixed below using `else if`.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left, *right;
    Node(int x) : val(x), left(NULL), right(NULL) {}
};

bool isLeaf(Node* node) {
    return !node->left && !node->right;
}

// Iterative: top-down, exclude leaves, prefer left child
void addLeftBoundary(Node* root, vector<int>& res) {
    Node* curr = root->left;
    while (curr) {
        if (!isLeaf(curr)) res.push_back(curr->val);
        if      (curr->left)  curr = curr->left;
        else if (curr->right) curr = curr->right;  // ← 'else if', not 'if'
        else                  break;
    }
}

// Iterative: top-down, exclude leaves, prefer right child → reverse for bottom-up
void addRightBoundary(Node* root, vector<int>& res) {
    Node* curr = root->right;
    vector<int> temp;
    while (curr) {
        if (!isLeaf(curr)) temp.push_back(curr->val);
        if      (curr->right) curr = curr->right;  // ← 'else if', not 'if'
        else if (curr->left)  curr = curr->left;
        else                  break;
    }
    // Append in reverse for bottom-up order
    for (int i = temp.size() - 1; i >= 0; i--)
        res.push_back(temp[i]);
}

// Recursive: add all leaf nodes L to R
void addLeaves(Node* root, vector<int>& res) {
    if (!root) return;
    if (isLeaf(root)) {
        res.push_back(root->val);
        return;
    }
    addLeaves(root->left, res);
    addLeaves(root->right, res);
}

vector<int> boundaryTraversal(Node* root) {
    vector<int> res;
    if (!root) return res;

    if (!isLeaf(root)) res.push_back(root->val);

    addLeftBoundary(root, res);
    addLeaves(root, res);
    addRightBoundary(root, res);

    return res;
}
```

---

## Key Observations

| Detail | Why it matters |
|---|---|
| Root added only if not a leaf | Prevents double-counting when the root is also a leaf node |
| Left boundary starts at `root.left` | Root is already added separately |
| Right boundary starts at `root.right` | Same reason; also avoids duplicating the root |
| Right boundary added **after** recursion (Java) / reversed (C++) | Produces bottom-up order as required |
| `else if` (not `if`) when advancing the pointer in iterative C++ | Without `else`, pointer advances twice per loop — skipping nodes |

---

## Edge Cases

| Input | Expected Output |
|---|---|
| Single node (root only) | `[root.val]` |
| Left-skewed tree | Left boundary + leaf (last node) |
| Right-skewed tree | Leaf (first node) + right boundary |
| Complete binary tree | Full boundary anti-clockwise |
| Root is a leaf | Just `[root.val]` |
