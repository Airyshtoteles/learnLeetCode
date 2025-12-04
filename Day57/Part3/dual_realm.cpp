#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

struct State {
    int cost;
    int r, c;
    int realm; // 0 for A, 1 for B
    int k; // shifts used

    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

int N, M, K;
vector<string> gridA, gridB;
int dist[305][305][2][55];

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> N >> M >> K)) return 0;
    // cout << N << " " << M << " " << K << endl;

    gridA.resize(N);
    gridB.resize(N);

    for (int i = 0; i < N; ++i) cin >> gridA[i];
    for (int i = 0; i < N; ++i) cin >> gridB[i];

    // Initialize dist
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            for (int r = 0; r < 2; ++r)
                for (int s = 0; s <= K; ++s)
                    dist[i][j][r][s] = 1e9;

    priority_queue<State, vector<State>, greater<State>> pq;

    // Start at (0,0) in Realm A
    if (gridA[0][0] == '#') {
        cout << -1 << endl;
        return 0;
    }

    dist[0][0][0][0] = 0;
    pq.push({0, 0, 0, 0, 0});

    while (!pq.empty()) {
        auto [d, r, c, realm, k] = pq.top();
        pq.pop();

        if (d > dist[r][c][realm][k]) continue;

        // Target reached?
        if (r == N - 1 && c == M - 1) {
            cout << d << endl;
            return 0;
        }

        // 1. Move adjacent
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                char cell = (realm == 0) ? gridA[nr][nc] : gridB[nr][nc];
                if (cell != '#') {
                    if (dist[r][c][realm][k] + 1 < dist[nr][nc][realm][k]) {
                        dist[nr][nc][realm][k] = dist[r][c][realm][k] + 1;
                        pq.push({dist[nr][nc][realm][k], nr, nc, realm, k});
                    }
                }
            }
        }

        // 2. Switch realm
        if (k < K) {
            int nrealm = 1 - realm;
            char cell = (nrealm == 0) ? gridA[r][c] : gridB[r][c];
            if (cell != '#') {
                if (dist[r][c][realm][k] + 2 < dist[r][c][nrealm][k + 1]) {
                    dist[r][c][nrealm][k + 1] = dist[r][c][realm][k] + 2;
                    pq.push({dist[r][c][nrealm][k + 1], r, c, nrealm, k + 1});
                }
            }
        }
    }

    cout << -1 << endl;

    return 0;
}
