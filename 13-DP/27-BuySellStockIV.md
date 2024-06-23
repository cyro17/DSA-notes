```
class Solution {
private:
  int util(int index, int buy, int cap, vector<int> &arr,  vector<vector<vector<int>>> &dp ){
    // base case
    int n = arr.size();
    if(index == n || cap == 0) return 0;
    int profit = 0;

    if(dp[index][buy][cap] != -1 ) return dp[index][buy][cap];

    if(buy)
        profit = max(     0     + util(index + 1, 1, cap, arr, dp),
                    -arr[index] + util(index + 1, 0, cap, arr, dp));
    else
        profit = max( 0 +        util(index + 1, 0, cap, arr, dp),
                    arr[index] + util(index + 1, 1, cap-1, arr, dp));
    return dp[index][buy][cap] = profit;
  }

public:
    int maxProfit(int k, vector<int>& arr) {
        int n = arr.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return util(0, 1, k, arr, dp);
    }
};
```
