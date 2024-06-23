```
class Solution {
public:
    int maxProfit(vector<int>& arr) {
      int profit = 0, min_ = arr[0], n = arr.size();
      for(int i = 1; i<n ; i++){
        profit = max(profit, arr[i] - min_);
        min_ = min(min_, arr[i]);
      }
      return profit;
    }
};
```
