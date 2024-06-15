# Maximum Product Subarray

#### Using Kadane Algorithm

> iterate over taking the sum from left array and right array simultaneously and keep updating the ans.

```
class Solution {
private:

public:
    int maxProduct(vector<int>& nums) {
     double suff = 1, pre = 1;
      int n = nums.size();
      int res =  INT_MIN;
      for(int i = 0; i<n; i++){
        if(pre == 0) pre = 1;
        if(suff == 0) suff = 1;

        suff = suff * nums[n-i-1];
        pre =  pre * nums[i];
        double tmp = pre > suff ? pre : suff;
        if(tmp > res ) res = tmp;
      }
      return res;
    }
};
```
