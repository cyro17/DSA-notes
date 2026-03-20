#include <bits/stdc++.h>
// TC -> O(N^3) , SC = O(1)

using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int max_ = 0;


        for(int i = 0; i<n; i++){
          for(int j = i; j<n; j++){
            string sub = s.substr(i, j-i + 1);
            if(check(sub)){
              max_ = max(max_, (int)sub.length());
            }
          }
        }
        return max_;

    }
  private: 
    bool check(string s){

      set<char> set;
      for(char c: s){
        if(set.find(c) != set.end())return false;
        set.insert(c);
      }
      return true;
    }
};
