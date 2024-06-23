```
class Solution {
private:
    int util(int index, int buy, int fee, vector<int> &arr, int n,  vector<vector<int>> &dp){
        if(index == n) return 0;
        if(dp[index][buy] != -1) return dp[index][buy];
        int profit = 0;
        if(buy){
            profit = max(0 + util(index + 1, 1, fee, arr,  n, dp),
                        -arr[index] -fee + util(index +1 , 0, fee, arr, n, dp));
        }
        else{
            profit = max(arr[index] + util(index + 1, 1, fee, arr, n, dp),
                        0 + util(index + 1, 0, fee, arr, n, dp));
        }
        return dp[index][buy] = profit;
    }
public:
    int maxProfit(vector<int> &arr, int fee){
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return util(0, 1, fee, arr, n, dp);
    }
};
```
