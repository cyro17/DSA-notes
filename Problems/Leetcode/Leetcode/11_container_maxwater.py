
from sys import maxsize


class Solution:
    def maxArea(self, height):
        l = 0
        r = len(height) - 1
        max_area = 0

        while(l < r):
            shorter = min(height[l], height[r])
            temp = shorter*(r-l)
            max_area = max(max_area, temp)

            if(height[l] < height[r]):
                l += 1
            else:
                r -= 1

        return max_area


if __name__ == '__main__':
    l = [int(i) for i in input().split()]
    s = Solution().maxArea(l)
    print(s)
