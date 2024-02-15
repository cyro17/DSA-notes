#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> pairSum(vector<int> &arr, int s)
{
    vector<vector<int>> res;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] + arr[j] == s)
            {
                vector<int> temp;
                temp.push_back(min(arr[i], arr[j]));
                temp.push_back(max(arr[i], arr[j]));
                // sort(temp.begin(), temp.end());
                res.push_back(temp);
            }
        }
    }
    sort(res.begin(), res.end());
    return res;
}
int main()
{
    vector<int> a = {1, 2, 3, 4, 5};

    vector<vector<int>> res = pairSum(a, 5);
    for (auto i : res)
        for (auto j : i)
            cout << j << " ";

    return 0;
}
