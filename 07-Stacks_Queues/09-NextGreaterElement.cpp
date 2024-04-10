#include <bits/stdc++.h>
using namespace std;

/* Brute force: using two nested loop: O(N ^ 2) approach */

/* optimal approach: using stack  : O(N)

    1. loop over to 2n size of array ( to make it a circular array)
    2. check if stack is not empty :
        1. if not empty and top element is less than the curr index element => remove the element
    3. for first half of the array :
        1. update the nge[i] = top element of the array
        2. push the element into the stack
*/
class Solution
{
public:
  vector<int> nextGreaterElements(vector<int> &nums)
  {
    int n = nums.size();
    vector<int> nge(n, -1);
    stack<int> st;
    for (int i = 2 * n - 1; i >= 0; i--)
    {
      while (!st.empty() && st.top() <= nums[i % n])
      {
        st.pop();
      }

      if (i < n)
      {
        if (!st.empty())
          nge[i] = st.top();
      }
      st.push(nums[i % n]);
    }
    return nge;
  }
};
int main()
{
  Solution obj;
  vector<int> v{5, 7, 1, 2, 6, 0};
  vector<int> res = obj.nextGreaterElements(v);
  cout << "The next greater elements are" << endl;
  for (int i = 0; i < res.size(); i++)
  {
    cout << res[i] << " ";
  }
}

Output: