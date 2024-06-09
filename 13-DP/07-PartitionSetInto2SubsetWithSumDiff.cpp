Memoization Approach

Get the dp array and use the last row to find the min diff
Time Complexity: O(N*totSum) +O(N) +O(N)

Reason: There are two nested loops that account for O(N*totSum), at starting we are running a for loop to calculate totSum and at last a for loop to traverse the last row.

Space Complexity: O(N*totSum) + O(N)

Reason: We are using an external array of size ‘N * totSum’ and a stack space of O(N).

```
class Solution
{
private:
  bool util(int index, int target, vector<int> &arr, vector<vector<int>> &dp)
  {
    if (target == 0)
      return 1;
    if (index == 0)
      return arr[0] == target;

    if (dp[index][target] != -1)
      return dp[index][target];

    bool not_pick = util(index - 1, target, arr, dp);
    bool pick = 0;
    if (arr[index] <= target)
      pick = util(index - 1, target - arr[index], arr, dp);

    return dp[index][target] = pick or not_pick;
  }

public:
  int canPartition(int n, vector<int> &arr)
  {
    int total = 0;
    for (int i : arr)
      total += i;

    vector<vector<int>> dp(n, vector<int>(total + 1, -1));
    for (int j = 0; j <= total; j++)
    {
      bool dummy = util(n - 1, j, arr, dp);
    }
    // edge case
    if (total - target < 0 || (total - target) & 1)
      return 0;

    int min_ = INT_MAX;
    for (int j = 0; j <= total / 2; j++)
    {
      if (dp[n - 1][j])
      {
        min_ = min(min_, abs(j - (total - j)));
      }
    }
    return min_;
  }
};

``` <br />

    Tabulation Approach :  

``` class Solution
{
  int canPartition_(int n, vector<int> &arr)
  {
    int total = 0;
    for (int i : arr)
      total += i;
    vector<vector<bool>> dp(n, vector<bool>(total + 1, 0));

    for (int i = 0; i < n; i++)
      dp[i][0] = true;

    for (int index = 1; index < n; index++)
    {
      for (int target = 0; target <= total; target++)
      {
        bool not_pick = dp[index - 1][target];
        bool pick = 0;
        if (arr[index] <= target)
          pick = dp[index - 1][target - arr[index]];

        dp[index][target] = pick || not_pick;
      }
    }

    int min_ = INT_MAX;
    for (int target = 0; target <= total / 2; target++)
    {
      if (dp[n - 1][target])
      {
        int diff = abs(target - (total - target));
        min_ = min(min_, diff);
      }
    }
    return min_;
  }
};
```