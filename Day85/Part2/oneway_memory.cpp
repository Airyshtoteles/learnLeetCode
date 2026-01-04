#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Problem: Dungeon With One-Way Memory
// Grid N x M.
// Rule: Can only enter a cell from one direction.
// Goal: Reach (N-1, M-1).
// Since we want a simple path (no cycles), we never re-enter a cell.
// Thus, the condition "enter from different direction" is never triggered on a simple path.
// So we just need to find a path.
// Assuming grid has obstacles ('#').

struct Point {
    int r, c;
};

int main() {
    int R, C;
    if (!(cin >> R >> C)) return 0;

    vector<string> grid(R);
    for (int i = 0; i < R; ++i) cin >> grid[i];

    queue<Point> q;
    q.push({0, 0});
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    visited[0][0] = true;

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr.r == R - 1 && curr.c == C - 1) {
            cout << "Possible" << endl;
            return 0;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C && !visited[nr][nc] && grid[nr][nc] != '#') {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    cout << "Impossible" << endl;
    return 0;
}
