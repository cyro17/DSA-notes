```
class BFS{
  public:
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
      vector<int> vis(V, 0);
      vis[0] = 1;
      queue<int> q;
      q.push(0);

      vector<int> bfs;
      while(!q.empty()){
        int node = q.front(); q.pop();
        bfs.push_back(node);
        for(auto it: adj[node]){
          if(!vis[it]){
            vis[it] = 1;
            q.push(it);
          }
        }
      }
    }
};
```

```
class DFS {
  private:
    void dfs_util(int node, vector<int> adj[],<int> &vis, vector<int> &res){
        vis[node] = 1;
        res.push_back(node);
        for(auto it: adj[node]){
          if(!vis[it])
            dfs_util(it, adj, vis, res);
        }
      }

  public:
    vector<int> dfsOfGraph(int v, vector<int> adj[]){
      vector<int> vis(v, 0);
      int start = 0;
      vector<int> dfs;
      dfs_util(start, adj, vis, res);
      return res;
    }
};
```
