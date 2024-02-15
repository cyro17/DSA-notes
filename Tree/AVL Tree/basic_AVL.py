
# AVL Tree - construct an AVL Tree and show insertion and deletion methods.
# functions used - getHeight(), getbalance(), leftRotate(), rightRotate()


class TreeNode:
    def __init__(self, val, left=None, right=None, height=1):
        self.val = val
        self.left = left
        self.right = right
        self.height = height


class AVL_Tree:
    def insert(self, root, key):

        # step 1 - Perform normal BST
        if not root:
            return
        elif key < root.val:
            root.left = self.insert(root.left, key)
        else:
            root.right = self.insert(root.right, key)

        # step 2 - Update the height of the ancestor node
        root.height = 1 + max(self)

    def getHeight(self, root):
        if not root:
            return
        return root.height

    def getBalance(self, root):
        if not root:
            return 0
        return self.getHeight(root.left) - self.getHeight(root.right)

    def preOrder(self, root):
        if not root:
            return
        print(root.val, end="")
        self.preOrder(root.left)
        self.preOrder(root.right)

    def leftRotate(self, z):
        y = z.right
        T2 = y.left

        y.left = z
        z.right = T2

        # update height
        z.height = 1 + max(self.getHeight(z.left), self.getHeight(z.right))
        y.height = 1 + max(self.getHeight(y.left), self.getHeight(y.right))

        # return the new Root
        return y

    def rightRotate(self, z):
        y = z.left
        T2 = y.right

        y.right = z
        z.left = T2

        # update height
        z.height = 1 + max((self.getHeight(z.left), self.getHeight(z.right))
        y.height=1 + max((self.getHeight(y.left), self.getHeight(y.right))

        # return the new Root
        return y
