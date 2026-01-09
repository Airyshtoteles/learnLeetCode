#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Problem: Adaptive Fog Oracle.
// Oracle can lie k times.
// We want to know if a strategy exists to reach Target.
// Since we can query indefinitely (or at least enough times), we can determine the true state of any cell.
// If we query a cell k+1 times and get consistent answers, we know the truth?
// Actually, if we query 2k+1 times, majority wins? No, Oracle lies adaptively.
// But if we query a cell k+1 times and get "Blocked" every time, it MUST be blocked.
// (If it was free, Oracle would have to lie k+1 times, which is > k).
// So if we get k+1 "Blocked", it is Blocked.
// If we get even one "Free", it MIGHT be Free.
// But if we query enough, we can force the truth.
// Effectively, if the underlying grid allows a path, we can find it.
// So the problem reduces to: Is there a path in the provided grid?
// We assume the input grid represents the "True Map" or the "Map we need to traverse".

struct Point {
    int r, c;
};

int main() {
    int R, C, K;
    if (!(cin >> R >> C >> K)) return 0;

    vector<string> grid(R);
    Point start = {-1, -1}, target = {-1, -1};

    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == 'S') start = {i, j};
            if (grid[i][j] == 'T') target = {i, j};
        }
    }

    if (start.r == -1 || target.r == -1) {
        cout << "Impossible" << endl;
        return 0;
    }

    queue<Point> q;
    q.push(start);
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    visited[start.r][start.c] = true;

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr.r == target.r && curr.c == target.c) {
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
