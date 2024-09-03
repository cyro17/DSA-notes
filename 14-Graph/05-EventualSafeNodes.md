## Eventual Safe Nodes

> BFS Approach ( Topo Sort )

1. reverse the edges 
2. calculate the indegrees of all the nodes
3. push the node with indegree == 0 to the queue
4. iterate the queue until its empty
5. get the front node of queue, push it to safe node 
6. iterate over its neighbours, and reduce their indegree by 1
7. if indegree == 0 , push it to the queue
8. sort the safe node array to get the required result

TC : O(V+E)+O(N*logN), where V = no. of nodes and E = no. of edges. This is a simple BFS algorithm. Extra O(N*logN) for sorting the safeNodes array, where N is the number of safe nodes.

SC : O(N) + O(N) + O(N) ~ O(3N), O(N) for the indegree array, O(N) for the queue data structure used in BFS(where N = no.of nodes), and extra O(N) for the adjacency list to store the graph in a reversed order.

```
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> adjRev[n];
        vector<int> indegree(n, 0);
        for(int i = 0; i<n; i++){
            for(auto it: graph[i]){
                adjRev[it].push_back(i);
                indegree[i]++;
            }
        }
        
        queue<int> q;
        vector<int> safeNodes;
        for (int i = 0; i < n; ++i)
        {
            if(indegree[i] == 0) q.push(i);
        } 

        while(!q.empty()){
            int node = q.front();
            q.pop();
            safeNodes.push_back(node);
            for(auto it: adjRev[node]){
                indegree[it]--;
                if(indegree[it] == 0) q.push(it);
            }
        }
        sort(safeNodes.begin(), safeNodes.end());
        return safeNodes;
    }
};
```
