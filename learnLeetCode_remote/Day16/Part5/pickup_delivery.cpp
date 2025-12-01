#include <bits/stdc++.h>
using namespace std;

// LC 1359 — Count All Valid Pickup and Delivery Options
// Answer = prod_{i=1..n} i * (2*i - 1) mod 1e9+7

static const long long MOD = 1'000'000'007LL;

int countOrders(int n){
    long long ans = 1;
    for (int i=1;i<=n;++i){
        ans = (ans * i) % MOD;
        ans = (ans * (2LL*i - 1)) % MOD;
    }
    return (int)ans;
}

int main(){
    cout << countOrders(3) << "\n"; // 90
    return 0;
}
