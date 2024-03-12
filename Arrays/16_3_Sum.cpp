
/*
Given array , return all possible triplets s.t their sum =0
 */

/* Brute Force:
   using 3 loops and check their sum == 0
*/

class Solution
{

   vector<vector<int>> triplet(int n, vector<int> &arr)
   {
      set<vector<int>> st;

      // check all possible triplets:
      for (int i = 0; i < n; i++)
      {
         for (int j = i + 1; j < n; j++)
         {
            for (int k = j + 1; k < n; k++)
            {
               if (arr[i] + arr[j] + arr[k] == 0)
               {
                  vector<int> temp = {arr[i], arr[j], arr[k]};
                  sort(temp.begin(), temp.end());
                  st.insert(temp);
               }
            }
         }
      }

      // store the set elements in the answer:
      vector<vector<int>> ans(st.begin(), st.end());
      return ans;
   }
};

/* Better Approach: Using sets

Time Complexity: O(N2 * log(no. of unique triplets)),
where N = size of the array.
Reason: Here, we are mainly using 3 nested loops. And inserting triplets into the
set takes O(log(no. of unique triplets)) time complexity. But we are not considering the
 time complexity of sorting as we are just sorting 3 elements every time.

Space Complexity: O(2 * no. of the unique triplets) + O(N) as we are using a set data structure
 and a list to store the triplets and extra O(N) for storing the array elements in another set.
*/

vector<vector<int>> triplet(int n, vector<int> &arr)
{
   set<vector<int>> st;

   for (int i = 0; i < n; i++)
   {
      set<int> hashset;
      for (int j = i + 1; j < n; j++)
      {
         // Calculate the 3rd element:
         int third = -(arr[i] + arr[j]);

         // Find the element in the set:
         if (hashset.find(third) != hashset.end())
         {
            vector<int> temp = {arr[i], arr[j], third};
            sort(temp.begin(), temp.end());
            st.insert(temp);
         }
         hashset.insert(arr[j]);
      }
   }

   // store the set in the answer:
   vector<vector<int>> ans(st.begin(), st.end());
   return ans;
}

/* Optimal Approach: Using 3 pointers

   TC => O(NlogN)+O(N2), where N = size of the array.
   SC =>  O(no. of quadruplets),
 */
vector<vector<int>> triplet(int n, vector<int> &arr)
{
   vector<vector<int>> ans;
   sort(arr.begin(), arr.end());
   for (int i = 0; i < n; i++)
   {
      // remove duplicates:
      if (i != 0 && arr[i] == arr[i - 1])
         continue;

      // moving 2 pointers:
      int j = i + 1;
      int k = n - 1;
      while (j < k)
      {
         int sum = arr[i] + arr[j] + arr[k];
         if (sum < 0)
         {
            j++;
         }
         else if (sum > 0)
         {
            k--;
         }
         else
         {
            vector<int> temp = {arr[i], arr[j], arr[k]};
            ans.push_back(temp);
            j++;
            k--;
            // skip the duplicates:
            while (j < k && arr[j] == arr[j - 1])
               j++;
            while (j < k && arr[k] == arr[k + 1])
               k--;
         }
      }
   }
   return ans;
}