# Python3 program to print the
# left view of Binary Tree

# Binary Tree Node
""" utility that allocates a newNode
with the given key """


from collections import deque


class newNode:

    # Construct to create a newNode
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

# Utility function to print the left
# view of the binary tree


class Solution:
    def leftView(root):
        queue = deque()
        queue.append(root)
        result = []
        while queue:
            size = len(queue)
            i = 0
            while i < size:
                curr = queue.popleft()
                i += 1
                if i == 1:
                    result.append(curr.val)
                if curr.left:
                    queue.append(curr.left)
                if curr.right:
                    queue.append(curr.right)
        return result


# Driver Code
if __name__ == '__main__':

    root = newNode(1)
    root.left = newNode(2)
    root.right = newNode(3)
    root.left.left = newNode(4)
    root.left.right = newNode(5)
    root.right.left = newNode(6)
    root.right.right = newNode(7)
    root.left.left.left = newNode(8)
    print(Solution.leftView(root))

# This code is contributed by
# Shubham Singh(SHUBHAMSINGH10)
