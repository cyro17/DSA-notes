#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  string reverseWords(string s)
  {
    int n = s.size();
    int left = 0, right = 0;
    int i = 0;
    while (i < n)
    {
      // removing leading whitespaces
      while (i < n && s[i] == ' ')
        i++;

      if (i == n)
        break;
      while (i < n && s[i] != ' ')
      {
        s[right++] = s[i++];
      }
      reverse(s.begin() + left, s.begin() + right);
      s[right++] = ' ';
      left = right;
      i++;
    }
    s.resize(right - 1);
    reverse(s.begin(), s.end());
    return s;
  }
};