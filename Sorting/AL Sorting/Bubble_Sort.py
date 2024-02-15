

def BubbleSort(arr):
    global n
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
                swapped = True

        if swapped == False:
            break
    return arr


def print_array(arr):
    global n
    for i in range(n):
        print(arr[i], end=" ")


if __name__ == "__main__":
    arr = [1, 5, 2, 3, 4, 8]
    BubbleSort(arr)
    print_array(arr)
