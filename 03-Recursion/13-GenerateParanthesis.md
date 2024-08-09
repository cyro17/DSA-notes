# Generate all Paranthesis

```
class Solution {
private:
  void util(int left, int right, string &s, vector<string> &res){

    if(left == 0 && right == 0){
      res.push_back(s);
    }

    if(left > right || left <0 || right <0)
      return;

    s.push_back('(');
    util(left -1, right, s, res);
    s.pop_back();

    s.push_back(')');
    util(left, right - 1, s, res);
    s.pop_back();
  }
public:
    vector<string> generateParenthesis(int n) {
        string s = "";
        vector<string> res;
        util(n, n, s, res);
        return res;
    }
};
```
