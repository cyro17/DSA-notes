PS -> Partition array into two subset with equal sum
1 5 11 5 => (5 5 1) (11)

Two subset with equal sum , that means each subset sum is equal to the half of the total array sum
similar to subset sum problem we sovled above , just the target changes to half of the total sum

Recursive approach :

```
class Solution
{
private:
  bool util(int idx, int target, vector<int> &arr){
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
  bool isSubsetSum(vector<int> arr, int sum){
    int n = arr.size(), total = 0;
    for (int i : arr)
      total += i;

    if (total & 1)
      return 0;

    vector<vector<int>> dp(n, vector<int>(total + 1, -1));
    return util(n - 1, total / 2, arr);
  }
};


Memoization Approach



class Solution{
private:
  bool util(int index, int target, vector<int> &arr, vector<vector<int>> &dp){
    if (target == 0)
      return 1;
    if (index == 0)
      return arr[0] == target;
    if (dp[index][target] != -1)
      return dp[index][target];

    bool not_pick = util(index - 1, target, arr, dp);
    bool pick = 0;
    if (arr[index] <= target)
      pick = util(index - 1, target - arr[index], arr, dp);

    return dp[index][target] = pick or not_pick;
}
public:
  bool canPartition(vector<int> &arr){
    int total = 0, n = arr.size();
    for (int i : arr)
      total += i;
    if (total & 1)
      return 0;

    vector<vector<int>> dp(n, vector<int>(total + 1, -1));
    return util(n - 1, total / 2, arr, dp);
  }
};

```

Tabulation Approach

```
class Solution
{
private:
bool findSum(int index, int target, vector<int> &arr)
{
int n = arr.size();

    for (int i = 0; i < n; i++)
      dp[i][0] = 1;
    dp[0][arr[0]] = 1;

    for (int i = 1; i < n; i++)
    {
      for (int j = 1; j <= target; j++)
      {
        bool not_pick = dp[i - 1][target];
        bool pick = 0;
        if (arr[index] <= j)
          pick = dp[i - 1][j - arr[i]];

        dp[index - 1][j] = pick or not_pick;
      }
    }
    return dp[n - 1][target];

}

public:
  bool canPartition(vector<int> &nums){
    int sum = 0;
    for (int i : nums)
      sum += i;
    if (sum & 1)
      return 0;

    int target = sum >> 1;
    vector<vector<int>> dp(n, vector<int>(target, 0));
    int n = nums.size();
    return findSum(n - 1, target, nums);
  }
};

```
