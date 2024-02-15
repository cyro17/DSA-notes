

def RecInsertionSort(arr, n=None):
    if not n:
        n = len(arr)
    if n <= 1:
        return

    RecInsertionSort(arr, n-1)
    last = arr[n-1]
    j = n-2

    while j >= 0 and arr[j] > last:
        arr[j+1] = arr[j]
        j -= 1
    arr[j+1] = last


def main():
    array = [5, 2, 4, 8, 1, 9]
    RecInsertionSort(array)
    return " ".join([str(i) for i in array])


if __name__ == "__main__":
    print(main())
