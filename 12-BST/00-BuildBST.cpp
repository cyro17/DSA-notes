/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
  TreeNode *insertIntoBST(TreeNode *root, int val)
  {
    if (!root)
    {
      TreeNode *root = new TreeNode(val);
      return root;
    }

    if (val < root->val)
      root->left = insertIntoBST(root->left, val);
    else
      root->right = insertIntoBST(root->right, val);

    return root;
  }

  TreeNode *deleteNode(TreeNode *root, int key)
  {
    if (!root)
      return root;
    if (key < root->val)
    {
      root->left = deleteNode(root->left, key);
      return root;
    }
    else if (key > root->val)
    {
      root->right = deleteNode(root->right, key);
      return root;
    }

    // found the node

    // delete leaf node or node with single child
    if (!root->left)
    {
      TreeNode *tmp = root->right;
      delete root;
      return tmp;
    }
    if (!root->right)
    {
      TreeNode *tmp = root->left;
      delete root;
      return tmp;
    }

    // delete TreeNode with 2 child
    TreeNode *succParent = root, *succ = root->right;
    while (succ->left)
    {
      succParent = succ;
      succ = succ->left;
    }

    root->val = succ->val;
    if (succParent->left == succ)
      succParent->left = succ->right;
    else
      succParent->right = succ->right;

    return root;
  }
};