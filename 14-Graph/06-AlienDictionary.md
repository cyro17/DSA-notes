
### Alien Dictionary
> BFS (Topo Sort) Approach

1. check the ordering of the characters by comparing consecutive words, and try to convert to a directed graph.
2. Apply Topo Sort on it, to get the linear ordering.

When is the ordering not possible?<br>
	There are two such cases when ordering is not possible: <br>
	1. If every character matches and the largest word appears before the shortest word: For example, if “abcd” appears before “abc”, we can say the ordering is not possible. <br>
	2. If there exists a cyclic dependency between the characters: For example, in the dictionary: dict: {“abc”, “bat”, “ade”} there exists a cyclic dependency between ‘a’ and ‘b’ <br>
	    because the dictionary states ‘a’ < ‘b’ < ‘a’, which is not possible.

```
class Solution{
private: 
	vector<int> topoSort(vector<int> adj[], int n) {
		vector<int> topo;
		vector<int> indegree(n, 0); 
		for (int i = 0; i < n; ++i)
		 {
		 	for(auto it: adj[i])
		 		indegree[it]++;
		 } 

		 queue<int> q;
		 for (int i = 0; i < n; ++i)
		 {
		 	if(indegree[i] == 0) q.push(i);
		 }

		 while(!q.empty()){
		 	int node = q.front();
		 	q.pop();

		 	topo.push_back(node);
		 	for(auto adjnode: adj[node]){
		 		indegree[adjnode]--;
		 		if(indegree[adjnode] == 0) 
		 			q.push(adjnode);	
		 	}
		 } 
		 return topo;
	}

public:
	string findOrder(string dict[], int n, int k){
		vector<int> adj[k];
		for (int i = 0; i < n-1; ++i)
		{
			string s1 = dict[i];
			string s2 = dict[i+1];
			int len = min(s1.size(), s2.size());

			for(int j = 0; j < len; j++){
				if(s1[j] != s2[j]){
					adj[s1[j] - 'a'].push_back(s2[j] - 'a');
					break;
				}
			}

		}

		vector<int> topo = topoSort(adj, k);
		string ans;
		for(auto it: topo){
			ans += char(it + 'a');
		} 

		return ans;
	}
};
```

Time Complexity: O(N*len)+O(K+E), where N is the number of words in the dictionary, ‘len’ is the length up to the index where the first inequality occurs, K = no. of nodes, and E = no. of edges.

Space Complexity: O(K) + O(K)+O(K)+O(K) ~ O(4K), O(K) for the indegree array, and O(K) for the queue data structure used in BFS(where K = no.of nodes), O(K) for the answer array and O(K) for the adjacency list
                  used in the algorithm.
