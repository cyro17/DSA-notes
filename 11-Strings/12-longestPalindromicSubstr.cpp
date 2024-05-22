class Solution
{
private:
  int util(string s, int left, int right)
  {
    while (left >= 0 && right < s.length() && s[left] == s[right])
    {
      left--;
      right++;
    }
    return right - left - 1;
  }

public:
  string longestPalindrome(string s)
  {
    if (s.empty())
      return "";
    int l = 0, r = 0;

    int start = 0, end = 0, n = s.length();
    for (int i = 0; i < n; ++i)
    {
      int odd = util(s, i, i);
      int even = util(s, i, i + 1);
      int max_ = max(odd, even);

      if (max_ > end - start)
      {
        start = i - (max_ - 1) / 2;
        end = i + max_ / 2;
      }
    }
    return s.substr(start, end - start + 1);
  }
};