/* leetcode 46
https://leetcode.com/problems/permutations/

Approach -1  : using Recursion
TC -> (n! * n)    'n!' no of perm generated and 'n' loooing over n elements
SC -> O(n) + O(n)  map and ds

steps: 

1. create map of size n and mark it as unvisited.
2. loop over the array
3. if element is unvisited => pur into the ds and mark it as visited.
4. call rec again 
5, backtrack => mark element as unvisited and remove the last element from the ds

 */

class Solution {
public:


    void rec(vector<int> ds, vector<int> &arr, int map[], vector<vector<int>> &res, int n){

        if(ds.size() == n){
            res.push_back(ds);
            return;
        }

        for (int i = 0; i < n; ++i)
        {
            if(!map[i]){
                ds.push_back(arr[i]);
                map[i] = 1;

                rec(ds, arr, map, res, n);

                // backtrack
                map[i] = 0;
                ds.pop_back();
            }
        }

    }

    vector<vector<int>> permute(vector<int>& arr) {
        vector<vector<int>> res;
        vector<int> ds;
        int n = arr.size();
        // create map and mark each element to 0
        int map[arr.size()];
        for (int i = 0; i < n; ++i)
        {
            map[i] = 0;
        }


        rec(ds, arr, map, res, n);
        return res;  
    }
};