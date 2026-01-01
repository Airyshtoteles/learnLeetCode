#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Max Flow (Dinic's Algorithm)
const int INF = 1e9;

struct Edge {
    int to, cap, flow, rev;
};

vector<vector<Edge>> adj;
vector<int> level, ptr;

void add_edge(int from, int to, int cap) {
    adj[from].push_back({to, cap, 0, (int)adj[to].size()});
    adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
}

bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto& e : adj[v]) {
            if (e.cap - e.flow > 0 && level[e.to] == -1) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
    return level[t] != -1;
}

int dfs(int v, int t, int pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;
    for (int& cid = ptr[v]; cid < adj[v].size(); ++cid) {
        auto& e = adj[v][cid];
        int tr = e.to;
        if (level[v] + 1 != level[tr] || e.cap - e.flow == 0) continue;
        int push = dfs(tr, t, min(pushed, e.cap - e.flow));
        if (push == 0) continue;
        e.flow += push;
        adj[tr][e.rev].flow -= push;
        return push;
    }
    return 0;
}

int dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        fill(ptr.begin(), ptr.end(), 0);
        while (int pushed = dfs(s, t, INF)) {
            flow += pushed;
        }
    }
    return flow;
}

int main() {
    int V, E, S, T;
    if (!(cin >> V >> E >> S >> T)) return 0;

    adj.assign(V, vector<Edge>());
    level.resize(V);
    ptr.resize(V);

    for (int i = 0; i < E; ++i) {
        int u, v, cap;
        cin >> u >> v >> cap;
        add_edge(u, v, cap);
        add_edge(v, u, cap); // Undirected
    }

    int max_flow = dinic(S, T);

    // If max_flow >= 2, there are at least 2 edge-disjoint paths.
    // Adversary can block one node (causing one path to fail), but another remains.
    if (max_flow >= 2) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}
