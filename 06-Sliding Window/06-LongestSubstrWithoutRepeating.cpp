class Solution
{
public:
  int solve(string s)
  {
    /* Brute force :
      TC => O(N^2)
      sc => O(256)

   */
    int n = s.size();
    if (n == 0)
      return 0;
    int max_ = 1;

    // brute force:

    // for (int i = 0; i < n; ++i)
    // {
    //     vector<bool> vis(256, 0);
    //     for (int j = i; j < n; ++j)
    //     {
    //         if(!vis[s[j]]){
    //           max_ = max(max_, j-i+1);
    //           vis[s[j]] = 1;
    //         }
    //         else{
    //           break;
    //         }
    //     }
    //     vis[s[i]] = 0;
    // }

    // optimized:  sliding window O(N)

    int left = 0, right = 0;
    vector<int> hash(256, -1);
    while (right < n)
    {
      if (hash[s[right]] != -1)
      {
        left = max(left, hash[s[right]] + 1);
      }
      hash[s[right]] = right;
      max_ = max(max_, right - left + 1);

      right++;
    }
    return max_;
  }
}
