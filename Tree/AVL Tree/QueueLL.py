# Python3 program to demonstrate linked list
# based implementation of queue

# A linked list (LL) node
# to store a queue entry
class Node:

    def __init__(self, value=None):
        self.value = value
        self.next = None

    def __str__(self) -> str:
        return str(self.value)

# A class to represent a queue

# The queue, head stores the head node
# of LL and tail stores the last node of LL


class Queue:

    def __init__(self):
        self.head = self.tail = None

    def isEmpty(self):
        return self.head == None

    # Method to add an item to the queue
    def EnQueue(self, item):
        newNode = Node(item)

        if self.tail == None:
            self.head = self.tail = newNode
            return

        self.tail.next = newNode
        self.tail = newNode

    # Method to remove an item from queue
    def DeQueue(self):

        if self.isEmpty():
            return "The Queue is empty."
        temp = self.head
        self.head = temp.next

        if(self.head == None):
            self.tail = None

    def peek(self):
        if self.isEmpty():
            return "there is no element in the queue."
        else:
            return self.head.value


# Driver Code
if __name__ == '__main__':
    q = Queue()
    q.EnQueue(10)
    q.EnQueue(20)
    q.DeQueue()
    q.DeQueue()
    q.EnQueue(30)
    q.EnQueue(40)
    q.EnQueue(50)
    q.DeQueue()
    print(q)
    print(q.peek())
    print("Queue Front " + str(q.head.value))
    print("Queue Rear " + str(q.tail.value))
