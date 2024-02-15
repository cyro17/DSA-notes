#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

vector<int> bottomView(Node *root)
{
    if (root == NULL)
        return {};
    map<int, int> mp;           // {distance, ans}
    queue<pair<Node *, int>> q; // {node, distance}
    q.push({root, 0});

    while (!q.empty())
    {
        int sz = (int)q.size();
        for (int i = 0; i < sz; i++)
        {
            auto cur = q.front();
            q.pop();
            mp[cur.second] = cur.first->data;
            if (cur.first->left != NULL)
                q.push({cur.first->left, cur.second - 1});
            if (cur.first->right != NULL)
                q.push({cur.first->right, cur.second + 1});
        }
    }

    vector<int> ans;
    for (auto it : mp)
        ans.push_back(it.second);
    return ans;
}

// Time Complexity: O(n)
// Space Complexity: O(n)