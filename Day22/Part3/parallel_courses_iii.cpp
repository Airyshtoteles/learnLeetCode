#include <bits/stdc++.h>
using namespace std;

// LC 2050 — Parallel Courses III
// Topo sort + DP longest time to each node

int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time){
    vector<vector<int>> g(n);
    vector<int> indeg(n,0);
    for(auto &e: relations){ int u=e[0]-1, v=e[1]-1; g[u].push_back(v); ++indeg[v]; }
    queue<int> q;
    vector<int> dist(n, 0);
    for(int i=0;i<n;++i){ if(indeg[i]==0){ q.push(i); dist[i]=time[i]; } }
    int ans=0;
    while(!q.empty()){
        int u=q.front(); q.pop();
        ans=max(ans, dist[u]);
        for(int v: g[u]){
            dist[v]=max(dist[v], dist[u]+time[v]);
            if(--indeg[v]==0) q.push(v);
        }
    }
    return ans;
}

int main(){
    vector<vector<int>> rel={{1,3},{2,3}}; vector<int> t={3,2,5};
    cout << minimumTime(3, rel, t) << "\n"; // 8
    return 0;
}
