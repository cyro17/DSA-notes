

def max_heapify(array, size, index):
    largest = index
    left = 2*index + 1
    right = 2*index + 2

    if left < size and array[left] > array[largest]:
        largest = left

    if right < size and array[right] > array[largest]:
        largest = right

    if largest != index:
        array[index], array[largest] = array[largest], array[index]
        max_heapify(array, size, largest)


def insert(array, data):
    size = len(array)
    if size == 0:
        array.append(data)
    else:
        array.append(data)
        for i in range((size//2)-1, -1, -1):
            max_heapify(array, size, i)


def leftIndex(array, index):
    return 2*index + 1


def rightIndex(array, index):
    return 2*index + 2


def parentIndex(array, index):
    return (index-1)//2


arr = []
insert(arr, 3)
insert(arr, 4)
insert(arr, 9)
insert(arr, 5)
insert(arr, 2)

print(str(arr))
