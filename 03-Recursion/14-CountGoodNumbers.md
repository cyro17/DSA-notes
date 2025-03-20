# Brute Force
> TC = O(N)

```
int countGoodNumbers_(long long n){
    int ans = 1;
    int mod = 1e9 + 7;

    for(int i =0; i<n; i++){
        if(i % 2 == 0) ans = (ans *5) %mod;
        else ans = (ans*4) % mod;
    }
    return ans;
}

```

> Optimized approach: TC = O(log N)

```
int countGoodNumbers(long long n) {
    long long odd = n/2;
    long long even = n/2 + n %2;
    return (power(5, even) * power(4, odd)) % mod;
}

long long power(long long x, long long y){
    if(y == 0) return 1;
    long long ans = power(x, y/2);
    ans *= ans;

    if(y & 1) ans *= x;
    ans %= mod;
    return ans;
}

```
