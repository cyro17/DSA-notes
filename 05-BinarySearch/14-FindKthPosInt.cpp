class Solution
{
public:
  int findKthPositive(vector<int> &arr, int k)
  {
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
      if (arr[i] <= k)
        k++;
      else
        break;
    }
    return k;
  }

  int findKthPositive_opt(vector<int> &arr, int k)
  {
    int n = arr.size();
    int low = 0, high = n - 1;
    while ((low <= high))
    {
      int mid = (low + high) / 2;
      int missing = arr[mid] - (mid + 1);
      if (missing < k)
      {
        low = mid + 1;
      }
      else
        high = mid - 1;
    }
    return k + high + 1;
  }
};