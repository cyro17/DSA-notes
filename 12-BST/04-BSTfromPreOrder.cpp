class Solution
{
private:
  TreeNode *recBuild(vector<int> &preorder, int &i, int bound)
  {
    if (i == preorder.size() || preorder[i] > bound)
      return NULL;

    TreeNode *root = new TreeNode(preorder[i++]);
    root->left = recBuild(preorder, i, root->val);
    root->right = recBuild(preorder, i, bound);
    return root;
  }

public:
  TreeNode *bstFromPreorder(vector<int> &preorder)
  {
    int i = 0;
    return recBuild(preorder, i, INT_MAX);
  }
};