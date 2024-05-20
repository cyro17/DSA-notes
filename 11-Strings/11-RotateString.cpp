class Solution
{
public:
  bool rotateString(string s, string goal)
  {
    string res = s + s;

    if (s.length() == goal.length() && res.find(goal) != string::npos)
      return 1;
    return 0;
  }
};