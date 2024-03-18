class Solution
{
public:
   vector<vector<int>> subsets(vector<int> &arr)
   {
      int n = arr.size();
      int subset = 1 << n;
      vector<vector<int>> res;
      for (int num = 0; num < subset; num++)
      {
         vector<int> ans;
         for (int i = 0; i < n; i++)
         {
            if (num & (1 << i))
               ans.push_back(arr[i]);
         }
         res.push_back(ans);
      }
      return res;
   }
};