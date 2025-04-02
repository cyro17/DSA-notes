/* 
https://leetcode.com/problems/combination-sum-ii/description/

Given a collection of candidate numbers (candidates) and a target number (target),
find all unique combinations in candidates where the candidate numbers sum to target.

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
      [
      [1,1,6],
      [1,2,5],
      [1,7],
      [2,6]
]

Each number in candidates may only be used once in the combination.
 */




class Solution {
public:
    void findComb(int ind, int target, vector<int> &arr,vector<vector<int>> &res, vector<int> &ds){
	if(target == 0){
		res.push_back(ds);
		return;
	}

	for(int i = ind; i<arr.size(); i++){
		if( i > ind && arr[i] == arr[i-1])
			continue;
		if(arr[i] > target)
			break;
		ds.push_back(arr[i]);
		findComb(i+1, target-arr[i], arr, res, ds);
		ds.pop_back();
	}
}

vector<vector<int>> combinationSum2(vector<int>& arr, int target) {
	sort(arr.begin(), arr.end());
	vector<vector<int>> res;
	vector<int> ds;
	findComb(0, target, arr, res, ds);
	return res;
}
// 
};
