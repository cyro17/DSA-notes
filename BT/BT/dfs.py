class Node:
    def __init__(self, value, left, right):
        self.value = value
        self.left = left
        self.right = right

    def __str__(self) -> str:
        return "Node( " + str(self.value) + " )"


def walk(tree):
    if tree is not None:
        walk(tree.left)
        walk(tree.right)
        print(tree)


def walk2(tree, stack):
    stack.append(tree)
    while len(stack) > 0:
        node = stack.pop()
        if node is not None:
            print(node)
            stack.append(node.right)
            stack.append(node.left)
