
// Given unsorted array A of size N of non-negative integers,
// find a continuous subarray which adds to a given number S.
// t.c = n log n

#include <iostream>
using namespace std;

void sol(int a[], int n, int s)
{
    int l = 0;
    int r = 0;
    int curr = 0;
    int st = -1;
    int end = -1;

    while (r < n && curr <= s)
    {
        curr += a[r];
        r++;
    }
    if (curr == s)
    {
    }
}

int main()
{
    int arr[] = {1, 5, 3, 8};
    int l = sizeof(arr) / sizeof(arr[0]);
    sol(arr, l, 8);
    return 0;
}
