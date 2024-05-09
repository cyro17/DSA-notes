#include <bits/stdc++.h>
using namespace std;

struct Node
{
  int val;
  Node *left, *right;
  Node(int x) : val(x), left(NULL), right(NULL) {}
};

Node *buildTree(vector<int> &nums)
{
  if (nums.empty())
    return NULL;

  Node *root = new Node(nums[0]);
  queue<Node *> q;
  q.push(root);
  int i = 1;
  while (i < nums.size())
  {
    Node *curr = q.front();
    q.pop();
    if (i < nums.size())
    {
      curr->left = new Node(nums[i++]);
      q.push(curr->left);
    }
    if (i < nums.size())
    {
      curr->right = new Node(nums[i++]);
      q.push(curr->right);
    }
  }
  return root;
}

void printTree(Node *root)
{
  if (!root)
  {
    return;
  }
  cout << root->val << " ";
  printTree(root->left);
  printTree(root->right);
}

int main()
{
  vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
  buildTree(arr);
  return 0;
}