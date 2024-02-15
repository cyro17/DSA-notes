# Definition for singly-linked list.


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def deleteDuplicates(self, head):
        curr = head

        while curr:
            runner = curr

            while runner.next:
                if runner.next.val == curr.val:
                    runner.next = runner.next.next
                else:
                    runner = runner.next
            curr = curr.next
        return head
