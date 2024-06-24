```
class Solution {
private:
    int util(int index, int prev, vector<int> &arr, vector<vector<int>> &dp){
        int n = arr.size();
        if(index == -1) return 0;

        if(dp[index][prev] != -1) return dp[index][prev];

        // dont pick
        int np = 0 + util(index -1, prev, arr, dp);

        // pick
        int p = INT_MIN;
        if(prev == n || arr[index] < arr[prev])
            p = 1 + util(index -1, index, arr, dp);
        return dp[index][prev] = max(p, np);
    }
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return util(n-1, n, nums, dp);
    }
};
```

> Print LIS

```
class Solution {
  public:
    vector<int> longestIncreasingSubsequence(int n, vector<int>& arr) {
        vector<int> dp(n, 1);
        int max_ = 1;
        for(int i = n-1; i>=0; i--){
            for(int j = i; i <n; i++){
                if(arr[i] < arr[j]){
                    dp[i] = max(dp[i], dp[j] + 1);
                    max_ = max(max_, dp[i]);
                }
            }
        }
        vector<int> res;
        for(int i = 0; i<n; i++){
            if(max_ == dp[i]){
                res.push_back(arr[i]);
                max_--;
            }
        }
        return res;
    }
};

```

> LIS using Binary Search

```
int
```
