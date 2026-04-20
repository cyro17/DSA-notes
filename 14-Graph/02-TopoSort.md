# Topological Sort

A **topological ordering** of a Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge `u → v`, vertex `u` comes before `v`.

> Only valid for **DAGs** — graphs with no cycles. If a cycle exists, no valid topological order is possible.

---

## Real World Analogy

```
Course prerequisites:
Arrays → Linked List → Trees → Graphs
                     ↗
          Recursion

You must learn Arrays before Linked List.
You must learn Recursion before Trees.
Topological sort gives a valid study order.
```

---

## Key Properties

```
1. Only works on Directed Acyclic Graphs (DAG)
2. Multiple valid orderings may exist
3. For every edge u→v: u appears before v in result
4. If cycle exists → no valid ordering → result.size() < n
```

---

## Approach 1 — DFS Based (Reverse Postorder)

### Intuition

Run DFS. When you **finish** processing a node (all its neighbors fully explored) — push it to a stack. Pop the stack at the end for the topological order.

```
Why stack?
  If u → v exists:
    v finishes BEFORE u (DFS goes deep first)
    v pushed to stack BEFORE u
    u comes OUT of stack BEFORE v
    → u before v in result ✅
```

Push AFTER neighbors = finish order = reverse topological order.

### The Three Rules

```
1. Visit each node exactly once (vis array)
2. Recurse into all unvisited neighbors first
3. Push to stack ONLY after all neighbors done
```

### Implementation (C++)

```cpp
class Solution {
private:
    void dfs(int node, vector<vector<int>>& adj,
             vector<bool>& vis, stack<int>& st) {
        vis[node] = true;

        for (int neighbor : adj[node])
            if (!vis[neighbor])
                dfs(neighbor, adj, vis, st);

        st.push(node);   // push AFTER all neighbors done — critical
    }

public:
    vector<int> topoSort(int n, vector<vector<int>>& adj) {
        vector<bool> vis(n, false);
        stack<int> st;

        // handle disconnected components
        for (int i = 0; i < n; i++)
            if (!vis[i])
                dfs(i, adj, vis, st);

        // drain stack → topological order
        vector<int> result;
        while (!st.empty()) {
            result.push_back(st.top());
            st.pop();
        }

        return result;
    }
};
```

### Dry Run

```
graph:
5→0, 5→2, 4→0, 4→1, 2→3, 3→1

adj:
0→[], 1→[], 2→[3], 3→[1], 4→[0,1], 5→[0,2]
```

```
i=0: dfs(0) → no neighbors → push 0    stack: [0]
i=1: dfs(1) → no neighbors → push 1    stack: [0,1]
i=2: dfs(2)
       dfs(3)
         dfs(1): already visited
         push 3                          stack: [0,1,3]
       push 2                            stack: [0,1,3,2]
i=3: already visited
i=4: dfs(4)
       dfs(0): already visited
       dfs(1): already visited
       push 4                            stack: [0,1,3,2,4]
i=5: dfs(5)
       dfs(0): already visited
       dfs(2): already visited
       push 5                            stack: [0,1,3,2,4,5]

pop all → result = [5, 4, 2, 3, 1, 0]

verify:
5→0 ✅  5→2 ✅  4→0 ✅  4→1 ✅  2→3 ✅  3→1 ✅
```

**Result: [5, 4, 2, 3, 1, 0] ✅**

### Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O(V+E) | Each node and edge visited exactly once |
| **Space** | O(V) | vis array + stack + recursion depth |

---

## Approach 2 — Kahn's Algorithm (BFS Based)

### Intuition

Use **indegree** — number of incoming edges per node.

```
indegree == 0 → no dependencies → safe to process first
```

Process indegree-0 nodes, remove their edges, check if neighbors now have indegree 0 — repeat.

```
Think of it as peeling layers:
Layer 1: nodes with no dependencies (indegree 0)
Layer 2: nodes whose only dependencies were in layer 1
Layer 3: nodes whose dependencies were in layers 1-2
...
```

### The Five Steps

```
1. Build adjacency list
2. Compute indegree for every node
3. Push all indegree-0 nodes to queue
4. BFS:
     pop node → add to result
     decrement neighbors' indegree
     if neighbor hits 0 → push to queue
5. result.size() == n → valid DAG
   result.size() <  n → cycle exists
```

### Implementation (C++)

```cpp
vector<int> topoSort(int n, vector<vector<int>>& adj) {
    // step 1 — compute indegrees
    vector<int> indegree(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : adj[u])
            indegree[v]++;

    // step 2 — seed queue with indegree-0 nodes
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            q.push(i);

    // step 3 — BFS
    vector<int> result;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        result.push_back(node);

        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    // step 4 — cycle check
    return result;   // result.size() < n → cycle exists
}
```

### Dry Run

```
graph:
5→0, 5→2, 4→0, 4→1, 2→3, 3→1

indegree:
node: 0  1  2  3  4  5
deg:  2  2  1  1  0  0
                     ↑  ↑
                  start here
```

| Step | Pop | Result | indegree changes | Queue |
|------|-----|--------|-----------------|-------|
| init | — | [] | — | [4,5] |
| 1 | 4 | [4] | [0]:2→1, [1]:2→1 | [5] |
| 2 | 5 | [4,5] | [0]:1→0→push, [2]:1→0→push | [0,2] |
| 3 | 0 | [4,5,0] | no neighbors | [2] |
| 4 | 2 | [4,5,0,2] | [3]:1→0→push | [3] |
| 5 | 3 | [4,5,0,2,3] | [1]:1→0→push | [1] |
| 6 | 1 | [4,5,0,2,3,1] | no neighbors | [] |

**Result: [4, 5, 0, 2, 3, 1] ✅**

```
result.size()=6 == n=6 → valid DAG, no cycle
```

### Cycle Detection — Built In

```
cycle: 1→2→3→1

indegree = [1,1,1]
no node reaches indegree 0
queue stays empty
result.size()=0 ≠ n=3 → cycle detected ✅
```

Nodes in a cycle always wait for each other — none ever reach indegree 0 — none enter queue — none in result.

### Complexity

| | Value | Why |
|-|-------|-----|
| **Time** | O(V+E) | Indegree build O(E) + BFS O(V+E) |
| **Space** | O(V) | indegree array + queue + result |

---

## DFS vs Kahn's — Full Comparison

| | DFS (Stack) | Kahn's (BFS) |
|-|-------------|--------------|
| **Time** | O(V+E) | O(V+E) |
| **Space** | O(V) | O(V) |
| **Approach** | Finish order reversed | Remove dependencies layer by layer |
| **Cycle detection** | Needs extra visited-on-path tracking | ✅ Built-in — result.size() check |
| **Iterative?** | ❌ Recursive by nature | ✅ Fully iterative |
| **Stack overflow risk** | ✅ Yes for deep graphs | ❌ None |
| **Intuition** | Harder | Easier |
| **Interview pick** | Good | ✅ Preferred |

---

## Common Mistakes

| Mistake | Effect | Fix |
|---------|--------|-----|
| `st.push(node)` inside neighbor loop | Node pushed multiple times | Push after entire for loop |
| `st.push(node)` before recursing neighbors | Wrong order | Push only after all neighbors done |
| Range-based loop over indegree values for seeding queue | Pushes wrong indices | Use index-based loop `for(int i=0; i<n; i++)` |
| Not handling disconnected components in DFS | Some nodes missed | Outer loop over all nodes |
| Checking `result.size() == n` for DFS | DFS doesn't detect cycles this way | Use Kahn's for cycle detection |

---

## Where Topological Sort Is Used

| Problem | How Topo Sort Helps |
|---------|---------------------|
| Course Schedule I | Detect cycle → can all courses be taken? |
| Course Schedule II | Return valid topo order |
| Alien Dictionary | Build char order graph → topo sort |
| Shortest Path in DAG | Process nodes in topo order, relax edges |
| Eventual Safe Nodes | Kahn's on reversed graph |
| Task Scheduling | Order tasks respecting dependencies |

---

## Key Takeaways

- Topo sort only works on DAGs — cycles make it impossible.
- **DFS approach** — push after all neighbors done. Stack pop order = topological order. The "after all neighbors" constraint is what guarantees correctness.
- **Kahn's approach** — indegree is the engine. Always process what has no remaining dependencies. Decrementing neighbors simulates removing processed edges.
- Both are O(V+E) — Kahn's is preferred in interviews for built-in cycle detection and no recursion risk.
- Multiple valid orderings exist — both approaches give one valid ordering, not necessarily the same one.
