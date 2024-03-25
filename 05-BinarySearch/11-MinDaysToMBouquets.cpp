
/* Brute Force :

    1.  If m*k > arr.size: This means we have insufficient flowers. So, it is impossible to make m bouquets
        and we will return -1.
    2.  We will run a loop(say i) from min(arr[]) to max(arr[]) to check all possible answers.
    3.  Next, we will pass each potential answer, represented by the variable ‘i’ (which corresponds to a
        specific day), to the ‘possible()’ function. If the function returns true, indicating that we can
        create ‘m’ bouquets, we will return the value of ‘i’.
    4.  Finally, if we are outside the loop, we can conclude that is impossible to make m bouquets.
        So, we will return -1.

          TC = O( (max - min )* N)
          SC = O(1)

  Optimized Approach:
    1. we can use binary search on our search space [ min...max ] eliminate the half search space;
*/

class Solution
{
private:
  bool possible(vector<int> &arr, int day, int m, int k)
  {
    int cnt = 0, noOfB = 0;
    for (int i = 0; i < n; ++i)
    {
      if (arr[i] <= day)
        cnt++;
      else
      {
        noOfB += (cnt / k);
        cnt = 0;
      }
    }
    noOfB += (cnt / k);
    return noOfB >= m;
  }

public:
  int minDays(vector<int> &arr, int k, int m)
  {
    int val = k * m;
    int n = arr.size();
    if (n < val)
      return -1;
    int min_ = *min_element(arr.begin(), arr.end());
    int max_ = *max_element(arr.begin(), arr.end());

    for (int i = min_; i <= max_; ++i)
    {
      if (possible(arr, i, m, k))
        return i;
    }
    return -1;
  }

  int minDays_opt(vector<int> &arr, int k, int m)
  {
    int val = k * m;
    int n = arr.size();
    if (n < val)
      return -1;
    int min_ = *min_element(arr.begin(), arr.end());
    int max_ = *max_element(arr.begin(), arr.end());

    int low = min_, high = max_;

    while (low <= high)
    {
      int mid = low + (high - low) / 2;
      if (possible, mid, m, k)
        high = mid - 1;
      else
        low = mid + 1;
    }
    return low;
  }
}