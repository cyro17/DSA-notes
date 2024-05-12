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

bool isLeaf(Node* node){
  return !node->left && !node->right;
}

void LeftBoundary(Node* root, vector<int> &res){
  Node* curr = root->left;
  while(curr){
    if(!isLeaf(curr)) res.push_back(curr->val);
    if(curr->left) curr = curr->left;
    if(curr->right) curr = curr->right;
  }
}
void RightBoundary(Node* root, vector<int> &res){
  Node* curr = root->right;
  while(curr){
    if(!isLeaf(curr)) res.push_back(curr->val);
    if(curr->right) curr = curr->right;
    if(curr->left) curr = curr->left;
  }
}

void addLeaves(Node* root, vector<int> &res){ 
  if(isLeaf(root)){
    res.push_back(root->val);
    return;
  }
  if(root->left) addLeaves(root->left, res);
  if(root->right) addLeaves(root->right, res);
  
}

int main()
{
  vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
  Node* root= buildTree(arr);
  printTree(root);
  vector<int> left; 
  vector<int> LeftBoundary = LeftBoundary(root, left); 

}