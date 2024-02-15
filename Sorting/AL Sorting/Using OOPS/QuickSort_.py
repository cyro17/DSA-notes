

def quickSort(array, start, end):
    pivot_ind = start
    pivot = array[pivot_ind]

    while start < end:
        while start < len(array) and array[start] <= pivot:
            start += 1

        while array[end] > pivot:
            end -= 1

        if (start < end):
            array[start], array[end] = array[end], array[start]

    array[end], array[pivot_ind] = array[pivot_ind], array[end]
    return end


def partition(array, start, end):
    if start < end:
        p = partition(array, start, end)
        quickSort(array, start, p-1)
        quickSort(array, p+1, end)
