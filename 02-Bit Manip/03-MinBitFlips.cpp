class Solution
{
private:
   int countSetBits(int n)
   {
      int cnt = 0;
      for (int i = 0; i < 32; i++)
      {
         if (n & (1 << i))
            cnt++;
      }
      return cnt;
   }

public:
   /*  TC = log (start ^ goal) */
   int minBitsFlip(int start, int goal)
   {
      int ans = start ^ goal;
      return countSetBits(ans);
   }
}