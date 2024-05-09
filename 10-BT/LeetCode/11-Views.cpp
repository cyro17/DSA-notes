vector<int> topView(Node *root){

    vector<int> res;
      if(!root) return res;
    
      map<int, int> mp;
      queue<pair<Node*, int>> q;
      q.push({root, 0}) ;
      while(!q.empty()){
        auto it = q.front();
        q.pop();
        Node* node = it.first;
        int line = it.second;
    
        if(mp.find(line) == mp.end()){
          mp[line] = node->data;
        }
    
        if(node->left) q.push({node->left, line-1});
        if(node->right) q.push({node->right, line+1});
      }
      for(auto it: mp)
        res.push_back(it.second);
    
      return res;
}


vector <int> bottomView(Node *root) {
    vector<int> res;
    if(!root) return res;
  
    map<int, int> mp;
    queue<pair<Node*, int>> q;
    q.push({root, 0}) ;
    while(!q.empty()){
      auto it = q.front();
      q.pop();
      Node* node = it.first;
      int line = it.second;
  
      
      mp[line] = node->data;
      
  
      if(node->left) q.push({node->left, line-1});
      if(node->right) q.push({node->right, line+1});
    }
    for(auto it: mp)
      res.push_back(it.second);
  
    return res;
}

/*
Brute Force:
  
*/

vector<int> rightSideView(TreeNode* root) {
    vector<vector<int>> res;
    vector<int> right;
    if(!root) return right;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        vector<int> level;
        while(size--){
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        res.push_back(level);
    }
    for(auto row: res){
        right.push_back(row.back());
    }
    return right;
}

vector<int> LeftSideView(TreeNode* root) {
    vector<vector<int>> res;
    vector<int> right;
    if(!root) return right;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        vector<int> level;
        while(size--){
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        res.push_back(level);
    }
    for(auto row: res){
        right.push_back(row.front());
    }
    return right;
}

/* Optimal : 
    
  
  */

void utilLeft(Node* root, int level, vector<int> &res){
  if(!root) return;
  if(res.size() == level)
    res.push_back(root->val);
  utilLeft(root->left, level+1, res);
  utilLeft(root->right, level+1, res);
}

vector<int> leftView(Node* root){
  vector<int> res;
  utilLeft(root, 0, res);
  return res; 
} 

void utilRight(Node* root, int level, vector<int> &res){
  if(!root) return;
  if(res.size() == level){
    res.push_back(root->val);
    utilRight(root->right, level+1, res);
    utilRight(root->left, level+1, res);
  }
}

vector<int> leftView(Node* root){
  vector<int> res;
  utilRight(root, 0, res);
  return res; 
} 