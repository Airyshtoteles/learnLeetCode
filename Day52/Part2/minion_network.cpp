#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<int>> adj;
vector<vector<int>> rev_adj;
vector<bool> visited;
stack<int> st;
vector<int> scc_id;
int num_sccs;

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs1(v);
    }
    st.push(u);
}

void dfs2(int u, int id) {
    visited[u] = true;
    scc_id[u] = id;
    for (int v : rev_adj[u]) {
        if (!visited[v]) dfs2(v, id);
    }
}

int solve_minion_network(int n, vector<pair<int, int>>& connections) {
    adj.assign(n, vector<int>());
    rev_adj.assign(n, vector<int>());
    
    for (auto& p : connections) {
        adj[p.first].push_back(p.second);
        rev_adj[p.second].push_back(p.first);
    }
    
    visited.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) dfs1(i);
    }
    
    visited.assign(n, false);
    scc_id.assign(n, -1);
    num_sccs = 0;
    
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (!visited[u]) {
            dfs2(u, num_sccs++);
        }
    }
    
    if (num_sccs == 1) return 0;
    
    vector<int> in_degree(num_sccs, 0);
    vector<int> out_degree(num_sccs, 0);
    set<pair<int, int>> scc_edges;
    
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            if (scc_id[u] != scc_id[v]) {
                if (scc_edges.find({scc_id[u], scc_id[v]}) == scc_edges.end()) {
                    scc_edges.insert({scc_id[u], scc_id[v]});
                    out_degree[scc_id[u]]++;
                    in_degree[scc_id[v]]++;
                }
            }
        }
    }
    
    int sources = 0;
    int sinks = 0;
    
    for (int i = 0; i < num_sccs; ++i) {
        if (in_degree[i] == 0) sources++;
        if (out_degree[i] == 0) sinks++;
    }
    
    return max(sources, sinks);
}

int main() {
    int n1 = 3;
    vector<pair<int, int>> conn1 = {{0, 1}, {1, 2}, {2, 0}};
    cout << "Min Edges (Ex 1): " << solve_minion_network(n1, conn1) << endl;
    
    int n2 = 4;
    vector<pair<int, int>> conn2 = {{0, 1}, {2, 3}};
    cout << "Min Edges (Ex 2): " << solve_minion_network(n2, conn2) << endl;
    
    int n3 = 3;
    vector<pair<int, int>> conn3 = {{0, 1}, {0, 2}};
    cout << "Min Edges (Ex 3): " << solve_minion_network(n3, conn3) << endl;
    
    return 0;
}
