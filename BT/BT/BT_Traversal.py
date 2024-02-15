

class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


def InorderTraversal(root):
    """
    Left -> Root -> Right
    """
    if root:
        InorderTraversal(root.left)
        print(root.value)
        InorderTraversal(root.right)
        return "InOrderTraversal Done"


def PreOrderTraverersal(root):
    """
    Root -> left -> Right
    """
    if root:
        print(root.value)
        InorderTraversal(root.left)
        InorderTraversal(root.right)
        return "PreOrderTraversal Done"


def PostOrderTraversal(root):
    """
    Left -> Right -> Root
    """
    if root:
        InorderTraversal(root.left)
        InorderTraversal(root.right)
        print(root.value)
        return "postOrderTraversal Done"


def LevelOrderTraversal(root):
    h = height(root)
    for i in range(1, h+1):
        currentLevel(root, i)
    print('\n')
    return "LevelOrderTraversal Done"


def height(node):
    if not node:
        return 0
    else:
        lheight = height(node.left)
        rheight = height(node.right)
        if lheight > rheight:
            return lheight + 1
        else:
            return rheight + 1


def currentLevel(root, level):
    if root is None:
        return
    if level == 1:
        print(root.value, end="")
    elif level > 1:
        currentLevel(root.left, level-1)
        currentLevel(root.right, level-1)


if __name__ == "__main__":
    root = Node(1)
    root.left = Node(2)
    root.right = Node(3)
    root.left.left = Node(4)
    root.left.right = Node(5)
    root.right.left = Node(6)
    root.right.right = Node(7)
    print(root)
    print("\n")
    print("InorderTraversal")
    print(InorderTraversal(root))
    print("\n")

    print("PreOrderTraversal")
    print(PreOrderTraverersal(root))
    print("\n")

    print("PostOrderTraversal")
    print(PostOrderTraversal(root))
    print("\n")

    print("LevelOrderTraversal")
    print(LevelOrderTraversal(root))
