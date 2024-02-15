from collections import Counter
# Definition for singly-linked list.


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def deleteDuplicates(self, head):

        curr = head
        temp = []

        while curr:
            temp.append(curr.val)
            curr = curr.next

        c = Counter(temp)
        temp = [k for k, v in c.items() if v == 1]

        dummy = curr = ListNode()

        for i in temp:
            curr.next = ListNode(i)
            curr = curr.next
        return dummy.next


class Solution:
    def deleteDuplicates(self, head):
        dummy = ListNode(next=head)
        curr = head
        slow = dummy

        while curr:
            if curr.next and curr.val == curr.next.val:
                while curr.next and curr.val == curr.next.val:
                    curr = curr.next
                slow.next = curr.next
            else:
                slow = slow.next
            curr = curr.next
        return dummy.next
