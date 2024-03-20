/*
https: // leetcode.com/problems/palindrome-partitioning/description/

T.C => 2^n * k * (n/2)              => 2^n  - generating every substring
                                    => k    - inserting palindrome in another ds
                                                k - avg length of palindrome list
                                    => n/2  - check if every substr generated is palindrome

S.C => O(k * x)
         k - avg length of palindrome list
         x - no of palindromes generated in ans list.


using recursive backtrack
1. loop over every index from idx to n.
2. if substr(idx...i) is palindrome
      => then add subs(idx...i) to path
      call rec(idx+1)

      backtrack **impt
      path.pop_back()
3. base case:
   => if idx == n
         add the path to ans vector.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
   vector<vector<string>> partition(string s)
   {
      vector<vector<string>> res;
      vector<string> path;
      util(0, s, path, res);
      return res;
   }

   void util(int idx, string s, vector<string> &path, vector<vector<string>> &res)
   {
      if (idx == s.size())
      {
         res.push_back(path);
         return;
      }

      for (int i = idx; i < s.size(); ++i)
      {
         if (isPalindrome(s, idx, i))
         {
            path.push_back(s.substr(idx, i - idx + 1));
            util(i + 1, s, path, res);

            // backtrack
            path.pop_back();
         }
      }
   }
   bool isPalindrome(string s, int left, int right)
   {
      while (left <= right)
      {
         if (s[left++] != s[right--])
            return false;
      }
      return true;
   }
};