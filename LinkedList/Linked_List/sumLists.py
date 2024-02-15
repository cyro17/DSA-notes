from Linked_List import Linked_List


def sumList(llA, llB):  # T.C = O(n),   S.C = O
    n1 = llA.head
    n2 = llB.head
    carry = 0
    ll = Linked_List()

    while n1 or n2:
        result = carry
        if n1:
            result += n1.value
            n1 = n1.next
        if n2:
            result += n2.value
            n2 = n2.next
        ll.add(int(result % 10))
        carry = result/10

    return ll


llA = Linked_List()
llB = Linked_List()

llA.add(7)
llA.add(1)
llA.add(6)

llB.add(5)
llB.add(9)
llB.add(2)

print(llA)
print(llB)
print(sumList(llA, llB))

# print(llA)
