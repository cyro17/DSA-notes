class Solution
{
public:
   string convert2Binary(int n)
   {
      string res = "";
      while (n)
      {
         if (n & 1)
            res += '1';
         else
            res += '0';
         n /= 2;
      }
      reverse(res.begin(), res.end());
      return res;
   }

   int convert2Decimal(string s)
   {
      int pow2 = 1, num = 0;
      for (int i = 0; i < s.size(); ++i)
      {
         if (s[i] == '1')
            num += pow2;
         pow2 *= 2;
         --
      }
      return num;
   }
};