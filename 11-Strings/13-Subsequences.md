using recursion : pick or dont pick method

TC = O(2 ^ N x N)

SC = O(N)

```
void util(int index, string &s, string &res, vector<string> &ds){
  int n = s.size();

  if(index == n){
    if(!res.empty())
    ds.push_back(res);
    return;
  }
  //pick
  res += s[index];
  solve(index + 1, s, res, ds);

  //dont pick
  res.pop_back();
  solve(index + 1, s, res, ds);

}

vector<string> solve(string &s){
  string res = "";
  vector<string> ds;
  util(0, s, res, ds);
}


```

Using Power Set Method

TC = O(2 ^ N x N)

SC = O(1)

```

vector<string> solve(string &s){
  int n = s.length();
  vector<string> res;
  for(int i = 0; i < (1 << n); i++){
    string tmp = "";
    for(int j = 0; j < n; ++j){
      if(i & (1 << j))
        tmp += s[j];
    }
    if(tmp.length() > 0) res.push_back(tmp);

  }
  return res;
}

```

```
int main(){
  string s = "abc";

  vector<string> ds = solve(s);
  for(string &i: ds) cout<<i<<endl;

  return 0;
}
```
