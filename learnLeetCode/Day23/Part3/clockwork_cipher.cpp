#include <bits/stdc++.h>
using namespace std;

// The Clockwork Cipher
// Try all targets 0..11 and all rotations; for each, count positive rises in the rotated inc array.

int min_ops_to_uniform(const vector<int>& gears){
    int n = (int)gears.size(); if(n==0) return 0;
    int best = INT_MAX;
    for(int t=0;t<12;++t){
        vector<int> inc(n);
        for(int i=0;i<n;++i){ inc[i] = (t - gears[i]) % 12; if(inc[i]<0) inc[i]+=12; }
        for(int r=0;r<n;++r){
            int ops=0, prev=0;
            for(int i=0;i<n;++i){
                int x = inc[(r+i)%n];
                if(x>prev) ops += x - prev;
                prev = x;
            }
            best = min(best, ops);
        }
    }
    return best;
}

int main(){
    cout << min_ops_to_uniform({3,5,7,1}) << "\n"; // expect 8
    return 0;
}
