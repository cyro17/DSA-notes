#include "bits/stdc++.h"
#define ll long long
using namespace std;

long long max_sum(int *arr, int n)
{
    long long max_s = INT_MIN;
    long long cur = 0;
    for (int i = 0; i < n; i++)
    {
        cur = cur + arr[i];
        if (cur > max_s)
            max_s = cur;
        if (max_s < 0)
            cur = 0;
    }
    return max_s;
}

int main()
{
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    cout << max_sum(arr, 8);
    return 0;
}