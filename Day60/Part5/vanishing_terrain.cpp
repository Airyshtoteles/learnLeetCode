#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<vector<int>> vanish(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> vanish[i][j];
        }
    }

    // If start point vanishes at t=0 (or before), impossible to start
    if (vanish[0][0] <= 0) {
        cout << -1 << endl;
        return 0;
    }

    queue<pair<int, int>> q;
    q.push({0, 0});
    
    vector<vector<int>> dist(N, vector<int>(M, -1));
    dist[0][0] = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (r == N - 1 && c == M - 1) {
            cout << dist[r][c] << endl;
            return 0;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                int next_time = dist[r][c] + 1;
                // Must arrive strictly before vanish time
                if (next_time < vanish[nr][nc]) {
                    if (dist[nr][nc] == -1) {
                        dist[nr][nc] = next_time;
                        q.push({nr, nc});
                    }
                }
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
