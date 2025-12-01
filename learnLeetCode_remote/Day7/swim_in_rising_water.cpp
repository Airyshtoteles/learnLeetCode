#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

// Day 7 — Swim in Rising Water (LeetCode #778, Hard)
// Approach: Dijkstra-style (min-heap) where the path cost is the max height along the path.
// We expand the cell with the smallest current path cost. Once we pop (n-1,n-1), that's optimal.
// Time: O(n^2 log n), Space: O(n^2)

int swimInWater(const vector<vector<int>>& grid) {
    int n = (int)grid.size();
    // min-heap of (time_so_far, r, c), where time_so_far is max height seen along the path
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    pq.emplace(grid[0][0], 0, 0);

    const int dr[4] = {1,-1,0,0};
    const int dc[4] = {0,0,1,-1};

    while (!pq.empty()) {
        auto [t, r, c] = pq.top();
        pq.pop();
        if (visited[r][c]) continue;
        visited[r][c] = true;
        if (r == n - 1 && c == n - 1) return t; // first time we reach target is optimal

        for (int k = 0; k < 4; ++k) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nc < 0 || nr >= n || nc >= n || visited[nr][nc]) continue;
            int nt = max(t, grid[nr][nc]);
            pq.emplace(nt, nr, nc);
        }
    }
    return -1; // unreachable (shouldn't happen with problem constraints)
}

int main() {
    vector<vector<int>> grid1{{0,2},{1,3}};
    cout << swimInWater(grid1) << "\n"; // expected 3

    // Basic checks
    if (swimInWater(grid1) != 3) return 1;

    // Additional small case
    vector<vector<int>> grid2{{0}}; // already at destination
    if (swimInWater(grid2) != 0) return 1;

    vector<vector<int>> grid3{{0,1,2},{5,4,3},{6,7,8}}; // must wait to pass through increasing heights
    if (swimInWater(grid3) != 8) return 1;

    return 0;
}