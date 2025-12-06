#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

int N, M;
vector<string> initial_grid;
int dist[105][105][105]; // N, M <= 100? Prompt says N, M <= 300 in Day 57, here not specified. I'll use 105. If larger, need dynamic.
// Prompt example is small. I'll assume N, M <= 100.

int dr[] = {0, 0, 1, -1, 0}; // 5 moves: Right, Left, Down, Up, Stay
int dc[] = {1, -1, 0, 0, 0};

bool is_wall(int r, int c, int t) {
    // Wall at (r, c) at time t if initial_grid[r][(c - t % M + M) % M] == 'W'
    int original_c = (c - t % M + M) % M;
    return initial_grid[r][original_c] == 'W';
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> N >> M)) return 0;
    initial_grid.resize(N);
    
    int startR, startC, endR, endC;
    
    for (int i = 0; i < N; ++i) {
        cin >> initial_grid[i];
        for (int j = 0; j < M; ++j) {
            if (initial_grid[i][j] == 'S') {
                startR = i; startC = j;
            } else if (initial_grid[i][j] == 'E') {
                endR = i; endC = j;
            }
        }
    }

    // Init dist
    // Use vector for safety if N, M > 100
    // vector<vector<vector<int>>> dist(N, vector<vector<int>>(M, vector<int>(M, 1e9)));
    // But M is the cycle length.
    // I'll use a flattened vector or just fixed size if N, M are small.
    // Let's use dynamic vector.
    vector<vector<vector<int>>> d(N, vector<vector<int>>(M, vector<int>(M, 1e9)));

    queue<tuple<int, int, int>> q;
    d[startR][startC][0] = 0;
    q.push({startR, startC, 0});

    while (!q.empty()) {
        auto [r, c, t] = q.front();
        q.pop();

        if (r == endR && c == endC) {
            cout << t << endl;
            return 0;
        }

        int nt = t + 1;
        for (int i = 0; i < 5; ++i) { // Include stay? Prompt says "Anda juga bergerak 1 langkah per turn". Usually implies mandatory move or stay is a move.
            // "Anda juga bergerak 1 langkah per turn" -> You move 1 step.
            // Does it allow waiting? "0 = kosong".
            // Usually "move 1 step" means change position.
            // But in mazes with moving obstacles, waiting is often key.
            // I'll assume "Stay" is allowed (move to same cell).
            // If not, I'll remove i=4.
            // Let's check example.
            // S 0 W 0
            // 0 1 0 0
            // 0 0 0 E
            // W moves right.
            // If I move Right to (0,1). W moves to (0,3).
            // If I wait?
            // I'll include Stay.
            
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                // Check static walls
                if (initial_grid[nr][nc] == '1') continue;
                
                // Check sliding walls at time nt
                if (is_wall(nr, nc, nt)) continue;

                // Check visited state (mod M)
                if (d[nr][nc][nt % M] > nt) {
                    d[nr][nc][nt % M] = nt;
                    q.push({nr, nc, nt});
                }
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
