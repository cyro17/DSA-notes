#include "bits/stdc++.h"
// #define int long long

using namespace std;

int merge(int *, int, int, int);

int mergesort(int *arr, int l, int r)
{
    int inv = 0;
    if (l < r)
    {
        int mid = (l + r) / 2;
        inv += mergesort(arr, l, mid);
        inv += mergesort(arr, mid + 1, r);
        inv += merge(arr, l, mid, r);
    }

    return inv;
}

int merge(int *arr, int l, int mid, int r)
{
    int n1 = mid - l + 1;
    int n2 = r - mid;

    int a[n1];
    int b[n2];

    for (int i = 0; i < n1; i++)
    {
        a[i] = arr[i];
    }

    for (int i = 0; i < n2; i++)
    {
        a[i] = arr[i];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (a[i] < b[j])
        {
            a[k] = a[i];
            k++;
            i++;
        }

        else
        {
            a[k] = b[j];
            k++;
            j++;
        }
    }

    while (i < n1)
    {
        a[k] = a[i];
        k++;
        i++;
    }
    while (j < n2)
    {
        a[k] = a[j];
        k++;
        j++;
    }
}

int main()
{
    int arr[] = {3, 5, 6, 9, 1, 2, 7, 8};
    cout << mergesort(arr, 0, 7);

    return 0;
}