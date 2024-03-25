class Solution
{
private:
  int findDays(vector<int> &weights, int cap)
  {
    int n = weights.size();
    int days = 1, load = 0;
    for (int i = 0; i < n; ++i)
    {
      if (weights[i] + load > cap)
      {
        load = weights[i];
        days++;
      }
      else
        load += weights[i];
    }
    return days;
  }

public:
  int shipWithinDays(vector<int> &weights, int days)
  {
    int n = weights.size();
    int max_ = *max_element(weights.begin(), weights.end());
    int sum = accumulate(weights.begin(), weights.end(), 0);

    for (int i = max_; i <= sum; i++)
    {
      if (findDays(weights, i) <= days)
        return i;
    }
    return -1;
  }

  int shipWithinDays_opt(vector<int> &weights, int days)
  {
    int n = weights.size();
    int max_ = *max_element(weights.begin(), weights.end());
    int sum = accumulate(weights.begin(), weights.end(), 0);

    int low = max_, high = sum;
    while (low <= high)
    {
      int mid = low + (high - low) / 2;
      if (findDays(weights, mid) <= days)
      {
        high = mid - 1;
      }
      else
        low = mid + 1;
    }
    return low;
  }
};