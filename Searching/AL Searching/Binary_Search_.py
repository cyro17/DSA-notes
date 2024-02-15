# Recursive method of binary search


class Binary_Search:
    def __init__(self, array):
        self.arr = array
        self.len = len(array)

    def search(self, l, h, value):

        if l == h:
            if self.arr[l] == value:
                return l
            return "list element not found"
        else:
            global mid
            mid = (l+h) // 2

            if self.arr[mid] == value:
                return mid+1
            if value < self.arr[mid]:
                return self.search(l, mid, value)
            else:
                return self.search(mid+1, h, value)


if __name__ == "__main__":
    arr = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]
    bs = Binary_Search(arr)
    # bs.search(0, len(arr), 5)
    print(bs.search(0, len(arr), 0))
