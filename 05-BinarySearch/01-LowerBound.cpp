#include <bits/stdc++.h>
using namespace std;


// lower bound => smallest index s.t arr[idx] >= target 
//                If not found => returns last index.

// upper bound => smallest index s.t arr[idx] > target, 
//                If not found => returns.

// using C++ STL method => lower_bound(start_iterator, end_iterator, target) => returns iterator pointing to the required element

// TC => Log(N)

class Solution
{
public:
   int lowerBound(vector<int> arr, int n, int x)
   {
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
