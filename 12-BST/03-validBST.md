
 */
TC = O (N) , each node visited once 
```
class Solution {

    public boolean isValidBST(TreeNode root) {

        return this.valid(root, Long.MIN_VALUE, Long.MAX_VALUE);
    }
    private boolean valid(TreeNode node, long min, long max){
        if(node == null) return true;
        if(node.val <= min || node.val >= max) return false;

        return this.valid(node.left, min, node.val) && 
               this.valid(node.right, node.val, max);
    }
}
```
