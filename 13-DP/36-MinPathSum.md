```
class Solution {
private:
    int rec(int i, int j, int m, int n, vector<vector<int>> &arr, vector<vector<int>> &dp){

        if(i == 0 && j == 0) return arr[0][0];

        if(i <0 || j <0) return 1e9;

        if(dp[i][j] != -1) return dp[i][j];

        int up = arr[i][j] + rec(i-1, j, m, n, arr, dp);
        int left = arr[i][j] + rec(i, j-1, m, n, arr, dp);

        return dp[i][j] = min(up, left);
    }
public:
    int minPathSum(vector<vector<int>>& arr) {
        int m = arr.size(), n = arr[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return rec(m-1, n-1, m, n, arr, dp);
    }
};
```
