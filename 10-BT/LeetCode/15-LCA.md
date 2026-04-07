# Lowest Common Ancestor of a Binary Tree

Find the **Lowest Common Ancestor (LCA)** of two nodes `p` and `q` in a binary tree.

> **LCA** = the deepest node that has both `p` and `q` as descendants (a node is a descendant of itself).

---

## Approaches

| | Approach | Time | Space |
|-|----------|------|-------|
| ✅ | Single-pass DFS (post-order) | O(n) | O(h) |
| 🔁 | Existence-check DFS | O(n²) | O(h) |

---

## Approach 1 — Single-Pass DFS (Optimal)

### Key Idea

Run a **post-order DFS**. At each node, ask:
- Did the left subtree return something?
- Did the right subtree return something?

If **both sides returned non-null** → current node is the LCA.  
If **only one side** returned non-null → bubble that result up.

The trick: `root == p || root == q` short-circuits — we don't need to find both nodes explicitly. If `p` is an ancestor of `q`, the first match is already the LCA.

### Implementation (Java)

```java
class Solution {
    private TreeNode dfs(TreeNode root, TreeNode p, TreeNode q) {
        // Base case: null or found one of the targets
        if (root == null || root == p || root == q) return root;

        TreeNode left  = dfs(root.left,  p, q);
        TreeNode right = dfs(root.right, p, q);

        // p and q are on opposite sides → current node is LCA
        if (left != null && right != null) return root;

        // Otherwise bubble up whichever side found something
        return left != null ? left : right;
    }

    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        return dfs(root, p, q);
    }
}
```

### Walkthrough

```
        3
       / \
      5   1
     / \ / \
    6  2 0  8
      / \
     7   4
```

Find LCA of `p = 5`, `q = 4`:

```
dfs(3) →
  dfs(5) → root == p → return 5       ← short-circuits here
  dfs(1) →
    dfs(0) → null
    dfs(8) → null
    return null
left = 5, right = null → return 5
```

**Answer: 5** ✓ (5 is an ancestor of 4, so 5 itself is the LCA)

---

Find LCA of `p = 5`, `q = 1`:

```
dfs(3) →
  dfs(5) → return 5
  dfs(1) → return 1
left = 5, right = 1 → both non-null → return 3
```

**Answer: 3** ✓

---

### Complexity

| | Value |
|-|-------|
| **Time** | O(n) — visits every node once |
| **Space** | O(h) — recursion stack; O(log n) balanced, O(n) skewed |

---

## Approach 2 — Existence-Check DFS

### Key Idea

At each node, explicitly check **which subtree contains `p` and which contains `q`** using a helper `exists()`. Based on where each node lives, recurse into the correct subtree.

- `p` and `q` in **different subtrees** → current node is LCA
- Both in **left subtree** → recurse left
- Both in **right subtree** → recurse right

### Implementation (C++)

```cpp
class Solution {
private:
    bool exists(TreeNode* node, TreeNode* target) {
        if (!node) return false;
        if (node == target) return true;
        return exists(node->left, target) || exists(node->right, target);
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;

        // If root itself is one of the targets, it must be the LCA
        if (root == p || root == q) return root;

        bool pInLeft = exists(root->left, p);
        bool qInLeft = exists(root->left, q);

        if (pInLeft != qInLeft) {
            // p and q are on opposite sides
            return root;
        } else if (pInLeft) {
            // Both in left subtree
            return lowestCommonAncestor(root->left, p, q);
        } else {
            // Both in right subtree
            return lowestCommonAncestor(root->right, p, q);
        }
    }
};
```

### Walkthrough

```
        3
       / \
      5   1
     / \ / \
    6  2 0  8
      / \
     7   4
```

Find LCA of `p = 7`, `q = 4`:

```
At node 3:
  exists(left=5, p=7) → true   → pInLeft = true
  exists(left=5, q=4) → true   → qInLeft = true
  pInLeft == qInLeft → recurse left

At node 5:
  exists(left=6, p=7) → false  → pInLeft = false
  exists(left=6, q=4) → false  → qInLeft = false
  pInLeft == qInLeft → recurse right

At node 2:
  exists(left=7, p=7) → true   → pInLeft = true
  exists(left=7, q=4) → false  → qInLeft = false
  pInLeft != qInLeft → return 2
```

**Answer: 2** ✓

---

### Complexity

| | Value |
|-|-------|
| **Time** | O(n²) — `exists()` is O(n), called at each level |
| **Space** | O(h) — recursion stack |

---

## Head-to-Head Comparison

| | Approach 1 (Single DFS) | Approach 2 (Exists Check) |
|-|--------------------------|---------------------------|
| **Language** | Java | C++ |
| **Time** | O(n) | O(n²) |
| **Space** | O(h) | O(h) |
| **Passes** | 1 | Multiple (re-traverses subtrees) |
| **Intuition** | Post-order bubbling | Explicit subtree containment |
| **Interview pick?** | ✅ Preferred | ❌ Suboptimal |

---

## Key Takeaways

- **Approach 1** is optimal — one pass, no repeated work. The post-order return value does all the heavy lifting.
- **Approach 2** is easier to reason about intuitively ("is the node on the left or right?") but pays a steep O(n²) cost due to repeated `exists()` calls at each node.
- The base case `root == p || root == q` in Approach 1 is subtle but crucial — it handles the case where one target is an ancestor of the other.
