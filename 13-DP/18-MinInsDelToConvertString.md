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

    int longestCommonSubsequence(string s1, string s2){
        int n = s1.size(), m = s2.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));
        return lcsUtil(n-1, m-1, s1, s2, dp);
  }
public:
    int minDistance(string word1, string word2) {
        int lcs_len =  longestCommonSubsequence(word1, word2);
        int del = word1.length() - lcs_len;
        int ins = word2.length() - lcs_len;

        return del + ins;
    }
};
```
