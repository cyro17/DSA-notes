/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
private:
  void markParents(TreeNode *root, unordered_map<TreeNode *, TreeNode *> parents_map)
  {
    // using BFS
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
      TreeNode *currNode = q.front();
      q.pop();
      if (currNode->left)
      {
        parents_map[currNode->left] = currNode;
        q.push(currNode->left);
      }
      if (currNode->right)
      {
        parents_map[currNode->right] = currNode;
        q.push(currNode->right);
      }
    }
  }

public:
  vector<int> distanceK(TreeNode *root, TreeNode *target, int k)
  {
    vector<int> res;
    if (!root)
      return res;

    // 1. parents map
    unordered_map<TreeNode *, TreeNode *> parents_map;
    markParents(root, parents_map);

    // 2. using DFS
    unordered_map<TreeNode *, bool> vis;
    queue<TreeNode *> q;
    q.push(target);
    int curr_level = 0;

    while (!q.empty())
    {
      int q_size = q.size();
      if (curr_level++ == k)
        break;

      while (q_size--)
      {
        TreeNode *currNode = q.front();
        q.pop();

        if (currNode->left && !vis[currNode->left])
        {
          q.push(currNode->left);
          vis[currNode->left] = true;
        }

        if (currNode->right && !vis[currNode->right])
        {
          q.push(currNode->right);
          vis[currNode->right] = true;
        }

        if (parents_map[currNode] && !vis[parents_map[currNode]])
        {
          q.push(parents_map[currNode]);
          vis[parents_map[currNode]] = true;
          ;
        }
      }
    }

    while (!q.empty())
    {
      res.push_back(q.front()->val);
      q.pop();
    }
    return res;
  }
};