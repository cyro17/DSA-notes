Similar to Coin change problem, but here we have to find all the combination which leads to the target.

Use Pick and not pick method, to explore all ways and take the sum of both.

Base Case :
index = 0 (since we are doing memoization (top-down) approach)
if target is divisible by the first element then return 1 => possible way

else return 0 => cannot be possible to get to the target sum with this

```
class Solution {
private:
  int mod = 1e9;
  int util(int index, int target, vector<int> &arr, vector<vector<int>> &dp){
    // Base Case
    if(index == 0) {
      return (target % arr[0] == 0);
    }

    if(dp[index][target] != -1) return dp[index][target];

    int not_pick = util(index - 1, target, arr, dp);
    int pick = 0;
    if(arr[index] <= target)
      pick = util(index, target - arr[index], arr, dp);
  return dp[index][target] =  (pick + not_pick);
  }
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
        return util(n-1, amount, coins, dp);
    }
};

```
