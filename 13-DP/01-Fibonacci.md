Recursive approach
TC = exp , since every func calls 2 other func
SC = O(N)

```
int Fibonacci(int n)
{
  if (n <= 1)
    return 1;
  return Fibonacci(n - 1) + Fibonacci(n - 2);
}
```

DP => Memoizing
TC = O(N)
SC = O(2N) since we are creating an array of n size and rec stack space takes o(n) space

```
class Solution
{
private:
  int fn(int n, vector<int> &dp)
  {
    if (n <= 1)
      return n;
    if (dp[n] != -1)
      return dp[n];
    return dp[n] = fn(n - 1, dp) + fn(n - 2, dp);
  }

public:
  int fib(int n)
  {
    vector<int> dp(n + 1, -1);
    return fn(n, dp);
  }
};

```

DP => Tabulation
TC = O(N)
SC = O(N) , we dont use the rec stack space here in tabulation

```

class Solution
{
public:
  int fib(int n)
  {
    vector<int> dp(n + 1, -1);

    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i < n; i++)
    {
      dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
  }
};

```

Space Optimization
TC = O(N)
SC = O(1)

```
class Solution
{
public:
  int fib(int n)
  {
    int prev2 = 0, prev = 1, curr = 0;
    for (int i = 2; i < n; i++)
    {
      curr = prev + prev2;
      prev2 = prev;
      prev = curr;
    }
    return prev;
  }
}
```
