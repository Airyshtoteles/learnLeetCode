#include <bits/stdc++.h>
using namespace std;

// The Abyssal Sequence
// S[0] = 1; S[i] = S[i-1] * (i ^ S[i-1]) mod MOD
// We attempt Floyd cycle detection on S; if a cycle is found, we can jump for large n.
// Otherwise, we cap simulation and report inability for very large n.

static const long long MOD = 1000000007LL;

pair<optional<long long>, string> abyssal_S(unsigned long long n, int cap = 2000000){
    auto next_val = [&](unsigned long long i, long long s){
        long long ns = ( (__int128)s * ((long long)(i ^ (unsigned long long)s)) ) % MOD;
        return make_pair(i+1, ns);
    };
    if(n==0) return {1, "ok"};
    unsigned long long i1=1, i2=1; long long s1 = (1 * (1 ^ 1)) % MOD; long long s2 = s1;
    tie(i2, s2) = next_val(i2, s2);
    int steps=0;
    while(steps < cap && s1 != s2){
        tie(i1, s1) = next_val(i1, s1);
        auto t = next_val(i2, s2);
        tie(i2, s2) = next_val(t.first, t.second);
        ++steps;
    }
    if(steps >= cap){
        if(n <= (unsigned long long)cap){
            unsigned long long i=0; long long s=1;
            while(i<n){ tie(i, s) = next_val(i, s); }
            return {s, "partial"};
        }
        return {nullopt, "no-cycle"};
    }
    // find mu
    unsigned long long mu_i=0; long long mu_s=1;
    unsigned long long it_i=0; long long it_s=1;
    unsigned long long ih_i=i1; long long ih_s=s1;
    while(it_s != ih_s){ tie(it_i, it_s) = next_val(it_i, it_s); tie(ih_i, ih_s) = next_val(ih_i, ih_s); ++mu_i; }
    // find lambda
    unsigned long long lam=1; unsigned long long j_i; long long j_s; tie(j_i, j_s) = next_val(it_i, it_s);
    while(j_s != it_s){ tie(j_i, j_s) = next_val(j_i, j_s); ++lam; }
    if(n < mu_i){ unsigned long long i=0; long long s=1; while(i<n){ tie(i, s) = next_val(i, s); } return {s, "ok"}; }
    unsigned long long k = (n - mu_i) % lam;
    unsigned long long i=0; long long s=1; for(unsigned long long t=0;t<mu_i;++t){ tie(i, s) = next_val(i, s); }
    for(unsigned long long t=0;t<k;++t){ tie(i, s) = next_val(i, s); }
    return {s, "ok"};
}

int main(){
    auto res = abyssal_S(1000);
    if(res.first.has_value()) cout << res.first.value() << "\n"; else cout << "NO-CYCLE" << "\n";
    return 0;
}
