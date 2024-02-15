
// minimum repeating index

#include <iostream>
#include <climits>
using namespace std;

void sol(int a[], int n)
{
    const int N = 1e6 + 2;
    int idx[N];

    int min_index = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (idx[a[i]] != -1)
            min_index = min(min_index, idx[a[i]]);
        else
            idx[a[i]] = i;
    }

    if (min_index == INT_MAX)
        cout << "-1" << endl;
    else
        cout << min_index + 1 << endl;
}

int main()
{
    int arr[] = {1, 5, 3, 4, 3, 5};
    int l = sizeof(arr) / sizeof(arr[0]);
    sol(arr, l);
    return 0;
}