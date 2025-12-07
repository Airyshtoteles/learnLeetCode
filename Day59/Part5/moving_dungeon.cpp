#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

int N, M;
vector<string> initial_grid;
int dist[205][205];

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> N >> M)) return 0;
    initial_grid.resize(N);
    for (int i = 0; i < N; ++i) cin >> initial_grid[i];

    // Logic:
    // The relative position of the player to the walls is invariant.
    // If player moves Right, walls shift Right. Relative diff is 0.
    // If player moves Down, walls shift Down. Relative diff is 0.
    // So effectively, the player is always standing on the tile corresponding to initial_grid[0][0].
    // And to move to a neighbor, we check the neighbor in the initial grid relative to (0,0).
    // i.e., to move Right, we check initial_grid[0][1].
    // to move Down, we check initial_grid[1][0].
    // If initial_grid[0][0] is '1', we can't start.
    
    if (initial_grid[0][0] == '1') {
        cout << -1 << endl;
        return 0;
    }

    // Check which moves are allowed globally
    bool can_right = (M > 1) ? (initial_grid[0][1] == '0') : false;
    bool can_left = (M > 1) ? (initial_grid[0][M-1] == '0') : false;
    bool can_down = (N > 1) ? (initial_grid[1][0] == '0') : false;
    bool can_up = (N > 1) ? (initial_grid[N-1][0] == '0') : false;

    // BFS on (r, c) using allowed moves
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            dist[i][j] = 1e9;

    queue<pair<int, int>> q;
    dist[0][0] = 0;
    q.push({0, 0});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (r == N - 1 && c == M - 1) {
            cout << dist[r][c] << endl;
            return 0;
        }

        // Try moves
        // Right
        if (can_right) {
            int nr = r;
            int nc = c + 1;
            // Check bounds? No, grid is infinite? No, dungeon is NxM.
            // "Dari (0,0) ke (N-1,M-1)".
            // So bounds apply.
            if (nc < M) {
                if (dist[nr][nc] > dist[r][c] + 1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
        // Left
        if (can_left) {
            int nr = r;
            int nc = c - 1;
            if (nc >= 0) {
                if (dist[nr][nc] > dist[r][c] + 1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
        // Down
        if (can_down) {
            int nr = r + 1;
            int nc = c;
            if (nr < N) {
                if (dist[nr][nc] > dist[r][c] + 1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
        // Up
        if (can_up) {
            int nr = r - 1;
            int nc = c;
            if (nr >= 0) {
                if (dist[nr][nc] > dist[r][c] + 1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    cout << -1 << endl;

    return 0;
}
