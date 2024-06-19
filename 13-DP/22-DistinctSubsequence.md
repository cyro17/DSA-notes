# Number of Distinct Subsequence of S1 which is equal to S2.

### Using String Matching :

> f(i, j) represents all distinct subsequence of s2[0...(j-1)] in s1[0...(i-1)].

> when characters match (s1[i] == s2[j]).
> f(i-1, j-1) + f(i-1, j) : work on the remaining index by decreasing both i and j + find more possiblity of matching.

> when characters dont match (s1[i] != s2[j]).
> decrease both the indexes and check for other possiblities.

```
class Solution {
    int util(int i, int j, string &s, string &t,  vector<vector<int>> &dp){
      if(j < 0) return 1;
      if(i < 0) return 0;


      if( dp[i][j] != -1) return dp[i][j];

      if(s[i] == t[j]){

         return dp[i][j] = util(i-1, j-1, s, t, dp) + util(i-1, j, s, t, dp);
      }
      else  return dp[i][j] = util(i-1, j, s, t, dp);

    }
public:
    int numDistinct(string &s, string &t) {
      int n = s.size(), m = t.size();
      if(m > n) return 0;
      vector<vector<int>> dp(n, vector<int>(m, -1));
      return util(n-1, m-1, s, t, dp);
    }
};

```

> Time Complexity: O(N\*M).

> Reason: There are N*M states therefore at max ‘N*M’ new problems will be solved.

> Space Complexity: O(N\*M) + O(N+M).

> Reason: We are using a recursion stack space(O(N+M)) and a 2D array ( O(N\*M)).

### Tabulation Approach

```
class Solution {
const int mod = 1e9 + 7;
public:
    int numDistinct(string &s, string &t) {
      int n = s.size(), m = t.size();
      vector<vector<int>> dp(n +1, vector<int>(m + 1, 0));
      // return util(n-1, m-1, s, t, dp);
      for (int i = 0; i <= n; ++i){
        dp[i][0] = 1;
      }
      for (int j = 1; j <= m; ++j){
        dp[0][j] = 0;
      }

      for (int i = 1; i < n+1; ++i)
      {
        for (int j = 1; j < m + 1; ++j)
        {
          if(s[i-1] == t[j-1])
            dp[i][j] =( dp[i-1][j-1] + dp[i-1][j]) % mod;
          else dp[i][j] = dp[i-1][j];
        }
      }
      return dp[n][m];
    }
};

```
