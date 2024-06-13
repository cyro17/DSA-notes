```
class Solution {
private:
    int util(int index, int prev, vector<int> &arr, vector<vector<int>> &dp){
        int n = arr.size();
        if(index == -1) return 0;

        if(dp[index][prev] != -1) return dp[index][prev];

        // dont pick
        int np = 0 + util(index -1, prev, arr, dp);

        // pick
        int p = INT_MIN;
        if(prev == n || arr[index] < arr[prev])
            p = 1 + util(index -1, index, arr, dp);
        return dp[index][prev] = max(p, np);
    }
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return util(n-1, n, nums, dp);
    }
};
```
