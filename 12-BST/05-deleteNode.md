# Delete Node in a BST

**Problem:** [LeetCode 450 – Delete Node in a BST](https://leetcode.com/problems/delete-node-in-a-bst/)  
**Difficulty:** Medium  
**Topic Tags:** Binary Search Tree, Tree, Recursion

---

## Problem Statement

Given the root of a Binary Search Tree (BST) and a key, delete the node with that key and return the updated root. The BST structure must be maintained after deletion.

---

## Key Observations

1. In a BST, for any node `n`: all values in the left subtree < `n.val` < all values in the right subtree.
2. Deletion has three cases based on the target node's children:
   - **No children (leaf):** Simply remove it.
   - **One child:** Replace the node with its only child.
   - **Two children:** Merge the two subtrees. The standard strategy is to attach the right subtree to the rightmost node of the left subtree, then return the left subtree as the replacement.

---

## Approach 1 – Iterative (Two-Pass with Parent Tracking)

This is the approach implemented in the submitted code.

### Intuition

- **Pass 1:** Use `findTarget` to confirm the key exists.
- **Pass 2:** Walk the tree again to find the **parent** of the target node, then rewire the parent's pointer using a `helper` function.
- `helper(node)` handles the three deletion cases and returns the correct replacement subtree.

### Helper: `findRight`

Finds the rightmost node in a subtree — used to attach the right subtree when the deleted node has two children.

```
findRight(node):
    walk right until node.right == null
    return that node
```

### Helper: `helper(node)` — the actual deletion logic

```
helper(node):
    if node.left == null → return node.right       // no left child
    if node.right == null → return node.left       // no right child

    // Two children:
    lastRight = findRight(node.left)               // rightmost of left subtree
    lastRight.right = node.right                   // attach right subtree there
    return node.left                               // left subtree is the new root
```

### Main Logic: `deleteNode`

```
deleteNode(root, key):
    if root == null → return null

    confirm key exists via findTarget (early exit if not found)

    if root.val == key → return helper(root)       // special case: deleting root

    tmp = root
    while tmp != null:
        if tmp.val > key:
            if tmp.left.val == key → tmp.left = helper(tmp.left); break
            else → go left
        else:
            if tmp.right.val == key → tmp.right = helper(tmp.right); break
            else → go right

    return root
```

---

## Dry Run — Approach 1

### Input Tree

```
        5
       / \
      3   6
     / \   \
    2   4   7

key = 3
```

**Pass 1 – `findTarget`:** Traverses 5 → 3, finds the node. Confirms it exists.

**Pass 2 – parent search:**
- `tmp = 5`, `5 > 3` → check `tmp.left.val == 3` ✅
- Call `helper(node_3)`

**`helper(node_3)` — node has two children (left=2, right=4):**
- `findRight(node_2)` → node_2 (no right child, it is the rightmost)
- `node_2.right = node_4`
- Return `node_2`

**Rewire:** `node_5.left = node_2`

### Output Tree

```
        5
       / \
      2   6
       \   \
        4   7
```

BST property holds ✅ (2 < 4 < 5 < 6 < 7)

---

## Approach 2 – Recursive (Cleaner, Standard)

### Intuition

Use the BST property to navigate directly to the target node. On the way back up (unwinding recursion), rewire the tree by returning the correct replacement node.

### Code

```java
public TreeNode deleteNode(TreeNode root, int key) {
    if (root == null) return null;

    if (key < root.val) {
        root.left = deleteNode(root.left, key);
    } else if (key > root.val) {
        root.right = deleteNode(root.right, key);
    } else {
        // Found the node to delete
        if (root.left == null) return root.right;
        if (root.right == null) return root.left;

        // Two children: find rightmost of left subtree
        TreeNode lastRight = root.left;
        while (lastRight.right != null) lastRight = lastRight.right;
        lastRight.right = root.right;
        return root.left;
    }

    return root;
}
```

### Dry Run — Approach 2

Same tree, key = 3:

```
deleteNode(5, 3)
  → 3 < 5, so: root.left = deleteNode(3, 3)
      → key == root.val, two children
      → findRight(2) → node_2 (no right child)
      → node_2.right = node_4
      → return node_2
  → root.left = node_2
  → return node_5
```

Output tree is identical to Approach 1. ✅

---

## Complexity Analysis

| | Approach 1 (Iterative, Two-Pass) | Approach 2 (Recursive, Single-Pass) |
|---|---|---|
| **Time – Average** | O(H) + O(H) = O(H) | O(H) |
| **Time – Worst Case** | O(N) | O(N) |
| **Space** | O(H) for `findTarget` recursion | O(H) for call stack |
| **Space – Worst Case** | O(N) | O(N) |

Where:
- **H** = height of the BST
- **Balanced BST:** H = O(log N)
- **Skewed BST (worst case):** H = O(N)

### Overhead Comparison

- Approach 1 makes **two passes** over the tree (once for `findTarget`, once for parent search). Asymptotically still O(H), but with a larger constant.
- Approach 2 makes **one pass**, touching each node on the path at most once. Preferred in interviews for its clarity and efficiency.
- Both approaches perform an extra O(H) walk inside `findRight` / `lastRight` traversal, but this is bounded by H and doesn't change the overall complexity class.

---

## Edge Cases

| Case | Behaviour |
|---|---|
| `root == null` | Return `null` |
| Key not present | Return `root` unchanged |
| Delete root (no children) | Return `null` |
| Delete root (one child) | Return that child |
| Delete root (two children) | Merge subtrees, return left |
| Skewed tree (all nodes in a line) | O(N) time, O(N) stack space |

---

## Summary

| | Approach 1 – Iterative Two-Pass | Approach 2 – Recursive Single-Pass |
|---|---|---|
| Passes | 2 (find + parent search) | 1 |
| Code length | Longer, more explicit | Concise |
| Stack usage | Partial (only findTarget recurses) | Full recursion depth |
| Interview preference | Demonstrates iterative skill | ✅ Preferred for clarity |
| Handles all cases | ✅ | ✅ |

**Recommended approach for interviews:** Approach 2 (recursive). It is concise, readable, and directly mirrors the BST invariant logic. Approach 1 is valid and demonstrates iterative thinking, but the double-traversal is a minor inefficiency worth noting.

---

## Full Code

### Approach 1 – Iterative Two-Pass (Your Solution)

```java
class Solution {
    private TreeNode findTarget(TreeNode root, int key) {
        if (root == null) return null;
        if (root.val == key) return root;
        if (root.val > key) return this.findTarget(root.left, key);
        else return this.findTarget(root.right, key);
    }

    private TreeNode findRight(TreeNode node) {
        if (node == null) return null;
        while (node.right != null) node = node.right;
        return node;
    }

    private TreeNode helper(TreeNode node) {
        if (node.left == null) return node.right;
        else if (node.right == null) return node.left;

        TreeNode lastRight = this.findRight(node.left);
        lastRight.right = node.right;
        return node.left;
    }

    public TreeNode deleteNode(TreeNode root, int key) {
        if (root == null) return null;

        TreeNode target = this.findTarget(root, key);
        if (target == null) return root;

        if (root.val == key) return this.helper(root);

        TreeNode tmp = root;
        while (tmp != null) {
            if (tmp.val > key) {
                if (tmp.left != null && tmp.left.val == key) {
                    tmp.left = this.helper(tmp.left);
                    break;
                } else {
                    tmp = tmp.left;
                }
            } else {
                if (tmp.right != null && tmp.right.val == key) {
                    tmp.right = this.helper(tmp.right);
                    break;
                } else {
                    tmp = tmp.right;
                }
            }
        }
        return root;
    }
}
```

---

### Approach 2 – Recursive Single-Pass (Recommended)

```java
class Solution {
    public TreeNode deleteNode(TreeNode root, int key) {
        if (root == null) return null;

        if (key < root.val) {
            root.left = deleteNode(root.left, key);
        } else if (key > root.val) {
            root.right = deleteNode(root.right, key);
        } else {
            // Node to delete found
            if (root.left == null) return root.right;
            if (root.right == null) return root.left;

            // Two children: attach right subtree to rightmost of left subtree
            TreeNode lastRight = root.left;
            while (lastRight.right != null) lastRight = lastRight.right;
            lastRight.right = root.right;
            return root.left;
        }

        return root;
    }
}
```
