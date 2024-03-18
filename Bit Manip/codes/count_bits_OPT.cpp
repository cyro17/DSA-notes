#include <iostream>
#include <math.h>
using namespace std;

// optimized solution
//    s(n) = 2^(x-1) + (n-2^x +1) + (n-2^x)

class Solution
{
public:
    int findGreatestPower(int n)
    {
        int x = 0;
        while ((1 << x) <= n)
            x++;
        return x - 1;
    }

    int countSetBits(int n)
    {
        int x = findGreatestPower(n);
        int res = (x * (1 << (x - 1))) + (n - (1 << x) + 1) - (n - (1 << x));
        return res;
    }
};

int main()
{
    int n;
    cin >> n;
    int res = Solution().countSetBits(n);
    cout << res;

    return 0;
}