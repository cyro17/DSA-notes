# Longest Palindromic Subsequence

> Brute Force: Generate all the subsequences and get the maximum palindromic one.
> Either by Power Set or using Recursive approach.

> Optimization using DP:
> Make a new string which will be the reverse of original string.
> Now get the LCS of both => longest palindromic subsequence.

> Memoization Approach:

```
class Solution {
private:
  int lcsUtil(int i, int j, string &s1, string &s2, vector<vector<int>> &dp){
    if(i<0 || j<0) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    if(s1[i] == s2[j])
      return dp[i][j] = 1 + lcsUtil(i-1, j-1, s1, s2, dp);
    else
      return dp[i][j] = max(lcsUtil(i, j-1, s1, s2, dp), lcsUtil(i-1, j, s1, s2, dp));
  }
public:
    int longestPalindromeSubseq(string s){
    int n = s.size();

    string s2 = string(s.rbegin(), s.rend());

    vector<vector<int>> dp(n, vector<int>(n, -1));
    return lcsUtil(n-1, n-1, s, s2, dp);
  }
};

```

> Tabulation Approach:

```
class Solution {
public:
    int longestPalindromeSubseq(string s){
    int n = s.size();
    string s2 = string(s.rbegin(), s.rend());

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    for(int i = 0; i<=n ; i++) dp[i][0] = 0;
    for(int j = 0; j<=n ; j++) dp[0][j] = 0;

    for(int i = 1; i<=n; i++){
      for(int j = 1; j<=n; j++){
        if(s[i-1] == s2[j-1])
          dp[i][j] = 1 + dp[i-1][j-1];
        else
          dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
      }
    }
    return dp[n][n];
  }
};
```
