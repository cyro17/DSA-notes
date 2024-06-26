recursive approach

- here we use pick and non-pick method as used in recurion
- if the element is picked :
  add the element and pass on recursion to index - 2, skipping the prev element.
- if the element is not picked :
  add 0 since the element is not picked and pass on recursion to index - 1.

TC = O(2 ^ N)
SC = O(N) , stack space is used

```
class Solution
{
  int util(int index, vector<int> &arr)
  {
    if (index == 0)
      return arr[index];
    if (index < 0)
      return 0;

    int pick = arr[index] + util(index - 2, arr);
    int non_pick = 0 + util(index - 1, arr);

    return max(pick, non_pick);
  }

public:
  int solve(vector<int> &nums)
  {
    int n = nums.size();
    return util(n - 1, nums);
  }
};

```

Optimizing using memoization

figuring out whether there is any overlapping sub problem , if there is then we can memoize it

TC = O(N)
SC = O(N ) + O(N) , stack space and dp aray

```

class Solution
{
int util(int index, vector<int> &arr, vector<int> &dp)
{
if (index == 0)
return arr[index];
if (index < 0)
return 0;

    if (dp[index] != -1)
      return dp[index];

    int pick = arr[index] + util(index - 2, arr, dp);
    int non_pick = 0 + util(index - 1, arr, dp);

    return dp[index] = max(pick, non_pick);

}

public:
  int rob(vector<int> &nums){
    int n = nums.size();
    vector<int> dp(n, -1);
    return util(n - 1, nums, dp);
  }
};

```

space optimization

using three pointers : prev2, prev and curr - prev2 holds max sum of adj element until index - 2 - prev holds max sum of adj element until index - 1 - curr is the max value of pick and non pick

update prev2 as prev , prev as curr

TC = O(N)
SC = O(1)

```
class Solution{
public:
  int rob(vector<int> &arr){
    int n = arr.size();
    int prev2 = 0, prev = arr[0];
    for (int i = 1; i < n; i++){
      int non_pick = 0 + prev;
      int pick = arr[i];
      if (i > 1)
        pick += prev2;

      int curr = max(pick, non_pick);
      prev2 = prev;
      prev = curr;
    }
  return prev;
  }
};
```

follow up question : array is circular

```
class Solution
{
private:
  int util(vector<int> &arr){
    int n = arr.size();
    int prev = arr[0];
    int p2 = 0;

    for (int i = 1; i < n; ++i){
      int pick = arr[i];
      if (i > 1)
        pick += p2;

      int non_pick = 0 + prev;
      int curr = max(pick, non_pick);

      p2 = prev;
      prev = curr;
    }
    return prev;

}

public:
  int robStreet(vector<int> &arr){
    int n = arr.size();
    vector<int> arr1, arr2;
    if (n == 1)
      return arr[0];
    for (int i = 0; i < n; ++i){
      if (i != 0)
        arr1.push_back(arr[i]);
      if (i != n - 1)
      arr1.push_back(arr[i]);
    }
    int ans1 = solve2(arr1);
    int ans2 = solve2(arr2);
    return max(ans1, ans2);
  }
};
```
