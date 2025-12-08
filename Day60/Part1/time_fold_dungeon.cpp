#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <tuple>

using namespace std;

int N, M;
vector<vector<int>> cost;
vector<vector<int>> portal;

struct State {
    int energy;
    int r, c;
    int step;

    bool operator>(const State& other) const {
        return energy > other.energy;
    }
};

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> N >> M)) return 0;

    cost.resize(N, vector<int>(M));
    portal.resize(N, vector<int>(M));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> cost[i][j];

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> portal[i][j];

    map<tuple<int, int, int>, int> dist;
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[{0, 0, 0}] = 0;
    pq.push({0, 0, 0, 0});

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (!pq.empty()) {
        auto [e, r, c, step] = pq.top();
        pq.pop();

        if (step > 100000) continue;

        auto key = make_tuple(r, c, step);
        if (dist.count(key) && dist[key] < e) continue;

        if (r == N - 1 && c == M - 1) {
            cout << e << endl;
            return 0;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                int new_energy = e + cost[nr][nc];
                int new_step = step + 1 + portal[nr][nc];

                if (new_step < 0 || new_step > 100000) continue;

                auto new_key = make_tuple(nr, nc, new_step);
                if (!dist.count(new_key) || dist[new_key] > new_energy) {
                    dist[new_key] = new_energy;
                    pq.push({new_energy, nr, nc, new_step});
                }
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
