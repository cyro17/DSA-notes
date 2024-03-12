
/* Brute Force:

TC = N^4
SC = (2 * no. of the quadruplets)

 */

class Solution
{

   vector<vector<int>> fourSum(vector<int> &nums, int target)
   {
      int n = nums.size(); // size of the array
      set<vector<int>> st;

      // checking all possible quadruplets:
      for (int i = 0; i < n; i++)
      {
         for (int j = i + 1; j < n; j++)
         {
            for (int k = j + 1; k < n; k++)
            {
               for (int l = k + 1; l < n; l++)
               {
                  // taking bigger data type
                  // to avoid integer overflow:
                  long long sum = nums[i] + nums[j];
                  sum += nums[k];
                  sum += nums[l];

                  if (sum == target)
                  {
                     vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                     sort(temp.begin(), temp.end());
                     st.insert(temp);
                  }
               }
            }
         }
      }
      vector<vector<int>> ans(st.begin(), st.end());
      return ans;
   }
};

/* Better Approach : (Using 3 loops and set data structure)
      TC = O(N3*log(M)),
            where N = size of the array, M = no. of elements in the set.

      SC =  O(2 * no. of the quadruplets)+O(N)
 */

class Solution
{
   vector<vector<int>> fourSum(vector<int> &nums, int target)
   {
      int n = nums.size(); // size of the array
      set<vector<int>> st;

      // checking all possible quadruplets:
      for (int i = 0; i < n; i++)
      {
         for (int j = i + 1; j < n; j++)
         {
            set<long long> hashset;
            for (int k = j + 1; k < n; k++)
            {
               // taking bigger data type
               // to avoid integer overflow:
               long long sum = nums[i] + nums[j];
               sum += nums[k];
               long long fourth = target - sum;
               if (hashset.find(fourth) != hashset.end())
               {
                  vector<int> temp = {nums[i], nums[j], nums[k], (int)(fourth)};
                  sort(temp.begin(), temp.end());
                  st.insert(temp);
               }
               // put the kth element into the hashset:
               hashset.insert(nums[k]);
            }
         }
      }
      vector<vector<int>> ans(st.begin(), st.end());
      return ans;
   }
};

/* Optimal Approach: using 4 pointers
      TC = O(N3)
      SC = O(no. of quadruplets)

 */

class Solution
{
   vector<vector<int>> fourSum(vector<int> &nums, int target)
   {
      int n = nums.size(); // size of the array
      vector<vector<int>> ans;

      // sort the given array:
      sort(nums.begin(), nums.end());

      // calculating the quadruplets:
      for (int i = 0; i < n; i++)
      {
         // avoid the duplicates while moving i:
         if (i > 0 && nums[i] == nums[i - 1])
            continue;
         for (int j = i + 1; j < n; j++)
         {
            // avoid the duplicates while moving j:
            if (j > i + 1 && nums[j] == nums[j - 1])
               continue;

            // 2 pointers:
            int k = j + 1;
            int l = n - 1;
            while (k < l)
            {
               long long sum = nums[i];
               sum += nums[j];
               sum += nums[k];
               sum += nums[l];
               if (sum == target)
               {
                  vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                  ans.push_back(temp);
                  k++;
                  l--;

                  // skip the duplicates:
                  while (k < l && nums[k] == nums[k - 1])
                     k++;
                  while (k < l && nums[l] == nums[l + 1])
                     l--;
               }
               else if (sum < target)
                  k++;
               else
                  l--;
            }
         }
      }

      return ans;
   }
};