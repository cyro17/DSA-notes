/* Brute Force:
      TC = O(N^2)
      SC = O(1)
 */

class Solution
{
public:
   int solve(vector<int> &arr)
   {
      int n = arr.size();
      int max_ = 0;
      for (int i = 0; i < n; ++i)
      {
         int sum = 0;
         for (int j = i; j < n; ++j)
         {
            sum += arr[j];
            if (sum == 0)
               max_ = max(max_, j - i + 1);
         }
      }
      return max_;
   }
};

/* Optimal Approach: Using Hashmaps
      TC = O(N)
      SC = O(N)
 */

/*You are required to complete this function*/

class Solution
{
public:
   int maxLen(vector<int> &arr, int n)
   {
      unordered_map<int, int> mp;
      int max_i = 0, sum = 0;
      for (int i = 0; i < n; ++i)
      {
         sum += arr[i];
         if (sum == 0)
         {
            max_i = i + 1;
         }
         else
         {
            if (mp.find(sum) != mp.end())
            {
               max_i = max(max_i, i - mp[sum]);
            }
            else
            {
               mp[sum] = i;
            }
         }
      }
      return max_i;
   }
};
