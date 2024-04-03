#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  int characterReplacement(string s, int k)
  {
    vector<int> charCount(26, 0);
    int l = 0, r = 0, maxCharCount = 0;
    for (r = 0; r < s.size(); ++r)
    {
      charCount[s[r] - 'A']++;
      maxCharCount = max(maxCharCount, charCount[s[r] - 'A']);

      if (r - l + 1 - maxCharCount > k)
      {
        charCount[s[l] - 'A']--; // Decrement the count for the character at the l index as it's going out of the window

        l++; // Shrink the window from the l
      }
    }
    return r - l;
  }
};

int main()
{
  Solution obj;
  string s = "ABAB";
  cout << obj.characterReplacement(s, 2);
  return 0;
}