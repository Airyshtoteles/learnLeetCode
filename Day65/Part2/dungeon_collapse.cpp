#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct State {
    int r, c, t;
};

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> grid[i][j];
        }
    }

    // visited[r][c][time % 2]
    vector<vector<vector<bool>>> visited(N, vector<vector<bool>>(M, vector<bool>(2, false)));
    queue<State> q;

    // Start at (0,0) at t=0
    // Check if start is valid at t=0
    // If grid[0][0] == 0, it is a hole at t=0.
    // Assuming start is always valid or we need to check.
    // If grid[0][0] == 0, we can't even start? 
    // Let's assume grid[0][0] is 1 based on typical problem constraints, 
    // or if it is 0, maybe we can't start.
    // However, if grid[0][0] is 0, we return -1 immediately.
    
    if (grid[0][0] == 0) {
        cout << -1 << endl;
        return 0;
    }

    q.push({0, 0, 0});
    visited[0][0][0] = true;

    int dr[] = {0, 0, 1, -1, 0}; // 0,0 is for waiting
    int dc[] = {1, -1, 0, 0, 0};

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        int r = current.r;
        int c = current.c;
        int t = current.t;

        if (r == N - 1 && c == M - 1) {
            cout << t << endl;
            return 0;
        }

        int nt = t + 1;
        int n_parity = nt % 2;

        for (int i = 0; i < 5; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                // Check if (nr, nc) is safe at nt
                bool is_safe = false;
                if (grid[nr][nc] == 1) {
                    is_safe = true;
                } else {
                    // grid is 0 (crumbling)
                    // It is safe (1) if time is odd
                    if (nt % 2 != 0) {
                        is_safe = true;
                    }
                }

                if (is_safe) {
                    if (!visited[nr][nc][n_parity]) {
                        visited[nr][nc][n_parity] = true;
                        q.push({nr, nc, nt});
                    }
                }
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
