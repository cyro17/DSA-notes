Approach similar to Knapsack : Just we will try to collect all the possible rod lengths while keep on maximizing the price

state(index, rod_length)

base case:

(index == 0 ) return as many rods possible to maximize the price

Complexity Analysis

Time Complexity: O(N^2)

Reason: There are two nested loops

Space Complexity: O(N^2)

Reason: We are using an external array of size ‘N^2’. Stack Space is eliminated.

```

class Solution{
  private:
    int util(int index, int n, int price[], vector<vector<int>> &dp){
        if(index == 0)
            return n * price[0];

        if(dp[index][n] != -1) return dp[index][n];
        int not_pick = 0 + util(index -1, n, price, dp);
        int pick = INT_MIN;
        int rod_length = index + 1;
        if(rod_length <= n)
            pick = price[index] + util(index, n - rod_length, price, dp);
        return dp[index][n] = max(pick, not_pick);
    }
  public:
    int cutRod(int price[], int N) {

        vector<vector<int>> dp(N, vector<int>(N+1, -1));
        return util(N-1, N, price, dp);
    }
};
```
