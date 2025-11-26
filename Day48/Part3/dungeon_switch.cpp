#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct Edge {
    int to;
    int has_switch;
};

int solveDungeonSwitchboard(int n, const vector<int>& colors, const vector<tuple<int, int, int>>& edges_input, int s, int t) {
    vector<vector<Edge>> adj(n);
    for (const auto& e : edges_input) {
        adj[get<0>(e)].push_back({get<1>(e), get<2>(e)});
        adj[get<1>(e)].push_back({get<0>(e), get<2>(e)});
    }

    // dist[u][phase]
    vector<vector<int>> dist(n, vector<int>(3, -1));
    queue<pair<int, int>> q;

    // Assume start is valid or we are already there
    dist[s][0] = 0;
    q.push({s, 0});

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        int u = curr.first;
        int phase = curr.second;
        int d = dist[u][phase];

        if (u == t) {
            return d;
        }

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int next_phase = edge.has_switch ? (phase + 1) % 3 : phase;

            // Check entry condition for v
            // Green is 1
            if ((colors[v] + next_phase) % 3 == 1) {
                if (dist[v][next_phase] == -1) {
                    dist[v][next_phase] = d + 1;
                    q.push({v, next_phase});
                }
            }
        }
    }

    return -1;
}

int main() {
    int N = 3;
    vector<int> Colors = {1, 0, 0}; // 0=Red, 1=Green, 2=Blue
    vector<tuple<int, int, int>> Edges = {
        {0, 1, 1},
        {1, 2, 0}
    };
    int S = 0;
    int T = 2;

    int result = solveDungeonSwitchboard(N, Colors, Edges, S, T);
    cout << "Minimum Steps: " << result << endl;

    return 0;
}
