# Edit Distance

> Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

### Using String Matching:

> if character matches:
> no operation reqd , iterate over next rec call
> 0 + f(i-1, j-1)

> if character dont match:
> case 1 : insertion => 1 + f(i, j-1).
> case 2 : deletion => 1 + f(i-1, j).
> case 3 : replacement => 1 + f(i-1, j-1).

>     return minimum of above 3 cases.

```
class Solution {
private:
  int util(int i, int j, string &s, string &t, vector<vector<int>> &dp){
    if( i< 0) return j + 1;
    if( j < 0) return i + 1;

    if(dp[i][j] != -1) return dp[i][j];
    if(s[i] == t[j])
      return dp[i][j] = 0 + util(i-1, j-1, s, t, dp);
    else{
      return dp[i][j] = 1 + min(util(i-1, j, s, t, dp), min(util(i, j-1, s, t, dp), util(i-1, j-1, s, t, dp) ));
    }
  }
public:
    int minDistance(string word1, string word2) {
      int n = word1.size(), m = word2.size();
      vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
      return util(n-1, m-1, word1, word2, dp);
    }
};

```
