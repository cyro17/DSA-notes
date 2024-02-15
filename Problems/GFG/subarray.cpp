#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> subarraySum(int arr[], int n, long long s)
    {
        int curr_sum = arr[0];
        int start = 0;
        int i = 1;

        while (i <= n)
        {
            if (curr_sum > s && start < i - 1)
            {
            }
        }
    }
};
