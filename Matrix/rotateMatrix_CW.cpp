#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void rotateMatrix(vector<vector<int>> &v)
{
    // take transpose first then reverse the rows
    int n = v.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            swap(v[i][j], v[j][i]);

    // reverse
    for (int i = 0; i < n; i++)
        reverse(v[i].begin(), v[i].end());
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
    int val;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        for (int j = 0; j < n; j++)
        {
            cin >> val;
            temp.push_back(val);
        }
        v.push_back(temp);
        temp.clear();
    }

    rotateMatrix(v);
    disp(v);

    return 0;
}