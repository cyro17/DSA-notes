#  Write a function detectAndCountLoop() that checks whether a given Linked List contains loop
#  and if loop is present then returns count of nodes in loop.


import Linked_List


def rotateLL(self, head, k):

    if head is None:
        return "there exist no element in the list."
    if k > len(self):
        return "value exceeded than length of the list."

    temp = None
    if head is not None:
        temp = head
        while temp:
            temp = temp.next
        temp.next = head

    return self
    # for i in range(0, k):


# ll = Linked_List()
# for i in range(0, 10):
#     ll.add(i)
# print(ll)
ll = Linked_List()
for i in range(0, 10):
    ll.add(i)
print(ll)
rotateLL(ll, ll.head, 4)
print(ll)

# if __name__ == "__main__":
#     ll = Linked_List()
#     for i in range(0, 10):
#         ll.add(i)
#     print(ll)
#     rotateLL(0, 4)
