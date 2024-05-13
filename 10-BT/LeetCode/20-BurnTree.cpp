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
private:
  void markParents(TreeNode *root, unordered_map<TreeNode *, TreeNode *> &parents_map)
  {
    // using BFS
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
      TreeNode *curr = q.front();
      q.pop();
      if (curr->left)
      {
        parents_map[curr->left] = curr;
        q.push(curr->left);
      }
      if (curr->right)
      {
        parents_map[curr->right] = curr;
        q.push(curr->right);
      }
    }
  }
  TreeNode *findTarget(TreeNode *root, int target)
  {
    if (!root || root->val == target)
      return root;

    TreeNode *node = findTarget(root->left, target);
    if (!node)
      node = findTarget(root->right, target);
    return node;
  }

public:
  int amountOfTime(TreeNode *root, int target)
  {

    if (!root)
      return -1;
    unordered_map<TreeNode *, TreeNode *> parents_mp;
    markParents(root, parents_mp);

    unordered_map<TreeNode *, bool> vis;
    queue<TreeNode *> q;
    int t = 0;
    int flag = 0;
    TreeNode *targetNode = findTarget(root, target);
    q.push(targetNode);
    vis[targetNode] = 1;
    while (!q.empty())
    {
      int size = q.size();
      if (flag)
        t++;
      while (size--)
      {
        TreeNode *curr = q.front();
        q.pop();
        if (curr->left && !vis[curr->left])
        {
          flag = 1;
          q.push(curr->left);
          vis[curr->left] = true;
        }

        if (curr->right && !vis[curr->right])
        {
          flag = 1;
          q.push(curr->right);
          vis[curr->right] = true;
        }

        if (parents_mp[curr] && !vis[parents_mp[curr]])
        {
          flag = 1;
          q.push(parents_mp[curr]);
          vis[parents_mp[curr]] = true;
        }
      }
    }
    return t;
  }
};