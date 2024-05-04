#include <bits/stdc++.h>
using namespace std;

/*
Approach 1: 
  1. create a copy of array as tmp array.
  2. loop over each elemnts of org array.
    1. initialize rank var = 1 and hash set;
    2. loop over tmp 
      1. if tmp[i] < arr[i] and not present in set => increment rank;
      2. replace arr[i] = rank;

  TC = N^2 
  SC = N
*/
vector<int> replaceRank(vector<int> &arr, int n){
  vector<int> tmp = arr;
  for (int i = 0; i < n; ++i)
   {
     int rank = 1;
     unordered_set<int> st;
     for(auto i: tmp){
      if(i < arr[i] && !st.count(i))
        rank+;

      st.insert(i);
     }
     arr[i] = rank;
   } 
   return arr;
} 

/*
optimize using hash map
  1. create copy of array 
  2. sort tmp array
  3. initialize rank = 1;
  4. loop over each element in tmp
    1. update rank into map if it is not presenet in set and less than curr arr element
  
  TC = n log n


*/

vector<int> replaceRank_(vector<int> &arr, int n){
  vector<int> tmp = arr;
  sort(tmp.begin(), tmp.end());
  unordered_map<int, int> mp;
  int rank = 1;
  for(int &i : tmp){
    if(!mp.count(i)){
      mp[i] = rank;
      rank++;
    }
  }

  for(auto &i: arr)
    i = mp[i];

  return arr;
}


int main(){
  vector<int> arr= {3, 1, 3, 5, 9, 0, 0};
  vector<int> res = replaceRank_(arr, 7);
  for(auto i: res) cout<<i<<" ";  
  return 0;
}