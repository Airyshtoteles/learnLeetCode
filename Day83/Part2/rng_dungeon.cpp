#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

// RNG: x = (x * A + B) % M
// Map x to cell: r = (x / C) % R, c = x % C (Assuming x maps to linear index or similar)
// Or maybe x directly gives coords?
// Let's assume x maps to (x % R, (x / R) % C) or similar.
// Given "Dungeon berbentuk grid", let's assume standard mapping:
// r = x % R
// c = (x / R) % C  (if M is large enough)
// Or maybe just r = x % R, c = (x * A) % C? No, that's random.
// I will use: r = x % R, c = (x / R) % C. If x >= R*C, it wraps or we take modulo.
// Actually, let's just use r = (x / C) % R, c = x % C.

struct Point {
    int r, c;
};

int main() {
    long long R, C;
    if (!(cin >> R >> C)) return 0;
    long long A, B, M, X0;
    cin >> A >> B >> M >> X0;

    // 1. Find all blocked cells
    // The RNG sequence is x0, x1, ...
    // It will cycle.
    // We collect all unique blocked cells.
    
    set<long long> visited_x;
    vector<vector<bool>> blocked(R, vector<bool>(C, false));
    
    long long x = X0;
    while (visited_x.find(x) == visited_x.end()) {
        visited_x.insert(x);
        
        // Map x to cell
        // Heuristic mapping since not specified:
        long long r = (x / C) % R;
        long long c = x % C;
        
        if (r >= 0 && r < R && c >= 0 && c < C) {
            blocked[r][c] = true;
        }
        
        x = (x * A + B) % M;
    }

    // 2. BFS to find path
    if (blocked[0][0] || blocked[R-1][C-1]) {
        cout << "Impossible" << endl;
        return 0;
    }

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

            if (nr >= 0 && nr < R && nc >= 0 && nc < C && !blocked[nr][nc] && !visited[nr][nc]) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    cout << "Impossible" << endl;
    return 0;
}
