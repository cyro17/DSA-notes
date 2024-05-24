

# # Queue LinkedList implementation UDEMY

# # class Node:
# #     def __init__(self, value):
# #         self.val = value
# #         self.next = next


# # class Linkedlist:
# #     def __init__(self, head=None, tail=None):
# #         self.head = head
# #         self.tail = tail


# # class Queue:
# #     def __init__(self) -> None:
# #         self.linkedlist = Linkedlist()

# #         def __str__(self):
# #             values = [str(x) for x in self.linkedList]
# #             return ' '.join(values)

# #     def enqueue(self, value):
# #         # create a newNode
# #         newNode = Node(value)
# #         # if there is no head node in the linkedlist then set the new node as head as well as tail node
# #         if self.linkedlist.head == None:
# #             self.head = self.tail = newNode
# #         # else set the next of tail node as newnode and after this set the new node as tail node
# #         else:
# #             self.tail.next = newNode
# #             self.tail = newNode

# #     def isEmpty(self) -> bool:
# #         if self.linkedlist.head == None:
# #             return True

# #         else:
# #             return False

# #     def dequeue(self):
# #         # check if the queue is empty
# #         if self.isEmpty():
# #             return "there is no node in the queue."

# #         # if not empty then save the head node as temp
# #         else:
# #             temp = self.linkedlist.head
# #             # if head node is equal to the tail node then set the head and tail node as NULL
# #             if self.linkedlist.head == self.linkedlist.tail:
# #                 self.linkedlist.head = self.linkedlist.tail = None
# #             # if head node is not equal to the tail node then delete the head node and set the next of head node as head node
# #             else:
# #                 self.linkedlist.head = self.linkedlist.head.next

# #             return temp

# #         # return the head node of the queue
# #     def peek(self):
# #         # if the queue is empty then return the message that there is no any node in the queue
# #         if self.isEmpty():
# #             return "Empty! there is no node in the queue."
# #         else:
# #             return self.linkedlist.head

# #         # to delete the queue set the head and tail of the linked list as null
# #     def delete(self):
# #         self.linkedlist.haed = None
# #         self.linkedlist.tail = None


# # if __name__ == "__main__":
# #     q = Queue()
# #     q.enqueue(1)
# #     q.enqueue(2)
# #     q.enqueue(3)
# #     q.enqueue(4)
# #     q.enqueue(5)

# #     print(q)


# # --------------------------------------------------------------------------------------------------------------------------------------------

# # Queue implementations GFG

# # LinkedLIst node to store the queue entry
# class Node:
#     def __init__(self, data):
#         self.data = data
#         self.next = None

#     def __str__(self) -> str:
#         return str(self.value)


# class Queue:
#     def __init__(self, front=None, rear=None):
#         self.rear = front
#         self.front = rear

#     def isEmpty(self):
#         if self.front == None:
#             return True
#         return False


#     def EnQueue(self, value):
#         newNode = Node(value)
#         # if rear node is empty then set the newNOde as front as well as rear node
#         if self.rear is None:
#             self.front = self.rear = None
#         else:
#             self.rear.next = newNode
#             self.rear = newNode

#     def DeQueue(self):
#         # if the queue is empty then print the message saying that the queue is empty
#         if self.isEmpty():
#             return "Empty ! there is no node in the queue"

#         temp = self.front               # save the front node in the temp node
#         self.front = temp.next

#         if self.front == None:
#             self.rear == None


# # if __name__ == '__main__':
# #     q = Queue()
# #     q.EnQueue(10)
# #     q.EnQueue(20)
# #     q.DeQueue()
# #     q.DeQueue()
# #     q.EnQueue(30)
# #     q.EnQueue(40)
# #     q.EnQueue(50)
# #     q.DeQueue()
# #     print("Queue Front " + str(q.front.data))
# #     print("Queue Rear " + str(q.rear.data))

import sys

print(-sys.maxsize)
