#include <bits/stdc++.h>
using namespace std;

class Solution
{
   /* Brute Force: Using maps

      keep count of key with their occurrence as the value of map
      if the val == 1 return the key
   */
   int solve1(vector<int> &arr)
   {
      map<int, int> mp;
      int n = arr.size();
      for (int i = 0; i < n; i++)
      {
         mp[arr[i]]++;
      }
      for (auto it : mp)
      {
         if (it.second == 1)
            return it.first;
      }
      return -1;
   }

   /* Optimal Approach: USing XOR  => O(N)
      double occurring no will get cancelled and we get our desired number
   */
   int solve_(vector<int> &arr)
   {
      int xor_ = 0;
      for (int i = 0; i < n; i++)
      {
         xor_ = xor_ ^ arr[i];
      }
      return xor_;
   }
};