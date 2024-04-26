#include <bits/stdc++.h>
using namespace std;

/* 0 - based indexing:
   parent = i , left = 2*i +1, right = 2*i + 2

   1 - based indexing:
   parent = i , left = 2*i, right = 2*i + 1

   creating heap : TC = O(N)
   insertion     : TC = O (logN)
   deletion     : TC = O (logN)

*/

class MaxHeap
{
public:
  int arr[100];
  int size;
  MaxHeap()
  {
    arr[0] = -1;
    size = 0;
  }

  void insert(int val)
  {
    size++;
    int index = size;
    arr[index] = val;

    while (index > 1)
    {
      int parent_index = index / 2;
      if (arr[parent_index] < arr[index])
      {
        swap(arr[parent_index], arr[index]);
        index = parent_index;
      }
      else
        return;
    }
  }

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

  /*
  deletion :
    1. replace the root node with last node
    2. remove tha last element
    3. heapify the root node
   */

  void delete()
  {
    if (size == 0)
      return;

    // 1. replace the root node with the last element
    arr[0] = arr[size];
    size--;
    // 2. heapify the root node
    heapify(arr, n, 0);
  }
};