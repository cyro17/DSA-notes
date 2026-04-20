# Eventual Safe Nodes

Find all **safe nodes** in a directed graph.

> A node is **safe** if every path from it eventually leads to a terminal node (node with no outgoing edges). Return all safe nodes in ascending order.

---

## Key Definitions

```
Terminal node = node with no outgoing edges → always safe
Safe node     = not in a cycle AND doesn't lead to a cycle
Unsafe node   = part of a cycle OR leads to a cycle
```

---

## Core Insight

```
Safe node  = all paths from it eventually terminate
           = cannot reach a cycle

Unsafe node = lies on a cycle
            = OR leads to a cycle
```

At most one of these is true for any node — and it propagates:

```
If node X only points to safe nodes → X is safe
If node X points to any unsafe node → X is unsafe

Safety spreads BACKWARDS from terminal nodes outward.
```

---

## Approach 1 — DFS with 3-State Coloring

### Intuition

Run DFS. Track each node's state:

```
0 = unvisited
1 = currently being processed (on DFS path)
2 = confirmed safe (fully processed)
```

If during DFS you reach a node with state `1` → you've found a cycle → current path is unsafe.
If you reach state `2` → already confirmed safe → return true immediately.
If all neighbors are safe → mark current node as `2` (safe).

### Implementation (C++)

```cpp
class Solution {
private:
    bool dfs(int node, vector<vector<int>>& graph, vector<int>& state) {
        if (state[node] == 1) return false;  // cycle detected
        if (state[node] == 2) return true;   // already confirmed safe

        state[node] = 1;  // mark as being processed

        for (int neighbor : graph[node]) {
            if (!dfs(neighbor, graph, state))
                return false;  // neighbor leads to cycle → unsafe
        }

        state[node] = 2;  // all neighbors safe → mark safe
        return true;
    }

public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> state(n, 0);

        vector<int> result;
        for (int i = 0; i < n; i++)
            if (dfs(i, graph, state))
                result.push_back(i);

        return result;
    }
};
```

### Dry Run

```
graph = [[1,2],[2,3],[5],[0],[5],[],[]]

0→[1,2], 1→[2,3], 2→[5], 3→[0], 4→[5], 5→[], 6→[]
cycle: 0→1→3→0
terminals: 5, 6
```

```
dfs(0): state[0]=1
  dfs(1): state[1]=1
    dfs(2): state[2]=1
      dfs(5): state[5]=1, no neighbors → state[5]=2 ✅
    state[2]=2 ✅
    dfs(3): state[3]=1
      dfs(0): state[0]==1 → cycle → return false ❌
    return false ← 3 unsafe
  return false ← 1 unsafe
return false ← 0 unsafe

dfs(4): state[4]=1
  dfs(5): state[5]==2 → return true ✅
state[4]=2 ✅

dfs(6): state[6]=1, no neighbors → state[6]=2 ✅

safe nodes = [2, 4, 5, 6] ✅
```

### Why O(V+E) Not O(V²)

The outer loop calls `dfs(i)` for every node — looks like O(V × DFS) = O(V²). But the **state array prevents reprocessing**:

```
state[node] == 1 or 2 → return immediately O(1)

Each node transitions exactly once: 0→1→2
Each edge traversed exactly once

Total = O(V) transitions + O(E) edge traversals = O(V+E)
```

### Complexity

| | Value |
|-|-------|
| **Time** | O(V+E) — state array ensures each node/edge processed once |
| **Space** | O(V) — state array + O(V) recursion stack |

---

## Approach 2 — Kahn's Algorithm on Reversed Graph

### Intuition

Instead of asking **"can this node reach a terminal?"** — ask the reverse:

> **"Can a terminal reach this node going backwards?"**

These are equivalent questions — just asked from opposite directions.

```
ORIGINAL:  terminal ← safe ← unsafe(cycle)
REVERSED:  terminal → safe → (blocked by cycle)

Reverse edges → terminals become SOURCES
BFS from sources → everything reachable = SAFE
Cycle nodes block the spread → UNSAFE
```

**Why Kahn's fits:** After reversing, terminal nodes have indegree 0 (no outgoing edges originally = no incoming edges in reversed). Kahn's naturally starts from indegree-0 nodes → starts from terminals → spreads safety outward.

### The Domino Effect

```
Safety propagates backwards from terminals:

Round 1: terminals processed → spread safety to their predecessors
Round 2: predecessors with all deps resolved → spread further
...
Cycle nodes: waiting on each other forever → never processed → unsafe
```

### Implementation (C++)

```cpp
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();

        // build reversed graph + indegrees
        vector<vector<int>> revAdj(n);
        vector<int> indegree(n, 0);

        for (int u = 0; u < n; u++) {
            for (int v : graph[u]) {
                revAdj[v].push_back(u);  // reverse edge v→u
                indegree[u]++;           // u's outdegree = indegree in reversed
            }
        }

        // seed queue with terminal nodes (indegree 0 = outdegree 0 in original)
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indegree[i] == 0)
                q.push(i);

        // Kahn's BFS
        vector<bool> safe(n, false);
        while (!q.empty()) {
            int node = q.front(); q.pop();
            safe[node] = true;

            for (int neighbor : revAdj[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }

        vector<int> result;
        for (int i = 0; i < n; i++)
            if (safe[i]) result.push_back(i);

        return result;
    }
};
```

### Dry Run

```
graph = [[1,2],[2,3],[5],[0],[5],[],[]]
n = 7
```

**Step 1 — Reverse edges:**

| Original | Reversed |
|----------|----------|
| 0→1 | 1→0 |
| 0→2 | 2→0 |
| 1→2 | 2→1 |
| 1→3 | 3→1 |
| 2→5 | 5→2 |
| 3→0 | 0→3 |
| 4→5 | 5→4 |

```
revAdj:
0→[3], 1→[0], 2→[0,1], 3→[1], 4→[], 5→[2,4], 6→[]
```

**Step 2 — Indegree (= outdegree in original):**

```
node: 0  1  2  3  4  5  6
deg:  2  2  1  1  1  0  0
                        ↑  ↑
                     terminals
```

**Step 3 — BFS:**

| Event | Queue | indegree | safe |
|-------|-------|----------|------|
| Init | [5,6] | [2,2,1,1,1,0,0] | [F,F,F,F,F,F,F] |
| pop 5 | [6,2,4] | [2,2,0,1,0,-,0] | [F,F,F,F,F,T,F] |
| pop 6 | [2,4] | [2,2,0,1,0,-,-] | [F,F,F,F,F,T,T] |
| pop 2 | [4] | [1,1,-,1,0,-,-] | [F,F,T,F,F,T,T] |
| pop 4 | [] | [1,1,-,1,-,-,-] | [F,F,T,F,T,T,T] |
| done | [] | — | [F,F,T,F,T,T,T] |

**Nodes 0,1,3 stuck in cycle — indegree never reaches 0.**

```
result = [2, 4, 5, 6] ✅
```

### Why Cycle Nodes Are Stuck

```
cycle in original: 0→1→3→0
cycle in reversed: 0→3→1→0  (still a cycle!)

node 0 waits for node 1
node 1 waits for node 3
node 3 waits for node 0
→ circular → none ever reach indegree 0 → all unsafe ✅
```

### Complexity

| | Value |
|-|-------|
| **Time** | O(V+E) — build reversed O(E) + Kahn's BFS O(V+E) |
| **Space** | O(V+E) — reversed adjacency list dominates |

---

## Node-by-Node Verdict

| Node | Safe? | Reason |
|------|-------|--------|
| 0 | ❌ | Part of cycle 0→1→3→0 |
| 1 | ❌ | Part of cycle 0→1→3→0 |
| 2 | ✅ | 2→5 (terminal) |
| 3 | ❌ | Part of cycle 0→1→3→0 |
| 4 | ✅ | 4→5 (terminal) |
| 5 | ✅ | Terminal node |
| 6 | ✅ | Terminal node |

---

## Both Approaches Compared

| | DFS 3-State | Kahn's Reverse |
|-|-------------|----------------|
| **Time** | O(V+E) | O(V+E) |
| **Space** | **O(V)** | O(V+E) — extra reversed graph |
| **Recursion risk** | ✅ Yes — stack depth O(V) | ❌ None — iterative |
| **Cycle detection** | Via state==1 check | Via indegree never reaching 0 |
| **Intuition** | Direct — track path state | Indirect — reverse + spread safety |
| **Interview signal** | ✅ Clean | ✅ Shows Kahn's mastery |

---

## Key Takeaways

- **DFS approach** — 3 states are the key. State 1 = "currently on path" → seeing it again = cycle. State 2 = "confirmed safe" → return immediately without reprocessing. This is what keeps it O(V+E) not O(V²).
- **Reverse approach** — safety is a property that flows backwards from terminals. Reversing edges lets BFS spread this property forward. Cycle nodes are self-blocking — they never fully resolve their indegree.
- Both approaches are O(V+E) time — DFS wins on space (O(V) vs O(V+E)) but carries recursion stack risk.
- The cycle in the reversed graph is still a cycle — reversing edges doesn't break cycles, just changes direction. This is why cyclic nodes remain stuck.
