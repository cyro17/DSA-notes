# MCM

> Memoization

```
class Solution{
private:
  int rec(int i, int j, int arr[], vector<vector<int>> &dp){
    if(i == j ) return 0;

    if(dp[i][j] != -1) return dp[i][j];

    int min_ = 1e9;
    for (int k = i; k < j; ++k)
    {
      int steps = arr[i-1] * arr[k] * arr[j] +
          rec(i, k, arr, dp) + rec(k+1, j, arr, dp);
      if(steps < min_) min_ = steps;
    }
    return dp[i][j] =  min_;
  }
public:
    int matrixMultiplication(int N, int arr[])
    {
       vector<vector<int>> dp(N, vector<int>(N, -1));
       return rec(1, N-1, arr, dp);
    }
};

```

> Using Tabulation
