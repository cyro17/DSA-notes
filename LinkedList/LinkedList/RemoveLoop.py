

class Node:
    def __init__(self, val=0):
        self.next = None
        self.data = val


class Solution:
    # Function to remove a loop in the linked list.
    def removeLoop(self, head):
        # code here
        # remove the loop without losing any nodes

        slow = head
        fast = head

        while(slow != fast):
            slow = slow.next
            fast = fast.next

            if slow == fast:
                self.utility(slow)
                return 1
        return 0

    def utility(self, node):
        slow = node
        fast = node

        k = 1
        while(slow.next != fast):
            slow = slow.next
            k += 1

        fast = self.head
        slow = self.head
        for i in range(k):
            slow = slow.next

        while(slow != fast):
            slow = slow.next
            fast = fast.next

        while(slow.next != fast):
            slow = slow.next

        slow.next = None
