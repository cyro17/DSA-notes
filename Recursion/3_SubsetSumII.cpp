// Leetcode 90

// Brute Force

/* 
Time Complexity: O( 2^n *(k log (x) )). 2^n  for generating every subset and k* log( x)  
   to insert every combination of average length k in a set of size x.
   After this, we have to convert the set of combinations back into a list of list /vector of vectors 
   which takes more time.

   Space Complexity:  O(2^n * k) to store every subset of average length k. Since we are initially using
   a set to store the answer another O(2^n *k) is also used. 
*/
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


// Optimal Solution 
/* 
Time Complexity: O(2^n) for generating every subset and O(k)  to insert every subset in another data structure
if the average length of every subset is k. Overall O(k * 2^n).

Space Complexity: O(2^n * k) to store every subset of average length k. Auxiliary space is O(n) 
if n is the depth of the recursion tree.
 */

class Solution {
public:

    void util(int ind, vector<int> &arr, vector<int> &ds, vector<vector<int>> &ans){
        ans.push_back(ds);
        for(int i = ind; i<arr.size(); i++){
            if(i!=ind && arr[i] == arr[i-1])
                continue;
            ds.push_back(arr[i]);
            util(i+1, arr, ds, ans);
            ds.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> ds;

        sort(nums.begin(), nums.end());
        util(0, nums, ds, ans);
        return ans;

    }
};
