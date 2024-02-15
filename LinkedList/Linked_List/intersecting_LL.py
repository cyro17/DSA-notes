from Linked_List import Linked_List, Node

# T.C = O(lenA + lenB), S.C = O(1)


def intersection(llA, llB):
    if llA.tail is not llB.tail:
        return False

    lenA = len(llA)
    lenB = len(llB)

    shorterList = llA if lenA < lenB else llB
    longerList = llA if lenB < lenA else llB

    diff = len(longerList) - len(shorterList)
    longerNode = longerList.head
    shorterNode = shorterList.head

    for i in range(0, diff):
        longerNode = longerNode.next

    while shorterNode is not longerNode:
        shorterNode = shorterNode.next
        longerNode = longerNode.next

    return longerNode


def addsameNode(llA, llB, value):
    tempNode = Node(value)
    llA.tail.next = tempNode
    llA.tail = tempNode

    llB.tail.next = tempNode
    llB.tail = tempNode


if __name__ == "__main__":
    llA = Linked_List()
    llA.generate(3, 0, 10)

    llB = Linked_List()
    llB.generate(4, 0, 10)
    addsameNode(llA, llB, 7)
    addsameNode(llA, llB, 14)
    print(llA)
    print(llB)
    print(intersection(llA, llB))
