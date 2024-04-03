#include <bits/stdc++.h>
using namespace std;

int longestOnes(vector<int> arr, int k)
{
  int i = 0, j;
  for (j = 0; j < arr.size(); j++)
  {
    if (arr[j] == 0)
      k--;
    if (k < 0 && arr[i++] == 0)
      k++;
  }
  return j - i;
}

int main()
{
  vector<int> arr = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
  cout << longestOnes(arr, 2);

  return 0;
}