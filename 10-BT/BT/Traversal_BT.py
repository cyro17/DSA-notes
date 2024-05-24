import QueueLinkedList as Queue

# class to store the node value


class TreeNode:
    def __init__(self, data):
        self.data = data
        self.lchild = None
        self.rchild = None


def preOrderTraversal(rootNode):
    if not rootNode:
        return
    print(rootNode.data)
    preOrderTraversal(rootNode.lchild)
    preOrderTraversal(rootNode.rchild)


def inOrderTraversal(rootNode):
    if not rootNode:
        return
    inOrderTraversal(rootNode.lchild)
    inOrderTraversal(rootNode)
    inOrderTraversal(rootNode.rchild)


def postOrderTraversal(rootNode):
    if not rootNode:
        return
    postOrderTraversal(rootNode.lchild)
    postOrderTraversal(rootNode.rchild)
    postOrderTraversal(rootNode)


def levelOrderTraversal(rootNode):
    if not rootNode:
        return
    else:
        custQ = Queue.Queue()
        custQ.enqueue(rootNode)

        while not (custQ.isEmpty()):
            root = custQ.dequeue()
            print(root.value.data)

            if (root.value.lchild is not None):
                custQ.enqueue(root.value.lchild)
            if (root.value.rchild is not None):
                custQ.enqueue(root.value.rchild)


newBT = TreeNode("drinks")
lchild = TreeNode("hot")
rchild = TreeNode("cold")
newBT.lchild = lchild
newBT.rchild = rchild

# preOrderTraversal(newBT)
# inOrderTraversal(newBT)
postOrderTraversal(newBT)
levelOrderTraversal(newBT)
