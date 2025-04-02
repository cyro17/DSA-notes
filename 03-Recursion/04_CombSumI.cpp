/* 
https://leetcode.com/problems/combination-sum/description/

	Given an array of distinct integers candidates and a target integer target,
	return a list of all unique combinations of candidates where the chosen numbers sum to target. 
	You may return the combinations in any order.
	The same number may be chosen from candidates an unlimited number of times.
	Two combinations are unique if the frequency  at least one of the chosen numbers is different.

	Input  : arr = [2,3,6,7], target = 7
	Output : [[2,2,3],[7]]

Recursive Approach

Time Complexity: O(2^t * k) where t is the target, k is the average length
      Assume if you were not allowed to pick a single element multiple times, every element will have
      a couple of options: pick or not pick which is 2^n different recursion calls, also assuming that 
      the average length of every combination generated is k. (to put length k data structure into another 
      data structure)

   Space Complexity: O(k*x), k is the average length and x is the no. of combinations.


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
