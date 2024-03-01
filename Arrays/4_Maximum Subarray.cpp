/* Kadane's Algorithm */

/* Brute Force:
   T.C => O(N^3), S.C = O(1)

   for(i = 0 -> n)
      for(j = i -> n)
         int sum = 0;
         for(k = i -> j)
            sum += arr[k]

         max_ = max(max_, sum)
   return max_;


   Bettter Approach:
      T.C => O(N^2), S.C = O(1)'

   int max_ = INT_MIN;
   for(i = 0-> n)
      int sum = 0;
      for (j = i -> n)
         sum += arr[j]
         max_ = max(max_, sum)
   return max_;


   Using kadane we can optimize the complexity to O(N)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
   int maxSubArray(vector<int> &arr)
   {
      int max_s = INT_MIN;
      int curr_s = 0;
      for (int i = 0; i < arr.size(); i++)
      {
         curr_s += arr[i];
         if (curr_s > max_s)
            max_s = curr_s;
         if (curr_s < 0)
            curr_s = 0;
      }
      return max_s;
   }
};