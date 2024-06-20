```
class Solution
{
public:
     vector<string> all_longest_common_subsequences(string s1, string s2){
    	int n = s1.size(), m = s2.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for(int i = 0; i<=n ; i++) dp[i][0] = 0;
        for(int j = 0; j<=m ; j++) dp[0][j] = 0;

        for(int i = 1; i<=n; i++){
          for(int j = 1; j<=m; j++){
            if(s1[i-1] == s2[j-1])
              dp[i][j] = 1 + dp[i-1][j-1];
            else
              dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
          }
        }

        int len = dp[n][m];
        int i = n, j = m;
        int index = len- 1;

        vector<string> ans;
        string res = "";

        for(int k = 0; k<len; k++) res += '$';

        while(i>0 && j > 0){
            if(s1[i-1] == s2[j-1]){
                res[index] = s1[i-1];
                index--;
                i--; j--;
            }
            else if(dp[i-1][j] > dp[i][j-1])
                i--;
            else
                j--;

            if(res.length() == len)
        }
        return ans;
    }
};
```
