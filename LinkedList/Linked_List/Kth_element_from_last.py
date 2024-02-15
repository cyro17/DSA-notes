from Linked_List import Linked_List

# using two pointer method


def nthTOLast(ll, n):
    pointer1 = ll.head
    pointer2 = ll.head

    for i in range(n):
        if pointer2 is None:
            return None
        pointer2 = pointer2.next
    while pointer2:
        pointer1 = pointer1.next
        pointer2 = pointer2.next
    return pointer1


cusll = Linked_List()
cusll.generate(10, 0, 99)
print(cusll)
print(f"Length : {len(cusll)}")
print(nthTOLast(cusll, 2))
