# Graph — Adjacency List Templates

Ready-to-use templates for building adjacency lists in C++ and Java. Copy, adapt, and go.

---

## Quick Decision Guide

| Situation | Use |
|-----------|-----|
| Unweighted, integer nodes | `vector<vector<int>>` / `List<List<Integer>>` |
| Weighted edges | `vector<vector<pair<int,int>>>` / `List<List<int[]>>` |
| String/non-integer nodes | `unordered_map` / `HashMap` |
| 0-indexed nodes | size `n` |
| 1-indexed nodes | size `n+1` |
| Undirected graph | add edge both ways |
| Directed graph | add edge one way only |

---

## C++ Templates

### Unweighted Undirected

```cpp
int n = 5;
vector<vector<int>> edges = {{0,1},{1,2},{2,3},{3,4}};

vector<vector<int>> graph(n);   // 0-indexed

for (auto& edge : edges) {
    int u = edge[0], v = edge[1];
    graph[u].push_back(v);
    graph[v].push_back(u);   // remove for directed
}

// iterate neighbors of node u
for (int neighbor : graph[u]) {
    // process neighbor
}
```

---

### Unweighted Directed

```cpp
vector<vector<int>> graph(n);

for (auto& edge : edges) {
    graph[edge[0]].push_back(edge[1]);   // one direction only
}
```

---

### Weighted Undirected

```cpp
// edges = {{u, v, weight}, ...}
vector<vector<int>> edges = {{0,1,5},{1,2,3},{2,3,8}};

vector<vector<pair<int,int>>> graph(n);   // {neighbor, weight}

for (auto& e : edges) {
    int u = e[0], v = e[1], w = e[2];
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});   // remove for directed
}

// iterate with structured binding (C++17)
for (auto [neighbor, weight] : graph[u]) {
    cout << neighbor << " " << weight;
}

// iterate without structured binding
for (auto& p : graph[u]) {
    int neighbor = p.first;
    int weight   = p.second;
}
```

---

### Weighted Directed

```cpp
vector<vector<pair<int,int>>> graph(n);

for (auto& e : edges) {
    graph[e[0]].push_back({e[1], e[2]});   // u → v with weight
}
```

---

### 1-Indexed Graph

```cpp
int n = 5;   // nodes 1 to 5
vector<vector<int>> graph(n + 1);   // size n+1

for (auto& edge : edges) {
    int u = edge[0], v = edge[1];
    graph[u].push_back(v);
    graph[v].push_back(u);
}
```

---

### String / Non-Integer Nodes

```cpp
unordered_map<string, vector<string>> graph;

// add edge
graph["A"].push_back("B");
graph["B"].push_back("A");   // undirected

// safe insert if key might not exist
graph["C"];   // default constructs empty vector

// iterate
for (auto& [node, neighbors] : graph) {
    for (auto& neighbor : neighbors) {
        cout << node << " → " << neighbor;
    }
}
```

---

### From Adjacency Matrix

```cpp
int n = 4;
vector<vector<int>> matrix = {
    {0,1,0,1},
    {1,0,1,0},
    {0,1,0,1},
    {1,0,1,0}
};

vector<vector<int>> graph(n);

for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        if (i != j && matrix[i][j] == 1)
            graph[i].push_back(j);
```

---

### Full BFS Template (C++)

```cpp
void bfs(int start, vector<vector<int>>& graph, int n) {
    vector<bool> vis(n, false);
    queue<int> q;

    vis[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front(); q.pop();
        cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!vis[neighbor]) {
                vis[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}
```

---

### Full DFS Template (C++)

```cpp
void dfs(int node, vector<vector<int>>& graph, vector<bool>& vis) {
    vis[node] = true;
    cout << node << " ";

    for (int neighbor : graph[node])
        if (!vis[neighbor])
            dfs(neighbor, graph, vis);
}

// call from main
vector<bool> vis(n, false);
for (int i = 0; i < n; i++)
    if (!vis[i])
        dfs(i, graph, vis);
```

---

## Java Templates

### Unweighted Undirected

```java
int n = 5;
int[][] edges = {{0,1},{1,2},{2,3},{3,4}};

List<List<Integer>> graph = new ArrayList<>();
for (int i = 0; i < n; i++)
    graph.add(new ArrayList<>());

for (int[] edge : edges) {
    graph.get(edge[0]).add(edge[1]);
    graph.get(edge[1]).add(edge[0]);   // remove for directed
}

// iterate neighbors
for (int neighbor : graph.get(u)) {
    // process neighbor
}
```

---

### Unweighted Directed

```java
List<List<Integer>> graph = new ArrayList<>();
for (int i = 0; i < n; i++)
    graph.add(new ArrayList<>());

for (int[] edge : edges)
    graph.get(edge[0]).add(edge[1]);   // one direction
```

---

### Weighted Undirected

```java
// int[] = {neighbor, weight}
List<List<int[]>> graph = new ArrayList<>();
for (int i = 0; i < n; i++)
    graph.add(new ArrayList<>());

for (int[] edge : edges) {
    int u = edge[0], v = edge[1], w = edge[2];
    graph.get(u).add(new int[]{v, w});
    graph.get(v).add(new int[]{u, w});   // remove for directed
}

// iterate
for (int[] neighborInfo : graph.get(u)) {
    int neighbor = neighborInfo[0];
    int weight   = neighborInfo[1];
}
```

---

### 1-Indexed Graph

```java
int n = 5;   // nodes 1 to 5
List<List<Integer>> graph = new ArrayList<>();
for (int i = 0; i <= n; i++)   // n+1 lists
    graph.add(new ArrayList<>());
```

---

### String / Non-Integer Nodes

```java
Map<String, List<String>> graph = new HashMap<>();

// add edge
graph.computeIfAbsent("A", k -> new ArrayList<>()).add("B");
graph.computeIfAbsent("B", k -> new ArrayList<>()).add("A");

// iterate
for (Map.Entry<String, List<String>> entry : graph.entrySet()) {
    String node = entry.getKey();
    for (String neighbor : entry.getValue()) {
        System.out.println(node + " → " + neighbor);
    }
}
```

---

### From Adjacency Matrix

```java
int n = 4;
int[][] matrix = {{0,1,0,1},{1,0,1,0},{0,1,0,1},{1,0,1,0}};

List<List<Integer>> graph = new ArrayList<>();
for (int i = 0; i < n; i++) graph.add(new ArrayList<>());

for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        if (i != j && matrix[i][j] == 1)
            graph.get(i).add(j);
```

---

### Full BFS Template (Java)

```java
void bfs(int start, List<List<Integer>> graph, int n) {
    boolean[] vis = new boolean[n];
    Queue<Integer> q = new LinkedList<>();

    vis[start] = true;
    q.offer(start);

    while (!q.isEmpty()) {
        int node = q.poll();
        System.out.print(node + " ");

        for (int neighbor : graph.get(node)) {
            if (!vis[neighbor]) {
                vis[neighbor] = true;
                q.offer(neighbor);
            }
        }
    }
}
```

---

### Full DFS Template (Java)

```java
void dfs(int node, List<List<Integer>> graph, boolean[] vis) {
    vis[node] = true;
    System.out.print(node + " ");

    for (int neighbor : graph.get(node))
        if (!vis[neighbor])
            dfs(neighbor, graph, vis);
}

// call from main — handles disconnected components
boolean[] vis = new boolean[n];
for (int i = 0; i < n; i++)
    if (!vis[i])
        dfs(i, graph, vis);
```

---

## Common Mistakes

| Mistake | Effect | Fix |
|---------|--------|-----|
| `vector<vector<int>> adj(n, vector<int>(m))` | Preallocates garbage entries | `vector<vector<int>> adj(n)` |
| Size `n` for 1-indexed nodes | Index out of bounds at node `n` | Size `n+1` |
| Adding edge one way for undirected | Neighbors missing in traversal | Add both `u→v` and `v→u` |
| Using `n` for column bounds in grid | Wrong bounds for non-square grids | Use separate `m = grid[0].size()` |
| Not checking `vis` before pushing to queue | Same node processed multiple times | Always check `!vis[node]` before push |

---

## Complexity Reference

| Operation | Adjacency List | Adjacency Matrix |
|-----------|---------------|-----------------|
| Build | O(V + E) | O(V²) |
| Find neighbors | O(degree) | O(V) |
| Check edge (u,v) | O(degree) | O(1) |
| BFS / DFS | O(V + E) | O(V²) |
| Space | O(V + E) | O(V²) |

> Use adjacency list for **sparse graphs** (most LeetCode problems). Use adjacency matrix only when frequent edge lookups are needed or graph is dense.
