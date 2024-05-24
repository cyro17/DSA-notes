#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

class Solution
{
public:
    int findPos(int in[], int ele, int n)
    {
        for (int i = 0; i < n; i++)
        {
            if (in[i] == ele)
            {
                return i;
            }
            return -1;
        }
    }

    Node *solve(int in[], int pre[], int &index, int INstart, int INend, int n)
    {
        if (index >= n || INstart > INend)
        {
            return NULL;
        }
        int element = pre[index++];
        Node *node = new Node(element);
        int pos = findPos(in, element, n);

        node->left = solve(in, pre, index, INstart, pos - 1, n);
        node->right = solve(in, pre, index, pos + 1, INend, n);
        return node;
    }

    Node *buildTree(int in[], int pre[], int n)
    {
        // Code here
        int preIdx = 0;
        Node *res = solve(in, pre, preIdx, 0, n - 1, n);
        return res;
    }
};

int main()
{

    return 0;
}