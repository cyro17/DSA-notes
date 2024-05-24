

#  get the height of the binary tree

class Node:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right


def get_Height(root):
    if not root:
        return -1
    left_depth = get_Height(root.left)
    right_depth = get_Height(root.right)

    return max(left_depth, right_depth)+1


if __name__ == "__main__":
    root = Node('A')
    root.left = Node('B')
    root.right = Node('C')
    root.left.left = Node('D')
    root.left.right = Node('F')
    print(get_Height(root))
