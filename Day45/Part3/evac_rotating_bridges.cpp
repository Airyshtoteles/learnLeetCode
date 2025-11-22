#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    int weight;
    int k;
};

struct Monster {
    int node;
    int deadline;
};

int N = 5;
vector<vector<Edge>> adj;

vector<long long> dijkstra(int start_node, long long start_time) {
    vector<long long> dist(N, INF);
    dist[start_node] = start_time;
    
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({start_time, start_node});
    
    while (!pq.empty()) {
        long long t = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (t > dist[u]) continue;
        
        for (const auto& e : adj[u]) {
            long long wait = 0;
            if (t % e.k != 0) {
                wait = e.k - (t % e.k);
            }
            
            long long arrival = t + wait + e.weight;
            
            if (arrival < dist[e.to]) {
                dist[e.to] = arrival;
                pq.push({arrival, e.to});
            }
        }
    }
    return dist;
}

int main() {
    // Hardcoded Input
    adj.resize(N);
    auto add_edge = [&](int u, int v, int w, int k) {
        adj[u].push_back({v, w, k});
        adj[v].push_back({u, w, k});
    };

    add_edge(0, 1, 5, 1);
    add_edge(1, 2, 2, 3);
    add_edge(2, 3, 4, 1);
    add_edge(0, 3, 15, 1);
    add_edge(3, 4, 3, 5);

    vector<Monster> monsters = {
        {2, 20},
        {4, 30}
    };

    // 1. Start -> All Nodes
    vector<long long> to_monsters = dijkstra(0, 0);

    long long max_time_needed = 0;

    for (const auto& m : monsters) {
        long long arrival_at_m = to_monsters[m.node];
        
        if (arrival_at_m == INF) {
            cout << "-1" << endl;
            return 0;
        }

        // 2. Monster -> Start
        // We only need dist to Start (node 0)
        // But we run full Dijkstra for simplicity or optimized single target
        // Here we use the same function
        vector<long long> from_monster = dijkstra(m.node, arrival_at_m);
        long long back_to_start = from_monster[0];

        if (back_to_start == INF) {
            cout << "-1" << endl;
            return 0;
        }

        if (back_to_start > m.deadline) {
            cout << "-1" << endl;
            return 0;
        }

        max_time_needed = max(max_time_needed, back_to_start);
    }

    cout << "Minimum Time: " << max_time_needed << endl;

    return 0;
}
