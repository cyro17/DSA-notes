#include <iostream>

using namespace std;
void swap(int arr[], int i, int j)
{
    if (arr[j] < arr[i])
    {
        int temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
    }
}

void selection_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[i])
                swap(arr, i, j);
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int arr[] = {12, 45, 23, 51, 19, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    selection_sort(arr, n);
    return 0;
}