#include <iostream>
using namespace std;

int count_bits(int x)
{
    int count = 0;
    while (x > 0)
    {
        if (x & 1)
            count++;
        x = x >> 1;
    }
    return count;
}

int utility(int x)
{
}

int main()
{
    int n;
    cin >> n;
    int res;
    for (int i = 1; i <= n; i++)
    {
        res = count_bits(i);
    }

    cout << res << endl;
    return 0;
}