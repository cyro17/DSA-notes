#include "bits/stdc++.h"

using namespace std;

void d2b(int n)
{
    int ans = 0;
    int i = 0;
    while (n > 0)
    {
        int bit = n & 1;
        ans = (bit * pow(10, i)) + ans;

        n = n >> 1;
        i++;
    }
    cout << ans;
}

void de2bin(int n)
{
    vector<int> v;
    int rem = 0;
    while (n != 0)
    {
        int rem = n % 2;
        v.push_back(rem);
        n /= 2;
    }

    reverse(v.begin(), v.end());
    for (auto i : v)
        cout << i;
}

int main()
{
    int n; // a decimal number
    cin >> n;
    d2b(n);

    return 0;
}