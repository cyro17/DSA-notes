from Linked_List import Linked_List


def partition(ll, x):
    tempNode = ll.head
    ll.tail = ll.head

    while tempNode:
        nextNode = tempNode.next
        tempNode.next = None
        if tempNode.value < x:
            tempNode.next = ll.head
            ll.head = tempNode
        else:
            ll.tail.next = tempNode
            ll.tail = tempNode
        tempNode = nextNode

    if ll.tail is not None:
        ll.tail.next = None


cusll = Linked_List()
cusll.generate(10, 0, 99)
# cusll.partition(cusll, 10)
print(cusll)
partition(cusll, 50)
print(cusll)
