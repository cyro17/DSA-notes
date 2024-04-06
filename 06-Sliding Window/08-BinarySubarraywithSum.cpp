#include <bits/stdc++.h>
using namespace std;

/* brute force : generate all the subarrays and check if their sum == goal ,
   and keep a counter variable to update the number of subarrays with sum == goal

  Optimal : using sliding window

  Find the no of (subarrays with sum <= goal ) - (subarrays with sum <= goal -1 )

    1. iterate the right pointer until n, update sum .
    2. if sum > goal  => shrink the left pointer and subtract the sum
    3. update the cnt of subarrys with length. since no of subarrys = length = (r - l + 1)
*/

class Solution
{
private:
  int util(vector<int> &arr, int goal)
  {
    int n = arr.size();
    int l = 0, r = 0, sum = 0, cnt = 0;
    for (int r = 0; r < n; r++)
    {
      sum += arr[r];
      while (sum > goal && l <= r)
      {
        sum -= arr[l];
        l++;
      }
      cnt += (r - l + 1);
    }
    return cnt;
  }

public:
  int numSubarraysWithSum(vector<int> &arr, int goal)
  {
    return util(arr, goal) - util(arr, goal - 1);
  }

  int solve_brute(vector<int> arr, int k)
  {
    int n = arr.size(), cnt = 0;
    for (int i = 0; i < n; ++i)
    {
      int cnt = 0;
      for (int j = i; j < n; ++j)
      {
        sum += arr[j];
        if (sum == k)
        {
          res++;
        }
        if (sum > k)
          break;
      }
    }
    return res;
  }
};

int main()
{

  return 0;
}