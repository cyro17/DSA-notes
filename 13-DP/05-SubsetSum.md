Given an array of non - negative integers, and a value sum,
determine if there is a subset of the given set with sum equal to given sum.

Using recursion
TC = O(2^N)

```

class Solution
{
private:
  bool util(int idx, int target, vector<int> &arr)
  {
    if (target == 0)
      return 1;
    if (idx == 0)
      return (arr[idx] == target);

    bool not_pick = util(idx - 1, target, arr);
    bool pick = false;
    if (target >= arr[idx])
      pick = util(idx - 1, target - arr[idx], arr);

    return pick || not_pick;
  }

public:
  bool isSubsetSum(vector<int> arr, int sum)
  {
    int n = arr.size(), k = sum;
    return util(n - 1, sum, arr);
  }
};

```

Memoization of overlapping subproblems
Time Complexity: O(N x K)

Space Complexity: O(N x K) + O(N)

Reason: We are using a recursion stack space(O(N)) and a 2D array ( O(N x K)).

```
class Solution {
    bool f(int index, int sum,  vector<int> &arr, int k, 
            vector<vector<int>> &dp){
                
        int n = arr.size();
        if(sum == k) return 1;
        if(index == n || sum > k) return 0;
        
        if(dp[index][sum] != -1) return dp[index][sum]; 
        
        return dp[index][k] = f(index + 1, sum + arr[index], arr, k, dp) || 
                f(index + 1, sum, arr, k, dp);
    }
  public:
    bool isSubsetSum(vector<int>& arr, int k) {
        // code here
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        return f(0, 0, arr, k, dp);
    }
};

```

Time Complexity: O(N x K)

Reason: There are N x K states therefore at max N x K new problems will be solved.

Space Complexity: O(N x K)

Reason: no extra rec stack space

```
class Solution
{
  bool solve(vector<int> &arr, int target)
  {
    int k = target;
    vector<vector<bool>> dp(n, vector<bool>(k + 1, 0));
    for (int i = 0; i < n; i++)
      dp[i][0] = 1;

    dp[0][arr[0]] = 1;
    for (int idx = 1; idx < n; idx++)
    {
      for (int j = 1; j <= target; j++)
      {
        bool dont_pick = dp[idx - 1][j];
        bool pick = 0;
        if (arr[idx] <= j)
          pick = dp[idx - 1][j - arr[idx]];
        dp[idx][j] = pick or dont_pick;
      }
    }
    return dp[n - 1][k];
  }
};
```
