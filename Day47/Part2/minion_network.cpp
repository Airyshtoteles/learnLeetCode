#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Edge {
    int u, v;
    int cost;
    bool is_corrupted;
    int actual_cost;

    bool operator<(const Edge& other) const {
        return actual_cost < other.actual_cost;
    }
};

struct UnionFind {
    vector<int> parent;
    vector<int> rank;
    int count;

    UnionFind(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        rank.assign(n, 0);
        count = n;
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    bool unite(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v) {
            if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            } else if (rank[root_u] < rank[root_v]) {
                parent[root_u] = root_v;
            } else {
                parent[root_v] = root_u;
                rank[root_u]++;
            }
            count--;
            return true;
        }
        return false;
    }
};

int solveMinionNetwork(int n, vector<Edge>& connections) {
    // Calculate actual costs
    for (auto& edge : connections) {
        edge.actual_cost = edge.is_corrupted ? edge.cost * 2 : edge.cost;
    }

    // Sort edges
    sort(connections.begin(), connections.end());

    UnionFind uf(n);
    int total_mana = 0;
    int edges_count = 0;

    // cout << "Processing " << connections.size() << " potential connections for " << n << " outposts..." << endl;

    for (const auto& edge : connections) {
        if (uf.unite(edge.u, edge.v)) {
            // cout << "  Connecting " << edge.u << " <-> " << edge.v << " with cost " << edge.actual_cost << endl;
            total_mana += edge.actual_cost;
            edges_count++;
        }
    }

    if (uf.count == 1) {
        return total_mana;
    } else {
        return -1;
    }
}

int main() {
    int N = 4;
    // {u, v, cost, is_corrupted, actual_cost (placeholder)}
    vector<Edge> connections = {
        {0, 1, 10, false, 0},
        {1, 2, 20, true, 0},
        {2, 3, 30, false, 0},
        {0, 3, 50, false, 0},
        {1, 3, 5, false, 0}
    };

    int result = solveMinionNetwork(N, connections);
    cout << "Minimum Mana Cost: " << result << endl;

    return 0;
}
