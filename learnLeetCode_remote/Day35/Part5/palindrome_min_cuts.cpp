#include <bits/stdc++.h>
using namespace std;

int min_cut(const string& s){
    int n = (int)s.size();
    vector<int> cut(n+1);
    for(int i=0;i<=n;++i) cut[i]=i-1; // cut[0]=-1
    for(int c=0;c<n;++c){
        int l=c,r=c; // odd
        while(l>=0 && r<n && s[l]==s[r]){
            cut[r+1] = min(cut[r+1], 1 + cut[l]);
            --l; ++r;
        }
        l=c; r=c+1; // even
        while(l>=0 && r<n && s[l]==s[r]){
            cut[r+1] = min(cut[r+1], 1 + cut[l]);
            --l; ++r;
        }
    }
    return cut[n];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << min_cut(string("aab")) << "\n"; // Expected 1
    return 0;
}
