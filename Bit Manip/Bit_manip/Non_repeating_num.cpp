#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> fun(vector<int> vec)
{
    vector<int> ans;
    int n = vec.size();
    // sort(vec.begin(), vec.end());
    int XOR = vec[0];
    for (int i = 1; i < n; i++)
    {
        XOR = XOR ^ vec[i];
    }
    int right_bit = XOR & ~(XOR - 1);

    int m = 0, p = 0;
    for (int i = 0; i < n; i++)
    {
        if (vec[i] & right_bit)
            m = m ^ vec[i];
        else
            p = p ^ vec[i];
    }
    ans.push_back(m);
    ans.push_back(p);
    sort(ans.begin(), ans.end());
    return ans;
}

vector<int> fun1(int arr[], int n, int x)
{
    vector<int> res;
    int s = 0;
    int f = 1;
    while (f <= n)
    {
        while (arr[s] != x)
        {
            s++;
            f++;
        }

        while (arr[f] == x)
        {
            f++;
        }
    }
    res.push_back(s);
    res.push_back(f - 1);
    return res;
}

int main()
{

    // vector<int> v{1, 2, 3, 2, 1, 4};
    // vector<int> res = fun(v);
    // for (auto i : res)
    //     cout << i << " ";

    return 0;
}