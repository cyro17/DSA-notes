// Given an array of non - negative integers, and a value sum,
// determine if there is a subset of the given set with sum equal to given sum.

/*
Using recursion
TC = O(2^N)
 */
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

/* Memoization of overlapping subproblems
Time Complexity: O(N*K)

Reason: There are N*K states therefore at max ‘N*K’ new problems will be solved.

Space Complexity: O(N*K) + O(N)

Reason: We are using a recursion stack space(O(N)) and a 2D array ( O(N*K)).

*/

class Solution
{
private:
  bool util(int idx, int target, vector<int> &arr, vector<vector<int>> &dp)
  {
    if (target == 0)
      return 1;
    if (idx == 0)
      return (arr[idx] == target);

    if (dp[idx][target] != -1)
      return dp[idx][target];

    bool not_pick = util(idx - 1, target, arr, dp);
    bool pick = false;
    if (target >= arr[idx])
      pick = util(idx - 1, target - arr[idx], arr, dp);

    return dp[idx][target] = pick || not_pick;
  }

public:
  bool isSubsetSum(vector<int> arr, int sum)
  {
    int n = arr.size(), k = sum;
    vector<vector<int>> dp(n, vector<int>(k + 1, -1));
    return util(n - 1, sum, arr, dp);
  }
};