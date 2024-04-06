#include <bits/stdc++.h>
using namespace std;

/* brute force : generate all the subarrays and check if their no of odds  == k ,
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
  int solve(vector<int> &arr, int k)
  {
    int n = arr.size();
    int l = 0, r = 0, odd = 0, cnt = 0;
    while (r < n)
    {
      odd += (arr[r] & 1);
      while (odd > k && l <= r)
      {
        odd -= (arr[l] & 1);
        l++;
      }
      cnt += (r - l + 1);
      r++;
    }
    return cnt;
  }

public:
  int numberOfSubarrays(vector<int> &arr, int k)
  {
    return solve(arr, k) - solve(arr, k - 1);
  }

  int solve_brute(vector<int> arr, int k)
  {
    int n = arr.size(), cnt = 0;
    for (int i = 0; i < n; ++i)
    {
      int odds = 0;
      for (int j = i; j < n; ++j)
      {
        if (arr[j] & 1) // odd check
          odds++;
        if (cnt == k)
        {
          cnt++;
        }
        if (odds > k)
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