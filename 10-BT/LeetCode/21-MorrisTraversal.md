# Morris Inorder Traversal

A **O(1) space** inorder traversal of a binary tree — no recursion stack, no auxiliary stack.

---

## Key Idea

Morris Traversal exploits the **unused `right` pointers of leaf nodes** (or inorder predecessors) to create temporary **threads** back to their inorder successor. After visiting a node, the thread is removed, restoring the original tree structure.

---

## Algorithm

For each node `curr`:

| Condition | Action |
|-----------|--------|
| `curr.left == null` | Visit `curr`, move right |
| Left exists, **no thread** (`prev.right == null`) | Create thread: `prev.right = curr`, move left |
| Left exists, **thread exists** (`prev.right == curr`) | Remove thread, visit `curr`, move right |

> **Inorder predecessor** = rightmost node in `curr`'s left subtree

---

## Walkthrough

Given tree:
```
    4
   / \
  2   5
 / \
1   3
```

| Step | `curr` | Action |
|------|--------|--------|
| 1 | 4 | Left exists, predecessor = 3, no thread → create thread `3→4`, go left |
| 2 | 2 | Left exists, predecessor = 1, no thread → create thread `1→2`, go left |
| 3 | 1 | No left → **visit 1**, follow thread to 2 |
| 4 | 2 | Thread exists → remove thread, **visit 2**, go right |
| 5 | 3 | No left → **visit 3**, follow thread to 4 |
| 6 | 4 | Thread exists → remove thread, **visit 4**, go right |
| 7 | 5 | No left → **visit 5** |

**Output:** `[1, 2, 3, 4, 5]` ✓

---

## Implementation (Java)

```java
class Solution {
    private void morrisInorder(TreeNode root, List<Integer> list) {
        TreeNode curr = root;

        while (curr != null) {
            if (curr.left == null) {
                // No left subtree — visit and move right
                list.add(curr.val);
                curr = curr.right;
            } else {
                // Find inorder predecessor (rightmost in left subtree)
                TreeNode prev = curr.left;
                while (prev.right != null && prev.right != curr) {
                    prev = prev.right;
                }

                if (prev.right == null) {
                    // No thread yet — create it and go left
                    prev.right = curr;
                    curr = curr.left;
                } else {
                    // Thread exists — remove it, visit, move right
                    prev.right = null;
                    list.add(curr.val);
                    curr = curr.right;
                }
            }
        }
    }

    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> list = new ArrayList<>();
        if (root == null) return list;
        morrisInorder(root, list);
        return list;
    }
}
```

---

## Complexity

| | Value |
|-|-------|
| **Time** | O(n) — each node visited at most twice |
| **Space** | O(1) — no stack or recursion |

---

## Comparison

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Recursive | O(n) | O(h) | Simple, but call stack risk on deep trees |
| Iterative (explicit stack) | O(n) | O(h) | Safer, but still O(h) space |
| **Morris (this)** | O(n) | **O(1)** | Modifies tree temporarily; restores on exit |

> `h` = height of tree. Worst case O(n) for skewed trees.

---

## Important Notes

- The tree is **temporarily modified** during traversal (threads are added and removed).
- The tree is **fully restored** to its original structure by the end.
- Not suitable in concurrent/multi-threaded environments where the tree is being read elsewhere during traversal.
