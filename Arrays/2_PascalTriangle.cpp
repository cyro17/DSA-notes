#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
   int ncr(int n, int r)
   {
      int res = 1;
      for (int i = 0; i < r; ++i)
      {
         res = res * (n - i);
         res = res / (i + 1);
      }
      return res;
   }

public:
   vector<vector<int>> generate(int n)
   {
      vector<vector<int>> res;
      for (int i = 1; i <= n; i++)
      {
         vector<int> tmp;
         for (int j = 1; j <= i; j++)
         {
            tmp.push_back(ncr(i - 1, j - 1));
         }
         res.push_back(tmp);
      }
      return res;
   }
};
