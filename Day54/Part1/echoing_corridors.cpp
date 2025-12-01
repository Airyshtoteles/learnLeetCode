#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

struct Point {
    int r, c;
    bool operator==(const Point& other) const {
        return r == other.r && c == other.c;
    }
    bool operator<(const Point& other) const {
        if (r != other.r) return r < other.r;
        return c < other.c;
    }
};

int dist_manhattan(Point p1, Point p2) {
    return abs(p1.r - p2.r) + abs(p1.c - p2.c);
}

int solve_echoing_corridors(int R, int C, vector<string> grid) {
    Point start, end;
    vector<Point> portals;
    
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == 'S') start = {i, j};
            else if (grid[i][j] == 'E') end = {i, j};
            else if (grid[i][j] == 'P') portals.push_back({i, j});
        }
    }

    // Precompute portal destinations
    map<Point, Point> portal_map;
    if (portals.size() > 1) {
        for (const auto& p1 : portals) {
            int max_d = -1;
            Point target = p1;
            for (const auto& p2 : portals) {
                if (p1 == p2) continue;
                int d = dist_manhattan(p1, p2);
                if (d > max_d) {
                    max_d = d;
                    target = p2;
                } else if (d == max_d) {
                    // Tie-breaking: smallest r, then smallest c
                    if (p2.r < target.r || (p2.r == target.r && p2.c < target.c)) {
                        target = p2;
                    }
                }
            }
            portal_map[p1] = target;
        }
    } else if (portals.size() == 1) {
        portal_map[portals[0]] = portals[0]; // Teleport to self (no-op effectively, but logic holds)
    }

    queue<pair<Point, int>> q;
    q.push({start, 0});
    
    vector<vector<int>> d(R, vector<int>(C, -1));
    d[start.r][start.c] = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        Point curr = q.front().first;
        int steps = q.front().second;
        q.pop();

        if (curr == end) return steps;

        for (int i = 0; i < 4; ++i) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#') {
                Point next_pos = {nr, nc};
                
                // Check for portal
                if (grid[nr][nc] == 'P') {
                    next_pos = portal_map[next_pos];
                }

                if (d[next_pos.r][next_pos.c] == -1) {
                    d[next_pos.r][next_pos.c] = steps + 1;
                    q.push({next_pos, steps + 1});
                }
            }
        }
    }

    return -1;
}

int main() {
    // Test Case 1
    /*
    S . P
    # # .
    P . E
    
    S(0,0), P1(0,2), P2(2,0), E(2,2)
    P1 dist to P2 = |0-2| + |2-0| = 4.
    Path:
    (0,0)->(0,1) step 1
    (0,1)->(0,2)[P1] -> teleports to P2(2,0). Step 2.
    (2,0)->(2,1) Step 3
    (2,1)->(2,2)[E] Step 4.
    Result: 4
    */
    vector<string> grid1 = {
        "S.P",
        "##.",
        "P.E"
    };
    cout << "Test 1 (Expected 4): " << solve_echoing_corridors(3, 3, grid1) << endl;

    // Test Case 2: Unreachable
    vector<string> grid2 = {
        "S#P",
        "###",
        "P#E"
    };
    cout << "Test 2 (Expected -1): " << solve_echoing_corridors(3, 3, grid2) << endl;

    return 0;
}
