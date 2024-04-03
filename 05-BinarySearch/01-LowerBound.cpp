#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
   int lowerBound(vector<int> arr, int n, int x)
   {
      // Write your code here

      int l = 0, h = n - 1;
      int ans = n;

      while (l <= h)
      {
         int mid = (l + h) / 2;
         if (arr[mid] >= x)
         {
            ans = mid;
            h = mid - 1;
         }
         else
         {
            l = mid + 1;
         }
      }
      return ans;
   }
};

int main()
{
   Solution obj;
   vector<int> arr = {1, 2, 4, 6, 7};
   cout << obj.lowerBound(arr, 5, 3);
   return 0;
}