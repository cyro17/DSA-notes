
# AVL Tree node to store the data

import QueueLinkedList as queue


class AVLNode:
    def __init__(self, data, left=None, right=None, height=1):
        self.data = data
        self.left = left
        self.right = right
        self.height = height


def preOrderTraverse(rootNode):
    if not rootNode:
        return
    print(rootNode.data)
    preOrderTraverse(rootNode.left)
    preOrderTraverse(rootNode.right)


def postOrderTraverse(rootNode):
    if not rootNode:
        return
    postOrderTraverse(rootNode.left)
    postOrderTraverse(rootNode.right)
    print(rootNode.data)


def inOrderTraversal(rootNode):
    if not rootNode:
        return
    inOrderTraversal(rootNode.left)
    print(rootNode.data)
    inOrderTraversal(rootNode.right)


def levelOrderTraverse(rootNode):
    if not rootNode:
        return
    else:
        # custQ = queue.Queue()
        # custQ.EnQueue(rootNode)
        # while not (custQ.isEmpty()):
        #     root = custQ.DeQueue()
        #     print(root.value.data)

        #     if root.value.left is not None:
        #         custQ.EnQueue(root.value.left)

        #     if root.value.right is not None:
        #         custQ.EnQueue(root.value.right)

        custQ = queue.Queue()
        custQ.enqueue(rootNode)
        while not (custQ.isEmpty()):
            root = custQ.dequeue()
            print(root.value.data)
            if root.value.left is not None:
                custQ.enqueue(root.value.left)
            if root.value.right is not None:
                custQ.enqueue(root.value.right)


def searchNode(rootNode, NodeValue):
    if rootNode.data == NodeValue:
        return "The NodeValue is found."

    elif NodeValue < rootNode:
        if rootNode.left.data == NodeValue:
            return " The NodeValue is found."
        else:
            searchNode(rootNode.left, NodeValue)
    else:
        if rootNode.right == NodeValue:
            return "The nodeavalue is found."
        else:
            searchNode(rootNode.right, NodeValue)


def rotateRight(UnbalancedNode):
    newRoot = UnbalancedNode.left
    UnbalancedNode.left = UnbalancedNode.left.right
    newRoot.right = UnbalancedNode
    UnbalancedNode.height = 1 + \
        max(getHeight(UnbalancedNode.left), getHeight(UnbalancedNode.right))
    newRoot.height = 1 + max(getHeight(newRoot.left), getHeight(newRoot.right))
    return newRoot


def rotateLeft(UnbalancedNode):
    newRoot = UnbalancedNode.right
    UnbalancedNode.right = UnbalancedNode.right.left
    newRoot.left = UnbalancedNode
    UnbalancedNode.height = 1 + \
        max(getHeight(UnbalancedNode.left), getHeight(UnbalancedNode.right))
    newRoot.height = 1 + \
        max(getHeight(newRoot.left), getHeight(newRoot.right))
    return newRoot


def getHeight(rootNode):
    if not rootNode:
        return
    return rootNode.height


def getbalance(rootNode):
    if not rootNode:
        return 0
    return getHeight(rootNode.left) - getHeight(rootNode.right)


def insertNode(rootNode, NodeValue):            # ----> O(LogN)

    if not rootNode:
        return

    if NodeValue < rootNode.data:
        rootNode.left = insertNode(rootNode.left, NodeValue)

    else:
        rootNode.right = insertNode(rootNode.right, NodeValue)

    # update the height of the rootnode
    rootNode.height = 1 + max(getHeight(rootNode.left),
                              getHeight(rootNode.right))

    # get balance of the rootnode
    balance = getbalance(rootNode)

    # left left condition
    if balance > 1 and NodeValue < rootNode.left.data:
        return rotateRight(rootNode)

    # right right condition
    if balance < -1 and NodeValue > rootNode.right.data:
        return rotateLeft(rootNode)

    # left right condition
    if balance > 1 and NodeValue > rootNode.left.data:
        rootNode.left = rotateLeft(rootNode.left)
        return rotateRight(rootNode)

    # right left condition
    if balance < -1 and NodeValue < rootNode.right.data:
        rootNode.right = rotateRight(rootNode.right)
        return rotateLeft(rootNode)

    return rootNode


def getMinValueNode(rootNode):
    if rootNode is None or rootNode.left is None:
        return rootNode
    return getMinValueNode(rootNode.left)


def deleteNode(rootNode, nodeValue):
    if not rootNode:
        return

    elif nodeValue < rootNode.data:
        rootNode.left = deleteNode(rootNode.left, nodeValue)

    elif nodeValue > rootNode.right:
        rootNode.right = deleteNode(rootNode.right, nodeValue)

    # the node to be deleted is the rootnode
    else:
        if rootNode.left is None:
            temp = rootNode.right
            rootNode = None
            return temp

        elif rootNode.right is None:
            temp = rootNode.left
            rootNode = None
            return temp

        # if the rootNode has both the child
        else:
            # find the successsor node if the node to be deleted has two child
            temp = getMinValueNode(rootNode.right)
            # replace the root
            rootNode.data = temp.data
            # delete the successor node
            rootNode.right = deleteNode(rootNode.right, temp.data)

            # get the balance factor of the rootnode
    balance = getbalance(rootNode)

    # LL condition
    if balance > 1 and getbalance(rootNode.left) >= 0:
        return rotateRight(rootNode)

    # RR condition
    if balance < -1 and getbalance(rootNode.right) < 0:
        return rotateLeft(rootNode)

    # LR condition
    if balance > 1 and getbalance(rootNode.right) < 0:
        rootNode.left = rotateLeft(rootNode.left)
        return rotateRight(rootNode)

    # RL condition
    if balance < -1 and getbalance(rootNode.left) > 0:
        rootNode.right = rotateRight(rootNode.right)
        return rotateLeft(rootNode)


def deleteAVL(rootNode):
    rootNode = None
    rootNode.left = None
    rootNode.right = None
    return " The AVL Tree has been deleted. "


# Driver Code
if __name__ == "__main__":
    newAVL = AVLNode(5)
    newAVL = insertNode(newAVL, 10)
    newAVL = insertNode(newAVL, 15)
    newAVL = insertNode(newAVL, 20)
    newAVL = insertNode(newAVL, 25)
    newAVL = insertNode(newAVL, 30)

levelOrderTraverse(newAVL)
