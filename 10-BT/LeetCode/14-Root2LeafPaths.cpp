#include <bits/stdc++.h>
using namespace std;

class Solution {
  private: 
    bool isLeaf(Node* node){
        return !node->left && !node->right;
    }
    bool util(Node* node, vector<vector<int>> &res, vector<int> &ans){
      if(!node) return 0;
      // leaf node
      if(isLeaf(node)){
        ans.push_back(node->val);
        res.push_back(ans);

        // backtrack
        ans.pop_back();
        return;

      }
      ans.push_back(node->val);
      util(node->left, res, ans);
      util(node->right, res, ans);

      // backtrack
      ans.pop_back();

    }
  public:
    vector<vector<int>> Paths(Node* root) {
        vector<vector<int>> res;
        if(!root) return res; 
        vector<int> ans;

        util(root, res, ans);

    }
};
int main(){
  return 0;
}