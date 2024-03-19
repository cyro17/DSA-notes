/*  Kadane's Algorithm

https://practice.geeksforgeeks.org/problems/kadanes-algorithm-1587115620/1
Constraints:
        1 ≤  N   ≤ 10^6
    -10^7 ≤ A[i] ≤ 10^7
*/

#include <iostream>
using namespace std;
const int N = 1e7 + 10;
int arr[N];

class Solution
{

    long long maxSubarraySum(int arr[], int n)
    {
        long long curr = 0;
        long long max_ = INT_MIN;

        for (int i = 0; i < n; i++)
        {
            curr = curr + arr[i];
            max_ = max(curr, max_);
            if (curr < 0)
                curr = 0;
        }
        return max_;
    }
};

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    long long res = maxSubarraySum(arr, N);
    cout << res << endl;
    return 0;
}
