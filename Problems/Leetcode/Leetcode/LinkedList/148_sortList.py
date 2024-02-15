# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

# ---using Recursion---

# class Solution:
#     def sortList(self, head):
#         dummy = ListNode(0)
#         curr = head
#         temp = []

#         while curr:
#             temp.append(curr.val)
#             curr = curr.next

#         temp = sorted(temp)
#         cur = dummy
#         for i in temp:
#             cur.next = ListNode(i)
#             cur = cur.next

#         return dummy.next


# ---using Merge Sort---

class Solution:
    def sortList(self,  head):
        if not head or not head.next:
            return head

        left = head
        right = self.getMid(head)
        temp = right.next
        right.next = None
        right = temp

        left = self.sortList(left)
        right = self.sortList(right)
        return self.merge(left, right)


    def getMid(self, node):
        slow = fast = node
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        return slow

    def merge(self, left, right):
        tail = dummy = ListNode()
        while left and right:
            if left.val < right.val:
                tail.next = left
                left = left.next
            else:
                tail.next = right
                right = right.next

            tail = tail.next
        if left:
            tail.next = left
        if right:
            tail.next = right

        return dummy.next

