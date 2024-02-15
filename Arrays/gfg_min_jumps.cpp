
#include <iostream>
using namespace std;

int min_jumps(int *arr, int n)
{
	if (n <= 1)
	{
		return 0;
	}
	if (arr[0] == 0)
		return -1;
	int maxReach = arr[0];
	int step = arr[0];

	int jumps = 1;

	int i = 1;
	for (int i = 1; i < n; ++i)
	{
		if (i == n - 1)
			return jumps;
		maxReach = max(maxReach, i + arr[i]);
		step--;
		if (step == 0)
		{
			jumps++;
			if (i >= maxReach)
				return -1;
			step = maxReach - i;
		}
	}

	return jumps;
}

int main()
{
	int n = 11;
	int arr[] = {
		1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};

	int res = min_jumps(arr, n);
	cout << res << endl;

	return 0;
}