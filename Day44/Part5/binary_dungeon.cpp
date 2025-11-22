#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct Edge {
    int to;
    int type;
};

int main() {
    int N = 5;
    
    vector<vector<Edge>> adj(N);
    auto add_edge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };

    add_edge(0, 1, 1);
    add_edge(1, 2, 1);
    add_edge(2, 3, 0);
    add_edge(3, 4, 1);
    add_edge(0, 1, 0);
    add_edge(1, 3, 1);

    // Constraints: -1=None, 0=Req 0, 1=Req 1
    vector<int> constraints(N, -1);
    constraints[2] = 0;
    constraints[3] = 1;

    int start_node = 0;
    int goal_node = 4;

    // dist[u][parity]
    vector<vector<int>> dist(N, vector<int>(2, -1));
    queue<pair<int, int>> q;

    if (constraints[start_node] != -1 && constraints[start_node] != 0) {
        cout << "Start node blocked" << endl;
        return 0;
    }

    dist[start_node][0] = 0;
    q.push({start_node, 0});

    while (!q.empty()) {
        auto [u, p] = q.front();
        q.pop();

        if (u == goal_node) {
            cout << "Shortest path: " << dist[u][p] << endl;
            return 0;
        }

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.type;
            int next_p = p ^ w;

            if (constraints[v] != -1 && constraints[v] != next_p) {
                continue;
            }

            if (dist[v][next_p] == -1) {
                dist[v][next_p] = dist[u][p] + 1;
                q.push({v, next_p});
            }
        }
    }

    cout << "-1" << endl;

    return 0;
}
