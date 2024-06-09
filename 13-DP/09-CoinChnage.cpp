class Solution
{
private:
  int util(int index, int target, vector<int> &arr, vector<vector<int>> &dp)
  {
    // Base case
    if (index == 0)
    {
      if (target % arr[0] == 0)
      {
        return target / arr[0];
      }
      return INT_MAX - 1;
    }
    if (dp[index][target] != -1)
      return dp[index][target];

    int not_pick = util(index - 1, target, arr, dp);
    int pick = INT_MAX;

    if (arr[index] <= target)
      pick = 1 + util(index, target - arr[index], arr, dp);

    return dp[index][target] = min(pick, not_pick);
  }

public:
  int coinChange(vector<int> &arr, int target)
  {
    int n = arr.size();
    int res = -1;
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    res = util(n - 1, target, arr, dp);
    if (res == INT_MAX || res == INT_MAX - 1)
      return -1;
    return res;
  }
};