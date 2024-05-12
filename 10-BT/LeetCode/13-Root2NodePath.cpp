#include <bits/stdc++.h>
using namespace std;



bool getPath(Node* root, vector<int>& res, int x) {
  if(!root) return 0;
  res.push_back(root->val);
  if(root->val == x)
    return 1;

  if(getPath(root->left, res, x) || getPath(root->right, res, x))
    return 1;

  res.pop_back();
  return 0; 

}

vector<int>  solve(Node* root, int x){
  vector<int> res;
  if(!root) return res;
  getPath(root, res, x); 
  return res;
}


int main(){
  return 0;
}


/*Time Complexity: O(N) where N is the number of nodes in the binary tree as each node of the binary tree is visited exactly once in the inorder traversal.

Space Complexity: O(N) awhere N is the number of nodes in the binary tree. This is because the stack can potentially hold all nodes in the tree when dealing with a skewed tree (all nodes have only one child), consuming space proportional to the number of nodes.

    O(H): In the average case or for a balanced tree, the maximum number of nodes that could be in the stack at any given time would be roughly the height of the tree hence O(log2N).*/