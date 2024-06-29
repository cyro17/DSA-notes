```
class Solution {
private:
    int rec(int i, int j, int m, int n, vector<vector<int>>& arr, vector<vector<int>> &dp){

        if(i <0  or j < 0 || arr[i][j] == 1 ) return 0;

        if(  i == 0 and j == 0) return 1;

        if(dp[i][j] != -1) return dp[i][j];

        return dp[i][j] =  rec(i-1, j, m, n, arr, dp) +  rec(i, j-1, m, n, arr, dp);
    }
public:
    int uniquePathsWithObstacles(vector<vector<int>>& arr) {
        int m = arr.size();
        int n = arr[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return rec(m-1, n-1, m, n, arr, dp);
    }
};
```
