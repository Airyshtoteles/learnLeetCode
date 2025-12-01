#include <bits/stdc++.h>
using namespace std;

// The Temple of Shadows
// Assumption: lighting a room sets its darkness to 0.
// Algorithm: SCCs; for SCCs that contain a cycle (size>1 or self-loop),
// if total sum < 0, light the most negative nodes until sum >= 0.

int min_lanterns(int n, const vector<pair<int,int>>& edges, const vector<int>& darkness){
    vector<vector<int>> g(n), gr(n);
    for(auto [u,v]: edges){ --u; --v; g[u].push_back(v); gr[v].push_back(u); }
    vector<int> vis(n,0), order;
    function<void(int)> dfs = [&](int u){
        vis[u]=1;
        for(int v: g[u]) if(!vis[v]) dfs(v);
        order.push_back(u);
    };
    for(int i=0;i<n;++i) if(!vis[i]) dfs(i);
    vector<int> comp(n, -1);
    function<void(int,int)> rdfs = [&](int u, int cid){
        comp[u]=cid;
        for(int v: gr[u]) if(comp[v]==-1) rdfs(v, cid);
    };
    int cid=0;
    for(int i=n-1;i>=0;--i){ int u=order[i]; if(comp[u]==-1) rdfs(u, cid++); }
    vector<vector<int>> vals(cid);
    vector<char> has_cycle(cid, 0);
    vector<int> sz(cid,0);
    for(int i=0;i<n;++i){ vals[comp[i]].push_back(darkness[i]); ++sz[comp[i]]; }
    for(int u=0;u<n;++u){
        for(int v: g[u]) if(comp[u]==comp[v]) has_cycle[comp[u]] = 1;
    }
    int ans=0;
    for(int c=0;c<cid;++c){
        if(!has_cycle[c]) continue; // no directed cycle
        long long s=0; for(int x: vals[c]) s+=x;
        if(s>=0) continue;
        vector<int> negs; for(int x: vals[c]) if(x<0) negs.push_back(x);
        sort(negs.begin(), negs.end()); // most negative first
        for(int x: negs){ s -= x; ++ans; if(s>=0) break; }
    }
    return ans;
}

int main(){
    int n=5; vector<pair<int,int>> edges={{1,2},{2,3},{3,1},{3,4},{4,5}}; vector<int> d={-2,1,-3,2,1};
    cout << min_lanterns(n, edges, d) << "\n"; // 2
    return 0;
}
