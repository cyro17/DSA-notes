from random import randint


class Node:
    def __init__(self, value):
        self.value = value
        self.next = None


class Solution:
    def __init__(self):
        self.head = None

    def __str__(self):
        values = [str(x.values) for x in self]
        return '-->'.join(values)

    def __iter__(self):
        tempnode = self.head
        while tempnode:
            yield tempnode
            tempnode = tempnode.next

    def middleNode_2_Pointer_method(self):
        slow = self.head
        fast = self.head
        while slow and fast.next:
            slow = slow.next
            fast = fast.next.next
        return f"the middle node is {slow}"

    def __len__(self):
        tempnode = self.head
        res = 0
        while tempnode:
            res += 1
            tempnode = tempnode.next
        return res

    def push(self, value):
        newNode = Node(value)
        if self.head is None:
            self.head = newNode
        else:
            newNode.next = self.head
            self.head = newNode
        return "The node has been added successfully."

    def printList(self):
        tempnode = self.head
        if self.head is None:
            print("there is no element in the list.")
        else:
            tempnode = self.head
            while tempnode:
                print(tempnode.value)
                tempnode = tempnode.next

    def middleNode(self):
        l = len(self)
        tempnode = self.head
        for i in range(0, l//2):
            tempnode = tempnode.next
        return f"The middle node is {tempnode.value}"


if __name__ == "__main__":
    ll = Solution()
    for i in range(0, 20):
        ll.push(i)
    Solution.printList(ll)
    print(ll.middleNode())
