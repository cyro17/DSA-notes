#include <iostream>
#include <vector>
using namespace std;

void reverseArray(vector<int> &arr, int m)
{
    int n = arr.size();
    int i = 0;
    int j = n - 1;

    while (i <= j)
    {
        swap(arr[i], arr[j]);
        i++;
        j--;
    }
    // Write your code here.
}

int main()
{
    vector<int> v{1, 2, 3, 4, 5, 6};
    reverseArray(v, 6);

    return 0;
}