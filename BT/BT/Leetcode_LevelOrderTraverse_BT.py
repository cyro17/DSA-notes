from _typeshed import Self
from typing import List


class TreeNode:
    def __init__(self, value) -> None:
        self.val = value
        self.left = None
        self.right = None


class Solution:
    def levelOrderTraverse(self, root: TreeNode) -> List[List[int]]:
        if root is None:
            return []
        queue = [root]
        next_queue = []
        level = []
        result = []

        while queue != []:
            for root in queue:
                level.append(root.val)
                if root.left is not None:
                    next_queue.append(root.left)
                if root.right is not None:
                    next_queue.append(root.right)
            result.append(level)
            level = []
            queue = next_queue
            next_queue = []
        return result
