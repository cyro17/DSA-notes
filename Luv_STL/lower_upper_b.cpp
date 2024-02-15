#include <bits/stdc++.h>

using namespace std;

int main(){
    vector<int> v = {2, 4, 5, 5, 7, 9, 25};
    auto it  =  upper_bound(v.begin(), v.end(), 7);
    // auto it  =  lower_bound(v.begin(), v.end(), 7);
    cout<<*it<<endl;
    return 0;
}