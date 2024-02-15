
from tkinter.tix import Select


class SelectionSort:
    def __init__(self, array) -> None:
        self.arr = array

    def sort(self):
        global n
        n = len(self.arr)
        for i in range(n):
            min_index = i
            for j in range(i+1, n):
                if self.arr[min_index] > self.arr[j]:
                    min_index = j

        self.arr[i], self.arr[min_index] = self.arr[min_index], self.arr[i]

    def print_array(self):
        global n
        print("sorted array : ")
        for i in range(n):
            print(f"{self.arr[i]}", end=" ")


if __name__ == "__main__":
    array = [11, 23, 10, 6, 20]
    s = SelectionSort(array)
    s.sort()
    s.print_array()
