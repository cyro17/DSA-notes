Recursive Approach

```

class FrogJumps
{
private:
  int rec(int idx, vector<int> &h)
  {
    if (n == 0)
      return 0;
    int left = rec(idx - 1, h) + abs(h[idx] - h[idx - 1]);
    int right = INT_MAX;
    if (i > 1)
      right = rec(idx - 2, h) + abs(h[idx] - h[idx - 2]);
    return min(left, right);
  }

public:
  int solve(int n, vector<int> &height)
  {
    return rec(n - 1, height);
  }
};
```

DP Memoization

```
class Solution
{
public:
  int rec(int idx, vector<int> &h, vector<int> &dp)
  {
    if (idx == 0)
      return 0;
    if (dp[idx] != -1)
      return dp[idx];
    int left = rec(idx - 1, h, dp) + abs(h[idx] - h[idx - 1]);
    int right = INT_MAX;
    if (idx > 1)
      right = rec(idx - 2, h, dp) + abs(h[idx] - h[idx - 2]);
    return dp[idx] = min(left, right);
  }

  int solve(vector<int> &h, int n)
  {
    vector<int> dp(n + 1, -1);
    return rec(n - 1, h, dp);
  }
};
```

DP Tabulation

```
class Solution
{
public:
  int solve(vector<int> &h, int n)
  {
    vector<int> dp(n + 1, -1);
    dp[0] = 0;
    for (int i = 1; i < n; ++i)
    {
      int fs = dp[i - 1] + abs(h[i] - h[i - 1]);
      int ss = INT_MAX;
      if (i > 1)
        ss = dp[i - 2] + abs(h[i] - h[i - 2]);
      dp[i] = min(fs, ss);
    }
    return dp[n - 1];
  }
};
```
