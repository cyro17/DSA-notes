class Solution
{
public:
  bool isValid(string s)
  {
    stack<char> st;
    unordered_map<char, int> mp = {
        {'[', -3},
        {'-{', -2},
        {'(', -1},
        {']', 3},
        {'}', 2},
        {')', 1},
    };
    // int n = s.length();

    for (auto i : s)
    {
      if (mp[i] < 0)
        st.push(i);
      else
      {
        if (st.empty())
          return 0;
        char ch = st.top();
        st.pop();
        if (mp[i] + mp[ch] != 0)
          return 0;
      }
    }
    if (st.empty())
      return 1;
    return 0;
  }
};