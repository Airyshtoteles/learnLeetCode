#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <map>

using namespace std;

struct State {
    int cost;
    int r, c, w;

    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

int solveQuantumMirror(int n, int m, const vector<vector<int>>& grid_r, const vector<tuple<int, int, int>>& gates) {
    map<pair<int, int>, int> gate_costs;
    for (const auto& gate : gates) {
        gate_costs[{get<0>(gate), get<1>(gate)}] = get<2>(gate);
    }

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, 0, 0, 0});

    // dist[r][c][w]
    // Using a map for sparse/easy indexing, or 3D vector
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(2, 1e9)));
    dist[0][0][0] = 0;

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int cost = current.cost;
        int r = current.r;
        int c = current.c;
        int w = current.w;

        if (r == n - 1 && c == m - 1 && w == 1) {
            return cost;
        }

        if (cost > dist[r][c][w]) {
            continue;
        }

        // 1. Move
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                bool is_safe = false;
                if (w == 0) {
                    if (grid_r[nr][nc] == 0) is_safe = true;
                } else {
                    if (grid_r[nr][nc] == 1) is_safe = true;
                }

                if (is_safe) {
                    int new_cost = cost + 1;
                    if (new_cost < dist[nr][nc][w]) {
                        dist[nr][nc][w] = new_cost;
                        pq.push({new_cost, nr, nc, w});
                    }
                }
            }
        }

        // 2. Switch
        if (gate_costs.count({r, c})) {
            int switch_cost = gate_costs[{r, c}];
            int nw = 1 - w;
            int new_cost = cost + switch_cost;

            if (new_cost < dist[r][c][nw]) {
                dist[r][c][nw] = new_cost;
                pq.push({new_cost, r, c, nw});
            }
        }
    }

    return -1;
}

int main() {
    int N = 3;
    int M = 3;
    vector<vector<int>> Grid_R = {
        {0, 0, 1},
        {1, 0, 0},
        {1, 1, 1}
    };
    vector<tuple<int, int, int>> Gates = {{1, 1, 5}};

    int result = solveQuantumMirror(N, M, Grid_R, Gates);
    cout << "Minimum Cost: " << result << endl;

    return 0;
}
