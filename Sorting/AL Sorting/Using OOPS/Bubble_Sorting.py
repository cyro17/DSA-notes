#  iterative method to solve bubble sort technique

# iterative method of Bubble Sort algorihtm


class BubbleSort:
    def __init__(self, array) -> None:
        self.array = array

    def sort(self):
        global n
        n = len(self.array)

        # maximum number of passes
        for i in range(n):
            swapped = False
            # at each pass the largest element remaining gets sorted
            for j in range(0, n-i-1):
                if self.array[j+1] < self.array[j]:
                    self.array[j], self.array[j + 1] =\
                        self.array[j+1], self.array[j]
                    swapped = True
            # if no elements gets swapped in the inner loop then the array is already sorted , no need to do more passes just break out of the loo
            if swapped == False:
                break
        return self.array

    def print_array(self):
        global n
        for i in range(n):
            print(self.array[i], end=" ")


if __name__ == "__main__":
    arr = [1, 2, 7, 8, 4, 0]
    b = BubbleSort(arr)
    b.sort()
    # b.print_array()
    print(arr)
