#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to;
    int capacity;
    int flow;
    int rev; // index of reverse edge
};

vector<vector<Edge>> adj;
vector<int> level;
vector<int> ptr;

void add_edge(int from, int to, int cap) {
    Edge a = {to, cap, 0, (int)adj[to].size()};
    Edge b = {from, cap, 0, (int)adj[from].size()}; // Undirected edge: cap in both directions?
    // Yes, for min-cut in undirected graph, we treat edge as two directed edges with capacity C.
    // Wait, if we push flow u->v, we use capacity.
    // If we push v->u, we use capacity.
    // This models the fact that the connection can carry information in either direction,
    // but cutting it removes BOTH.
    // Actually, standard reduction for undirected min-cut is replace (u,v) with u->v (cap) and v->u (cap).
    adj[from].push_back(a);
    adj[to].push_back(b);
}

// For Source/Sink edges which are directed (S->Node, Node->T)
void add_directed_edge(int from, int to, int cap) {
    Edge a = {to, cap, 0, (int)adj[to].size()};
    Edge b = {from, 0, 0, (int)adj[from].size()}; // Reverse edge has 0 capacity
    adj[from].push_back(a);
    adj[to].push_back(b);
}

int bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    level[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto& edge : adj[v]) {
            if (edge.capacity - edge.flow > 0 && level[edge.to] == -1) {
                level[edge.to] = level[v] + 1;
                q.push(edge.to);
            }
        }
    }
    return level[t] != -1;
}

int dfs(int v, int t, int pushed) {
    if (pushed == 0) return 0;
    if (v == t) return pushed;
    for (int& cid = ptr[v]; cid < adj[v].size(); ++cid) {
        auto& edge = adj[v][cid];
        int tr = edge.to;
        if (level[v] + 1 != level[tr] || edge.capacity - edge.flow == 0) continue;
        int push = dfs(tr, t, min(pushed, edge.capacity - edge.flow));
        if (push == 0) continue;
        edge.flow += push;
        adj[tr][edge.rev].flow -= push;
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

int solve_virus_containment(int n, vector<pair<int, int>> connections, vector<int> infected, vector<int> critical) {
    // Check overlap
    set<int> inf_set(infected.begin(), infected.end());
    for (int c : critical) {
        if (inf_set.count(c)) return -1;
    }
    
    int S = n;
    int T = n + 1;
    adj.assign(n + 2, vector<Edge>());
    level.resize(n + 2);
    ptr.resize(n + 2);
    
    // S -> Infected
    for (int i : infected) {
        add_directed_edge(S, i, INF);
    }
    
    // Critical -> T
    for (int c : critical) {
        add_directed_edge(c, T, INF);
    }
    
    // Connections
    for (auto& p : connections) {
        add_edge(p.first, p.second, 1);
    }
    
    return dinic(S, T);
}

int main() {
    // Example 1
    int n = 3;
    vector<pair<int, int>> conn = {{0, 1}, {1, 2}};
    vector<int> inf = {0};
    vector<int> crit = {2};
    
    cout << "Min edges (Ex 1): " << solve_virus_containment(n, conn, inf, crit) << endl;
    
    // Example 2
    int n2 = 5;
    vector<pair<int, int>> conn2 = {{0, 1}, {1, 2}, {0, 3}, {3, 4}, {1, 4}};
    vector<int> inf2 = {0};
    vector<int> crit2 = {2, 4};
    
    cout << "Min edges (Ex 2): " << solve_virus_containment(n2, conn2, inf2, crit2) << endl;
    
    return 0;
}
