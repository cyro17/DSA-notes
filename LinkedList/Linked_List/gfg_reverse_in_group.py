#  Reverse a Linked List in groups of given size

#  Given a linked list of size N. The task is to reverse every k nodes (where k is an input to the function)
#  in the linked list. If the number of nodes is not a multiple of k then left-out nodes,
#  in the end, should be considered as a group and must be reversed

from Linked_List import Linked_List


class Solution:
    def reverse(self, head, k):
        if head is None:
            return
        current = head
        nextP = None
        prevP = None
        count = 0

        while (current is not None and count < k):
            nextP = current.next
            current.next = prevP
            prevP = current
            count += 1

        if nextP is not None:
            head.next = self.reverse(nextP, k)
        return prevP


if __name__ == "__main__":
    lis = Linked_List()
    for i in range(0, 10):
        lis.add(i)

    print(lis)
    lis.reverse()
    print(lis)
