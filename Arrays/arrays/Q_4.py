
class Solution:
    def subArraySum(self, arr, n, s):
        curr_sum = 0
        i, j = 0, 0
        start = -1
        end = -1
        res = []

        while(j < n and curr_sum <= s):
            curr_sum += arr[j]
            j += 1

        if (curr_sum == s):
            res.append(i+1)
            res.append(j+1)
            return res

        while (curr_sum > s and i < n):
            curr_sum -= arr[i]
            i += 1

        if curr_sum == s:
            res.append(i+1)
            res.append(j+1)
            return res


if __name__ == '__main__':
    arr = [1, 3, 7, 9, 15, 1, 2]
    s = Solution()
    print(s.subArraySum(arr, 7, 10))
