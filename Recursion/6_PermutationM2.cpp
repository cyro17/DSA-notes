#include <bits/stdc++.h>
using namespace std;

/* 

M-2 => using Backtracking

   T.C => (N! * N ) 
   S.C => O(1)
      Here we are saving space  as we are not using any DS or map to store any res

 */

class Solution
{
    public:
        void rec(int idx, vector<int> &arr, vector<vector<int>> &res){
            // base condn
            if(idx == arr.size()){
                res.push_back(arr);
                return;
            }

            for (int i = idx; i < arr.size(); i++)
            {
                swap(arr[idx], arr[i]);
                rec(idx+1, arr, res);

                // backtrack
                swap(arr[idx], arr[i]);
            }
        }

        vector<vector<int>> permute(vector<int> &arr) {
            vector<vector<int>> res;
            rec(0, arr, res);
            return res; 
        }
};


int main(){
    Solution obj;
    vector < int > v {1,2,3};
    vector < vector < int >> sum = obj.permute(v);
    cout << "All Permutations are" << endl; 
    for (int i = 0; i < sum.size(); i++) {
        for (int j = 0; j < sum[i].size(); j++)
          cout << sum[i][j] << " ";
        cout << endl;
      }
    return 0;
}   