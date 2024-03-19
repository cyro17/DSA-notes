
#include <iostream>
using namespace std;

// not optimized
class Solution
{
public:
    // n: input to count the number of set bits
    // Function to return sum of count of set bits in the integers from 1 to n.
    int countSetBits(int n)
    {
        // Your logic here
        int res = 0;
        if (n <= 1)
        {
            return 1;
        }

        for (int j = 1; j <= n; j++)
        {
            res += this->utility(j);
        }
        return res;
    }

    int utility(int n)
    {
        int i = 0;
        int count = 0;
        while (n != 0)
        {
            if (n & 1)
                count++;
            n = n >> 1;
        }
        return count;
    }
};

int main()
{
    int res = Solution().countSetBits(5);
    cout << res;

    return 0;
}