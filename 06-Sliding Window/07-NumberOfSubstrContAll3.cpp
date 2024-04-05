#include <bits/stdc++.h>
using namespace std;

class Solution
{

  int numberOfSubstrings(string s)
  {

    /*Brute force: */
    int cnt = 0;
    int n = s.size();
    // for (int i = 0; i < n; ++i)
    // {
    //   int hash[3] = {0};
    //   for (int j = i; j < n; ++j)
    //   {
    //     hash[s[j] - 'a'] = 1;

    //     if(hash[0] + hash[1] + hash[2] == 3)
    //       // cnt++;

    //     /*better approach: */
    //       // cnt++ => remove
    //     {
    //       cnt += (n-j);
    //       break;
    //     }

    //   }
    // }

    /* Optimal Approach: */
    vector<int> last_seen(3, -1);
    // int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
      last_seen[s[i] - 'a'] = i;

      // check can be ommitted also
      // if(last_seen[0] != -1 &&
      //    last_seen[1] != -1 &&
      //    last_seen[2] != -1 ){

      cnt += 1 + *min_element(last_seen.begin(), last_seen.end());
      // }
    }
    return cnt;
  }
};

int main()
{
  Solution obj;

  string s = "aabcab";
  cout << obj.numberOfSubstrings(s) << endl;
}