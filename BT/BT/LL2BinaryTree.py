# Python program to create a Complete Binary Tree fromits linked list representation

# Linked List node


class ListNode:

    # Constructor to create a new node
    def __init__(self, data):
        self.data = data
        self.next = None

# Binary Tree Node structure


class BinaryTreeNode:

    # Constructor to create a new node
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

# Class to convert the linked list to Binary Tree


class Conversion:

    # Constructor for storing head of linked list
    # and root for the Binary Tree
    def __init__(self, data=None):
        self.head = None
        self.root = None
        self.flag = False

    def push(self, new_data):

        # Creating a new linked list node and storing data
        new_node = ListNode(new_data)

        # Make next of new node as head
        new_node.next = self.head

        # Move the head to point to new node
        self.head = new_node

    def convertList2Binary(self):

        # Queue to store the parent nodes
        q = []

        # Base Case
        if self.head is None:
            self.root = None
            return

        # 1.) The first node is always the root node,
        # and add it to the queue
        self.root = BinaryTreeNode(self.head.data)
        q.append(self.root)

        # Advance the pointer to the next node
        self.head = self.head.next

        # Until th end of linked list is reached, do:
        while(self.head):

            # 2.a) Take the parent node from the q and
            # and remove it from q
            parent = q.pop(0)  # Front of queue

            # 2.c) Take next two nodes from the linked list.
            # We will add them as children of the current
            # parent node in step 2.b.
            # Push them into the queue so that they will be
            # parent to the future node
            leftChild = None
            rightChild = None

            leftChild = BinaryTreeNode(self.head.data)
            q.append(leftChild)
            self.head = self.head.next
            if(self.head):
                rightChild = BinaryTreeNode(self.head.data)
                q.append(rightChild)
                self.head = self.head.next

            # 2.b) Assign the left and right children of parent
            parent.left = leftChild
            parent.right = rightChild

    def searchNode(self, node, value):
        if (self.root == None):
            return "the Tree is empty."
        else:
            if (node.data == value):
                self.flag = True
                return

            if (self.flag == False and node.left != None):
                self.searchNode(node.left, value)

            if (self.flag == False and node.right != None):
                self.searchNode(node.right, value)

    def inorderTraversal(self, root):
        if(root):
            self.inorderTraversal(root.left)
            print(root.data)
            self.inorderTraversal(root.right)


if __name__ == "__main__":
    # Driver Program to test above function

    # Object of conversion class
    conv = Conversion()
    conv.push(36)
    conv.push(30)
    conv.push(25)
    conv.push(15)
    conv.push(12)
    conv.push(10)
    print(conv.head.data)
    conv.convertList2Binary()

    conv.searchNode(conv.root, 15)
    if conv.flag:
        print(f"the node is present in the binary tree")
    else:
        print("there is no node in the binary tree.")

    print("Inorder Traversal of the contructed Binary Tree is:")
    conv.inorderTraversal(conv.root)

    # This code is contributed by Nikhil Kumar Singh(nickzuck_007)
