```
class TopoSort{
private:
	void dfs(int node, vector<int> &vis, vector<int> adj[], stack<int> &st){
		vis[node] = 1;
		for(auto it: adj[node]){
			if(!vis[it])
				dfs(it, vis, adj, st);
		}
		st.push(node);
	}

public:
	vector<int> topo(int n, vector<int> adj[]){
		vector<int> vis(n, 0);
		stack<int> st;
		for (int i = 0; i < n; ++i)
		{
			if(!vis[i]){
				dfs(i, vis, adj, st);
			}
		}

		vector<int> res;
		while(!st.empty()){
			res.push_back(st.top());
			st.pop();
		}

		return res;
	} 
}
```
