#include <bits/stdc++.h>
using namespace std;

int main(){
   vector<int> nums = [1,2,3];
   int n = nums.size();

   vector<vector<int>> res;

   for(int num = 0; num<(1<<n); num++){
      vector<int> sub;
      for(int i = 0; i<n; i++){
         if(num & (1<<i)){
            sub.push_back(nums[i]);
         }
      }
      if(sub.size()>=0){
         res.push_back(sub);
      }
   }

   int n = res.size();
   for(auto it : res){  
      
   }
}