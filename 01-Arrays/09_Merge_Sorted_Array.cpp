#include <bits/stdc++.h>
using namespace std;

/* Brute Force:

Time Complexity: O(n+m) + O(n+m), where n and m are the sizes of the given arrays.
Reason: O(n+m) is for copying the elements from arr1[] and arr2[] to arr3[]. And another O(n+m) is for filling back the two given arrays from arr3[].

Space Complexity: O(n+m) as we use an extra array of size n+m.

*/

class Solution
{
public:
   void merge(vector<int> &arr1, int m, vector<int> &arr2, int n)
   {
      int left = 0, right = 0;
      vector<int> res(n + m, 0);

      /* Insert the elements from the 2 arrays
      into the 3rd array using left and right pointers */

      int i = 0;
      while (left < m && right < n)
      {
         if (arr1[left] <= arr2[right])
         {
            res[i++] = arr1[left++];
         }

         else
            res[i++] = arr2[right++];
      }

      // If right pointer reaches the end and left elements are still left
      while (left < m)
         res[i++] = arr1[left++];

      // If left pointer reaches the end  and right elements are still left
      while (right < n)
         res[i++] = arr2[right++];

      for (int i = 0; i < n + m; i++)
      {
         arr1[i] = res[i];
      }
   }
};
