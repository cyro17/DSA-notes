```
class Solution {
public:
    int findNumberOfLIS(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp(n, 1);
        vector<int> cnt(n, 1);
        int max_ = -1;

        for(int i = 0; i<n; i++){
            for(int j = 0; j < i; j++){
                if(arr[j] < arr[i] && 1 + dp[j] > dp[i]){
                    dp[i] = 1 + dp[j];
                    cnt[i] = cnt[j];
                }
                else if(arr[j] < arr[i] && 1 + dp[j] == dp[i])
                    cnt[i] += cnt[j];
            }
            max_ = max(max_, dp[i]);
        }

        int ans = 0;
        for(int i = 0; i<n; i++){
            if(dp[i] == max_)
                ans += cnt[i];
        }
        return ans;
    }
};
```
