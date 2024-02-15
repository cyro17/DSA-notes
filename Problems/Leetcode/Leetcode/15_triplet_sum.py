class Solution:
    def threeSum(self, nums):
        nums.sort()
        res = []
        n = len(nums)

        for i in range(0, n):
            if i > 0 and nums[i] == nums[i-1]:
                continue

            j = i+1
            k = n-1
    
            while(j < k):
                if nums[i] + nums[j] + nums[k] == 0:
                    res.append([nums[i], nums[j], nums[k]])
                    j += 1

                    while(j < k and nums[j] == nums[j-1]):
                        j += 1

                elif nums[i] + nums[j] + nums[k] < 0:
                    j += 1

                else:
                    k -= 1
        return res
