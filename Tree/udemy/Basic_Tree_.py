
class TreeNode:
    def __init__(self, data, children=[]):
        self.data = data
        self.children = children

    def __str__(self, level=0):
        ret = " " * level + str(self.data) + "\n"
        for child in self.children:
            ret += child.__str__(level + 1)
        return ret

    def addchild(self, TreeNode):
        self.children.append(TreeNode)


if __name__ == "__main__":
    # create nodes of the tree first
    tr = TreeNode('Drinks', [])
    # two child nodes of the root node tr
    cold = TreeNode('Cold', [])
    hot = TreeNode('Hot', [])
    # hot drinks
    tea = TreeNode('Tea', [])
    coffee = TreeNode('coffee', [])
    # cold drinks
    cola = TreeNode('Cola', [])
    fanta = TreeNode('Fanta', [])

    tr.addchild(hot)
    tr.addchild(cold)
    # print(tr)
    # Add subnodes to the hot node
    hot.addchild(tea)
    hot.addchild(coffee)
    # Add subnodes to the cold nodse
    cold.addchild(cola)
    cold.addchild(fanta)
    print(tr)
