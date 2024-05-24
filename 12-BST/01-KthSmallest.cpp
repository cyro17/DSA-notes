class Solution
{
private:
  void inorder(TreeNode *node, int &cnt, int &k, int &res)
  {
    if (!node || cnt >= k)
      return;
    inorder(node->left, cnt, k, res);
    cnt++;
    if (cnt == k)
    {
      res = node->val;
      return;
    }
    inorder(node->right, cnt, k, res);
  }

public:
  int kthSmallest(TreeNode *root, int k)
  {
    int cnt = 0, res = INT_MAX;
    inorder(root, cnt, k, res);
    return res;
  }
};
