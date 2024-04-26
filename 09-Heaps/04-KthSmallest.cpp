#include <bits/stdc++.h>
using namespace std;

/*
 brute force:
      1. sort the array
      2. return arr[k-1]

the max heap of size k consist of all the smaller element in the array
and root node of the heap is the kth smallest element in the array.

optimized:
      1. build max heap of size k
      2. for rest of the elements , compare if element is smaller than heap's top element
        1. if smaller then replace it with the root element

 */

int KthSmallest(vector<int> &arr, int k)
{
  priority_queue<int> pq;
  for (int i = 0; i < k; i++)
  {
    pq.push(arr[i]);
  }
  for (int i = k; i < arr.size(); i++)
  {
    if (arr[i] < pq.top())
    {
      pq.pop();
      pq.push(arr[i]);
    }
  }
  return pq.top();
}

int main()
{

  return 0;
}