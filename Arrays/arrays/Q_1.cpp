#include <iostream>
using namespace std;

void subarrrays_sum(int arr[], int n)
{
    int curr = 0;
    for (int i = 0; i < n; i++)
    {
        curr = 0;
        for (int j = 0; j < n; j++)
        {
            curr += arr[j];
            cout << curr << endl;
        }
    }
}

int main()
{

    int arr[] = {12, 45, 23, 51, 19, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    return 0;
}