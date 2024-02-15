
// longest arithmetic subarrays

#include <iostream>
using namespace std;

int sol(int a[], int n)
{
    int ans = 2;
    int pd = a[1] - a[0];
    int j = 2;
    int curr = 2;

    while (j < n)
    {
        if (pd == a[j] - a[j - 1])
        {
            curr++;
        }
        else
        {
            pd = a[j] - a[j - 1];
            curr = 2;
        }
        ans = max(ans, curr);
        j++;
    }
}

int main()
{
    int arr[] = {10, 7, 4, 6, 8, 10, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << sol(arr, n) << endl;
    return 0;
}