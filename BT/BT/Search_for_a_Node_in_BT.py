class Node:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right


class Node_in_BT:
    def __init__(self, root=None, flag=False):
        self.root = root
        self.flag = flag

    def searchNode(self, temp, value):
        if (self.root == None):
            print("Tree is empty.")
            return
        else:
            if (temp.data == value):
                self.flag = True
                return

            # if the flag is false and the temp node has left child
            if (self.flag == False and temp.left != None):
                # using recursion go throught the left node of the temp node
                self.searchNode(temp.left, value)

            # if the flag is false and the temp node has right child
            if (self.flag == False and temp.left != None):
                # using recursion go throught the right node of the temp node
                self.searchNode(temp.left, value)
