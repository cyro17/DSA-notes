#include <iostream>
using namespace std;

void swap(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void sort012(int *arr, int n)
{
    int mid = 0, l = 0;
    int r = n - 1;
    while (mid <= r)
    {
        if (arr[mid] == 0)
        {
            swap(arr, l, mid);
            l++;
            mid++;
        }
        else if (arr[mid] == 1)
        {
            mid++;
        }
        else
        {
            swap(arr, mid, r);
            r--;
        }
    }
}

int main()
{
    int arr[] = {0, 0, 1, 2, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    sort012(arr, n);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}