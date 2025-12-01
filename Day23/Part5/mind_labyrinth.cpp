#include <bits/stdc++.h>
using namespace std;

// The Mind Labyrinth
// Approximate Dijkstra on (node, k = visited_count) with Pareto-like pruning.

long long min_cost_mind_labyrinth(int n, const vector<tuple<int,int,int>>& edges){
    vector<vector<pair<int,int>>> g(n);
    for(auto [u,v,w]: edges){ --u; --v; g[u].push_back({v,w}); g[v].push_back({u,w}); }
    const long long INF = (long long)4e18;
    vector<vector<long long>> dist(n, vector<long long>(n+1, INF));
    priority_queue<tuple<long long,int,int>, vector<tuple<long long,int,int>>, greater<>> pq;
    dist[0][1]=0; pq.emplace(0,0,1);
    while(!pq.empty()){
        auto [d,u,k] = pq.top(); pq.pop();
        if(d != dist[u][k]) continue;
        if(u==n-1) return d;
        for(auto [v,w]: g[u]){
            long long nd = d + 1LL*w*k;
            if(nd < dist[v][k]){ dist[v][k]=nd; pq.emplace(nd, v, k); }
            if(k < n){
                long long nd2 = d + 1LL*w*(k+1);
                if(nd2 < dist[v][k+1]){ dist[v][k+1]=nd2; pq.emplace(nd2, v, k+1); }
            }
        }
    }
    return -1;
}

int main(){
    int n=4; vector<tuple<int,int,int>> edges={{1,2,3},{2,3,2},{3,4,4},{1,3,10}};
    cout << min_cost_mind_labyrinth(n, edges) << "\n"; // ~19 per prompt
    return 0;
}
