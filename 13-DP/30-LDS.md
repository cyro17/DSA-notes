```
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp(n, 1), hash(n);

        sort(arr.begin(), arr.end());

        for (int i = 0; i < n; ++i){
            hash[i] = i;
            for(int j = 0; j<i; j++){
                if(arr[i] % arr[j] == 0 && 1 + dp[j] > dp[i]){
                    dp[i] = 1 + dp[j];
                    hash[i] = j;
                }
            }
        }

        int ans = -1, last_index = -1;

        for(int i = 0; i<n ; i++){
            if(dp[i] > ans){
                ans = dp[i];
                last_index = i;
            }
        }

        vector<int> tmp;
        tmp.push_back(arr[last_index]);

        while(hash[last_index] != last_index){
            last_index = hash[last_index];
            tmp.push_back(arr[last_index]);
        }

        reverse(tmp.begin(), tmp.end());
        return tmp;
    }
};
```
