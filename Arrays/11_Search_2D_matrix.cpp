#include <bits/stdc++.h>
using namespace std;

/*
Brute Force:
   run two loops i and j , if target is equal to arr[i][j] return true else false.

   TC = O(N*M)
   SC = O(1)


Better Approach : Using Binary Search

   To optimize TC we wont use BS in every row, instead we wil focus on the particular row
   where there is chances for the target is to be.

   Steps:
      1. use loop i to select a particular row at a time.
      2. if the row contains the target then we will apply Bianry search on row i.
      3. else on completion of traversal we will return false.

   TC = O(N + log M)
   SC = const.

 */
class Solution
{
   bool binarySearch(vector<int> &nums, int target)
   {
      int n = nums.size(); // size of the array
      int low = 0, high = n - 1;

      // Perform the steps:
      while (low <= high)
      {
         int mid = (low + high) / 2;
         if (nums[mid] == target)
            return true;
         else if (target > nums[mid])
            low = mid + 1;
         else
            high = mid - 1;
      }
      return false;
   }

   bool searchMatrix(vector<vector<int>> &matrix, int target)
   {
      int n = matrix.size();
      int m = matrix[0].size();

      for (int i = 0; i < n; i++)
      {
         if (matrix[i][0] <= target && target <= matrix[i][m - 1])
         {
            return binarySearch(matrix[i], target);
         }
      }
      return false;
   }
};

/*
Optimal Approach:  Flattening 2D array into 1D array .

   But it increases our TC (N*M) and extra space to stroe the 1D array.
   so , we will convert the index of 1D array into the correspoding cell number in 2D matrix

   idx = 5
      row = index / m
      col = index % m

   TC = log(N*M)
   SC = const.

 */

class Solution
{

   bool searchMatrix(vector<vector<int>> &matrix, int target)
   {
      int n = matrix.size();
      int m = matrix[0].size();

      // apply binary search:
      int low = 0, high = n * m - 1;
      while (low <= high)
      {
         int mid = (low + high) / 2;
         int row = mid / m, col = mid % m;
         if (matrix[row][col] == target)
            return true;
         else if (matrix[row][col] < target)
            low = mid + 1;
         else
            high = mid - 1;
      }
      return false;
   }
};