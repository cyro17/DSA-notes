/*
return the element appearing more than N/3 times.
 */

/* Note: At max there can be only 2 integer appearing N/3 times */

/* Brute Force: use two loops  */
#include <bits/stdc++.h>
using namespace std;

class Solution
{
   vector<int> majority_element(vector<int> &arr)
   {
      int n = arr.size();
      vector<int> res;
      for (int i = 0; i < n; i++)
      {
         int cnt = 0;
         if (res.size() == 0 || res[0] != arr[i])
         {
            cnt = 0;
            for (int j = 0; j < n; j++)
            {
               if (arr[i] == arr[j])
               {
                  cnt++;
               }
               if (cnt > (n / 3))
                  res.push_back(arr[i]);
            }
         }
      }
   }
}