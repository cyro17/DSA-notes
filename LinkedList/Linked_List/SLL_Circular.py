class Node:
    def __init__(self, value=None):
        self.value = value
        self.next = None


class CircularSLL:
    def __init__(self):
        self.head = None
        self.tail = None

    def __iter__(self):
        node = self.head
        while node:
            yield node
            if node.next == self.head:
                break
            node = node.next

    def createCSLL(self, nodevalue):
        node = Node(nodevalue)
        node.next = node
        self.head = node
        self.tail = node
        return "the CSLL has been created."

    def insertCSLL(self, location, Value):
        if self.head is None:
            return "The head reference is None."
        else:
            newNode = Node(Value)
            if location == 0:
                newNode.next = self.head
                self.head = newNode
                self.tail.next = newNode
            elif location == -1:
                newNode.next = self.tail.next
                self.tail.next = newNode
                self.tail = newNode
            else:
                tempNode = self.head
                index = 0
                while index < location - 1:
                    tempNode = tempNode.next
                    index += 1
                nextNode = tempNode.next
                tempNode.next = nextNode
            return f"The node has been successfully inserted."

    def Traversal_CSLL(self):
        if self.head is None:
            print("there si no element to traverse in CSLL")
        else:
            tempNode = self.head
            while tempNode:
                print(tempNode.value)
                tempNode = tempNode.next
                if tempNode == self.tail.next:
                    break

    def deleteNode(self, location):
        if self.head is None:
            print("there is no node in CSLL")

        else:
            if location == 0:
                if self.head == self.tail:
                    self.head = None
                    self.tail = None
                    self.head.next = None
                else:
                    self.head = self.head.next
                    self.tail.next = self.head

            elif location == -1:
                if self.head == self.tail:
                    self.head = None
                    self.tail = None
                    self.head.next = None

                else:
                    tempNode = self.head
                    while tempNode is not None:
                        if tempNode.next == self.tail:
                            break
                        tempNode = tempNode.next
                    tempNode.next = self.head
                    self.tail = tempNode

            else:
                tempNode = self.head
                index = 0
                while index < location - 1:
                    tempNode = tempNode.next
                    index += 1
                nextNode = tempNode.next
                tempNode.next = nextNode.next

    def deleteEntireCSLL(self):
        self.head = None
        self.tail.next = None
        self.tail = None


clist = CircularSLL()
# clist.createCSLL(1)
# clist.createCSLL(2)
# clist.createCSLL(3)
clist.insertCSLL(0, 0)
clist.insertCSLL(-1, 1)
clist.insertCSLL(1, 2)
clist.insertCSLL(2, 3)
print([i.Value for i in clist])
