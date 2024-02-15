# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def rotateRight(self, head, k):

        if not head:
            return None

        tail, length, curr = head, 1, head

        while tail.next:
            tail = tail.next
            length += 1

        k = k % length
        for i in range(length-k-1):
            curr = curr.next
        tail.next = head
        res = curr.next
        curr.next = None

        return res
