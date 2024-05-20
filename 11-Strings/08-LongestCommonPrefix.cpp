class Solution
{
public:
  string longestCommonPrefix(vector<string> &strs)
  {
    string pref = strs[0];
    int pref_l = pref.length();

    for (int i = 1; i < strs.size(); i++)
    {
      while (pref != strs[i].substr(0, pref_l))
      {
        pref_l -= 1;
        if (pref_l == 0)
          return "";

        pref = pref.substr(0, pref_l);
      }
    }
    return pref;
  }
};