
struct Node
{
  int val;
  Node *left;
  Node *right;
  Node(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
  Node *lowestCommonAncestor(Node *root, Node *p, Node *q)
  {
    if (!root || root == p || root == q)
      return root;
    Node *left = lowestCommonAncestor(root->left, p, q);
    Node *right = lowestCommonAncestor(root->right, p, q);
    if (!left)
      return right;
    else if (!right)
      return left;
    else
      return root;
  }
};