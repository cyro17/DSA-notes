// find the smallest positive missing number

#include <iostream>
using namespace std;

int sol(int a[], int n)
{
    const int N = 1e6 + 2;
    bool check[N];
    for (int i = 0; i < N; i++)
    {
        check[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (a[i] >= 0)
            check[a[i]] = 1;
    }

    int ans = -1;

    for (int i = 0; i < N; i++)
    {
        if (check[i] == false)
        {
            ans = i;
            break;
        }
    }
    return ans;
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

    cout << sol(arr, n) << endl;
    return 0;
}