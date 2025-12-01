#include <bits/stdc++.h>
using namespace std;

static inline int popcountll(unsigned long long x){
#if defined(_MSC_VER)
    return (int)__popcnt64(x);
#else
    return __builtin_popcountll(x);
#endif
}

long long min_cost_to_zero_attr(int n, const vector<tuple<int,int,unsigned long long>>& edges){
    vector<vector<pair<int,unsigned long long>>> adj(n);
    for(auto &e: edges){ int u,v; unsigned long long a; tie(u,v,a)=e; adj[u].push_back({v,a}); }

    const long long INF = (long long)9e18;
    vector<unordered_map<unsigned long long, long long>> dist(n);
    vector<long long> best_node(n, INF);
    const size_t CAP = 512;
    const long long MARGIN = 64LL * 60LL;

    using State = tuple<long long,int,unsigned long long>; // cost,node,attr
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[0][0]=0; best_node[0]=0; pq.emplace(0,0,0ULL);

    while(!pq.empty()){
        auto [cost,u,a]=pq.top(); pq.pop();
        auto it = dist[u].find(a);
        if(it==dist[u].end() || it->second!=cost) continue;
        if(u==n-1 && a==0ULL) return cost;
        for(auto &p: adj[u]){
            int v=p.first; unsigned long long w=p.second;
            unsigned long long na = a ^ w;
            long long ncost = cost + popcountll(na);
            if(ncost > best_node[v] + MARGIN) continue;
            auto it2 = dist[v].find(na);
            if(it2==dist[v].end() || ncost < it2->second){
                dist[v][na] = ncost;
                if(ncost < best_node[v]) best_node[v] = ncost;
                if(dist[v].size() > CAP){
                    // soft prune overly bad states
                    vector<unsigned long long> del;
                    del.reserve(dist[v].size());
                    for(auto &kv: dist[v]) if(kv.second > best_node[v] + MARGIN) del.push_back(kv.first);
                    for(auto key: del){ if(dist[v].size() <= CAP) break; dist[v].erase(key); }
                }
                pq.emplace(ncost, v, na);
            }
        }
    }
    return -1;
}

int main(){
    int n=3; vector<tuple<int,int,unsigned long long>> edges={{0,1,3ULL},{1,2,1ULL},{0,2,2ULL}};
    cout << min_cost_to_zero_attr(n, edges) << "\n"; // -1
    return 0;
}
