#include <bits/stdc++.h>
using namespace std;

int getHeight(Node* root){
    if(!root ) return 0;
    int left_height = getHeight(root->left);
    int right_height = getHeight(root->right);

    return 1+ max(left_height, right_height);
}

bool isBalanced(Node* root) {
    if(!root) return 1;
    int left_h = getHeight(root->left);
  int right_h = getHeight(root->right);

    if(abs(left_h - right_h)<=1 
        && isBalanced(root->left)
        && isBalanced(root->right))
            return 1;
    return 0;
}

int main(){
  return 0;
}