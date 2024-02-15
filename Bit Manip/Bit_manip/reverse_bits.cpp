#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> v;
    int i = 0;
    int rev = 0;
    int l = floor(log2(n)) + 1;

    cout << l << endl;

    while (n != 0)
    {
        int bit = 1 & n;

    }
    for (auto i : v)
        cout << i << " ";

    cout << rev;
    return 0;
}