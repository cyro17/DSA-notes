Node *searchNode(Node *root, int target)
{
  if (!root || root->val == target)
    return root;

  Node *node = searchNode(root->left, target);
  if (!node)
    node = searchNode(root->right, target);
  return Node;
}