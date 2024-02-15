
from bubble_sorting import *


class RecBubbleSort:
    def __init__(self, array):
        self.arr = array
        self.length = len(array)

    def __str__(self) -> str:
        return " ".join([str(i) for i in self.arr])

    def sort(self, n=None):

        if not n:
            n = self.length

        if n == 1:
            return

        for i in range(n-1):
            if self.arr[i] > self.arr[i+1]:
                self.arr[i], self.arr[i+1] = self.arr[i+1], self.arr[i]

        self.sort(n - 1)

    # def print_array(self):
    #     for i in range(self.length):
    #         print(arr[i], end=" ")


if __name__ == "__main__":
    arr = [64, 34, 25, 12, 22, 11, 90]
    b = RecBubbleSort(arr)
    b.sort()
    print(str(arr))
