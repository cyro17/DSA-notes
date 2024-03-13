/* Given arr , and k = number
   Find the total no of subarray having bitwise XOR of all the elements.

   eg. arrr = [4 2 2 6 4]
   num = 6

   ans = 4 total no of array having xor = num
*/

/* Brute Force:  Using three loops and finding xor of all the elements combination
      TC = O(N^3)
      SC = O(1)
*/
class Solution
{
public:
   int solve(vector<int> &arr, int num)
   {
      int n = arr.size();
      int cnt = 0;
      for (int i = 0; i < n; ++i)
      {
         for (int j = 0; j < n; ++j)
         {
            int xor_ = 0;
            for (int k = i; k <= j; ++k)
            {
               xor_ = xor_ ^ arr[k];
            }
            if (xor_ == num)
               cnt++;
         }
      }
      return cnt;
   }
};

/* Better Approach: We can optimize the solution into two loops and bring down the complexity to
                     N^2
 */

class Solution
{
public:
   int solve(vector<int> &arr, int num)
   {
      int n = arr.size();
      int cnt = 0;
      for (int i = 0; i < n; ++i)
      {
         int xor_ = 0;
         for (int j = i; j < n; ++j)
         {
            xor_ = xor_ ^ arr[j];
            if (xor_ == num)
               cnt++;
         }
      }
      return cnt;
   }
};

/* Optimal Approach: Using Hash maps
   Time Complexity: O(N) or O(N*logN) depending on which map data structure we are using,
                     where N = size of the array.
   Reason: For example, if we are using an unordered_map data structure in C++ the time complexity
           will be O(N) but if we are using a map data structure, the time complexity will be
           O(N*logN). The least complexity will be O(N) as we are using a loop to traverse the
           array. Point to remember for unordered_map in the worst case, the searching time
           increases to O(N), and hence the overall time complexity increases to O(N2).

Space Complexity: O(N) as we are using a map data structure.
*/

class Solution
{
public:
   int solve(vector<int> &arr, int num)
   {
      int n = arr.size();
      int cnt = 0, xor_ = 0;
      map<int, int> mp;

      mp[xor_] = 1;
      for (int i = 0; i < n; ++i)
      {
         xor_ = xor_ ^ arr[i];
         int x = xor_ ^ num;
         cnt += mp[x];
         mp[xor_]++;
      }

      return cnt;
   }
};