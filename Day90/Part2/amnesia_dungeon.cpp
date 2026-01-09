#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

// Problem: Dungeon With Directional Amnesia
// Task: Reach (R-1, C-1) from (0,0).
// Constraint: Cannot enter a cell from the same direction twice.
// Interpretation: Directed Edge Capacity = 1.
// Since simple paths respect this (never entering a cell twice implies never entering from same direction twice),
// and standard BFS finds the shortest simple path, we can just use BFS.

int main() {
    int R, C;
    if (!(cin >> R >> C)) return 0;

    vector<string> grid(R);
    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
    }

    // BFS
    // visited[r][c] is enough because we only care about existence of a simple path.
    // If strict edge usage allowed loops (e.g. entering from Top, leaving, entering from Bottom, leaving, entering from Top => Fail),
    // BFS still finds a path if one exists without loops.
    // If the ONLY path requires loops (e.g. oscillating to wait for something), that's different.
    // But here no time dependency.
    
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    queue<pair<int, int>> q;

    if (grid[0][0] != '#') {
        q.push({0, 0});
        visited[0][0] = true;
    }

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    bool possible = false;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (r == R - 1 && c == C - 1) {
            possible = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C && 
                grid[nr][nc] != '#' && !visited[nr][nc]) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    if (possible) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
