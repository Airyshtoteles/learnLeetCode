#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <tuple>

using namespace std;

int N, M;
vector<vector<long long>> light_grid;
vector<vector<long long>> shadow_grid;

struct State {
    long long cost;
    int r, c;
    int realm; // 0=Light, 1=Shadow
    int parity; // 0=Even, 1=Odd

    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> N >> M)) return 0;

    light_grid.resize(N, vector<long long>(M));
    shadow_grid.resize(N, vector<long long>(M));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> light_grid[i][j];

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> shadow_grid[i][j];

    map<tuple<int, int, int, int>, long long> dist;
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[{0, 0, 0, 0}] = 0;
    pq.push({0, 0, 0, 0, 0});

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (!pq.empty()) {
        auto [cst, r, c, realm, parity] = pq.top();
        pq.pop();

        auto key = make_tuple(r, c, realm, parity);
        if (dist.count(key) && dist[key] < cst) continue;

        if (r == N - 1 && c == M - 1 && realm == 0) {
            cout << cst << endl;
            return 0;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                long long move_cost = (realm == 0) ? light_grid[nr][nc] : shadow_grid[nr][nc];
                long long new_cost = cst + move_cost;
                int new_parity = 1 - parity;
                int new_realm = realm;

                // Check auto-swap
                if (move_cost == 0) {
                    new_realm = 1 - realm;
                }

                auto new_key = make_tuple(nr, nc, new_realm, new_parity);
                if (!dist.count(new_key) || dist[new_key] > new_cost) {
                    dist[new_key] = new_cost;
                    pq.push({new_cost, nr, nc, new_realm, new_parity});
                }
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
