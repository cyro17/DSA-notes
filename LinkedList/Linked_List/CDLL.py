
class Node:
    def __init__(self, value=None):
        self.value = value
        self.next = None
        self.prev = None


class CDLL:
    def __init__(self):
        self.head = None
        self.tail = None

    def __iter__(self):
        node = self.head
        while node:
            yield node
            node = node.next
            if node == self.tail.next:
                break

    def create_CDLL(self, nodeValue):
        newNode = Node(nodeValue)
        self.head = newNode
        self.tail = newNode
        newNode.prev = newNode
        newNode.head = newNode
        return "The CDLL has been created successfully."

    def insert_CDLL(self, value, location):
        if self.head is None:
            return "the CDLL does not exist."
        else:
            newNode = Node(value)
            if location == 0:
                newNode.next = self.head
                newNode.prev = self.tail
                self.head.prev = newNode
                self.head = newNode
                self.tail.next = newNode
            elif location == -1:
                newNode.next = self.head
                newNode.prev = self.tail
                self.head.prev = newNode
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
            return "The node insertion is completed succcefully."

    def traverse_CDLL(self):
        if self.head is None:
            print("there is no element in CDLL")
        else:
            tempNode = self.head
            while tempNode:
                print(tempNode.value)
                if tempNode == self.tail:
                    break
                tempNode = tempNode.next

    def rev_traverse_CDLL(self):
        if self.head is None:
            print("there is no element in CDLL")
        else:
            tempNode = self.tail
            while tempNode:
                print(tempNode.value)
                if tempNode == self.head:
                    break
                tempNode = tempNode.prev

    def searchCDLL(self, nodevalue):
        if self.head is None:
            print('there is no element in CDLL')
        else:
            tempNode = self.head
            while tempNode:
                if tempNode.value == nodevalue:
                    return tempNode.value
                if tempNode.value == self.tail:
                    return "the value dne in the CDLL"
                tempNode = tempNode.next

    def delete_CDLL(self, location):
        if self.head is None:
            print('there is no element in CDLL')
        else:
            if location == 0:
                if self.head == self.tail:
                    self.head.next = None
                    self.head.prev = None
                    self.head = None
                    self.tail = None
                else:
                    self.head = self.head.next
                    self.head.prev = self.tail
                    self.tail.next = self.head
            elif location == -1:
                if self.head == self.tail:
                    self.head.next = None
                    self.head.prev = None
                    self.head = None
                    self.tail = None
                else:
                    self.tail = self.tail.prev
                    self.tail.next = self.head
                    self.head.prev = self.tail

            else:
                curNode = self.head
                index = 0
                while index < location - 1:
                    curNode = curNode.next
                    index += 1

                curNode.next = curNode.next.next
                curNode.next.prev = curNode

            print("the node deletion is succesfull.")

    def deleteEntireCDLL(self):
        if self.head is None:
            print("there is no element in CDLL.")
        else:
            self.tail.next = None
            tempNode = self.head
            while tempNode:
                tempNode.prev = None
                tempNode = tempNode.next
            self.head = None
            self.tail = None
        print("the CDLL has been deleetd succesfully.")


cdll = CDLL()
cdll.create_CDLL(5)

print([node.value for node in cdll])
