class Solution
{
   /* Brute Force:  O(N)
         for i == 1...N
            res = res ^ i;
   */
   int xor_n(int n)
   {
      int res = 0;
      for (int i = 1; i < n; i++)
      {
         res = res ^ i;
      }
      return res;
   }

   /* Optimal Approach: O(1)

         n % 4      ans

            1        1
            2        N+1
            3        0
            0        N
   */

   int solve(int n)
   {
      if (n % 4 == 1)
         return 1;
      else if (n % 4 == 2)
         return n + 1;
      else if (n % 4 == 3)
         return 0;
      else
         return n;
   }

   /* follow up ques : find xor of n (L--> R)

         we can use find in O(1) using our last approach:
            first find until L-1 and take XOR with R
   */
   int xor_L2R(int L, int R)
   {
      return solve(L - 1) ^ solve(R);
   }
};