

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def removeNthFromEnd(self, head, n: int):

        dummy = ListNode(next=head)

        slow, fast = head, head
        for i in range(n):
            if not fast.next:
                if i == n-1:
                    head = head.next
                return head
            fast = fast.next

        while fast and fast.next:
            slow = slow.next
            fast = fast.next

        if slow.next:
            slow.next = slow.next.next

        return dummy.next
