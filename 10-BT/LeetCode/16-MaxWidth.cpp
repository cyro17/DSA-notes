
struct Node
{
  int val;
  Node *left;
  Node *right;
  Node(int x) : val(x), left(NULL), right(NULL) {}
};

int getWidthBT(Node *root)
{
  if (!root)
    return 0;
  int max_ = 1;

  queue<pair<Node *, int>> q;
  q.push({root, 0});
  while (!q.empty())
  {
    int size = q.size();

    int start = q.front().second;
    int end = q.back().second;
    max_ = max(max_, end - start + 1);

    while (size--)
    {
      pair<Node *, int> p = q.front();
      int curr_idx = p.second;
      q.pop();

      if (p.first->left)
        q.push({p.first->left, curr_idx * 2 + 1});
      if (p.first->right)
        q.push({p.first->right, curr_idx * 2 + 2});
    }
  }
}