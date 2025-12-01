#include <bits/stdc++.h>
using namespace std;

// The Lost Player IDs
// missing = XOR(1..n) XOR XOR(players with odd participation count in swaps)

int missing_id(int n, const vector<pair<int,int>>& records){
    int xr = 0; for(int i=1;i<=n;++i) xr ^= i;
    vector<int> freq(n+1,0);
    for(auto [a,b]: records){ if(1<=a && a<=n) freq[a]^=1; if(1<=b && b<=n) freq[b]^=1; }
    for(int i=1;i<=n;++i) if(freq[i]) xr ^= i;
    return xr;
}

int main(){
    int n=5; vector<pair<int,int>> rec={{1,2},{3,4},{2,3}};
    cout << missing_id(n, rec) << "\n"; // 5
    return 0;
}
