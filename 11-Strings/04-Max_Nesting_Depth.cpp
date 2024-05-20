class Solution
{
public:
  int maxDepth(string s)
  {
    int max_ = 0, cnt = 0;

    for (char c : s)
    {
      if (c == '(')
      {
        cnt++;
        max_ = max(max_, cnt);
      }
      if (c == ')')
      {
        cnt--;
        max_ = max(max_, cnt);
      }
    }
    return max_;
  }
};