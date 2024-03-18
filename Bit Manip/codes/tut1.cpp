#include <iostream>
using namespace std;

int getBit(int n, int pos)
{
    return ((n & (1 << pos)) != 0);
}

int setBit(int n, int pos)
{
    return ((n | (1 << pos)));
}

int clearBit(int n, int pos)
{
    int mask = ~(1 << pos);
    return (n & mask);
}

int updateBit(int n, int pos, int value)
{
    int mask = ~(1 << pos);
    n = n & mask;
    return (n | value << pos);
}

bool isPower2(int n)
{
    return (n && !(n & n - 1));
}

int numberOfones(int n)
{
    int count = 0;
    while (n)
    {
        n = n & n - 1;
        count++;
    }
    return count;
}

int main()
{
    // cout << getBit(5, 2);
    // cout << setBit(8, 1);
    // cout << clearBit(5, 2);
    // cout << updateBit(5, 1, 1);
    // cout << (isPower2(7) ? "True" : "False");
    cout << numberOfones(19) << endl;
    return 0;
}