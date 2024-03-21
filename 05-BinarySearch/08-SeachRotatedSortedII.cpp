class Solution
{
public:
   bool search(vector<int> &arr, int target)
   {
      int n = arr.size();
      int low = 0, high = n - 1;
      while (low <= high)
      {
         int mid = (low + high) / 2;
         if (arr[mid] == target)
            return 1;

         // case check
         if (arr[low] == arr[mid] && arr[mid] == arr[high])
         {
            low++;
            high--;
            continue;
         }

         if (arr[low] <= arr[mid])
         {
            if (arr[low] <= target && target <= arr[mid])
            {
               high = mid - 1;
            }
            else
            {
               low = mid + 1;
            }
         }
         else
         {
            if (arr[mid] <= target && target <= arr[high])
            {
               low = mid + 1;
            }
            else
               high = mid - 1;
         }
      }
      return 0;
   }
};