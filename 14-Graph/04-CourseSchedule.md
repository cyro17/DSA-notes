
1. Create adjacency list first.
2. apply Kahn's Algorithm ( Topological sort using BFS)
3. if linear ordering array returned is equal to the number of nodes, then it it possible to complete the entire course,
4. else not possible.

Time Complexity: O(V+E), where V = no. of nodes and E = no. of edges. This is a simple BFS algorithm.

Space Complexity: O(N) + O(N) ~ O(2N), O(N) for the indegree array, and O(N) for the queue data structure used in BFS(where N = no.of nodes). Extra O(N) for storing the topological sorting. Total ~ O(3N).
```
class Solution {
private:
  vector<int> topoBFS(int n, vector<int> adj[]){
  	  vector<int> indegree(n, 0); 
  	  for(int i =0; i<n; i++){
        for(auto it: adj[i]){
          indegree[it]++;
        }
      }

  	  queue<int> q;
  	  for (int i = 0; i < n; ++i)
  	  {
  	  	if(indegree[i] == 0) 
  	  		q.push(i);
  	  }
  	  vector<int> topo; 
  	  while(!q.empty()){
  	  	int node = q.front();
  	  	q.pop();
  	  	topo.push_back(node);

  	  	for(auto it: adj[node]){
  	  		indegree[it]--;
  	  		if(indegree[it] == 0)
  	  			q.push(it);
  	  	}
  	  }
  	  return topo;
  }
public:
  bool canFinish(int n, vector<vector<int>>& arr) {
      vector<int> adj[n];
      for(auto it: arr){
      	adj[it[1]].push_back(it[0]);
      }

      vector<int> topo = topoBFS(n, adj);
      return topo.size() == n;
  }
};
```
