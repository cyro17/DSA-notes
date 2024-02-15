

from collections import deque
import queue


class newNode:

    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None


class Solution:
    def rightView(root):
        queue = deque()
        queue.append(root)
        result = []

        while queue:
            size = len(queue)
            i = 0
            while i < size:
                curr = queue.popleft()
                i += 1

                if i == size:
                    result.append(curr.val)
                if curr.left:
                    queue.append(curr.left)
                if curr.right:
                    queue.append(curr.right)
        return result


if __name__ == '__main__':

    root = newNode(1)
    root.left = newNode(2)
    root.right = newNode(3)
    root.left.left = newNode(4)
    root.left.right = newNode(5)
    root.right.left = newNode(6)
    root.right.right = newNode(7)
    root.left.left.left = newNode(8)
    print(Solution.rightView(root))
