#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

struct State {
    int r, c, rot; // rot: 0=0, 1=90, 2=180, 3=270
    int dist;
};

// Rotate point (r, c) in NxN grid 90 degrees clockwise
pair<int, int> rotate_point(int r, int c, int N) {
    return {c, N - 1 - r};
}

// Rotate grid 90 degrees clockwise
vector<string> rotate_grid(const vector<string>& grid) {
    int N = grid.size();
    vector<string> new_grid(N, string(N, ' '));
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            new_grid[c][N - 1 - r] = grid[r][c];
        }
    }
    return new_grid;
}

int solve_gravity_shift(int N, vector<string> grid) {
    // Precompute 4 grids
    vector<vector<string>> grids(4);
    grids[0] = grid;
    for (int i = 1; i < 4; ++i) {
        grids[i] = rotate_grid(grids[i - 1]);
    }

    // Find Start and Target in initial grid
    int sr, sc, tr, tc;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (grid[r][c] == 'S') { sr = r; sc = c; }
            if (grid[r][c] == 'T') { tr = r; tc = c; }
        }
    }

    // Precompute Target positions for each rotation
    // Actually, we don't need to. We can just check if grid[r][c] == 'T' in the current rotation.
    // Because 'T' rotates with the grid.
    // So if we are at (r,c) in rotation 'rot', and grids[rot][r][c] == 'T', we win.
    
    // BFS
    // dist[rot][r][c]
    vector<vector<vector<int>>> d(4, vector<vector<int>>(N, vector<int>(N, -1)));
    queue<State> q;

    d[0][sr][sc] = 0;
    q.push({sr, sc, 0, 0});

    int dr[] = {-1, 1, 0, 0}; // U, D, L, R
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [r, c, rot, dist] = q.front();
        q.pop();

        // Check if current pos is Target
        if (grids[rot][r][c] == 'T') return dist;

        // Try 4 gravity directions
        for (int i = 0; i < 4; ++i) {
            // Fall in direction i
            int nr = r;
            int nc = c;
            
            // Slide until blocked
            while (true) {
                int next_r = nr + dr[i];
                int next_c = nc + dc[i];
                
                if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= N || grids[rot][next_r][next_c] == '#') {
                    break; // Blocked
                }
                nr = next_r;
                nc = next_c;
                
                // Check if we passed T?
                // "Player jatuh sampai menabrak". Usually you stop AT the wall.
                // If T is in the path, do we stop?
                // "mencapai T". Usually implies stopping at T or passing through?
                // "Jatuh sampai menabrak". Usually implies you can't stop mid-air.
                // But if you pass T, you reached it?
                // Let's assume we must END the turn at T?
                // Or if we pass T, we win immediately?
                // "mencapai T". I'll assume if we touch T during fall, we win.
                if (grids[rot][nr][nc] == 'T') return dist + 1;
            }

            // After fall, rotate
            // Current pos in 'rot' is (nr, nc).
            // Next rot is (rot + 1) % 4.
            // Pos transforms: (nr, nc) -> (nc, N - 1 - nr).
            
            pair<int, int> next_pos = rotate_point(nr, nc, N);
            int n_rot = (rot + 1) % 4;
            
            if (d[n_rot][next_pos.first][next_pos.second] == -1) {
                d[n_rot][next_pos.first][next_pos.second] = dist + 1;
                q.push({next_pos.first, next_pos.second, n_rot, dist + 1});
            }
        }
    }

    return -1;
}

int main() {
    // Test 1
    /*
    S . .
    . . .
    . . T
    
    1. Gravity Right. S(0,0) -> (0,2).
       Rotate 90. (0,2) -> (2, 2).
       Grid 90:
       . . S
       . . .
       T . .
       Wait, T was at (2,2). Rotate (2,2) -> (2, 0).
       So at rot 1, I am at (2,2). T is at (2,0).
    2. Gravity Left. (2,2) -> (2,0).
       Hit T! Win.
       Steps: 2.
    */
    vector<string> grid1 = {
        "S..",
        "...",
        "..T"
    };
    cout << "Test 1 (Expected 2): " << solve_gravity_shift(3, grid1) << endl;

    // Test 2: Wall
    /*
    S # .
    . . .
    . . T
    
    1. Right. S(0,0) -> (0,0) (Blocked by # at 0,1).
       Rotate. (0,0) -> (0,2).
       Grid 90:
       . . S
       . . #
       T . .
       I am at (0,2). T at (2,0).
    2. Down. (0,2) -> (2,2).
       Rotate. (2,2) -> (2,0).
       Grid 180:
       T . .
       . . .
       . # S
       I am at (2,0). T at (0,0).
    3. Up. (2,0) -> (0,0). Hit T.
       Steps: 3.
    */
    vector<string> grid2 = {
        "S#.",
        "...",
        "..T"
    };
    cout << "Test 2 (Expected 3): " << solve_gravity_shift(3, grid2) << endl;

    return 0;
}
