#include <iostream>
using namespace std;

int BinarySearch(int *arr, int n, int k)
{
    int st = 0;
    int end = n - 1;
    int mid = st + (end - st) / 2;

    while (st <= end)
    {
        if (arr[mid] == k)
            return mid + 1;
        else if (k > arr[mid])
            st = mid + 1;
        else
            end = mid - 1;

        mid = st + (end - st) / 2;
    }
    return -1;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int res = BinarySearch(arr, 7, 5);
    cout << res << endl;

    return 0;
}