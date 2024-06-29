```
class Solution {
private:
    int rec(int i, int j, int m, int n, vector<vector<int>> &dp){
        if(  i == 0 and j == 0) return 1;
        if(i <0  or j < 0) return 0;

        if(dp[i][j] != -1) return dp[i][j];

        return dp[i][j] =  rec(i-1, j, m, n, dp) +  rec(i, j-1, m, n, dp);
    }
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return rec(m-1, n-1, m, n, dp);
    }
};
```
