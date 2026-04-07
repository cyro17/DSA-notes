
TC = O(N) , every node visited once 
SC = O(H) , rec stack space
```
private TreeNode dfs(TreeNode root, TreeNode p, TreeNode q){
    if(root == null || root == p || root == q ) return root;
    TreeNode left = this.dfs(root.left, p, q);
    TreeNode right = this.dfs(root.right, p, q);

    if(left != null && right != null) return root;
    return left != null ? left:  right;
}

public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
    return this.dfs(root, p, q);
}
```
