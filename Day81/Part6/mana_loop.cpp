#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int u, v;
    int cost;
};

int main() {
    int N, M, Start, Target;
    if (!(cin >> N >> M >> Start >> Target)) return 0;

    vector<int> a(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> a[i];
    }

    vector<Edge> edges;
    for (int i = 0; i < M; ++i) {
        int u, v, cost;
        cin >> u >> v >> cost;
        edges.push_back({u, v, cost});
    }

    // Bellman-Ford
    // dist[i] = max mana at node i
    // Initialize with -INF
    vector<long long> dist(N + 1, -INF);
    dist[Start] = 0; // Initial mana 0

    // Run N-1 iterations
    for (int i = 0; i < N - 1; ++i) {
        for (const auto& e : edges) {
            if (dist[e.u] != -INF) {
                // Gain a[v] - cost
                long long new_val = dist[e.u] + a[e.v] - e.cost;
                if (new_val > dist[e.v]) {
                    dist[e.v] = new_val;
                }
            }
        }
    }

    // Check for positive cycles reachable from Start
    // And check if Target is reachable from such cycles
    // We can run N more iterations. If any node updates, it's part of or reachable from a positive cycle.
    // We mark such nodes as having INF mana.
    
    for (int i = 0; i < N; ++i) {
        for (const auto& e : edges) {
            if (dist[e.u] != -INF) {
                long long new_val = dist[e.u] + a[e.v] - e.cost;
                if (new_val > dist[e.v]) {
                    dist[e.v] = INF; // Mark as infinite
                }
                if (dist[e.u] == INF) {
                    dist[e.v] = INF; // Propagate infinity
                }
            }
        }
    }

    if (dist[Target] == INF) {
        cout << "true" << endl;
    } else {
        // Also need to check if we can reach Target at all?
        // "Tentukan apakah bisa mencapai target node dengan mana tak terbatas."
        // If we reach target with finite mana, answer is false.
        // We specifically need "mana tak terbatas".
        cout << "false" << endl;
    }

    return 0;
}
