#include <bits/stdc++.h>
using namespace std;

/* Brute Force:
   1. sort the given array
   2. select one element at a time (using for loop)

   3. skip all the merged interval
         => mark (first, second ) = curr_first , curr_end
         => if the res array is not empty and curr_end is less than last end of array
            then skip the iteration as the result already have the interval ]\

   4. check the rest of the interval
      - if the first element of next interval is less than curr_end
         - update the curr_end as next end
      - else it wont be a part of interval
   5. push the curr_first, curr_end into the res array.


   T.C => O(nlogn) + O(2n)       - we use 2 for loop , we can optimize this to one
   S.C => O(n)

 */

class Solution
{
public:
   vector<vector<int>> merge(vector<vector<int>> &arr)
   {

      int n = arr.size();
      vector<vector<int>> res;
      sort(arr.begin(), arr.end());

      for (int i = 0; i < n; ++i)
      {
         int cur_start = arr[i][0];
         int cur_end = arr[i][1];

         if (!res.empty() && cur_end <= res.back()[1])
            continue;

         for (int j = i + 1; j < n; ++j)
         {
            if (arr[j][0] <= cur_end)
               cur_end = max(cur_end, arr[j][1]);
            else
               break;
         }
         res.push_back({cur_start, cur_end});
      }
      return res;
   }
};

/* Optimize Approach :

   In brute force approach we were traversing every interval twice.
   Here we will only update the last inserted end to curr_end if it is mergable,
   else add the new interval.

   T.C => O(nlogn) + O(n)       - we use only  1 for loop in this optimize approach
   S.C => O(n)
*/

class Solution
{
public:
   vector<vector<int>> merge(vector<vector<int>> &arr)
   {

      int n = arr.size();
      vector<vector<int>> res;
      sort(arr.begin(), arr.end());

      for (int i = 0; i < n; ++i)
      {
         // current interval does NOT lie in the last interval
         if (res.empty() || arr[i][0] > res.back()[1])
            res.push_back(arr[i]);

         /* current interval lies in the last interval so its mergable
           so we will just update the last insered end interval */
         else
            res.back()[1] = max(res.back()[1], arr[i][1]);
      }
      return res;
   }
};
