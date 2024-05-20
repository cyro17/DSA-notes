class Solution
{
public:
  bool isIsomorphic(string s, string t)
  {
    vector<int> arr(256, -1);
    vector<bool> vis_s(256, 0), vis_t(256, 0);
    for (int i = 0; i < s.length(); i++)
    {
      if (vis_s[s[i]] == 1 || vis_t[t[i]] == 1)
      {
        if (arr[s[i]] != t[i] - 'a')
          return false;
      }
      else
      {
        vis_s[s[i]] = 1;
        vis_t[t[i]] = 1;
        arr[s[i]] = t[i] - 'a';
      }
    }
    return true;
  }
};