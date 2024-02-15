#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> v;
    int n = 3;
    for (int i = 0; i < n; i++)
    {
        v.push_back(i);
    }

    for (auto i : v)
    {
        cout << i << " ";
    }

    return 0;
}