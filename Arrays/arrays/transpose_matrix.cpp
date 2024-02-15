#include "bits/stdc++.h"
using namespace std;

int main()
{
    static int m, n;
    cin >> m >> n;
    int arr[m][n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }

    for (int i = 0; i < m; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            // swap
            int temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
        }

    return 0;
}