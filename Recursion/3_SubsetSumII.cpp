// Leetcode 90

class Solution {
public:
    void util(int i, vector<int> ds, vector<int>& arr, set<vector<int>> &set, vector<vector<int>> res){
        if(i == arr.size()){
            sort(ds.begin(), ds.end());
            set.insert(ds);
            return;
	}
        ds.push_back(arr[i]);
        util(i+1, ds, arr, set, res); 
        ds.pop_back();   // backtrack
        util(i+1, ds, arr, set, res); 
        }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> ds;
        set<vector<int>> set; 

        util(0, ds, nums, set, res);
        for(auto it = set.begin(); it!= set.end(); it++){
            res.push_back(*it);
        }
        return res;
    }
};