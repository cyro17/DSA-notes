#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> sym = {{'[', -1}, {'{', -2}, {'(', -3},
                                {']', 1}, {'}', 2}, {')', 3} };

string isBalanced(string s) {
    stack<char> st;
    for(char bracket: s){
        if (sym[bracket] < 0) {
            st.push(bracket);
        }
        else{
            if(st.empty())return "NO";
            char top = st.top();
            st.pop();
            if(sym[bracket] + sym[top] != 0){
                return "NO";
            }
        }
    }
    if(st.empty()) return "YES";
    return "NO";
    
}

int main(){
    int t;
    cin>>t;
    while(t--){
        string s = "{[()]}";
        string res = isBalanced(s);
        cout<<res<<endl;
    }
    
    return 0;
}