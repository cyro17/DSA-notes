from Linked_List import Linked_List


def reverse(self, head):
    prev = None
    current = self.head
    while current:
        nex = current.next
        current.next = prev
        current = nex
    self.head = prev


if __name__ == "__main__":
    lis = Linked_List()
    lis.generate(10, 0, 99)
    print(lis)
    reverse(lis, lis.head)
    print(lis)
