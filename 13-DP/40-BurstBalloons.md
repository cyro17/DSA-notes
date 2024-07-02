```
class Solution {
private:
    int rec(int i, int j, vector<int> &arr, vector<vector<int>> &dp){
        if( i > j ) return 0;
        int max_ = INT_MIN;
        int n = arr.size();

        if(dp[i][j] != -1 ) return dp[i][j];
        for(int k = i; k <= j; k++){
            int tmp = arr[k];
            if(j + 1 < n) tmp *= arr[j+1];
            if( i -1 >=0) tmp *= arr[i-1];
            tmp += (rec(i, k-1, arr, dp) + rec(k+1, j, arr, dp));
            max_ = max(max_, tmp);
        }
        return dp[i][j] = max_;
    }
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.push_back(1);
        nums.insert(nums.begin(), 1);

        vector<vector<int>> dp(n+2, vector<int>(n+2, -1));
        return rec(1, n, nums, dp);
    }
};
```
