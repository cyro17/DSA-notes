# Min Insertion needed to make string Palindrome

> Maximum Insetion will be to add another string reverse of the original string.
> Leave the longest Palindromic Subsequence intact.
> therefore min operation will be (total - longest palindromic subsequence )

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
    int longestPalindromeSubseq(string &s){
        int n = s.size();

        string s2 = string(s.rbegin(), s.rend());

        vector<vector<int>> dp(n, vector<int>(n, -1));
        return lcsUtil(n-1, n-1, s, s2, dp);
    }
public:
    int minInsertions(string s) {
        int n = s.length();
        return n - longestPalindromeSubseq(s);
    }
};
```
