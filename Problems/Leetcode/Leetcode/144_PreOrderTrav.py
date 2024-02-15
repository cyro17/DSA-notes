

# class Node:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right


class Solution:
    def preOrderTrav(self, root):

        if root is None:
            return []

        stack = []
        res = []

        stack.append(root)
        while (len(stack) > 0):
            node = stack.pop()
            res.append(node.val)
            if node.right is not None:
                stack.append(node.right)
            if node.left is not None:
                stack.append(node.left)

        return res

# Driver Code

# if __name__ == '__main__':

#     root = Node(10)
#     root.left = Node(8)
#     root.right = Node(2)
#     root.left.left = Node(3)
#     root.left.right = Node(5)
#     root.right.left = Node(2)

#     sol = Solution()
#     print(sol.preOrderTrav(root))
