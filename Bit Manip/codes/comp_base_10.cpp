#include <iostream>
#include <math.h>
using namespace std;

int bitwiseComplement(int n)
{
    int m = n;
    int mask = 0;
    if (n == 0)
        return 1;
    while (m != 0)
    {
        mask = (mask << 1) | 1;
        m = m >> 1;
    }
    int ans = mask & (~n);
    return ans;
}

bool isPowerOfTwo(int n)
{
    int ans = 1;
    for (int i = 0; i <= 30; i++)
    {
        if (ans == n)
            return true;
        ans = ans * 2;
    }

    return false;
}

int main()
{
    int res = bitwiseComplement(5);
    bool y = isPowerOfTwo(6);
    cout << y;
    // cout << res;

    return 0;
}