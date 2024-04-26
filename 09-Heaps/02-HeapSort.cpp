#include <bits/stdc++.h>
using namespace std;

/*
1. convert the array to a max heap
2. until heap size > 1
    1. swap the first value with the last element
    2. heapify the root value
*/
void heapify(vector<int> &arr, int n, int i)
{
  int index = i, left = 2 * i + 1, right = 2 * i + 2;
  if (left < n && arr[smallest] > arr[left])
    left = index;
  if (right < n && arr[smallest] > arr[right])
    right = index;
  if (index != i)
  {
    swap(arr[index], arr[i]);
    heapify(arr, n, index);
  }
}

void heapSort(int arr[], int n)
{
  int size = n;
  while (size > 1)
  {
    swap(arr[size], arr[i]);
    size--;
    heapify(arr, n, 0);
  }
}

int main()
{
  return 0;
}