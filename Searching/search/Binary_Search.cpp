#include <iostream>
using namespace std;

int binarySearch(int arr[], int n, int k)
{
    int s = 0;
    int e = n;
    while (s <= e)
    {
        int mid = (s + e) / 2;
        if (arr[mid] == k)
            return mid;
        else if (arr[mid] > k)
        {
            e = mid - 1;
        }
        else
            s = mid + 1;
    }
    return -1;
}

int main()
{
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << binarySearch(arr, n, 40) << endl;
    return 0;
}