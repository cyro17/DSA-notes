# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def isPalindrome(self, head) -> bool:
        stack = []
        slow, temp = head, head
        while slow:
            stack.append(slow.val)
            slow = slow.next

        isPalin = True

        while temp:
            i = stack.pop()
            if i == temp.val:
                isPalin = True
            else:
                isPalin = False
                break
            temp = temp.next

        return isPalin
