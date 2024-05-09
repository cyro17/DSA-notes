#include <bits/stdc++.h>
using namespace std;

int getHeight(TreeNode* root, int &d){
    if(!root) return 0;
    int lh = getHeight(root->left, d);
    int rh= getHeight(root->right, d);
    d = max(d, lh + rh);
    return 1 + max(lh, rh);
}

int diameterOfBinaryTree(TreeNode* root){
    int d = 0;
    getHeight(root, d);
    return d;
}
