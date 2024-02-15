#include <iostream>
using namespace std;

void swap(int &i, int &j)
{
    int temp = i;
    i = j;
    j = temp;
}

void sort012(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (arr[i] > arr[j])
                swap(arr[i], arr[j]);
        }
    }   
}

int main()
{
    int arr[] = {2, 2, 2, 1, 1, 1, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    sort012(arr, n);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}