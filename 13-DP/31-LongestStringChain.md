```
class Solution {
private:
    bool check(string &s1, string &s2){
        if(s1.length() != s2.length() + 1) return 0;

        int p1=0, p2 = 0;
        while(p1 < s1.size()){
            if(s1[p1] == s2[p2]){
                p1++;
                p2++;
            }
            else p1++;
        }
        if(p1 == s1.size() && p2 == s2.size()) return 1;
        return 0;
    }

    static bool cmp(string &s1, string &s2){
        return s1.size() < s2.size();
    }
public:
    int longestStrChain(vector<string>& arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end(), cmp);
        vector<int> dp(n, 1);
        int max_ = 1;
        for(int i = 0; i<n; i++){
            for(int j = 0; j <i; j++){
                if(check(arr[i], arr[j]) && dp[j] + 1 > dp[i]){
                    dp[i] = 1 + dp[j];
                }
            }
            if(dp[i] > max_) max_ = dp[i];
        }
        return max_;
    }
};
```
