# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def swapPairs(self, head):

        dummy = ListNode(next=head)
        curr = dummy

        while curr.next and curr.next.next:
            first = curr.next
            second = curr.next.next

            first.next = second.next
            curr.next = second
            curr.next.next = first

            curr = curr.next.next
        return dummy.next
