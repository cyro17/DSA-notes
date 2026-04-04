# Binary Tree Paths

A collection of **root-to-leaf path** problems on Binary Trees — covering all paths, and path to a specific node.

---

## Table of Contents
- [Problem 1 — All Root-to-Leaf Paths](#problem-1--all-root-to-leaf-paths)
  - [Approach 1 — String DFS](#approach-1--string-dfs)
  - [Approach 2 — List + Backtracking](#approach-2--list--backtracking)
- [Problem 2 — Path to a Given Node](#problem-2--path-to-a-given-node)
- [Comparison Summary](#comparison-summary)

---

## Problem 1 — All Root-to-Leaf Paths

Given the `root` of a binary tree, return **all root-to-leaf paths** in any order.

```
      1
     / \
    2   3
     \
      5
```

**Output:** `["1->2->5", "1->3"]`

---

### Approach 1 — String DFS

**Idea:** Pass the current path as a `String` down each recursive call, appending the node value and `"->"` at each step. When a leaf is reached, record the path directly.

**Why no backtracking needed:**
Strings in Java are **immutable**. Every `path += node.val` creates a brand new string and assigns it to the local variable — the caller's `path` is never mutated. So each recursive call naturally gets its own independent copy of the path. The "undo" happens for free.

```java
dfs(node.left,  path, res);   // gets "1->"
dfs(node.right, path, res);   // also gets "1->" — nothing changed
```

#### Dry Run

```
      1
     / \
    2   3
     \
      5
```

| Call | Node | Path | Action |
|------|------|------|--------|
| dfs(1, "") | 1 | "1" | not leaf → append "->" → "1->" |
| dfs(2, "1->") | 2 | "1->2" | not leaf → append "->" → "1->2->" |
| dfs(5, "1->2->") | 5 | "1->2->5" | leaf → add to result |
| dfs(3, "1->") | 3 | "1->3" | leaf → add to result |

**Output:** `["1->2->5", "1->3"]` ✅

#### Java

```java
class Solution {
    private void dfs(TreeNode node, String path, List<String> res) {
        if (node == null) return;

        path += node.val;                            // new string, caller unaffected

        if (node.left == null && node.right == null) {
            res.add(path);                           // leaf → record path
            return;
        }

        path += "->";                                // new string again

        dfs(node.left,  path, res);
        dfs(node.right, path, res);
    }

    public List<String> binaryTreePaths(TreeNode root) {
        List<String> res = new ArrayList<>();
        dfs(root, "", res);
        return res;
    }
}
```

#### Complexity

| | Time | Space |
|--|------|-------|
| Traversal | O(N) | O(H) recursion stack |
| String creation | O(N) per node — new object each time | O(N·H) total |
| **Total** | **O(N²)** worst case | **O(N·H)** |

> String is built at **every node**, not just leaves. On a skewed tree with N nodes, each path costs O(N) → O(N²) overall.

---

### Approach 2 — List + Backtracking

**Idea:** Use a **shared** `List<Integer>` to track the current path. Add the node on the way down, recurse, then **remove it on the way back up** (backtrack). Build the result string only at leaves.

**Why backtracking is needed:**
Unlike strings, a `List` is **mutable and shared** across all calls. If you don't remove after recursing, the left subtree's nodes bleed into the right subtree's path.

**Why no explicit undo before the right call:**
The left call is responsible for cleaning up after itself — every node added inside `dfs(left)` is removed before it returns. By the time `dfs(right)` runs, the list is already restored.

```java
path.add(node.val);
dfs(node.left,  path, res);   // left cleans up after itself
dfs(node.right, path, res);   // sees clean list ✅
path.remove(path.size() - 1); // current node removes itself
```

#### Dry Run

```
      1
     / \
    2   3
     \
      5
```

```
path = [1]
  → dfs(left=2)
      path = [1, 2]
        → dfs(right=5)
            path = [1, 2, 5] → leaf → record "1->2->5"
            path.remove()    → [1, 2]
      path.remove()          → [1]         ← list restored before right call
  → dfs(right=3)             ← sees [1] ✅
      path = [1, 3]          → leaf → record "1->3"
      path.remove()          → [1]
path.remove()                → []
```

#### Java

```java
class Solution {
    private boolean isLeaf(TreeNode node) {
        return node.left == null && node.right == null;
    }

    private void dfs(TreeNode node, List<Integer> path, List<String> res) {
        if (node == null) return;

        path.add(node.val);                          // choose

        if (this.isLeaf(node)) {
            int size = path.size();
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < size; i++) {
                sb.append(path.get(i));
                if (i != size - 1) sb.append("->");
            }
            res.add(sb.toString());                  // build string only at leaf
        } else {
            dfs(node.left,  path, res);              // explore
            dfs(node.right, path, res);
        }

        path.remove(path.size() - 1);               // unchoose (backtrack)
    }

    public List<String> binaryTreePaths(TreeNode root) {
        List<String> res = new ArrayList<>();
        if (root == null) return res;
        dfs(root, new ArrayList<>(), res);
        return res;
    }
}
```

#### Complexity

| | Time | Space |
|--|------|-------|
| Traversal | O(N) | O(H) recursion stack |
| String building | O(H) per leaf — built once per path | O(H) path list |
| **Total** | **O(N·H)** | **O(H)** auxiliary |

> O(N·H) = O(N log N) balanced, O(N²) skewed — but string is built **only at leaves**, not every node, making it meaningfully faster than Approach 1 in practice.

---

### Approach 1 vs Approach 2

| | String DFS | List + Backtracking |
|--|------------|---------------------|
| Time | O(N²) always | O(N·H) |
| Auxiliary space | O(N·H) — new string per node | O(H) — one shared list |
| String copies created | One per **node** | One per **leaf** |
| Needs explicit backtrack? | ❌ Immutability handles it | ✅ `remove()` after recursion |
| Code simplicity | ✅ Simpler | Slightly more verbose |

---

## Problem 2 — Path to a Given Node

Given the `root` of a binary tree and a target value `x`, return the **path from root to that node** as a list of integers. Return an empty list if the node doesn't exist.

**Key idea:** DFS with backtracking. Add the node, check if it's the target, recurse left and right. If neither subtree finds the target, **backtrack** by removing the node before returning `false`.

```
      1
     / \
    2   3
   / \
  4   5

Target: 5
Output: [1, 2, 5]
```

### Why backtracking here is critical

If you reach node `4` (wrong leaf), you must remove it before trying `5`. Without `pop_back()`, the path would carry stale nodes from dead ends.

```
path = [1]
  → push 2 → [1, 2]
    → push 4 → [1, 2, 4]  ← not target, left=null, right=null
    → pop   → [1, 2]       ← backtrack
    → push 5 → [1, 2, 5]  ← found! return true
```

### C++

```cpp
bool getPath(Node* root, vector<int>& res, int x) {
    if (!root) return false;

    res.push_back(root->val);               // choose

    if (root->val == x) return true;        // found target

    // If target found in either subtree, propagate true upward
    if (getPath(root->left, res, x) || getPath(root->right, res, x))
        return true;

    res.pop_back();                         // unchoose (backtrack)
    return false;
}

vector<int> solve(Node* root, int x) {
    vector<int> res;
    if (!root) return res;
    getPath(root, res, x);
    return res;
}
```

### Complexity

| | Time | Space |
|--|------|-------|
| Traversal | O(N) — visits each node once | O(H) recursion stack |
| Path vector | O(H) — holds one root-to-node path | — |
| **Total** | **O(N)** | **O(H)** |

> O(H) = O(log N) balanced, O(N) skewed.

---

## Comparison Summary

| Problem | Approach | Time | Aux Space | Backtrack? |
|---------|----------|------|-----------|------------|
| All paths — String DFS | Immutable string copy | O(N²) | O(N·H) | ❌ Not needed |
| All paths — List + BT | Shared list, undo on return | O(N·H) | O(H) | ✅ `remove()` after both children |
| Path to node | Shared vector, undo on miss | O(N) | O(H) | ✅ `pop_back()` on dead ends |

---

## Key Takeaways

| Concept | Rule |
|---------|------|
| Immutable path (String) | No backtrack needed — each call gets its own copy automatically |
| Mutable path (List/vector) | Always backtrack — shared object, must undo after recursion |
| When to build the string | Only at leaves — avoids O(N) string cost at every node |
| Left call cleans up itself | Right call always sees a clean path — no manual undo between siblings |
