class Solution
{
private:
  void reverseInorder(Node *node, int &cnt, int &k, int &largest)
  {
    if (!node)
      return;
    reverseInorder(node->right, cnt, k, largest);
    cnt++;
    if (cnt == k)
    {
      largest = node->data;
      return;
    }
    reverseInorder(node->left, cnt, k, largest);
  }

public:
  int kthLargest(Node *root, int k)
  {
    int cnt = 0, largest = INT_MIN;
    reverseInorder(root, cnt, k, largest);
    return largest;
  }
};