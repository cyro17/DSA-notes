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

/*
Optimized code: 
      Here we took two flags which marks the if the first row or first col has any zero , if it does then set the flag as true;
      Now traverse the matrix from (1, 1) and track if element is 0 then mark the relative first row and col = 0
      Now traverse again from (1, 1) and if the relative first row or col is 0 then mark the element as 0;

      finally check the flag if it is marked, then mark the respective row or col as 0;

      T.C = O ( N * M)
      S.C = O (1 )  -- space saved and optimized
 
*/

class Solution {
public:
    void setZeroes(vector<vector<int>>& arr) {
        int n = arr.size(), m = arr[0].size();

        // keep two flags first row and first col to keep check if any of it has zero 
        // later on if it has then mark the entire first row or col = 0
        bool firstRowZero = 0, firstColZero = 0;

        // check the first col if it has zero 
        for (int i = 0; i < n; ++i)
        {
            if(arr[i][0] == 0){
                firstColZero = 1;
                break;
            }
        }

        // check the first row if has zero 
        for (int j = 0; j < m; ++j)
        {
            if(arr[0][j] == 0){
                firstRowZero = 1;
                break;
            }
        }

        // traverse the array apart from first row and first col 
        // and check if zero is present then mark the respective first row and first col = 0
        for (int i = 1; i < n; ++i)
        {
            for (int j = 1; j < m; ++j)
            {
                if(arr[i][j] == 0){
                    arr[0][j] = 0;
                    arr[i][0] = 0;
                } 
            }
        }

        // now traverse again and check if the respective first row and col = 0
        for (int i = 1; i < n; ++i)
        {
            for (int j = 1; j < m; ++j)
            {
                if(arr[i][0] == 0 || arr[0][j] == 0){
                    arr[i][j] = 0;
                }
            }
        }

        // check the firstrow and firstcol flag, 
        // if it has zero then mark the entrie sequence as 0 

        if(firstRowZero){
            for (int j = 0; j < m; ++j)
            {
                arr[0][j] = 0;
            }
        }

        if(firstColZero){
            for (int i = 0; i < n; ++i)
            {
                arr[i][0] = 0;
            }
        }
    }
};


