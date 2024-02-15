// Leetcode 78  Subset sum 
/* 
Brute Force => Using Power set 
	t .c  => 2^n * N

uing recursion => 
	t.c => 2^n

*/ 

// m-2
void util_subsetSums(int index, int sum, vector<int> &arr, int n, vector<int> &ans){

	if(index == n){
		ans.push_back(sum);
		return;
	}
	//pick 
	util_subsetSums(index+1, sum + arr[index], arr, n, ans);
	// dont pick
	util_subsetSums(index+1, sum, arr, n, ans);
}

vector<int> subsetSums(vector<int>& nums) {
	vector<int> ans;
	
	int n = nums.size();
	util_subsetSums(0, 0, nums, n, ans);

	return ans;
	
}