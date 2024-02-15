#include <iostream>
using namespace std;

void bubble_sort(int arr[], int n)
{
    int ctr = 1;
    while (ctr < n)
    {
        for (int i = 0; i < n - ctr; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
        ctr++;
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
    bubble_sort(arr, n);
    return 0;
}