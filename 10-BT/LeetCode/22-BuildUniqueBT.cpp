
/* Using preOrder and Inorder  */
class Solution
{
private:
    TreeNode *build(vector<int> &inorder, vector<int> &preorder, int &root_index, int left, int right, unordered_map<int, int> &mp)
    {
        if (left > right || root_index > preorder.size() - 1)
            return NULL;
        int in_root = mp[preorder[root_index]];

        TreeNode *node = new TreeNode(preorder[root_index++]);
        node->left = build(inorder, preorder, root_index, left, in_root - 1, mp);
        node->right = build(inorder, preorder, root_index, in_root + 1, right, mp);
        return node;
    }

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        unordered_map<int, int> mp;
        int root_index = 0;
        for (int i = 0; i < inorder.size(); i++)
        {
            mp[inorder[i]] = i;
        }
        return build(inorder, preorder, root_index, 0, inorder.size() - 1, mp);
    }
};

/* Using postOrder and Inorder */

class Solution_2
{
public:
    TreeNode *build(vector<int> &inorder, vector<int> &postorder, int &idx, int left, int right, unordered_map<int, int> &mp)
    {
        if (idx < 0 || left > right)
        {
            return NULL;
        }
        int in_root = mp[postorder[idx]];

        TreeNode *root = new TreeNode(postorder[idx--]);
        root->right = build(inorder, postorder, idx, in_root + 1, right, mp);
        root->left = build(inorder, postorder, idx, left, in_root - 1, mp);

        return root;
    }
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        unordered_map<int, int> mp;

        for (int i = 0; i < inorder.size(); i++)
        {
            mp[inorder[i]] = i;
        }
        int idx = postorder.size() - 1;
        return build(inorder, postorder, idx, 0, inorder.size() - 1, mp);
    }
};