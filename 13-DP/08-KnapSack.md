Recursive Approach:

TC = O (2^N) <br/>
SC = O (N)

```
class Knapsack
{
private:
  int util(int index, int w, int wt[], int val[], int n)
  {
    // base case
    if (index == 0)
    {
      if (wt[0] <= w)
        return val[0];
      return 0;
    }
    int max_ = INT_MIN;
    int not_pick = util(index - 1, w, wt, val, n);
    int pick = 0;
    if (wt[index] <= w)
      pick = util(index - 1, w - wt[index], wt, val, n);
    max_ = max(pick, not_pick);
    return max_;
  }

public:
  int knapSack(int W, int wt[], int val[], int n)
  {
    return util(n - 1, W, we, val, n);
  }
};
```

Memoization

Complexity Analysis

Time Complexity: O(NxW)

Reason: There are NxW states therefore at max NxW new problems will be solved.

Space Complexity: O(NxW) + O(N)

Reason: We are using a recursion stack space(O(N)) and a 2D array ( O(NxW)).

```
class Solution
{
private:
  int util(int index, int w, int wt[], int val[], int n, vector<vector<int>> &dp)
  {
    // base case
    if (index == 0)
    {
      if (wt[0] <= w)
        return val[0];
      return 0;
    }
    if (dp[index][w] != -1)
      return dp[index][w];

    int max_ = INT_MIN;
    int not_pick = 0 + util(index - 1, w, wt, val, n, dp);
    int pick = 0;
    if (wt[index] <= w)
      pick = val[index] + util(index - 1, w - wt[index], wt, val, n, dp);
    max_ = max(pick, not_pick);

    return dp[index][w] = max_;
  }

public:
  int knapSack(int W, int wt[], int val[], int n)
  {
    vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    return util(n - 1, W, wt, val, n, dp);
  }
};

```

Tabulation:

Time Complexity: O(NxW)

Reason: There are two nested loops

Space Complexity: O(NxW)

Reason: We are using an external array of size NxW. Stack Space is eliminated.

```
int knapSack(int W, int wt[], int val[], int n)
{

  vector<vector<int>> dp(n, vector<int>(W + 1, 0));
  for (int i = wt[0]; i <= W; i++)
    dp[0][i] = val[0];

  for (int index = 1; index < n; ++index)
  {
    for (int cap = 0; cap <= W; ++cap)
    {
      int not_pick = dp[index - 1][cap];
      int pick = INT_MIN;
      if (wt[index] <= cap)
        pick = val[index] + dp[index - 1][cap - wt[index]];

      dp[index][cap] = max(pick, not_pick);
    }
  }
  return dp[n - 1][W];
}

```
