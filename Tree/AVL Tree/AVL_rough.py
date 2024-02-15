

# getHeight(), getbalance(), leftRotate(), rightRotate(), successorNode()


class Node:
    def __init__(self, data, left=None, right=None, height=1):
        self.data = data
        self.left = left
        self.right = right
        self.height = height


class AVL_Tree:
    def getHeight(self, root):
        if not root:
            return 0
        else:
            return root.height

    def getBalance(self, root):
        if not root:
            return 0
        return self.getHeight(root.left) - self.getHeight(root.right)

    def successorNode(self, root):
        if root is None or root.left is None:
            return root
        return self.successorNode(root.left)

    # def levelOrderTraversal(self, root):
    #     if not root:
    #         return
    #     else:
    #         custQ = queue.Queue()
    #         custQ.enqueue(root)
    #         while not (custQ.isEmpty()):
    #             root = custQ.dequeue()
    #             print(root.value.data)
    #             if root.value.left is not None:
    #                 custQ.enqueue(root.value.left)
    #             if root.value.right is not None:
    #                 custQ.enqueue(root.value.right)

    def preOrder(self, root):
        if not root:
            return
        print(root.data)
        self.preOrder(root.left)
        self.preOrder(root.right)

    def leftRotate(self, UnbalancedNode):
        newRoot = UnbalancedNode.right
        UnbalancedNode.right = UnbalancedNode.right.left
        newRoot.left = UnbalancedNode
        UnbalancedNode.height = 1 + \
            max(self.getHeight(UnbalancedNode.left),
                self.getHeight(UnbalancedNode.right))
        newRoot.height = 1 + \
            max(self.getHeight(newRoot.left), self.getHeight(newRoot.right))
        return newRoot

    def rightRotate(self, UnbalancedNode):
        newRoot = UnbalancedNode.left
        UnbalancedNode.left = UnbalancedNode.left.right
        newRoot.right = UnbalancedNode

        UnbalancedNode.height = 1 + \
            max(self.getHeight(UnbalancedNode.left),
                self.getHeight(UnbalancedNode.right))
        newRoot.height = 1 + \
            max(self.getHeight(newRoot.left), self.getHeight(newRoot.right))
        return newRoot

    def searchNode(self, root, nodeValue):
        if not root:
            return
        if nodeValue == root.data:
            return "Value found."
        elif nodeValue < root.data:
            if nodeValue == root.left.data:
                print(" Value found.")
            else:
                return self.searchNode(root.left, nodeValue)
        else:
            if nodeValue == root.right.data:
                print("value found.")
            else:
                return self.searchNode(root.right, nodeValue)

    def insertNode(self, root, nodeValue):
        if not root:
            return Node(nodeValue)
        elif nodeValue < root.data:
            root.left = self.insertNode(root.left, nodeValue)
        else:
            root.right = self.insertNode(root.right, nodeValue)

        root.height = 1 + max(self.getHeight(root.left),
                              self.getHeight(root.right))
        balance = self.getBalance(root)

        # LL
        if balance > 1 and nodeValue < root.left:
            return self.rightRotate(root)

        # RR
        if balance < -1 and nodeValue > root.right:
            return self.leftRotate(root)

        # LR
        if balance > 1 and nodeValue > root.right:
            root.left = self.leftRotate(root.left)
            return self.rightRotate(root)

        # RL
        if balance < -1 and nodeValue < root.left:
            root.right = self.rightRotate(root.right)
            return self.leftRotate(root)

        return root

    def deleteNode(self, root, nodeValue):
        if not root:
            return
        elif nodeValue < root.data:
            self.deleteNode(root.left, nodeValue)
        elif nodeValue > root.data:
            self.deleteNode(root.right, nodeValue)

        # if the value to be deleted is rootNode
        else:
            # if rootNode has only right child
            if root.left is None:
                tempNode = root.right
                root = None
                return tempNode

            # if the rootnode has only left child
            elif root.right is None:
                tempNode = root.left
                root = None
                return tempNode

            # if the rootNode to be deleted has two child
            else:
                temp = self.successorNode(root.right)
                root.data = temp.data
                root.right = self.deleteNode(root.right, temp.data)

        # get the balance of the rootNOde
        balance = self.getBalance(root)

        # LL rotation
        if balance > 1 and self.getBalance(root.left) >= 0:
            self.leftRotate(root)

        # RR rotation
        if balance < -1 and self.getBalance(root.right) < 0:
            self.rightRotate(root.right)

        # LR rotation
        if balance > 1 and self.getBalance(root.right) < 0:
            root.left = self.leftRotate(root.left)
            return self.rightRotate(root)

        # RL rotation
        if balance < -1 and self.getBalance(root.left) >= 0:
            root.right = self.rightRotate(root.right)
            return self.leftRotate(root)

        return root


# if __name__ == "__main__":
#     mytree = AVL_Tree()
#     root = None
#     nums = [9, 5, 10, 5, 9, 7, 17]

#     for num in nums:
#         mytree.insertNode(root, num)

#     mytree.preOrder(root)
#     mytree.searchNode(root, 5)

mytree = AVL_Tree()
root = None
nums = [9, 5, 10, 5, 9, 7, 17]

for num in nums:
    mytree.insertNode(root, num)

mytree.preOrder(root)
mytree.searchNode(root, 5)
