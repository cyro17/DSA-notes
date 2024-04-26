#include <bits/stdc++.h>
using namespace std;

/*
steps:
  1. build heap from array . starting from right index (non-left node) to the
     first element.
  2. heapify the array and convert it to max heap
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

void buildHeap(vector<int> &arr, int n)
{
  for (int i = n / 2 - 1; i >= 0; i--)
  {
    heapify(arr, n, i);
  }
}

vector<int> min2MaxHeap(vector<int> &arr, int n)
{
  buildHeap(arr, n);
}

int main()
{

  return 0;
}