

```
#include <bits/stdc++.h> 
void heapify(int i, int n, vector<int> &arr){
    int left = 2*i + 1, right = 2*i + 2;
    int max_ = i;

    if(left < n && arr[left] > arr[max_]) max_ = left;
    if(right < n && arr[right] > arr[max_]) max_ = right;

    if(max_ != i){
        swap(arr[max_], arr[i]);
        heapify(max_, n, arr);
    }
}
vector<int> mergeHeap(int n, int m, vector<int> &arr1, vector<int> &arr2) {
    vector<int> res;
    for(auto i : arr1) res.push_back(i);
    for(auto i : arr2) res.push_back(i);

    int l = res.size();
    for(int i = l / 2 - 1 ; i >=0 ; i--){
        heapify(i, l, res);
    }
    return res;
}


```
