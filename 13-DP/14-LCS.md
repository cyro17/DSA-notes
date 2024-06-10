# Largest Common Subsequences

> M - 1 : Get all the subsequences of both the strings either using power set or using recursion.
> **TC = O(2 ^ n + m)**.
> **SC = O(1)**.

```
class Solution {
private:
  int lcsUtil(int i, int j, string &s1, string &s2){
    if(i<0 || j<0) return 0;

    if(s1[i] == s2[j])
      return 1 + lcsUtil(i-1, j-1, s1, s2);
    else
      return max(lcsUtil(i, j-1, s1, s2), lcsUtil(i-1, j, s1, s2));
  }
public:
    int longestCommonSubsequence(string s1, string s2){
    int n = s1.size(), m = s2.size();

    return lcsUtil(n-1, m-1, s1, s2);
  }
};

```

> M-2 : Memoized approach.
> **TC = O(NxM)**.
> **SC = O(NxM) + O(N)**

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
    int longestCommonSubsequence(string s1, string s2){
    int n = s1.size(), m = s2.size();

    vector<vector<int>> dp(n, vector<int>(m, -1));
    return lcsUtil(n-1, m-1, s1, s2, dp);
  }
};
```
