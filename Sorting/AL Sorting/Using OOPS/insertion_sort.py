

class InsertionSort:

    def __init__(self, array):
        self.arr = array
        self.length = len(array)

    def __str__(self) -> str:
        return " ".join([str(i) for i in self.arr])

    def sort(self):
        n = self.length

        for i in range(1, n):
            key = self.arr[i]
            j = i-1

            while j >= 0 and self.arr[j] > key:
                self.arr[j+1] = self.arr[j]
                j -= 1

            self.arr[j+1] = key


if __name__ == "__main__":
    arr = [64, 34, 25, 12, 22, 11, 90]
    b = InsertionSort(arr)
    b.sort()
    print(str(arr))
