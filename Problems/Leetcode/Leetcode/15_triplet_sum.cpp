#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        int n = nums.size();

        for (int i = 0; i < n; i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int j = i + 1;
            int k = n - 1;

            while (j < k)
            {
                if (nums[i] + nums[j] + nums[k] == 0)
                {
                    res.push_back(vector<int>{nums[i], nums[j], nums[k]});

                    j += 1;
                    while (j < k && nums[j] == nums[j - 1])
                        j++;
                }
                else if (nums[i] + nums[j] + nums[k] < 0)
                {
                    j++;
                }
                else
                {
                    k--;
                }
            }
        }
        return res;
    }
};

int main()
{
    vector<int> v{-1, 0, 1, 2, -1, -4};
    vector<vector<int>> s = Solution().threeSum(v);

    return 0;
}