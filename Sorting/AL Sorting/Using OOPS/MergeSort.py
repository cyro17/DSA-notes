
class MergeSort_:
    def __init__(self, array):
        self.arr = array
        self.len = len(self.arr)

    def __str__(self) -> str:
        return " ".join([str(i) for i in self.arr])

    def mergesort(self, ar=None):
        n = self.len
        if n <= 1:
            return

        i = j = k = 0
        mid = n//2
        L = self.arr[:mid]
        R = self.arr[mid:]

        self.mergesort(L)
        self.mergesort(R)

        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                self.arr[k] = L[i]
                i += 1
            else:
                self.arr[k] = R[j]
                j += 1
            k += 1

        while i < len(L):
            self.arr[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            self.arr[k] = R[j]
            j += 1
            k += 1


if __name__ == "__main":
    arr = [7, 9, 4, 3, 10]
    m = MergeSort_()
    m.mergesort()
    print(str(arr))
