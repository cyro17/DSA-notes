# Doubly Linked LIst

class Node:
    def __init__(self, value=None):
        self.value = value
        self.next = None
        self.prev = None


class DLL:
    def __init__(self):
        self.head = None
        self.tail = None

    def __iter__(self):
        node = self.head
        while node:
            yield node
            node = node.next

    def create_DLL(self, nodeValue):
        node = Node(nodeValue)
        node.prev = None
        node.next = None
        self.head = node
        self.tail = node
        return "the DLL has been created"

    def insertNode(self, nodeValue, location):
        if self.head is None:
            print("the node can't be inserted.")
        else:
            newNode = Node(nodeValue)
            if location == 0:
                newNode.prev = None
                newNode.next = self.head
                self.head.prev = newNode
                self.head = newNode

            if location == -1:
                newNode.next = None
                newNode.prev = self.tail
                self.tail.next = newNode
                self.tail = newNode

            else:
                tempNode = self.head
                index = 0
                while index < location - 1:
                    tempNode = tempNode.next
                    index += 1
                newNode.next = tempNode.next
                newNode.prev = tempNode
                newNode.next.prev = newNode
                tempNode.next = newNode

    def Traverse_DLL(self):
        if self.head is None:
            print("there is no element to traverse in DLL")
        else:
            tempNode = self.head
            while tempNode:
                tempNode = self.head
                tempNode = tempNode.next

    def reverse_TraversalDLL(self):
        if self.head is None:
            print("there is no element to traverse in DLL")
        else:
            tempNode = self.tail
            while tempNode:
                print(tempNode.value)
                tempNode = tempNode.prev

    def deleteNode(self, location):
        if self.head is None:
            print("the list has no element .")
        else:
            if location == 0:
                if self.head == self.tail:
                    self.head = None
                    self.tail = None
                else:
                    self.head = self.head.next
                    self.head.prev = None
            elif location == -1:
                if self.head == self.tail:
                    self.head = None
                    self.tail = None
                else:
                    self.tail = self.tail.prev
                    self.tail.next = None

            else:
                curNode = self.head
                index = 0
                while index < location - 1:
                    curNode = curNode.next
                    index += 1

                curNode = curNode.next.next
                curNode.next.prev = curNode

            print("the node has been successfully deleted.")

    def deleteDLL(self):
        if self.head is None:
            print("the lsit is empty")
        else:
            tempNode = self.head
            while tempNode:
                tempNode.prev = None
                tempNode = tempNode.next
            self.head = None
            self.tail = None
            print("the DLL has been deleted successfully.")


dll = DLL()
dll.create_DLL(5)
dll.insertNode(0, 0)
dll.insertNode(2, 1)
dll.insertNode(4, 2)
dll.insertNode(5, 3)


print([i.value for i in dll])
