

class BinaryTree:       # T.C = O(1), S.C = O(N)
    def __init__(self, size):
        self.customList = size * [None]
        self.lastusedIndex = 0
        self.maxSizeList = size

    def insertNode(self, value):    # T.C = o(1), S.C = O(1)
        if self.lastusedIndex + 1 == self.maxSizeList:
            return "the binary tree is full."
            self.customList[self.lastusedIndex + 1] = value
            self.lastusedIndex += 1
            return "Node insertion completed."

    def searchBT(self, value):      # T.C = O(N)     S.C = O(1)
        for i in range(len(self.customList)):
            if self.customList[i] == value:
                return "success ! Value fround in the Binary tree"
        return "Not found."

    # Left, Root, Right
    def InOrderTraverse(self, index):  # L, root, R
        if index > self.lastusedIndex:
            return "we have visited all the nodes"
        self.InOrderTraverse(self, index * 2)
        print(self.customList[index])
        self.InOrderTraverse(self, index*2 + 1)

    # all the traversal has the same time and space complexities.
    # Root, Left, Right
    def preOrderTraverse(self, index):      # T.c = O(N), s.c = O(N)
        # it means we have visited all the nodes, we should stop here .
        if index > self.lastusedIndex:
            return "We have visited all the nodes."
        print(self.customList[index])
        self.preOrderTraverse(index*2)
        self.preOrderTraverse(index*2 + 1)

    # post order LEFT, RIGHT, ROOT
    def postOrderTraverse(self, index):
        if index > self.lastusedIndex:
            return "all the nodes have been visited already."
        self.postOrderTraverse(index*2)
        self.postOrderTraverse(index*2 + 1)
        print(self.customList[index])

    def levelOrderTraverse(self, index):
        for i in range(index, self.lastusedIndex+1):
            print(self.customList[i])
        return

    def deletNode(self, value):  # T.C = O(N)    S.C = O(1)
        if self.lastusedIndex == 0:
            return "there is not any node in the tree."

        for i in range(1, self.lastusedIndex+1):  # -----------> T.C = O(N)
            if self.customList[i] == value:
                # replace the node value as the deepest node value
                self.customList[i] = self.customList[self.lastusedIndex]
                self.customList[self.lastusedIndex] = None
                self.lastusedIndex -= 1
                return "the node has been successfully deleted."

    def deleteBT(self):  # T.C = O(1)  S.C = O(1)
        self.customList = None
        return "the binary tree has been successfully deleted."


if __name__ == "__main__":
    newBT = BinaryTree(8)
    newBT.insertNode("Drinks")
    newBT.insertNode("Hot")
    newBT.insertNode("Cold")
    newBT.insertNode("Tea")
    newBT.insertNode("coffee")
    newBT.insertNode("coco cola ")
    newBT.insertNode("pepsi")

    print(newBT.levelOrderTraverse(1))
    newBT.deletNode("Tea")
    newBT.deleteBT()
