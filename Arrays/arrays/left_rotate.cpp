
// using BLOCK SWAP algorithm rotate the array to the left

#include <iostream>
using namespace std;

void printArray(int arr[], int size);
void swap(int arr[], int fi, int si, int d);

void leftRotate(int arr[], int d, int n)
{
    if (d == 0 || d == n)
        return;

    if (d > n)
        d = d % n;

    // both A and B of same length
    if (d == n - d)
    {
        swap(arr, 0, n - d, d);
        return;
    }
    // if A is shorter
    if (d < n - d)
    {
        swap(arr, 0, n - d, d);
        leftRotate(arr, d, n - d);
    }
    // if B is shorter
    else
    {
        swap(arr, 0, d, n - d);
        leftRotate(arr + n - d, 2 * d - n, d);
    }
}

void swap(int arr[], int fi, int si, int d)
{
    int temp;
    for (int i = 0; i < d; i++)
    {
        temp = arr[fi + i];
        arr[fi + i] = arr[si + i];
        arr[si + i] = temp;
    }
}
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    leftRotate(arr, 2, 7);
    printArray(arr, 7);
    return 0;
}