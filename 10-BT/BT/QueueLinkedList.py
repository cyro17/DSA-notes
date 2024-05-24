
class Node:
    def __init__(self, value=None):
        self.value = value
        self.next = None

    def __str__(self) -> str:
        return str(self.value)


class LinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def __iter__(self):
        temp = self.head
        while temp:
            yield temp
            temp = temp.next


class Queue:

    def __init__(self):
        self.linkedlist = LinkedList()

    def isEmpty(self):
        return self.linkedlist.head == None

    def enqueue(self, value):
        newNode = Node(value)
        if self.linkedlist.head == None:
            self.linkedlist.head = newNode
            self.linkedlist.tail = newNode
            return
        self.linkedlist.tail.next = newNode
        self.linkedlist.tail = newNode

    def dequeue(self):
        if self.isEmpty():
            return "the queue is empty."
        else:
            temp = self.linkedlist.head
            if self.linkedlist.head == self.linkedlist.tail:
                self.linkedlist.head = self.linkedlist.tail = None
            else:
                self.linkedlist.head = self.linkedlist.head.next
            return temp

    def peek(self):
        return self.head.value

    def delete(self):
        self.head = self.tail = None
        return "the queue has been deleted successfully."


if __name__ == "__main__":
    q = Queue()
    q.enqueue(10)
    q.enqueue(20)
    q.dequeue()
    q.dequeue()
    q.enqueue(30)
    q.enqueue(40)
    q.enqueue(50)
    q.dequeue()
    print(q)
    print("Queue Head " + str(q.linkedlist.head.value))
    print("Queue Tail " + str(q.linkedlist.tail.value))
