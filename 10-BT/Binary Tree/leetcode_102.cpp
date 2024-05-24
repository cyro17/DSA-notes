// bfs
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
};

class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> res;
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            vector<int> level;
            int len = q.size();
            for (int i = 0; i < len; i++)
            {
                TreeNode *node = q.front();
                q.pop();
                if (!node == NULL)
                {
                    level.push_back(node->val);
                    q.push(node->left);
                    q.push(node->right);
                }
            }
            if (!level.empty())
                res.push_back(level);
        }
        return res;
    }
};

int main()
{
}