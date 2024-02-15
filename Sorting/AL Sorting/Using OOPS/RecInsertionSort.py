

class RecInsertionSort:
    def __init__(self, array) -> None:
        self.arr = array
        self.len = len(array)

    def __str__(self) -> str:
        return " ".join([str(i) for i in self.arr])

    def sort(self, n=None):
        if not n:
            n = self.len
        if n <= 1:
            return

        self.sort(n-1)

        last = self.arr[n-1]
        j = n-2

        while j >= 0 and self.arr[j] > last:
            self.arr[j+1] = self.arr[j]
            j -= 1

        self.arr[j+1] = last


if __name__ == "__main__":
    arr = [64, 34, 25, 12, 22, 11, 90]
    b = RecInsertionSort(arr)
    b.sort()
    print(str(arr))
