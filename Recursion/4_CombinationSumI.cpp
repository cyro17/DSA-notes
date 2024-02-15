/* 
Recursive Approach

Time Complexity: O(2^t * k) where t is the target, k is the average length
      Assume if you were not allowed to pick a single element multiple times, every element will have
      a couple of options: pick or not pick which is 2^n different recursion calls, also assuming that 
      the average length of every combination generated is k. (to put length k data structure into another 
      data structure)

   Space Complexity: O(k*x), k is the average length and x is the no. of combinations 
*/


class Solution {
public:
    void rec(int ind, int target, vector<vector<int>> &res, vector<int> &ds, vector<int> &arr){

		if(ind == arr.size()){
			if(target==0)
				res.push_back(ds);
			return;
		}

		if(arr[ind] <=target){
			//pick
			ds.push_back(arr[ind]);
			rec(ind, target-arr[ind], res, ds, arr);
			ds.pop_back();
		}
		// dont pick 
		rec(ind+1, target, res, ds, arr);
	}

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> ds;
        rec(0, target, res, ds, candidates);
        return res; 
    }
};