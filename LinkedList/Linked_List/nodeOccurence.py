from random import randint


class Node:
    def __init__(self, value):
        self.value = value
        self.next = None


class Solution:
    def __init__(self):
        self.head = None

    def __iter__(self):
        tempnode = self.head
        while tempnode:
            yield tempnode
            tempnode = tempnode.next

    def __str__(self):
        values = [str(x.value) for x in self]
        return "-->".join(values)

    def __len__(self):
        result = 0
        tempnode = self.head
        while tempnode:
            result += 1
            tempnode = tempnode.next
        return result

    def traverse(self):
        if self.head is None:
            return "there is no element in the list."
        else:
            temp = self.head
            while temp:
                print(temp.value)
                temp = temp.next
        return "The list has been traversed."

    def push(self, value):
        newnode = Node(value)
        if self.head is None:
            self.head = newnode
        else:
            newnode.next = self.head
            self.head = newnode

    def generate(self, n, min_value, max_value):
        self.head = None
        for i in range(n):
            self.push(randint(min_value, max_value))

    def occurrence(self, n):
        if self.head is None:
            return "there is no elements in the list."
        else:
            count = 0
            temp = self.head
            while temp:
                if temp.value == n:
                    count += 1
                    temp = temp.next

        return count

    def printList(self):
        tempnode = self.head
        while tempnode:
            print(tempnode.value)
            tempnode = tempnode.next


if __name__ == "__main__":

    ll = Solution()
    ll.generate(10, 0, 99)
    print(ll)
    n = input("enter node u wnna search")
    print(ll.occurrence(n))

    # print(ll.traverse())
