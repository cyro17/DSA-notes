#include <iostream>
#include <vector>
using namespace std;

int first(vector<int> &arr, int key, int n)
{
    int st = 0;
    int end = n - 1;
    int mid = st + (end - st) / 2;

    int res = 0;

    while (st <= end)
    {
        if (key == arr[mid])
        {
            res = mid;
            end = mid - 1;
        }
        else if (key > arr[mid])
            st = mid + 1;
        else
        {
            end = mid - 1;
        }
        mid = st + (end - st) / 2;
    }
    return res;
}

int last(vector<int> &arr, int key, int n)
{
    int st = 0;
    int end = n - 1;
    int mid = st + (end - st) / 2;

    int res = 0;

    while (st <= end)
    {
        if (key == arr[mid])
        {
            res = mid + 1;
            st = mid + 1;
        }
        else if (key > arr[mid])
            st = mid + 1;
        else
        {
            end = mid - 1;
        }
        mid = st + (end - st) / 2;
    }
    return res;
}

int main()
{
    vector<int> arr = {1, 2, 3, 3, 5};
    int f = first(arr, 3, 5);
    int l = last(arr, 3, 5);
    vector<int> res;
    res.push_back(f);
    res.push_back(l);

    for (auto i : res)
        cout << i << " ";

    return 0;
}