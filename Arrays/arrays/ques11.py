

class Solution:

    def input_array(self):
        n = int(input())
        for i in range(n):
            pass

    def binarysearch(self, arr, n, k):
        start = 0
        end = n
        mid = 0
        while(start <= end):
            mid = (start+end)//2
            if (k == arr[mid]):
                return mid+1
            elif (k > arr[mid]):
                start = mid + 1
            else:
                end = mid - 1
        return -1


if __name__ == '__main__':

    s = Solution().binarysearch()
    print(s)
