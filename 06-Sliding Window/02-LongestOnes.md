

> Brute Force
```

int longestOnes(vector<int> &arr, int k){
    int n = arr.size(), max_ = 0;
    for (int i = 0; i < n; ++i)
    {
        int zeros = 0;
        for (int j = i; j < n; ++j)
        {
            if(arr[j] == 0) zeros++;
            if(zeros<=k)
                max_ = max(max_, j - i + 1);
            else break;
            
        }
    }
    return max_;
}

```

```
int longestOnes(vector<int> arr, int k)
{
  int i = 0, j;
  for (j = 0; j < arr.size(); j++)
  {
    if (arr[j] == 0)
      k--;
    if (k < 0 && arr[i++] == 0)
      k++;
  }
  return j - i;
}

int main()
{
  vector<int> arr = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
  cout << longestOnes(arr, 2);

  return 0;
}
```
