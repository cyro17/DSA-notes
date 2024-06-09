/* Memoization

similar to diff problem :
s1 - s2 = target
s1 + s2 = total

s2 = (total - target ) / 2;

*/

class Solution
{
private:
  int mod = 1e9;
  int util(int idx, int target, vector<int> &arr, vector<vector<int>> &dp)
  {
    if (idx == 0)
    {
      if (target == 0 && arr[0] == 0)
        return 2;
      if (target == 0 || target == arr[0])
        return 1;
      return 0;
    }
    if (dp[idx][target] != -1)
      return dp[idx][target];

    int not_pick = util(idx - 1, target, arr, dp);
    int pick = 0;
    if (target >= arr[idx])
      pick = util(idx - 1, target - arr[idx], arr, dp);

    return dp[idx][target] = (pick + not_pick) % mod;
  }

public:
  int findTargetSumWays(vector<int> &arr, int target)
  {
    int n = arr.size(), total = 0;
    for (int i : arr)
      total += i;

    if (total - target < 0 || (total - target) & 1)
      return 0;
    int s2 = (total - target) / 2;
    vector<vector<int>> dp(n, vector<int>(s2 + 1, -1));
    return util(n - 1, s2, arr, dp);
  }
};