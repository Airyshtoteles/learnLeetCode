#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        if (rank[px] < rank[py]) swap(px, py);
        parent[py] = px;
        if (rank[px] == rank[py]) rank[px]++;
        return true;
    }
};

int bfsMaxDistance(int n, const vector<vector<int>>& adj) {
    int maxDist = 0;
    for (int start = 0; start < n; ++start) {
        vector<int> dist(n, -1);
        dist[start] = 0;
        queue<int> q;
        q.push(start);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        for (int d : dist) maxDist = max(maxDist, d);
    }
    return maxDist;
}

int shadowRelay(int n, vector<vector<int>> edges) {
    sort(edges.begin(), edges.end(), [](auto &a, auto &b) { return a[2] < b[2]; });
    UnionFind uf(n);
    vector<vector<int>> selected;
    int totalCost = 0;

    // Build MST
    for (auto &e : edges) {
        if (uf.unite(e[0], e[1])) {
            selected.push_back(e);
            totalCost += e[2];
            if ((int)selected.size() == n - 1) break;
        }
    }

    // Build adjacency list
    vector<vector<int>> adj(n);
    for (auto &e : selected) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }

    int diameter = bfsMaxDistance(n, adj);
    if (diameter <= 2) return totalCost;

    // Try adding cheapest remaining edges to reduce diameter
    for (auto &e : edges) {
        bool inSelected = false;
        for (auto &s : selected) {
            if ((e[0] == s[0] && e[1] == s[1]) || (e[0] == s[1] && e[1] == s[0])) {
                inSelected = true;
                break;
            }
        }
        if (inSelected) continue;

        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
        int newDiam = bfsMaxDistance(n, adj);
        if (newDiam <= 2) {
            totalCost += e[2];
            return totalCost;
        }
        adj[e[0]].pop_back();
        adj[e[1]].pop_back();
    }

    return totalCost;
}

int main() {
    int res1 = shadowRelay(4, {{0,1,1},{1,2,2},{2,3,3},{0,3,10}});
    cout << "Day10 Part2 shadow_relay.cpp result for example: " << res1 << endl;

    // Simple triangle test
    if (shadowRelay(3, {{0,1,1},{1,2,1},{0,2,2}}) != 2) return 1;

    cout << "Day10 Part2 shadow_relay.cpp: basic tests passed" << endl;
    return 0;
}
