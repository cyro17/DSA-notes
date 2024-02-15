#include "bits/stdc++.h"
using namespace std;

int findPivot(int *arr, int n)
{
    int s = 0, end = n - 1;
    int mid = s + (end - s) / 2;

    while (s < end)
    {
        if (arr[mid] >= arr[0])
            s = mid + 1;
        else
            end = mid;
    }
    mid = s + (end - s) / 2;
}

int main()
{
    int arr[] = {8, 10, 17, 1, 3};
    cout << findPivot(arr, n);

    return 0;
}