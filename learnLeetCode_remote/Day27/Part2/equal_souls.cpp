#include <bits/stdc++.h>
using namespace std;

long long min_diff(int n, const vector<pair<int,int>>& edges, const vector<long long>& power){
    vector<vector<int>> g(n);
    for(auto [u,v]: edges){ --u; --v; g[u].push_back(v); g[v].push_back(u); }
    long long S = 0; for(auto x: power) S += x;
    vector<long long> sub(n,0);
    long long ans = (1LL<<62);
    function<void(int,int)> dfs = [&](int u,int p){
        long long s = power[u];
        for(int v: g[u]) if(v!=p){
            dfs(v,u);
            s += sub[v];
            ans = min(ans, llabs(S - 2*sub[v]));
        }
        sub[u]=s;
    };
    dfs(0,-1);
    return ans;
}

int main(){
    int n=5; vector<pair<int,int>> edges={{1,2},{1,3},{3,4},{3,5}}; vector<long long> power={1,2,3,6,2};
    cout << min_diff(n, edges, power) << "\n"; // Expected 2
    return 0;
}
