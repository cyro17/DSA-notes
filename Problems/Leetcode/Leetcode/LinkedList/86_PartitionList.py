# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def partition(self, head, x):

        dummy1 = ListNode()
        dummy2 = ListNode()
        small = dummy1
        big = dummy2

        curr = head
        while curr:
            if curr.val < x:
                small.next = ListNode(curr.val)
                small = small.next
            else:
                big.next = ListNode(curr.val)
                big = big.next

            curr = curr.next

        big.next = None
        small.next = dummy2.next

        return dummy1.next
