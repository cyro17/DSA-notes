

Task Scheduler :
    Brute Force approach: O(N^2)

```
int leastInterval(vector<char>& arr, int n) {
    
    int total = arr.size();
    int* freq = new int[26];

    for(char c : arr)
        freq[c - 'A']++;

    int time = 0;
    int* nextavail = new int[26];

    while(total > 0){
        // get the currently avaialble task
        vector<int> avail;
        for(int i = 0; i< 26; i++){
            if(freq[i] > 0 && nextavail[i] <= time)
                avail.push_back(i);
        }

        if(!avail.empty()){
            int chosen = avail[0];
            for(int index: avail){
                if(freq[index] > freq[chosen])
                    chosen = index;
            }

            freq[chosen]--;
            total--;
            nextavail[chosen] = time + n + 1;

        }
        time++;
    }
    return time;
}
```
Java code 
```

        int total = arr.length;
        int[] freq  = new int[26];
        for(char c: arr) freq[c-'A']++;

        int time = 0;
        int[] nextAvailable = new int[26];

        while(total> 0){
            ArrayList<Integer> available = new ArrayList<>();
            for (int i = 0; i < 26; i++) {
                if(freq[i] > 0 && nextAvailable[i] <= time) {
                    available.add(i);
                }
            }

            if(!available.isEmpty()){
                int chosen = available.getFirst();
                for(int index : available){
                    if(freq[index] > freq[chosen]) chosen = index;
                }

                freq[chosen]--;
                total--;
                nextAvailable[chosen] = time + n + 1;

            }
            time++;
        }
        return time;
    }
```
```

    Using heaps greedily:

      1. create a map and store the occurrences of each character
      2. put the values of the map into a max heaps.

        we initilize max heap so that we can get the char with highest occurrences first

      3. now take n+1 elements from the pq until it is not empty.

          1. if(pq is not empty)
              1. get freq by getting the top element of the pq
              2. since its getting marked, decrease its value and push
                 it back to a temp array

      4. loop over temp array and push its value back to heap if the value if > 0
      5. if pq is empty
          time = time + tmp.size()
         else
          time += n+1

      return time;

TC = O(n)

```

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

```

# Java Solution 

```
public int leastInterval(char[] arr, int n) {

        int total = arr.length;
        ArrayList<Integer> freqMap = new ArrayList<>(Collections.nCopies(26, 0));
        for(char c : arr)
            freqMap.set(c-'A', freqMap.get(c-'A')+1);

        PriorityQueue<Integer> pq = new PriorityQueue<>((a, b)-> b - a);
        for(int f: freqMap)
            if(f > 0) pq.offer(f);

        int time = 0;
        while(!pq.isEmpty()){
            ArrayList<Integer> temp = new ArrayList<>();

            for (int i = 1; i <= n + 1; i++) {
                if(!pq.isEmpty()){
                    int freq = pq.peek(); pq.poll();
                    freq--;
                    temp.add(freq);
                }
            }
            for(int i: temp){
                if(i > 0) pq.offer(i);
            }
            if(pq.isEmpty()) time += temp.size();
            else time += (n + 1);
        }

        return time;
}

```
