/* Return element that appears more than N/2 times

Brute Force:
   use two loops and check whether the selected element appears more than
   n/2 times or not

   TC = N^2
   SC = 1


Better Approach: (Using HashMaps)
   initialize a map ds ;
   iterate over the array and udpate the map ds
   if map value > n/2 => then return the map key

   TC = NlogN   => inserting each element into map takes log N ,  since we have n elements therefore NlogN
   SC = N , since we used map ds
*/

class Solution
{
   int majority_element(vector<int> &arr)
   {
      int n = arr.size();
      map<int, int> mpp;
      for (int i = 0; i < n; i++)
      {
         mpp[arr[i]]++;
      }

      for (auto it : mpp)
         if (it.second > (n / 2))
            return it.first;
   }
   return -1;
};

/*
Optimizeed approach: using Moore's voting Algorithm

   TC = N + N  ; only two loops used one in algo and another in check function
   SC = 1
*/

class Solution
{
private:
   bool check(vector<int> &arr, int el)
   {
      int n = arr.size(), cnt = 0;
      for (int i = 0; i < n; i++)
      {
         if (arr[i] == el)
            cnt++;
      }
      if (cnt > (n / 2))
         return true;
      return false;
   }

public:
   int majorityElement(vector<int> &arr)
   {
      int n = arr.size();
      int cnt = 0, el;
      for (int i = 0; i < n; i++)
      {
         if (cnt == 0)
         {
            cnt = 1;
            el = arr[i];
         }
         else if (arr[i] == el)
            cnt++;
         else
            cnt--;
      }
      return check(arr, el) == 1 ? el : -1;
   }
};