#include <bits/stdc++.h>
using namespace std;

/*
doc:
   https://takeuforward.org/data-structure/set-matrix-zero/
   */

/*
      T.C =>  N^2
      SC =>  N + M  -- extra space --> optimized in later approch 

      1. Take two array representing row and col 
      2. traverse through the matrix and if 0 is found , mark the respective row and col = 1;
      3. loop over matrix, and check the relative row | col, if its marked 1 -> mark the respective element = 0;

      in optimal approach we will try to optimize the space comp
 */
class Solution
{
public:
   void setZeroes(vector<vector<int>> &arr)
   {
      int n = arr.size();
      int m = arr[0].size();

      vector<int> row(n, 0);
      vector<int> col(m, 0);

      for (int i = 0; i < n; ++i)
      {
         for (int j = 0; j < m; ++j)
         {
            if (arr[i][j] == 0)
            {
               row[i] = 1;
               col[j] = 1;
            }
         }
      }

      for (int i = 0; i < n; ++i)
      {
         for (int j = 0; j < m; ++j)
         {
            if (row[i] || col[j])
               arr[i][j] = 0;
         }
      }
   }
};



