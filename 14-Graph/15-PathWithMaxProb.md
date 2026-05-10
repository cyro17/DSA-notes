#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges,
                          vector<double>& succProb,
                          int start_node, int end_node) {

        // Build adjacency list
        vector<vector<pair<int, double>>> adj(n);
        for (int i = 0; i < (int)edges.size(); ++i) {
            int u = edges[i][0], v = edges[i][1];
            double w = succProb[i];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w}); // undirected
        }

        // Max-heap: {probability, node}
        priority_queue<pair<double, int>> pq;
        pq.push({1.0, start_node});

        vector<double> prob(n, 0.0);
        prob[start_node] = 1.0;

        while (!pq.empty()) {
            auto [p, node] = pq.top();
            pq.pop();

            for (auto &[adjnode, w] : adj[node]) {
                if (p * w > prob[adjnode]) {
                    prob[adjnode] = p * w;
                    pq.push({prob[adjnode], adjnode});
                }
            }
        }

        return prob[end_node];
    }
};
