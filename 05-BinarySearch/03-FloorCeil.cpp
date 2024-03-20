class Solution
{
   pair<int, int> getFloorAndCeil(vector<int> &arr, int n, int x)
   {
      pair<int, int> res;

      // floor = largest nu in arr which is smaller than x
      //  ceil = smallest no in arr which is greater than x

      int floor = -1, ceil = -1;
      int low = 0, high = n - 1;
      while (low <= high)
      {
         int mid = (low + high) / 2;
         if (arr[mid] <= x)
         {
            floor = arr[mid];
            low = mid + 1;
         }
         else
         {
            high = mid - 1;
         }
      }

      low = 0, high = n - 1;

      while (low <= high)
      {
         int mid = (low + high) / 2;
         if (arr[mid] >= x)
         {
            ceil = arr[mid];
            high = mid - 1;
         }
         else
            low = mid + 1;
      }

      res = make_pair(floor, ceil);
      return res;
   }
};