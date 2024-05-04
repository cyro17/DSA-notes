#include <bits/stdc++.h>
using namespace std;

/*
Brute Force:
  1. create ans array
  2. insert all elements of k arrays into it .
  3. sort the ans array

  TC = (n * k) log (n * k)
  SC = (N * K)


Approach-2 :  USing min-heap

  1. create min heap which contains the first element of all k arrays.
  2. while (heap size > 1 )
    1. insert the top element into ans array  &&
       insert the next element of same array into heap if present.


  TC = (N* K) log K
  SC = N * k
 */

class Node{
public:
  int data, i, j;
  Node(int data, int row, int col)
  {
    this->data = data;
    i = row;
    j = col;
  }
}

class compare{
public:
  bool operator()(Node *a, Node *b)
  {
    return a->data > b->data;
  }
}

vector<int> solve(vector << int >> arr, int k){
  // 1. create a min heap of first elements of each array 
  priority_queue<Node *, vector<Node *>, compare> min_heap;
  for (int i = 0; i < k; ++i)
  {
    Node *tmp = new Node(arr[i][0], i, 0);
    min_heap.push(tmp);
  }

  // 2. unitl there is element in heap , push the top element of the heap to ans array 
  //    and look up if there are more elements in tht same array if, there push it into heap 
  vector<int> ans;
  while(min_heap.size() > 0){
    Node* tmp = min_heap.top();
    ans.push_back(tmp->data);
    min_heap.pop();

    int i = tmp->i;
    int j = tmp->j;

    if(j+1 < arr[i].size()){
      Node* nxt = new Node(arr[i][j], i, j+1);
      min_heap.push(nxt);
    }
  }
  return ans;
}


