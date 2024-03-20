class Solution
{
public:
   vector<int> searchRange(vector<int> &nums, int target)
   {
      int start = -1, end = -1;
      int n = nums.size();

      int lb = lower_bound(nums.begin(), nums.end(), target) - nums.begin();

      if (lb == n || nums[lb] != target)
         return {-1, -1};

      int ub = upper_bound(nums.begin(), nums.end(), target) - nums.begin();

      return {lb, ub - 1};
   }
};