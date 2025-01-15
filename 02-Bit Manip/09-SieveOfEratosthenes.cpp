/* list out the prime numbers upto N(given) */

/* Naive Approach :
      Loop over from 1...N:
         check if the numbers are prime or not .

      TC = O(N)^3/2

 */
class Solution
{

private:
   bool isPrime(int n)
   {
      if (n == 0 || n == 1)
         return 0;
      for (int i = 2; i < sqrt(n); ++i)
      {
         if (n % i == 0)
            return 0;
      }
      return 1;
   }

public:
   vector<int> primes(int n)
   {
      vector<int> res;
      for (int i = 1; i < n; ++i)
      {
         if (isPrime(i))
            res.push_back(i);
      }
      return res;
   }
};

/* Using Sieve of Eratosthenes :
      The TC can be optimized to( N log logN)
   algo:

      1. take a hash array of size n+1 and mark it all to true
      2. mark the index with multiples of 2 , 3 and 5 as false
      3. now all the index with flag true are primes, take until N
 */

class Solution_opt
{
   void sieve(int n)
   {
      vector<bool> hash(n + 1, 1);
      for (int i = 2; i <= sqrt(n); i++)
      {
         if (hash[i])
         {
            for (int j = 2 * i; j <= n; j++)
            {
               check[j] = 0;
            }
         }
      }

      vector<int> res;
      for (int i = 2; i <= n; i++)
      {
         if (hash[i])
            res.push_back(i);
      }
      return res;
   }
};
