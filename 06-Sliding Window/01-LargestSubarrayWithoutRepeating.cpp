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

TC = O(2N) 
    
class Solution {
    public int lengthOfLongestSubstring(String s) {
         int n = s.length();
    boolean[] hash = new boolean[256];

    int l = 0, r = 0, max_len = 0, len = 0;

    while (r < n){

      while(hash[s.charAt(r)] ){
        hash[s.charAt(l)]= false;
        l++;
      }

      hash[s.charAt(r)] = true;
      max_len = Math.max(max_len, r - l + 1);
      r++;

    }
    return max_len;
    }
}



class Solution {
    public int lengthOfLongestSubstring(String s) {
        int n = s.length();
        int[] hash = new int[256];
        Arrays.fill(hash,-1);

        int l = 0, r = 0, max_len = 0, len = 0;

        while (r < n){

        if(hash[s.charAt(r)] >= l){
            l = Math.max(hash[s.charAt(r)] + 1, l);
        }

        hash[s.charAt(r)] = r;
        max_len = Math.max(max_len, r - l + 1);
        r++;

        }
        return max_len;
    }
}
