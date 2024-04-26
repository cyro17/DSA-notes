#include <bits/stdc++.h>
using namespace std;

/*
 brute force:
      1. sort the array
      2. return arr[n-k]

the min heap of size k consist of all the bigger elements in the array
and root node of the heap is the kth largest element in the array.

optimized:
      1. build min heap of size k
      2. for rest of the elements , compare if element is greater than heap's top element
        1. if greater then replace it with the root element.
      3. the root node of the heap is the kth largest element.

 */

int KthLargest(vector<int> &arr, int k)
{
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < k; i++)
  {
    pq.push(arr[i]);
  }

  for (int i = k; i < arr.size(); i++)
  {
    if (arr[i] > pq.top())
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
(vector<int> &arr, int k)
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