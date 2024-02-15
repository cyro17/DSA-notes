# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def deleteMiddle(self, head):
        dummy = ListNode(next=head)
        slow, fast = head, head
        prev = dummy

        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            prev = prev.next

        prev.next = slow.next

        return dummy.next
