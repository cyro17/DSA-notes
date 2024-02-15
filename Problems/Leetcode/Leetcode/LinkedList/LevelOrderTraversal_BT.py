# Python3 program to print the
# left view of Binary Tree

# Binary Tree Node
""" utility that allocates a newNode
with the given key """


import queue
from unittest import result


class newNode:

    # Construct to create a newNode
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.hd = 0

# Utility function to print the left
# view of the binary tree


class Solution:
    def levelordertraversal(root):
        if not root:
            return []
        queue = [root]
        next_queue = []
        level = []
        result = []

        while queue != []:
            for node in queue:
                level.append(node.data)
                if node.left:
                    next_queue.append(node.left)
                if node.right:
                    next_queue.append(node.right)
            result.append(level)
            level = []
            queue = next_queue
            next_queue = []
        return result


# Driver Code
if __name__ == '__main__':

    root = newNode(1)
    root.left = newNode(2)
    root.right = newNode(3)
    root.left.right = newNode(4)
    root.right.left = newNode(5)
    root.right.left.right = newNode(6)
    root.right.left.right.left = newNode(7)
    root.right.left.right.right = newNode(8)
    print(Solution.levelordertraversal(root))

# This code is contributed by
# Shubham Singh(SHUBHAMSINGH10)
