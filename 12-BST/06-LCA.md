# Lowest Common Ancestor — Binary Search Tree

Find the **Lowest Common Ancestor (LCA)** of two nodes `p` and `q` in a **Binary Search Tree**.

> **LCA** = the deepest node that has both `p` and `q` as descendants (a node is a descendant of itself).

---

## Why BST Makes This Easier

In a **general binary tree**, you must visit every node — O(n) always.  
In a **BST**, ordering lets you **prune** at every step — you always know which subtree to go into.

---

## Approach 1 — Recursive DFS

### Key Idea

At each node, use BST ordering to decide direction:

| Condition | Action |
|-----------|--------|
| Both `p`, `q` < `node` | LCA is in left subtree |
| Both `p`, `q` > `node` | LCA is in right subtree |
| They split (or one equals `node`) | Current node is the LCA |

### Implementation (Java)

```java
class Solution {
    private TreeNode dfs(TreeNode node, TreeNode p, TreeNode q) {
        if (node == null || p == node || q == node) return node;

        if (p.val < node.val && q.val < node.val)
            return dfs(node.left, p, q);
        else if (p.val > node.val && q.val > node.val)
            return dfs(node.right, p, q);
        else
            return node; // split point → this is the LCA
    }

    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        return dfs(root, p, q);
    }
}
```

### Walkthrough

```
        6
       / \
      2   8
     / \ / \
    0  4 7  9
      / \
     3   5
```

**Find LCA of `p = 2`, `q = 4`:**

```
dfs(6): p=2 < 6, q=4 < 6 → go left
dfs(2): p == node → return 2
```
**Answer: 2** ✓ (2 is an ancestor of 4)

---

**Find LCA of `p = 2`, `q = 8`:**

```
dfs(6): p=2 < 6, q=8 > 6 → split → return 6
```
**Answer: 6** ✓

---

**Find LCA of `p = 3`, `q = 5`:**

```
dfs(6): both < 6 → go left
dfs(2): both > 2 → go right
dfs(4): p=3 < 4, q=5 > 4 → split → return 4
```
**Answer: 4** ✓

---

### Complexity

| | Balanced BST | Skewed BST |
|-|-------------|------------|
| **Time** | O(log n) | O(n) |
| **Space** | O(log n) | O(n) |

Space is the **recursion call stack** — one frame per level traversed.

---

## Approach 2 — Iterative (O(1) Space)

### Key Idea

Same logic as the recursive approach, but replace the call stack with a `while` loop. No recursion overhead, constant space.

### Implementation (Java)

```java
class Solution {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        TreeNode node = root;

        while (node != null) {
            if (p.val < node.val && q.val < node.val)
                node = node.left;
            else if (p.val > node.val && q.val > node.val)
                node = node.right;
            else
                return node; // split point → LCA
        }

        return null;
    }
}
```

### Complexity

| | Balanced BST | Skewed BST |
|-|-------------|------------|
| **Time** | O(log n) | O(n) |
| **Space** | **O(1)** | **O(1)** |

---

## Full Comparison

| | Recursive | Iterative |
|-|-----------|-----------|
| **Time** | O(h) | O(h) |
| **Space** | O(h) — call stack | **O(1)** |
| **Readability** | Slightly cleaner | Equally clean |
| **Interview pick** | ✅ Fine | ✅ Preferred |

> `h` = height of tree. O(log n) for balanced, O(n) for skewed.

---

## BST vs General Binary Tree LCA

| | General BT LCA | BST LCA |
|-|----------------|---------|
| **Strategy** | Post-order DFS, visit all nodes | Prune using BST ordering |
| **Time** | O(n) always | O(h) — O(log n) best case |
| **Space** | O(h) | O(h) recursive / O(1) iterative |
| **Both subtrees visited?** | Always | Never |

---

## Key Takeaways

- BST ordering eliminates the need to explore both subtrees — at every node you make a **deterministic** left/right/stop decision.
- The **split point** (where `p` and `q` diverge) is always the LCA in a BST.
- The iterative version is strictly better on space — prefer it when space is a concern.
- The `p == node || q == node` base case in the recursive version is technically redundant in a BST (the `else` branch catches it), but harmless to keep for defensive clarity.
