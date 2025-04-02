![image](https://github.com/user-attachments/assets/15181e18-4b1e-4766-b423-9f0f19550938)/*   leetcode 78  https://leetcode.com/problems/subsets/
*/

```

class Solution {
public:
    // power set 
    vector<vector<int>> subsets(vector<int>& nums) {
    	int n = nums.size();
    	vector<vector<int>> res; 
        for (int i = 0; i < (1<<n); ++i){

        	vector<int> ds; 
        	for (int j = 0; j < n ; ++j){

                // check if bit is set, if yes then put into ds
                if(i & (1<<j))
                    ds.push_back(nums[j]);
        		
        	}
        	if(ds.size()>=0)	
        		res.push_back(ds);
        }
        sort(res.begin(), res.end());
        return res;
    }
};

```

Recursive Approach : 

![image](https://github.com/user-attachments/assets/2d80f870-36de-4f00-abad-cb4dbc75c844)

```
class Solution {
private:
    void rec(int index, vector<int> &arr, vector<int> &ds, vector<vector<int>> &res){
			if(index == arr.size()){
				res.push_back(ds);
				return;
			}

			//pick 
			ds.push_back(arr[index]);
			rec(index + 1, arr, ds, res);

			// non-pick
			ds.pop_back();
			rec(index + 1, arr, ds, res);
		}
public:
    vector<vector<int>> subsets(vector<int>& arr) {
        vector<vector<int>> res;
			vector<int> ds;
			rec(0, arr, ds, res);
			return res;
    }
};
```
