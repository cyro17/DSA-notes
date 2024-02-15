#include <iostream>
using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    int arr[m][n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }

    int row_start = 0, row_end = m - 1;
    int col_start = 0, col_end = n - 1;

    while (row_start <= row_end && col_start <= col_end)
    {
        // row start
        for (int col = col_start; col <= col_end; col++)
        {
            cout << arr[row_start][col] << " ";
        }
        cout << endl;
        row_start++;

        // col end
        for (int row = row_start; row <= row_end; row++)
        {
            cout << arr[row][col_end] << " ";
        }
        cout << endl;
        col_end--;

        // row end
        for (int col = col_end; col >= col_start; col--)
        {
            cout << arr[row_end][col] << " ";
        }
        cout << endl;
        row_end--;

        // col start
        for (int row = row_end; row >= row_start; row--)
        {
            cout << arr[row][col_start] << " ";
        }
        cout << endl;
        col_start++;
    }
    return 0;
}