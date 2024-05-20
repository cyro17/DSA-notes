// User function template for C++

class Solution
{
private:
  int util(string s, int k)
  {
    int cnt = 0, n = s.size();

    int i = 0, j = 0;
    vector<int> freq(26, 0);
    int distinct_count = 0;

    while (j < n)
    {
      freq[s[j] - 'a']++;
      if (freq[s[j] - 'a'] == 1)
        distinct_count++;

      while (distinct_count > k)
      {
        freq[s[i] - 'a']--;
        if (freq[s[i] - 'a'] == 0)
          distinct_count--;
        i++;
      }
      cnt += j - i + 1;
      j++;
    }

    return cnt;
  }

public:
  long long int substrCount(string s, int k)
  {
    return util(s, k) - util(s, k - 1);
  }
};