#include <iostream>
#include <limits.h>
using namespace std;

int sumOfMaxMin(int arr[], int n)
{
    // Write your code here.
    int min = INT_MAX;
    int max = INT_MIN;
    for (int i = 0; i < n; i++)
    {

        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
    }

    int s = min + max;
    return s;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6};
    int s = sumOfMaxMin(arr, 6);
    cout << s;

    return 0;
}