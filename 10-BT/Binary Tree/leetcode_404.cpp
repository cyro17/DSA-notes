

// sum of left leaf nodes
struct node
{
    int val = 0;
    node *left = nullptr;
    node *right = nullptr;
};

bool isLeaf(node *node)
{
    if (!node)
    {
        return false;
    }
    if (!node->left && !node->right)
        return true;

    return false;
}

int leftLeafSum(node *root)
{
    int sum = 0;
    if (root)
    {
        if (isLeaf(root->left))
            sum += root->left->val;

        else
            sum += leftLeafSum(root->left);

        sum += leftLeafSum(root->right);
    }
    return sum;
}
