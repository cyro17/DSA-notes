#include <iostream>
#include <set>
using namespace std;

void reverse(int arr[], int n)
{
    int l = 0;
    int r = n - 1;

    while (l <= r)
    {
        swap(arr[l], arr[r]);
        l++;
        r--;
    }

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}

void reverseWord(string &str)
{
    int n = str.length();
    int l = 0;
    int r = n - 1;
    while (l <= r)
    {
        swap(str[l], str[r]);
        l++;
        r--;
    }

    for (int i = 0; i < n; i++)
    {
        cout << str[i] << " ";
    }

    // return str;
}

bool checkdup(int arr[])
{
}
int main()
{
    // int arr[] = {5, 6, 3, 324, 9, -1, 23, 1};
    // int n = sizeof(arr) / sizeof(arr[0]);

    set<int> s{1, 2, 3, 4};
    set<int> t{2, 6, 4};

    set<int> r = s & t;
    for (auto i : r)
        cout << i << " ";

    return 0;
}