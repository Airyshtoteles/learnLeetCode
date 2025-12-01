#include <bits/stdc++.h>
using namespace std;

// The Missing Witness
// Score each witness by how supported their statements are by others, plus how many see them.

int missing_witness(int n, const vector<vector<int>>& statements){
    vector<int> cnt(n+1,0);
    for(int i=0;i<n;++i){
        for(int x: statements[i]) if(1<=x && x<=n) cnt[x]++;
    }
    tuple<long long,long long,int> best = {LLONG_MAX, LLONG_MAX, INT_MAX};
    int best_i = -1;
    for(int i=1;i<=n;++i){
        vector<int> cnt_ex = cnt;
        for(int x: statements[i-1]) if(1<=x && x<=n) cnt_ex[x]--; // remove self contribution
        long long s=0; long long zeroes=0;
        for(int x: statements[i-1]){
            int c = (1<=x && x<=n) ? cnt_ex[x] : 0;
            s += c; if(c==0) ++zeroes;
        }
        s += cnt_ex[i];
        auto key = make_tuple(s, -zeroes, i);
        if(key < best){ best = key; best_i=i; }
    }
    return best_i;
}

int main(){
    int n=4; vector<vector<int>> st={{2,3},{1,3},{1,2},{2,4}};
    cout << missing_witness(n, st) << "\n"; // 4
    return 0;
}
