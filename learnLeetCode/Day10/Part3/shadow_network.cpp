#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <climits>
using namespace std;

class UnionFind {
    map<int, int> parent;
public:
    int find(int x) {
        if (parent.find(x) == parent.end()) parent[x] = x;
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        parent[py] = px;
        return true;
    }
};

int computeCostWithRelays(int n, const vector<vector<int>>& edges, const set<int>& relays) {
    map<pair<int,int>, int> edgeMap;
    for (auto &e : edges) {
        int u = e[0], v = e[1], w = e[2];
        auto key = make_pair(min(u,v), max(u,v));
        if (edgeMap.find(key) == edgeMap.end() || edgeMap[key] > w) {
            edgeMap[key] = w;
        }
    }

    int cost = 0;
    set<int> nonRelays;
    for (int i = 0; i < n; ++i) {
        if (relays.find(i) == relays.end()) nonRelays.insert(i);
    }

    // Connect each non-relay to cheapest relay
    for (int node : nonRelays) {
        int minCost = INT_MAX;
        for (int relay : relays) {
            auto key = make_pair(min(node, relay), max(node, relay));
            if (edgeMap.find(key) != edgeMap.end()) {
                minCost = min(minCost, edgeMap[key]);
            }
        }
        if (minCost == INT_MAX) return INT_MAX;
        cost += minCost;
    }

    // MST among relays
    vector<vector<int>> relayEdges;
    vector<int> relayList(relays.begin(), relays.end());
    for (size_t i = 0; i < relayList.size(); ++i) {
        for (size_t j = i+1; j < relayList.size(); ++j) {
            int u = relayList[i], v = relayList[j];
            auto key = make_pair(min(u,v), max(u,v));
            if (edgeMap.find(key) != edgeMap.end()) {
                relayEdges.push_back({u, v, edgeMap[key]});
            }
        }
    }

    sort(relayEdges.begin(), relayEdges.end(), [](auto &a, auto &b) { return a[2] < b[2]; });
    UnionFind uf;
    for (auto &e : relayEdges) {
        if (uf.unite(e[0], e[1])) {
            cost += e[2];
        }
    }

    return cost;
}

void generateCombinations(int n, int k, int start, vector<int>& current, vector<vector<int>>& result) {
    if ((int)current.size() == k) {
        result.push_back(current);
        return;
    }
    for (int i = start; i < n; ++i) {
        current.push_back(i);
        generateCombinations(n, k, i+1, current, result);
        current.pop_back();
    }
}

int shadowNetwork(int n, const vector<vector<int>>& edges, int k) {
    if (k >= n) {
        // MST
        vector<vector<int>> sortedEdges = edges;
        sort(sortedEdges.begin(), sortedEdges.end(), [](auto &a, auto &b) { return a[2] < b[2]; });
        UnionFind uf;
        int cost = 0;
        for (auto &e : sortedEdges) {
            if (uf.unite(e[0], e[1])) cost += e[2];
        }
        return cost;
    }

    vector<vector<int>> combos;
    vector<int> current;
    generateCombinations(n, k, 0, current, combos);

    int minCost = INT_MAX;
    for (auto &combo : combos) {
        set<int> relaySet(combo.begin(), combo.end());
        int cost = computeCostWithRelays(n, edges, relaySet);
        minCost = min(minCost, cost);
    }

    return (minCost == INT_MAX) ? -1 : minCost;
}

int main() {
    int res = shadowNetwork(5, {{0,1,4},{0,2,3},{1,3,2},{2,4,6},{3,4,1}}, 2);
    cout << "Day10 Part3 shadow_network.cpp result for example: " << res << endl;

    // Simple test
    if (shadowNetwork(3, {{0,1,1},{1,2,1},{0,2,2}}, 1) != 2) return 1;

    cout << "Day10 Part3 shadow_network.cpp: basic tests passed" << endl;
    return 0;
}
