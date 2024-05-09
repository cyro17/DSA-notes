#include <bits/stdc++.h>
using namespace std;

/* 
Iterative PreOrder traversal
  
  using stack 
    1. take a stack push root into it.
    2. pop out top element of stack 
    3. insert the right child first then left.

  
*/

vector<int> preorderTraversal(Node *root){
  vector<int> ans;
  if (!root)
    return ans;
  stack<Node *> st;
  st.push(root);
  while (!st.empty())
  {
    Node *node = st.top();
    st.pop();
    ans.push_back(node->val);
    if (node->right != nullptr)
      st.push(node->right);
    if (node->left != nullptr)
      st.push(node->left);
  }
  return ans;
}

/* 
Iterative inorder traversal
  
  using stack 
    1. take a stack push root into it.
    2. pop out top element of stack 
    3. insert the right child first then left.

  
*/

vector<int> inorderTraversal(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* node = root;
    vector<int> res;
    while(true){
        if(node){
            st.push(node);
            node = node->left;
        }
        else{
            if(st.empty()) break;
            node = st.top(); st.pop();
            res.push_back(node->val);
            node = node->right;
        }
    }
    return res;
}

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> res;
    if(!root) return res;

    stack<TreeNode*> st1, st2;
    st1.push(root);
    while(!st1.empty()){
        root= st1.top();
        st1.pop();
        st2.push(root);
        if(root->left) st1.push(root->left);
        if(root->right) st1.push(root->right);
    }

    while(!st2.empty()){
        res.push_back(st2.top()->val);
        st2.pop();
    }
    return res;
        
}

int main(){
  return 0;
}