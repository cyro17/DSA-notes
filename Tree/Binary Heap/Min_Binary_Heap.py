

def min_heapify(array, size, index):
    smallest = index
    left = 2*index + 1
    right = 2*index + 2

    if left < size and array[left] < array[smallest]:
        smallest = left

    if right < size and array[right] < array[smallest]:
        smallest = right

    if smallest != index:
        array[index], array[smallest] = array[smallest], array[index]
        min_heapify(array, size, smallest)


def insert(array, data):
    size = len(array)
    if size == 0:
        array.append(data)
    else:
        array.append(data)
        for i in range((size//2)-1, -1, -1):
            min_heapify(array, size, i)


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
