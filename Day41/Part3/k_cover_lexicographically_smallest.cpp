#include <bits/stdc++.h>
using namespace std;

vector<int> k_cover_lex_smallest(int n, const vector<pair<int,int>>& edges, int k){
    if(k==0) return {};
    vector<vector<int>> adj(n);
    vector<int> deg(n);
    for(auto &e: edges){ adj[e.first].push_back(e.second); adj[e.second].push_back(e.first); deg[e.first]++; deg[e.second]++; }
    for(int d: deg) if(d<k) return {}; // impossible
    vector<int> contrib(n,0); vector<char> selected(n,false);
    for(int v=0; v<n; ++v){
        bool need=false;
        for(int u: adj[v]) if(contrib[u] < k){ need=true; break; }
        if(!need && contrib[v] >= k) continue;
        selected[v]=true;
        for(int u: adj[v]) contrib[u]++;
    }
    for(int v=0; v<n; ++v){
        if(contrib[v] < k){
            for(int u: adj[v]) if(!selected[u]){ selected[u]=true; for(int w: adj[u]) contrib[w]++; }
            if(contrib[v] < k) return {}; // still impossible
        }
    }
    vector<int> ans; for(int i=0;i<n;++i) if(selected[i]) ans.push_back(i);
    return ans;
}

int main(){
    int n=5; vector<pair<int,int>> edges={{0,1},{1,2},{2,3},{3,4},{1,3},{0,2},{2,4}}; int k=2;
    auto res=k_cover_lex_smallest(n,edges,k);
    for(int x: res) cout<<x<<' '; cout<<"\n";
    return 0;
}
