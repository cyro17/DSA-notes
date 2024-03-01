#include <bits/stdc++.h>
using namespace std;

/* M-1 : Recursive approach

   1. find all possible permutation and store them in a ds.
   2. search input in the ds and print the result next to it.

   T.C => O (N! * N)
   S.C => constant


   M-2 : using unbuilt-fn
            next_permutation(array);

   M-3 : optimized approach:
         T.C => O(3N)
         S.C => constt.

   1. Find break-point =>  (first index from the end where there is dip ( arr[i]< arr[i+1] )).
   2. If no such break-point is found i.e the array is in decreasing order ,
         hence the given array is in the last permutation => get the next permutation (sort the given array.)
   3. If (break-point )
         find the smallest no greater than the pivot in the right half .   // pivot = arr[break-point] //
         swap with the pivot .
         reverse the entire right half.
  */
class Solution
{
public:
   void nextPermutation(vector<int> &arr)
   {
      int n = arr.size(), i, j;

      for (i = n - 2; i >= 0; i--)
      {
         if (arr[i] < arr[i + 1])
         {
            break;
         }
      }

      // Check if pivot is not found
      if (i < 0)
      {
         reverse(arr.begin(), arr.end());
      }

      // if pivot is found
      else
      {

         // Find for the successor of pivot in suffix
         for (j = n - 1; j > i; j--)
         {
            if (arr[j] > arr[i])
            {
               break;
            }
         }

         // Swap the pivot and successor
         swap(arr[i], arr[j]);

         // Minimise the suffix part
         reverse(arr.begin() + i + 1, arr.end());
      }
   }
};