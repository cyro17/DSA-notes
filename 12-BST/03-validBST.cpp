/*


    If the current node is null then return true
    If the max value of the left subtree  is greater than or equal to the current node then return false
    If the min value of the right subtree is less than or equal to the current node then return false
    If the left subtree or the right subtree is not a BST then return false
    Else return true


 */

class Solution
{

private:
  int max_(TreeNode *node)
  {
    int max__ = INT_MIN;
    while (node->right)
    {
      node = node->right;
    }
    return node->val;
  }

  int min_(TreeNode *node)
  {
    int min__ = INT_MAX;
    while (node->left)
    {
      node = node->left;
    }
    return node->val;
  }

public:
  bool isValidBST(TreeNode *root)
  {
    if (!root)
      return 1;
    if (root->left && max_(root->left) >= root->val)
      return 0;
    if (root->right && min_(root->right) <= root->val)
      return 0;

    if (!isValidBST(root->left) || !isValidBST(root->right))
      return 0;

    return 1;
  }
};