#include <bits/stdc++.h>
using namespace std;

int maxDepth(Node* root) {
   if(!root) return 0;
    queue<Node*> q;
    q.push(root);
    int level = 0;
    while(!q.empty()){
        level++;
        int size = q.size();
        while(size--){
            Node* tmp = q.front(); q.pop();
            if(tmp->left) q.push(tmp->left);
            if(tmp->right) q.push(tmp->right);
        }
    }
    return level;
}
