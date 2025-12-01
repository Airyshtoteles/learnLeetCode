#include <bits/stdc++.h>
using namespace std;

// LC 847 — Shortest Path Visiting All Nodes
// BFS with state (node, mask)

int shortestPathLength(vector<vector<int>>& graph){
    int n = graph.size();
    if (n <= 1) return 0;
    int allmask = (1<<n) - 1;
    queue<tuple<int,int,int>> q; // node, mask, dist
    vector<vector<char>> vis(n, vector<char>(1<<n, 0));
    for(int i=0;i<n;++i){
        int m = 1<<i; vis[i][m]=1; q.emplace(i, m, 0);
    }
    while(!q.empty()){
        auto [u, mask, d] = q.front(); q.pop();
        if (mask == allmask) return d;
        for(int v: graph[u]){
            int nmask = mask | (1<<v);
            if (!vis[v][nmask]){ vis[v][nmask]=1; q.emplace(v, nmask, d+1); }
        }
    }
    return -1;
}

int main(){
    vector<vector<int>> g = {{1,2,3},{0},{0},{0}};
    cout << shortestPathLength(g) << "\n"; // 4
    return 0;
}
