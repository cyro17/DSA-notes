
# Algorithm used :

import sys
# time complexity = O(n^2)

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

    root = Node(preOrder[start])  # create the root node of the BST

    i = start
    while i <= end:
        if preOrder[i] > root.data:
            break
        i += 1

    root.left = constructBST(preOrder, start+1, i-1)

    root.right = constructBST(preOrder, i, end)
    return root


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

# -----------------------------------------------------------------------------------------------------------------------------

# algorithm - 2
    # time complexity = O(n)


class Node:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right


def inOrderTraverse(root):
    if root:
        inOrderTraversal(root.left)
        print(root.data)
        inOrderTraversal(root.right)


def buildBST(preOrder, pIndex=0, min=-sys.maxsize, max=sys.maxsize):

    if pIndex == len(preOrder):
        return None, pIndex

    val = preOrder[pIndex]
    if val < min or val > max:
        return None, pIndex

    root = Node(val)
    pIndex += 1

    root.left, pIndex = buildBST(preOrder, pIndex, min, val-1)

    root.right, pIndex = buildBST(preOrder, pIndex, val+1, max)

    return root, pIndex


if __name__ == "__main__":
    preOrder = [15, 10, 8, 12, 20, 16, 25]
    root = buildBST(preOrder)[0]
    print("the inorder traversal of BST:")
    inOrderTraverse(root)

# -----------------------------------------------------------------------------------------------------------------------------

# GFG - set 2

# algorithm :


class Node:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right


class BST:
    def constructTree(self, preOrder, size):
        root = Node(preOrder[0])
        s = []  # create an empty stack
        s.append(root)  # append the root node to the stack
        i = 1

        while (i < size):
            temp = None

            # while the lenght of the stack is greater than 0 and element of the preorder is greater than last element value of
            # the stack,
            while (len(s) > 0 and preOrder[i] > s[-1].data):
                temp = s.pop()

            # make this greater value as right child and append it to the stack.
            if (temp != None):
                temp.right = Node(preOrder[i])
                s.append(temp.right)

            # if next value is less than stack's top value, make this value as the left child of the stack's top value .t
            else:
                temp = s[-1]
                temp.left = Node(preOrder[i])
                s.append(temp.left)
            i += 1
        return root
