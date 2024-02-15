#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void rotateMatrix(vector<vector<int>> &a)
{
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        reverse(a[i].begin(), a[i].end());
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            swap(a[i][j], a[j][i]);
        }
    }
}

void disp(vector<vector<int>> &v)
{
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> v;
    int n;
    cin >> n;
    int in;
    for (int i = 0; i < n; i++)
    {
        vector<int> d;
        for (int j = 0; j < n; j++)
        {
            cin >> in;
            d.push_back(in);
        }
        v.push_back(d);
        d.clear();
    }

    // for anticlockise --> 1. reverse the rows
    //                      2. take transpose of the matrix

    rotateMatrix(v);
    disp(v);

    return 0;
}