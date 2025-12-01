#include <bits/stdc++.h>
using namespace std;

long long min_cost_with_energy(int n, vector<array<int,4>> edges, int E){
    vector<vector<array<int,3>>> g(n); // v,cost,reward
    long long pos_sum=0;
    for(auto &e: edges){
        int u=e[0], v=e[1], c=e[2], r=e[3];
        g[u].push_back({v,c,r});
        g[v].push_back({u,c,r});
        if(r>0) pos_sum += r;
    }
    long long cap_ll = (long long)E + pos_sum;
    if(cap_ll > 100000) cap_ll = 100000; // safety cap
    int cap = (int)cap_ll;

    const long long INF = (long long)4e18;
    vector<vector<long long>> dist(n, vector<long long>(cap+1, INF));
    int e0 = min(E, cap);
    dist[0][e0] = 0;
    using T = tuple<long long,int,int>; // cost,u,en
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.emplace(0LL,0,e0);

    while(!pq.empty()){
        auto [cost,u,en] = pq.top(); pq.pop();
        if(cost != dist[u][en]) continue;
        if(u == n-1) return cost;
        for(auto &x: g[u]){
            int v=x[0], c=x[1], r=x[2];
            if(en < c) continue;
            int nen = en - c + r;
            if(nen > cap) nen = cap;
            long long ncost = cost + c;
            if(ncost < dist[v][nen]){
                dist[v][nen] = ncost;
                pq.emplace(ncost, v, nen);
            }
        }
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n=4; vector<array<int,4>> edges={{0,1,4,2},{1,2,3,3},{2,3,5,5}}; int E=3;
    cout<<min_cost_with_energy(n, edges, E)<<"\n"; // Expected 7
    return 0;
}
