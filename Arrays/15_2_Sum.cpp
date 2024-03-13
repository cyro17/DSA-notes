#include <bits/stdc++.h>
using namespace std;

/* Brute Force:
   Using two nested loops i and j and check for every comb
   TC = N^2
   SC = N
 */
class Solution
{
public:
   vector<int> twoSum(vector<int> &v, int target)
   {
      int n = v.size();
      vector<int> res;
      for (int i = 0; i < n - 1; ++i)
      {
         for (int j = i + 1; j < n; ++j)
         {
            if (v[i] + v[j] == target)
               return {i, j};
         }
      }
      return {};
   }
};

/* Better Approach : Using Hashing
      1. loop over and select an element
      2. if left(target - arr[i]) exist in hash
         1. if exist => retrun {mp[left], i};
         2. if doesnt exist => store the current into hash.

   TC => O(N)
   SC => O(N)
*/

class Solution
{
public:
   vector<int> twoSum(vector<int> &arr, int target)
   {
      int n = arr.size();
      unordered_map<int, int> mp;
      for (int i = 0; i < n; i++)
      {
         int num = arr[i];
         int left = target - num;
         if (mp.find(left) != mp.end())
            return {mp[left], i};
         mp[num] = i;
      }

      return {-1, -1};
   }
};