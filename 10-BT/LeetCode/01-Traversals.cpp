#include <bits/stdc++.h>
using namespace std;

/* 
  Recursive Traversal  
 
*/


void preorderTraversal(TreeNode *root){

  if(!root) return ;
  cout<<root->val<<" ";
  preorderTraversal(root->left); 
  preorderTraversal(root->right); 
}

void InOrderTraversal(TreeNode *root){

  if(!root) return ;
  preorderTraversal(root->left); 
  cout<<root->val<<" ";
  preorderTraversal(root->right); 
}

void PostOrderTraversal(TreeNode *root){

  if(!root) return;
  preorderTraversal(root->left); 
  preorderTraversal(root->right); 
  cout<<root->val<<" ";
}

int main()
{
  return 0;
}