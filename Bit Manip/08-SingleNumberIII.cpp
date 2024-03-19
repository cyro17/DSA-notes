/* Single Number III
all numbers are present two times except few numbers , return a list of all such number
   [2, 4, 2, 6,, 3, 7, 7, 3]  => [4, 6]

   Brute Force: using map , count the occurrence of each element using map DS and
                all the map key to answer list which count only one
      TC = logM + M    M = N/2 + 1
      SC = O(M)
 */

class Solution
{
public:
   vector<int> singleNumber(vector<int> &arr)
   {
      map<int, int> mp;
      for (int i = 0; i < arr.size(); ++i)
      {
         mp[arr[i]]++;
      }

      vector<int> res;
      for (auto it : mp)
      {
         if (it.second == 1)
            res.push_back(it.first);
      }
      return res;
   }
};

/* Using bitwise operator (buckets)

   1. take the xor value of all the elements , all double occurring elements will cancel out
      will  be left with xor of numbers which are only occurring once  (say a ^ b = x)

      ( NOTE : Two distict number have atleast 1 bit different. )

   2. get the right most bit of the number x
   3. iterate over the array and check if the right most bit of the number is set
   4. if it is set then put into bucket 1 (b1)
      else into bucket 2 (b2)


      TC = O(2N)
      SC = 1
*/

class Solution_opt
{
public:
   vector<int> singleNumber(vector<int> &arr)
   {
      int n = arr.size();
      long xr = 0;
      for (int i = 0; i < n; ++i)
      {
         xr ^= arr[i];
      }

      int right_bit = (xr & xr - 1) ^ xr;
      int b1 = 0, b2 = 0;

      for (int i = 0; i < n; ++i)
      {
         if (arr[i] & right_bit)
            b1 = b1 ^ arr[i];
         else
            b2 = b2 ^ arr[i];
      }
      return {b1, b2};
   }
};