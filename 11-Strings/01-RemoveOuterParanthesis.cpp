/*
iterate over string ,
  1. if char is '(' then increase the opened var
    if there are more than 1 brak
  2. else
 */

class Solution
{
public:
  string removeOuterParentheses(string s)
  {
    string res = "";
    int opened = 0;
    for (auto i : s)
    {
      if (i == '(')
      {
        opened++;
        if (opened > 1)
        {
          res.push_back(i);
        }
      }
      else
      {
        opened--;
        if (opened > 0)
        {
          res.push_back(i);
        }
      }
    }
    return res;
  }
};
