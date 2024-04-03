/*
using sliding window: TC = O(2*K)
 */

class Solution
{
public:
  int maxScore_bf(vector<int> &arr, int k)
  {
    int n = arr.size();
    int max_sum = 0;
    int left_sum = 0, right_sum;

    // store sun of first k elements from the left
    for (int i = 0; i < k; i++)
    {
      left_sum += arr[i];
      max_sum = max(max_sum, left_sum);
    }

    //  initialize right index as last element of the array
    right = n - 1;
    for (int i = k - 1; i >= 0; i++)
    {
      left_sum -= arr[i];
      right_sum += arr[right];
      right--;
      max_sum = max(max_sum, left_sum + right_sum);
    }

    return max_sum;
  }
  int maxScore(vector<int> &arr, int k)
  {
    int n = arr.size();
    int lsum = 0, rsum = 0, max_sum = INT_MIN;
    for (int i = 0; i < k; ++i)
    {
      lsum += arr[i];
      max_sum = max(max_sum, lsum);
    }

    int right = n - 1;
    for (int i = k - 1; i >= 0; --i)
    {
      lsum -= arr[i];
      rsum += arr[right];
      right--;
      max_sum = max(max_sum, lsum + rsum);
    }
    return max_sum;
  }
};