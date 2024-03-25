/* Brute Force:
      The extremely naive approach is to check all possible divisors from 1 to max(arr[]).
      The minimum number for which the result <= threshold value, will be our answer.

  Algo:
    1. We will run a loop(say d) from 1 to max(arr[]) to check all possible divisors.
    2. To calculate the result, we will iterate over the given array using a loop. Within this loop,
       we will divide each element in the array by the current divisor, d, and sum up the obtained ceiling
       values.
    3. Inside the outer loop, If result <= threshold: We will return d as our answer.
    4. Finally, if we are outside the nested loops, we will return -1.


            TC = O(N^2)
            SC = O(1)

  Optimized Approach :
       use Binary Search on search space to eliminate the undesirable range.

            TC = O(log(max - min + 1)* N)
            SC = O(1)

*/

class Solution
{
  int smallestDivisor(vector<int> &arr, int threshold)
  {
    int n = arr.size();
    int max_ = *max_element(arr.begin(), arr.end());

    for (int div = 1; div < max_; div++)
    {
      int sum = 0;
      for (int i = 0; i < n; i++)
        sum += ceil((double)(arr[i]) / i);

      if (sum <= threshold)
        return i;
    }
    return -1;
  }

  int smallestDivisor_opt(vector<int> &arr, int threshold)
  {
    int n = arr.size();
    int max_ = *max_element(arr.begin(), arr.end());

    if (threshold < n)
      return -1;
    int low = 1, high = max_;
    while (low <= high)
    {
      int sum = 0;
      int mid = low + (high - low) / 2;
      for (int i = 0; i < n; ++i)
      {
        sum += ceil((double)(arr[i]) / mid);
      }
      if (sum <= threshold)
        high = mid - 1;
      else
      {
        low = mid + 1;
      }
    }
    return low;
  }
}