

class HeapSort_:
    def __init__(self, array) -> None:
        self.arr = array
        self.len = len(self.arr)

    def heapSort(self):
        n = self.len
        # create max_heap
        for i in range(n//2, -1, -1):
            self.heapify(n, i)

        for i in range(n-1, 0, -1):
            self.arr[i], self.arr[0] = self.arr[0], self.arr[i]
            self.heapify(i, 0)

    def heapify(self, n, i):
        largest = i
        l = 2*i + 1
        r = 2*i + 2

        if l < n and self.arr[largest] < self.arr[l]:
            largest = l

        if r < n and self.arr[largest] < self.arr[r]:
            largest = r

        if largest != i:
            self.arr[i], self.arr[largest] = self.arr[largest], self.arr[i]
            self.heapify(n, largest)


if __name__ == "__main__":
    arr = [12, 11, 13, 5, 6, 7]
    h = HeapSort_(arr)
    h.heapSort()
    for i in range(len(arr)):
        print(f"{arr[i]}", end=" ")
