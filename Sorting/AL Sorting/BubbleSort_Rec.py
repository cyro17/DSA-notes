

def RecursiveBubbleSort(arr, n=None):
    if not n:
        n = len(arr)
    if n == 1:
        return

    for i in range(n-1):
        if arr[i+1] < arr[i]:
            arr[i], arr[i+1] = arr[i+1], arr[i]

    RecursiveBubbleSort(arr, n-1)


def main():
    array = [5, 2, 4, 8, 1, 9]
    RecursiveBubbleSort(array)


if __name__ == "__main__":
    main()
