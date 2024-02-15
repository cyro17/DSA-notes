

def selection_sort(arr):
    global n
    n = len(arr)

    for i in range(n):
        min_index = i

        for j in range(i+1, n):
            if arr[min_index] > arr[j]:
                min_index = j

        # swap elements
        arr[i], arr[min_index] = arr[min_index], arr[i]


def print_array(arr):
    global n
    for i in range(n):
        print(f"{arr[i]}", end=" ")


if __name__ == "__main__":
    array = [5, 2, 1, 8, 9]
    selection_sort(array)
    print_array(array)
