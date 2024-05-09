bool util(TreeNode* left, TreeNode* right){
  if(!left || !right){
      return left == right;
  }
  return (left->val == right->val) &&
          util(left->left, right->right) &&
          util(left->right, right->left);
}

bool isSymmetric(TreeNode* root) {
  if(!root) return 1;
  return util(root->left, root->right);
}