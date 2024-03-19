/*
   [2, 2, 2, 3, 4, 4, 4] ==> return 3
 */

/* Approach 1 : count no of occ of each bit position
                  if (cnt % 3 == 1) set that bit

         TC = O(N*32)
         SC = 1
 */

class Solution
{
public:
   int singleNumber(vector<int> &arr)
   {
      int n = arr.size(), ans = 0;
      for (int bitIndex = 0; bitIndex < 32; ++bitIndex)
      {
         int cnt = 0;
         for (int i = 0; i < n; ++i)
         {
            if (arr[i] & (1 << bitIndex))
               cnt++;
         }
         if (cnt % 3 == 1)
         {
            ans = ans | (1 << bitIndex); // set that bit
         }
      }
      return ans;
   }

   /* Using Middle Pointer : TC = NlogN + N/3
         1. sort the array
   1     2. start loop from 1...N , steps = 3 (jumping on the middle points)
         3. if arr[i] != arr[i-1]
                  return arr[i-1]
         4. return arr[n-1]
   */
   int singleNumber_(vector<int> &arr)
   {
      sort(arr.begin(), arr.end());
      for (int i = 1; i < N; i++)
      {
         if (arr[i] != arr[i - 1])
            return arr[i - 1];
      }
      return arr[n - 1];
   }

   /* USing concept of buckets :

         arr[i] will go to ones if not in twos
                will go to twos if it is already in ones
                will go to three if it is in already in twos
    */
   int singleNumber_(vector<int> &arr)
   {
      int ones = 0, twos = 0;
      for (int i = 0; i < n; i++)
      {
         ones = (ones ^ arr[i]) & ~twos;
         twos = (twos ^ arr[i]) & ~ones;
      }
      return ones;
   }
};