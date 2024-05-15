class morrisTraversal
{
private:
  TreeNode *findPredecessor(TreeNode *node)
  {
    TreeNode *prev = node->left;
    while (prev->right && prev->right != node)
    {
      prev = prev->right;
    }
    return prev;
  }

public:
  vector<int> inOrder(Node *root)
  {
    vector<int> res;
    Node *curr = root;
    while (curr)
    {
      // if curr left child DNE , move to right child
      if (!curr->left)
      {
        res.push_back(curr->val);
        curr = curr->right;
      }
      // left child exist, so find predecessor (rightmost node of left subtree)
      else
      {
        Node *prev = curr->left;
        // found the predecessor node
        while (prev->right && prev->right != curr)
        {
          pre = prev->right;
        }

        // check if link DNE
        if (!prev->right)
        {
          prev->right = curr;
          curr = curr->left;
        }

        // link exist , so break the link and move to the right
        else
        {
          prev->right = NULL;
          res.push_back(curr->val);
          curr = curr->right;
        }
      }
    }
    return res;
  }

  vector<int> preOrder(TreeNode *root)
  {
    vector<int> res;
    if (!root)
      return res;

    TreeNode *curr = root;
    while (curr)
    {

      if (!curr->left)
      {
        res.push_back(curr->val);
        curr = curr->right;
      }
      else
      {
        TreeNode *pred = findPredecessor(curr);
        if (!pred->right)
        {
          pred->right = curr;
          res.push_back(curr->val);
          curr = curr->left;
        }
        else
        {
          pred->right = NULL;
          curr = curr->right;
        }
      }
    }
    return res;
  }
};