Similar to 0/1 KnaSack but here we have multiple possiblilities to pick up

changes:
after picking up dont go to the next index

base case:
if index = 0
return as much as value possible from the last index

Complexity Analysis

Time Complexity: O(NxW)

Reason: There are NxW states therefore at max ‘NxW’ new problems will be solved.

Space Complexity: O(NxW) + O(N)

Reason: We are using a recursion stack space(O(N)) and a 2D array ( O(NxW)).

```

class Solution{
    private:
      int util(int index, int w, int wt[], int val[], int n, vector<vector<int>> &dp){
        // base case
        if(index == 0){
          if(wt[0]<=w) return (w / wt[0])*val[0];
          return 0;
        }
        if(dp[index][w] != -1) return dp[index][w];

        int max_ = INT_MIN;
        int not_pick = 0 + util(index -1, w, wt, val, n, dp);
        int pick = 0;
        if(wt[index] <= w)
          pick = val[index] + util(index, w-wt[index], wt, val, n, dp);
        max_ =  max(pick, not_pick);

        return dp[index][w] = max_;
      }


public:
    int knapSack(int n, int W, int val[], int wt[])
    {
        vector<vector<int>> dp(n, vector<int>(W + 1, -1));
        return util(n-1, W, wt, val, n, dp);
    }
};
```
