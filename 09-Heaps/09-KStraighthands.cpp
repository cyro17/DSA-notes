#include <bits/stdc++.h>
using namespace std;

/*
Approach 1:
  1. create a frequency map
  2. sort the array 
  3. loop over array 
    1. if not present in map 
      1. get all the combination startig from first card

  TC = N^2
  SC = O(N)
*/
int straightHands(vector<int> &arr, int k){
  int n = arr.size();
  unordered_map<int, int> mp;
  sort(arr.begin(), arr.end());

  for(int &i: arr){
    if(mp[i] == 0) continue;
    for (int j = 0; j < k; ++j)
    {
      int curr = i + j;
      if(!mp[curr]) return 0;
      mp[curr]--;
    }
  }
  return 1;
}

/*
Approach 2: 
  1. create frequency map 
  2. create min heap and insett distinct values
  3. loop over pq 
    1. for top element , check if next two cards are avail
      1. if avail => update map value 
      2. if not => return 0;

  TC = NlogN + N*K

*/

bool straightHands_opt1(vector<int>& arr, int k) {
    int n = arr.size();
    if(n % k) return 0;

    unordered_map<int, int> mp;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < n; ++i)
    {
    // 1. if not present in map then only push into pq
      if(mp.find(arr[i]) == mp.end())
        pq.push(arr[i]);
    // 2. update the frequency of elements in map
      mp[arr[i]]++;
    }

    while(!pq.empty()){
    // 1. get the sequence of cards
      int first = pq.top();
      int min_ = INT_MAX;

    for (int card = first; card <= first + k -1; ++card)
    {
      if(pq.empty() || pq.top() != card)
        return 0;

      pq.pop();
      min_ = min(min_, mp[card]);
    }

    // 2. update the map and pq
    for (int card = first; card <= first + k -1; ++card)
    {
      int val = mp[card];
      mp[card] = val - min_;
      if(val - min_ > 0) 
        pq.push(card);
    }
  }    
  return 1;
}

/*
Approach 3: 
  1. create a frequency map 
  2. sort the array 
  3. loop over each card
    1. if card is in map 
      1. check if next 2 cards is present 
        1. if available, decrease their values in map 
        2. if not then return 0

  TC = NlogN + N*K
*/

int straightHands_opt2(vector<int> &arr, int k){
  int n = arr.size();
  unordered_map<int, int> mp;
  sort(arr.begin(), arr.end());

  for(int &i: arr){
    if(mp[i] == 0) continue;
    for (int j = 0; j < k; ++j)
    {
      int curr = i + j;
      if(!mp[curr]) return 0;
      mp[curr]--;
    }
  }

  return 1;
}


int main(){
  return 0;
}