from Linked_List import Linked_List


def removeDups(ll):
    if ll.head is None:
        return
    else:
        curnode = ll.head
        visited = list([curnode.value])
        while curnode.next:
            if curnode.next.value in visited:
                curnode.next = curnode.next.next
            else:
                visited.append(curnode.next.value)
                curnode = curnode.next
        return ll


def removeDups1(ll):    # T.C = O(n^2), S.C = O(1)
    if ll.head is None:
        return
    curnode = ll.head
    while curnode:
        runner = curnode
        while runner.next:
            if runner.next.value == curnode.value:
                runner.next = runner.next.next
            else:
                runner = runner.next
        curnode = curnode.next
    return ll.head


cusll = Linked_List()
cusll.generate(10, 0, 99)
print(cusll)
print(f"the length of list is {len(cusll)}")
removeDups1(cusll)
print(cusll)
print(f"the length of list is {len(cusll)}")
