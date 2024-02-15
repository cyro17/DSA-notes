# User function Template for python3

class Solution:
    # Function to sort a list using quick sort algorithm.
    def quickSort(self, arr, low, high):
        # code here
        if(low < high):
            pi = self.partition(arr, low, high)
            self.quickSort(arr, low, pi-1)
            self.quickSort(arr, pi+1, high)

    def partition(self, arr, low, high):
        # code here
        pi = arr[high]
        i = low-1

        for j in range(low, high):
            if(arr[j] < pi):
                i += 1
                self.swap(arr, i, j)

        self.swap(arr, i+1, high)
        return i+1

    def swap(self, arr, i, j):
        temp = arr[i]
        arr[i] = arr[j]
        arr[j] = temp


if __name__ == '__main__':
    arr = [5, 4, 3, 2, 1]
    s = Solution().quickSort(arr, 0, 4)
    for i in range(5):
        print(arr[i], end=" ")
