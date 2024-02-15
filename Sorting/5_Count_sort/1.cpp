#include <iostream>

using namespace std;

void count_sort(int arr[], int n)
{

    //  1. Find the max element in the array
    int k = arr[0];
    for (int i = 0; i < n; i++)
    {
        k = max(k, arr[i]);
    }

    //  2. make a count array of specified size
    int count[10] = {0};
    for (int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }

    //  3. accumulate the count array
    for (int i = 1; i <= k; i++)
        count[i] += count[i - 1];

    int res[n];
    for (int i = n - 1; i >= 0; i--)
        res[--count[arr[i]]] = arr[i];

    for (int i = 0; i < n; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    count_sort(arr, n);

    return 0;
}

// time comp = O(n)
