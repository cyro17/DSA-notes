// find the no of nodes in a complete binary tree

struct node
{
    int data = 0;
    node *left = nullptr;
    node *right = nullptr;
};

int left_height(node *node)
{
    int height = 0;
    while (node)
    {
        height++;
        node = node->left;
    }
    return height;
}

int right_height(node *node)
{
    int height = 0;
    while (node)
    {
        height++;
        node = node->right;
    }
    return height;
}

int countNodes(node *root)
{
    if (!root)
    {
        return 0;
    }

    int lh = left_height(root);
    int rh = right_height(root);

    if (lh == rh)
    {
        return (1 << lh) - 1;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
}
