/* TC = O(N) */

class Solution
{
public:
  int countNodes(TreeNode *root)
  {
    if (!root)
      return 0;
    queue<TreeNode *> q;
    q.push(root);
    int cnt = 0;
    while (!q.empty())
    {
      TreeNode *tmp = q.front();
      q.pop();
      cnt++;
      if (tmp->left)
        q.push(tmp->left);
      if (tmp->right)
        q.push(tmp->right);
    }
    return cnt;
  }
};

/*  optimal : TC = O(log N) */
class Solution
{
public:
  int left_height(TreeNode *node)
  {
    int h = 0;
    while (node)
    {
      h++;
      node = node->left;
    }
    return h;
  }

  int right_height(TreeNode *node)
  {
    int h = 0;
    while (node)
    {
      h++;
      node = node->right;
    }
    return h;
  }

  int countNodes(TreeNode *root)
  {
    if (!root)
    {
      return 0;
    }

    int lh = left_height(root);
    int rh = right_height(root);

    if (lh == rh)
    {
      return (1 << lh) - 1;
    }

    return 1 + countNodes(root->left) +
           countNodes(root->right);
  }
};