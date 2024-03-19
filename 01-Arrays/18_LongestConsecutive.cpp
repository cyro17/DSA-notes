/* Brute force:
      TC = n^2
      SC = 1
    */
class Solution
{
private:
   bool ls(vector<int> &arr, int num)
   {
      int n = arr.size();
      for (int i = 0; i < n; ++i)
      {
         if (arr[i] == num)
            return 1;
      }
      return 0;
   }

public:
   int longestConsecutive(vector<int> &a)
   {
      int n = a.size();
      if (n == 0)
         return 0;

      sort(a.begin(), a.end());
      int last_smaller = INT_MIN;
      int cnt = 0;
      int longest = 1;

      for (int i = 0; i < n; ++i)
      {
         if (a[i] - 1 == last_smaller)
         {
            cnt++;
            last_smaller = a[i];
         }
         else if (a[i] != last_smaller)
         {
            cnt = 1;
            last_smaller = a[i];
         }
         longest = max(longest, cnt);
      }
      return longest;
   }
};

/* Better Approach: Using Sorting

   TC = O(NlogN) + O(N)
   SC = 1
*/

class Solution
{
   int longestSuccessiveElements(vector<int> &a)
   {
      int n = a.size();
      if (n == 0)
         return 0;

      // sort the array:
      sort(a.begin(), a.end());
      int lastSmaller = INT_MIN;
      int cnt = 0;
      int longest = 1;

      // find longest sequence:
      for (int i = 0; i < n; i++)
      {
         if (a[i] - 1 == lastSmaller)
         {
            // a[i] is the next element of the
            // current sequence.
            cnt += 1;
            lastSmaller = a[i];
         }
         else if (a[i] != lastSmaller)
         {
            cnt = 1;
            lastSmaller = a[i];
         }
         longest = max(longest, cnt);
      }
      return longest;
   }
};

/* Optimal Approach:
      TC =  O(N) + O(2*N) ~ O(3*N)
             O(N) for putting all the elements into the set data structure. After that for every starting element,
             we are finding the consecutive elements. Though we are using nested loops, the set will be traversed
             at most twice in the worst case.
             So, the time complexity is O(2*N) instead of O(N^2).

      SC = N
*/
class Solution
{
   nt longestSuccessiveElements(vector<int> &a)
   {
      int n = a.size();
      if (n == 0)
         return 0;

      int longest = 1;
      unordered_set<int> st;
      // put all the array elements into set:
      for (int i = 0; i < n; i++)
      {
         st.insert(a[i]);
      }

      // Find the longest sequence:
      for (auto it : st)
      {
         // if 'it' is a starting number:
         if (st.find(it - 1) == st.end())
         {
            // find consecutive numbers:
            int cnt = 1;
            int x = it;
            while (st.find(x + 1) != st.end())
            {
               x = x + 1;
               cnt = cnt + 1;
            }
            longest = max(longest, cnt);
         }
      }
      return longest;
   }
};