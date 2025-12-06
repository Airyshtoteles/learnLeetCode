#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

int N, M;
vector<string> grid;
int dist[1005][1005];
vector<pair<int, int>> mirrors;

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> N >> M)) return 0;
    // cout << N << " " << M << endl;
    grid.resize(N);
    
    int startR, startC, endR, endC;
    
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'S') {
                startR = i; startC = j;
            } else if (grid[i][j] == 'E') {
                endR = i; endC = j;
            } else if (grid[i][j] == 'M') {
                mirrors.push_back({i, j});
            }
        }
    }

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            dist[i][j] = 1e9;

    deque<pair<int, int>> q;
    dist[startR][startC] = 0;
    q.push_back({startR, startC});
    
    bool mirrors_activated = false;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop_front();

        if (r == endR && c == endC) {
            cout << dist[r][c] << endl;
            return 0;
        }

        // If current is M
        if (grid[r][c] == 'M') {
            // 1. Activate all other mirrors (Cost 0)
            if (!mirrors_activated) {
                mirrors_activated = true;
                for (auto [mr, mc] : mirrors) {
                    if (dist[mr][mc] > dist[r][c]) {
                        dist[mr][mc] = dist[r][c];
                        q.push_front({mr, mc});
                    }
                }
            }
            
            // 2. Move to neighbors from M (Cost 0)
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != '1') {
                    if (dist[nr][nc] > dist[r][c]) { // Cost 0
                        dist[nr][nc] = dist[r][c];
                        q.push_front({nr, nc});
                    }
                }
            }
        } else {
            // Standard moves from non-M (Cost 1)
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != '1') {
                    if (dist[nr][nc] > dist[r][c] + 1) {
                        dist[nr][nc] = dist[r][c] + 1;
                        q.push_back({nr, nc});
                    }
                }
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
