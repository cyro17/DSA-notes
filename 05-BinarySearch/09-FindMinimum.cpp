/* Find minimum in sorted array. */
class Solution
{
public:
   int findMin(vector<int> &arr)
   {
      int n = arr.size();
      int low = 0, high = n - 1, min_ = INT_MAX;
      while (low <= high)
      {
         int mid = (low + high) / 2;
         if (arr[low] <= arr[mid])
         {
            min_ = min(min_, arr[low]);
            low = mid + 1;
         }
         else
         {
            min_ = min(min_, arr[mid]);
            high = mid - 1;
         }
      }
      return min_;
   }
};