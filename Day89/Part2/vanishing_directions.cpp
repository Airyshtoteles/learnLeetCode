#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

// Problem: Dungeon With Vanishing Directions
// Any edge used is removed?
// "Saat kamu keluar dari sel lewat satu arah, arah itu hilang permanen".
// Goal: Reach Target.
// This is finding a simple path. 
// A single path uses 1 outgoing edge per visited node.
// Initially, we have 4 (or fewer if boundary/wall) outgoing edges.
// Traversing a simple path reduces degree by 1.
// Unless we visit the same node multiple times?
// "Apakah target bisa dicapai?".
// Just need ONE path. 
// Standard BFS is sufficient to find if Target is reachable.
// (Unless there are trap conditions like "Must visit X first").
// Assuming standard "Reach T from S".

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    int StartR, StartC, TargetR, TargetC;
    cin >> StartR >> StartC >> TargetR >> TargetC;

    vector<string> grid(N);
    for (int i = 0; i < N; ++i) cin >> grid[i];

    // BFS
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    q.push({StartR, StartC});
    visited[StartR][StartC] = true;

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (r == TargetR && c == TargetC) {
            cout << "Possible" << endl;
            return 0;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M && 
                grid[nr][nc] != '#' && !visited[nr][nc]) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    cout << "Impossible" << endl;
    return 0;
}
