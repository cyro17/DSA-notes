#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int x)
    {
        data = x;
        left = right = NULL;
    }
};

void rec_right_view(Node *root, int level, vector<int> &res)
{
    if (!root)
        return;

    if (res.size() == level)
        res.push_back(root->data);
    rec_right_view(root->right, level + 1, res);
    rec_right_view(root->left, level + 1, res);
}

vector<int> right_view(Node *root)
{
    vector<int> res;
    rec_right_view(root, 0, res);
    return res;
}
