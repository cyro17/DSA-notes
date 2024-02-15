
# Algorithm used :
# 1. construct the root node of the BST, which would be the first key in the preorder sequence.
# 2. find the index 'i' of the first key in the preorder sequence, which is greater than the root node.
# 3. recur for the left subtree with keys in the preorder sequence that appears before
#    the i'th index(excluding the first index.)
# 4. recur for the right subtree with keys in the preorder sequence that appears after
#    the i'th index(excluding the i'th  index.)


class Node:
    def __init__(self, data):
        self.data = data


def constructBST(preOrder, start, end):
    if start > end:
        return
    node = Node(preOrder[start])

    i = start
    while i <= end:
        if preOrder[i] > node.data:
            break
        i += 1

    node.left = constructBST(preOrder, start+1, i-1)

    node.right = constructBST(preOrder, i, end)
    return node


def inOrderTraversal(root):
    if root is None:
        return

    inOrderTraversal(root.left)
    print(root.data, end=' ')
    inOrderTraversal(root.right)


if __name__ == "__main__":
    preOrder = [15, 10, 8, 12, 20, 16, 25]

    root = constructBST(preOrder, 0, len(preOrder)-1)
    print("the inorder traversal fo the binary search tree :")
    inOrderTraversal(root)
