
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = None

    def isListEmpty(self):
        if self.head is None:
            return True

        else:
            return False

    def ListLength(self):
        currentNode = self.head
        length = 0

        while currentNode is not None:
            length += 1
            currentNode = currentNode.next
        return length

    def insertHead(self, newNode):
        tempNode = self.head
        self.head = newNode
        self.head.next = tempNode
        del tempNode

    def insertAt(self, newNode, pos):

        if pos < 0 or pos > self.ListLength():
            print("invalid lentgh")
            return

        if pos == 0:
            self.insertHead(newNode)
            return
        currentNode = self.head
        currentpos = 0
        while True:
            if currentpos == pos:
                previousNode.next = newNode
                newNode.next = currentNode
                break
            previousNode = currentNode
            currentNode = currentNode.next
            currentpos += 1

    def insertEnd(self, newNode):
        if self.head is None:
            self.head = newNode

        else:
            lastNode = self.head  # say lastnode is the first header node
            while True:
                if lastNode.next is None:  # if there is no next pointer in the lastnode then break
                    break
                lastNode = lastNode.next

            lastNode = newNode

    def deleteAt(self, pos):
        if pos < 0 or pos >= self.ListLength():
            print("invalid position")
            return

        if self.isListEmpty() is False:
            if pos is 0:
                self.deleteHead()

        currentNode = self.head
        currentpos = 0
        while True:
            if currentpos == pos:
                previousNode.next = currentNode.next
                currentNode.next = None
                break
            previousNode = currentNode
            currentNode = currentNode.next
            currentpos += 1

    def deleteEnd(self):
        lastnode = self.head
        while lastnode.next is not None:
            previousnode = lastnode
            lastnode = lastnode.next
        previousnode.next = None

    def printList(self):
        if self.head is None:
            print('list is empty')
            return

        currentNode = self.head
        while True:
            if currentNode is None:
                break
            print(currentNode.data)
            currentNode = currentNode.next


fNode = Node(10)
linklist = LinkedList()
linklist.insertEnd(fNode)

secnode = Node(20)
linklist.insertEnd(secnode)

third = Node(15)
linklist.insertAt(third, 1)
print(linklist.printList())
