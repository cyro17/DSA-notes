# sorted array to Binary Search Tree

# Input: Array {1, 2, 3, 4}
# Output: A Balanced BST
#           3
#         /  \
#       2    4
#      /
#     1


class Node:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

# input : sorted array of integer.
# output : root node of the BST.


def sortedArrayToBST(arr):
    if not arr:
        return None

    # find the middle
    mid = (len(arr)) / 2

    # make the middle element the root node
    root = Node(arr[mid])

    # left subtree of root has all values < mid[arr]
    root.left = sortedArrayToBST(arr[:mid])

    # right subtree of root has all values > mid[arr]
    root.right = sortedArrayToBST(arr[mid+1:])

    return root


def preOrder(root):
    if not root:
        return
    print(root.data)
    preOrder(root.left)
    preOrder(root.right)
