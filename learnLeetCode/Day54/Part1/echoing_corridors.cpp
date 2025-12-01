#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int r, c;
    bool operator==(const Point& other) const {
        return r == other.r && c == other.c;
    }
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

int dist(Point p1, Point p2) {
    return abs(p1.r - p2.r) + abs(p1.c - p2.c);
}

int solve_echoing_corridors(int N, int M, const vector<vector<int>>& grid) {
    vector<Point> portals;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            if (grid[r][c] == 2) {
                portals.push_back({r, c});
            }
        }
    }

    // Precompute destinations
    // Map (r,c) -> index in portals
    vector<vector<int>> portal_idx(N, vector<int>(M, -1));
    for (int i = 0; i < portals.size(); ++i) {
        portal_idx[portals[i].r][portals[i].c] = i;
    }

    vector<int> dest_idx(portals.size());
    for (int i = 0; i < portals.size(); ++i) {
        int max_d = -1;
        int best_j = -1;
        for (int j = 0; j < portals.size(); ++j) {
            if (i == j) continue;
            int d = dist(portals[i], portals[j]);
            if (d > max_d) {
                max_d = d;
                best_j = j;
            } else if (d == max_d) {
                if (best_j == -1 || j < best_j) {
                    best_j = j;
                }
            }
        }
        dest_idx[i] = best_j; // Can be -1 if only 1 portal
    }

    // BFS
    vector<vector<int>> d(N, vector<int>(M, -1));
    queue<Point> q;

    q.push({0, 0});
    d[0][0] = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        Point u = q.front();
        q.pop();

        if (u.r == N - 1 && u.c == M - 1) return d[u.r][u.c];

        for (int i = 0; i < 4; ++i) {
            int nr = u.r + dr[i];
            int nc = u.c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                if (grid[nr][nc] == 1) continue; // Wall

                Point next_pos = {nr, nc};
                
                // Check portal logic
                if (grid[nr][nc] == 2) {
                    int p_id = portal_idx[nr][nc];
                    if (p_id != -1 && dest_idx[p_id] != -1) {
                        // Teleport
                        next_pos = portals[dest_idx[p_id]];
                    }
                }

                if (d[next_pos.r][next_pos.c] == -1) {
                    d[next_pos.r][next_pos.c] = d[u.r][u.c] + 1;
                    q.push(next_pos);
                }
            }
        }
    }

    return -1;
}

int main() {
    // Example 1
    // 3x3
    // S . P
    // . # .
    // P . E
    // Portals at (0,2) and (2,0). Dist = 4.
    // (0,2) teleports to (2,0).
    // (2,0) teleports to (0,2).
    // Path: (0,0)->(0,1)->(0,2)-warp->(2,0)->(2,1)->(2,2).
    // Steps:
    // (0,0) 0
    // (0,1) 1
    // (0,2) warp to (2,0). So dist[(2,0)] = 2.
    // (2,1) 3
    // (2,2) 4.
    
    vector<vector<int>> grid1 = {
        {0, 0, 2},
        {0, 1, 0},
        {2, 0, 0}
    };
    
    cout << "Test 1: " << solve_echoing_corridors(3, 3, grid1) << endl;

    // Example 2: No path
    vector<vector<int>> grid2 = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 0}
    };
    cout << "Test 2: " << solve_echoing_corridors(3, 3, grid2) << endl;

    return 0;
}
