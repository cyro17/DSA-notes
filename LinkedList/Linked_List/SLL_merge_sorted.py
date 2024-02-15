from SLL_Singly import Node, LinkedList


def mergeList(firstList, secondList, mergeList):
    currentFirst = firstList.head
    currentSecond = secondList.head

    while True:
        if currentFirst is None:
            mergeList.insertEnd(currentSecond)
            break
        if currentSecond is None:
            mergeList.insertEnd(currentFirst)
            break

        if currentFirst.data < currentSecond.data:

            currentFirstNext = currentFirst.next
            currentFirst.next = None
            mergeList.insertEnd(currentFirst)
            currentFirst = currentFirstNext

        else:
            currentSecondNext = currentSecond.next
            currentSecond.next = None
            mergeList.insertEnd(currentSecond)
            currentSecond = currentSecondNext
