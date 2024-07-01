# Minimum Cost to Cut a Stick

```
class Solution {
private:
    int rec(int i, int j, vector<int> &arr,  vector<vector<int>> &dp){
        if(i > j) return 0;

        if(dp[i][j] != -1) return dp[i][j];

        int min_ = INT_MAX;
        for(int idx = i; idx <= j; idx++){
            int cost = arr[j+1] - arr[i-1] +
                    rec(i, idx -1 , a6rr, dp)  + rec(idx + 1, j, arr, dp);
            min_ = min(min_, cost);
        }
        return dp[i][j] = min_;
    }
public:
    int minCost(int n, vector<int>& cuts) {
        int c = cuts.size();
        cuts.push_back(n);
        cuts.insert(cuts.begin(), 0);
        sort(cuts.begin(), cuts.end());
        vector<vector<int>> dp(c+1, vector<int>(c+1, -1));
        return rec(1, c, cuts, dp);
    }
};

```
