#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct Edge {
    int to;
    int weight;
};

struct State {
    int durability;
    int u;
    int repaired; // 0 or 1

    bool operator<(const State& other) const {
        return durability < other.durability; // Max heap
    }
};

int main() {
    int N, M, S, E, InitDur;
    if (!(cin >> N >> M >> S >> E >> InitDur)) return 0;

    vector<vector<Edge>> adj(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Assuming undirected? "Graph berbobot". Usually undirected unless specified.
        // "Path" usually implies directed or undirected. Let's assume undirected for standard map.
    }

    // dist[u][repaired] = max durability
    vector<vector<int>> max_dur(N + 1, vector<int>(2, -1));
    priority_queue<State> pq;

    max_dur[S][0] = InitDur;
    pq.push({InitDur, S, 0});

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        int d = curr.durability;
        int u = curr.u;
        int r = curr.repaired;

        if (d < max_dur[u][r]) continue;
        if (u == E) {
            cout << "true" << endl;
            return 0;
        }

        // Option 1: Move to neighbor
        for (auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;
            int new_d = d - w;

            if (new_d >= 0) {
                if (new_d > max_dur[v][r]) {
                    max_dur[v][r] = new_d;
                    pq.push({new_d, v, r});
                }
            }
        }

        // Option 2: Repair (if not yet repaired)
        if (r == 0) {
            // Repair resets durability to InitDur
            // We stay at u, but state changes to 1
            int new_d = InitDur;
            if (new_d > max_dur[u][1]) {
                max_dur[u][1] = new_d;
                pq.push({new_d, u, 1});
            }
        }
    }

    cout << "false" << endl;

    return 0;
}
