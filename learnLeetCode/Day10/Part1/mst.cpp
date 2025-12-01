#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Union-Find (Disjoint Set Union)
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

// Minimum Spanning Tree using Kruskal
int minimumSpanningTree(int n, vector<vector<int>> edges) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](auto &a, auto &b) { return a[2] < b[2]; });
    UnionFind uf(n);
    int totalCost = 0, edgesUsed = 0;
    for (auto &e : edges) {
        int u = e[0], v = e[1], w = e[2];
        if (uf.unite(u, v)) {
            totalCost += w;
            edgesUsed++;
            if (edgesUsed == n - 1) break;
        }
    }
    return (edgesUsed == n - 1) ? totalCost : -1;
}

int main() {
    // Example from problem
    int res1 = minimumSpanningTree(4, {{0,1,3},{0,2,5},{1,2,1},{2,3,4}});
    if (res1 != 8) return 1;

    // Additional tests
    if (minimumSpanningTree(3, {{0,1,1},{1,2,2},{0,2,3}}) != 3) return 1;
    if (minimumSpanningTree(2, {{0,1,5}}) != 5) return 1;

    cout << "Day10 Part1 mst.cpp: all tests passed" << endl;
    return 0;
}
