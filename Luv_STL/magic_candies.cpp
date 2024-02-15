#include <bits/stdc++.h>
using namespace std;

int main(){
    int q;
    cin>>q;
    while(q--){
        int n, k;
        cin>>n>>k;
        multiset<long long> bags;
        for(int i = 0; i< n; i++){
            long long candy_ct;
            cin>>candy_ct;
            bags.insert(candy_ct);
        }
        long long candies_eaten = 0;
        for(int i = 0; i< k; i++){
           auto it = (--bags.end());
           int candy_ct = *it;
           candies_eaten += candy_ct;
           bags.erase(it);
           bags.insert(candy_ct/2);
        }
        cout<<candies_eaten<<endl;   

    }
    return 0;
}