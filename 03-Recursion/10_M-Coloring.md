> TC = O(N^M)   , N-> no of vertices, M-> no of possible colors

```
class Solution
{
private:
   bool isSafe(int node, int c, vector<int> &colors, vector<vector<int>> &adjList, int v, int m){
   	for(auto it: adjList[node]){
   		if(colors[it] == c ) return 0;
   	}
   	return 1;
   }
   
   bool solve(int node, vector<int> &colors, int v, int m, vector<vector<int>> &adjList){
   	if(node == v) return 1;
   
   	for (int i = 0; i < m; ++i)
   	{
   		if(isSafe(node, i, colors, adjList, v, m)){
   			colors[node] = i;
   			if(solve(node + 1, colors, v, m, adjList)) 
   				return 1;
   
   			// backtrack 
   			colors[node] = -1;
   		}
   	}
   	return 0;
   }
public:
   bool graphColoring(int v, vector<pair<int, int >> &edges, int m){
   	vector<vector<int>> adjList(v);
   	for(auto it: edges){
   		adjList[it.first].push_back(it.second);
   		adjList[it.second].push_back(it.first);
   	}
   
   	vector<int> colors(v, -1);
   	if(solve(0, colors, v, m, adjList)) return 1;
   	return 0;
   }
};
```

Java Solution

```
class Solution{
    private boolean isSafe(int node, int color, int[] colors,
                           int v, int m, List<List<Integer>> adjList){
        for(int it :  adjList.get(node)){
            if(colors[it] == color) return false;
        }
        return  true;
    }


    private boolean solve(int node, int[] colors, int v, int m, List<List<Integer>> adjList){
        if(node == v) return  true;
        for (int i = 0; i < m; i++) {
            if(isSafe(node, i, colors, v, m, adjList)){
                colors[node] = i;
                if(solve(node + 1, colors, v, m, adjList)) return true;

                colors[node] = -1;
            }
        }
        return false;
    }

    public boolean graphColoring(int v, List<int[]> edges, int m){
        List<List<Integer>> adjList = new ArrayList<>();
        for (int i = 0; i < v; i++) {
            adjList.add(new ArrayList<>());
        }

        for(int[] edge : edges){
            adjList.get(edge[0]).add(edge[1]);
            adjList.get(edge[1]).add(edge[0]);
        }

        int[] colors = new int[v];
        Arrays.fill(colors, -1);

        return solve(0, colors, v, m, adjList);
    }
}

```
