import sys
sys.setrecursionlimit(10**6)


class Solution:

    def __init__(self, l=0, r=0):
        self.l = l
        self.r = r

    def merge(self, arr, l, m, r):
        n1 = m - l + 1
        n2 = r-m

        a = [] * n1
        b = [] * n2

        for i in range(n1):
            a.append(arr[i])

        for j in range(n2):
            b.append(arr[j])

        i, j = 0, 0
        k = l

        while(i < n1 and j < n2):
            if (a[i] < b[j]):
                arr[k] = a[i]
                k += 1
                i += 1
            else:
                arr[k] = b[j]
                k += 1
                j += 1

        while(i < n1):
            arr[k] = a[i]
            k += 1
            i += 1

        while(j < n2):
            arr[k] = b[j]
            k += 1
            j += 1

    def mergeSort(self, arr, l, r):
        m = (l+r) // 2
        self.mergeSort(arr, l, m)
        self.mergeSort(arr, m+1, r)

        self.merge(arr, l, m, r)


arr = [5, 4, 3, 2, 1]
n = len(arr)
s = Solution().mergeSort(arr, 0, n-1)
for i in range(n):
    print(arr[i], end=" ")
