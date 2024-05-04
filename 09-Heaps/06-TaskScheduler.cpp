#include <bits/stdc++.h>
using namespace std;

/* Task Scheduler :
    Using heaps greedily:

      1. create a map and store the occurrences of each character
      2. put the values of the map into a max heaps.

        we initilize max heap so that we can get the char with highest occurrences first

      3. now take n+1 elements from the pq until it is not empty.

          1. if(pq is not empty)
              1. get freq by getting the top element of the pq
              2. since its getting marked, decrease its value and push
                 it back to a temp array

      4. loop over temp array and push its value back to heap
      5. if pq is empty
          time = time + tmp.size()
         else
          time += n+1

      return time;

TC = O(n)

 */

int leastInterval(vector<char> &tasks, int n)
{
  vector<int> mp(26, 0);
  for (char &ch : tasks)
  {
    mp[ch - 'A']++;
  }

  priority_queue<int> pq;
  for (int i = 0; i < 26; i++)
  {
    if (mp[i] > 0)
      pq.push(mp[i]);
  }

  int time = 0;
  while (!pq.empty())
  {
    vector<int> tmp;
    for (int i = 1; i <= n + 1; i++)
    {
      if (!pq.empty())
      {
        int freq = pq.top();
        pq.pop();
        freq--;
        tmp.push_back(freq);
      }
    }

    for (int &f : tmp)
    {
      if (f > 0)
        pq.push(f);
    }
    if (pq.empty())
    {
      time += tmp.size();
    }
    else
      time += (n + 1);
  }
  return time;
}
int main()
{
  vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
  int n = 2;
  cout << leastInterval(tasks, n);
  return 0;
}