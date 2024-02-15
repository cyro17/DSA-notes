# check whether LL has cycle or not

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def hasCycle(self, head) -> bool:
        slow, fast = head, head

        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next

            if slow == fast:
                return True
        return False


# M-2

class Solution:
    def hasCycle(self, head) -> bool:

        seen = set()
        temp = head

        while temp:
            if temp in seen:
                return True
            seen.add(temp)
            temp = temp.next
        return False
