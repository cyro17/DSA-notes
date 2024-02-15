class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def getIntersectionNode(self, headA, headB):

        diff = self.get_length(headA) - self.get_length(headB)

        if diff > 0:
            longerL = headA
            shorterL = headB
        else:
            longerL = headB
            shorterL = headA

        for i in range(abs(diff)):
            longerL = longerL.next

        while shorterL is not longerL:
            shorterL = shorterL.next
            longerL = longerL.next
        return longerL

    def get_length(self, head):
        l = 0
        temp = head
        while temp and temp.next:
            l += 1
            temp = temp.next
        return l
