#include <bits/stdc++.h>
using namespace std;

// The Mirror Code — flip up to k zero runs; reflection adds up to 1 on each side if outside bit is 0.

int max_ones_with_reflection(const string& s, int k){
    int n = (int)s.size(); if(n==0) return 0;
    vector<pair<int,int>> zr; // [L,R]
    for(int i=0;i<n;){
        if(s[i]=='0'){
            int j=i; while(j+1<n && s[j+1]=='0') ++j; zr.push_back({i,j}); i=j+1;
        }else ++i;
    }
    if(zr.empty()) return n;
    if(k==0){
        int best=0;
        for(int i=0;i<n;){
            if(s[i]=='1'){ int j=i; while(j+1<n && s[j+1]=='1') ++j; best=max(best, j-i+1); i=j+1; }
            else ++i;
        }
        return best;
    }
    int m = (int)zr.size();
    int ans=0; int l=0;
    for(int r=0;r<m;++r){
        while(r-l+1>k) ++l;
        int L=zr[l].first, R=zr[r].second;
        int length = R-L+1;
        if(L-1>=0 && s[L-1]=='0') ++length;
        if(R+1<n && s[R+1]=='0') ++length;
        int a=L-1; while(a>=0 && s[a]=='1'){ ++length; --a; }
        int b=R+1; while(b<n && s[b]=='1'){ ++length; ++b; }
        ans = max(ans, length);
    }
    return min(ans, n);
}

int main(){
    cout << max_ones_with_reflection(string("0101001"), 2) << "\n"; // 5
    return 0;
}
