/*  Using XOR
   swap a with b without using any extra variables

      a = a^ b;
      b = a ^ b;     // b = (a ^ b) ^ b =>  b = a
      a = a ^ b;     // a = a ^ (a ^ b) =>  a = b
 */

// check set bit (Kth)   N & ( 1<<K )

// set Kth bit     N | ( 1 << K )

// clear Kth bit     N & ~ ( 1 << K )

// toggle Kth bit    N ^ ( 1<<K )

// Remove last set bit   N & N-1

/*  check power of 2

   every power of 2 has only 1 set bit


      if( N & N-1 ) == 0  ==> then it is power of 2
 */

/* count number of set bits

      1. using STL function
            __builtin_popcount(n)

   Brute Force:
         keep dividing n until n > 0
         if rem == 1 => increase count
 */
class Solution
{
public:
   int countSetBits(int n)
   {
      int cnt = 0;
      while (n)
      {
         if (n & 1) // odd check => last bit of odd is always 1
            cnt++;
         n = n / 2;
      }
      return cnt;
   }
   /* M - 2
         Keep turning off the right most set bit and increase the counter

         TC = O(no of set bits)
   */
   int countSetBits_(int n)
   {
      int cnt = 0;
      while (n != 0)
      {
         n = n & (n - 1);
         cnt++;
      }
      return cnt;
   }

   int countSetBits_2(int n)
   {
      int cnt = 0;
      for (int i = 0; i < 32; i++)
      {
         if (n & (1 << i))
            cnt++;
      }
      return cnt;
   }
};