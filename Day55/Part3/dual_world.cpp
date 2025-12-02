#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

struct State {
    int r, c, w; // w: 0=Light, 1=Dark
    int dist;
};

int solve_dual_world(int N, pair<int, int> start, pair<int, int> target, 
                     vector<pair<int, int>> portals, 
                     vector<pair<int, int>> light_hazards, 
                     vector<pair<int, int>> dark_hazards) {
    
    // Hazards sets
    set<pair<int, int>> haz[2];
    for (auto p : light_hazards) haz[0].insert(p);
    for (auto p : dark_hazards) haz[1].insert(p);

    // Portals set
    set<pair<int, int>> portal_set;
    for (auto p : portals) portal_set.insert(p);

    // BFS
    queue<State> q;
    // dist[r][c][w]
    vector<vector<vector<int>>> d(N, vector<vector<int>>(N, vector<int>(2, -1)));

    // Start at Light (0)
    if (haz[0].count(start)) return -1; // Start is hazardous?
    
    d[start.first][start.second][0] = 0;
    q.push({start.first, start.second, 0, 0});

    int dr[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dc[] = {1, 2, 2, 1, -1, -2, -2, -1};

    while (!q.empty()) {
        auto [r, c, w, dist] = q.front();
        q.pop();

        if (r == target.first && c == target.second && w == 1) return dist;

        // 1. Move
        if (w == 0) {
            // Light: Normal Knight
            for (int i = 0; i < 8; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < N && nc >= 0 && nc < N && !haz[0].count({nr, nc})) {
                    if (d[nr][nc][0] == -1) {
                        d[nr][nc][0] = dist + 1;
                        q.push({nr, nc, 0, dist + 1});
                    }
                }
            }
        } else {
            // Dark: Double Knight
            // Generate all reachable squares
            // 2 steps.
            // We can use a set to avoid duplicates for this expansion
            set<pair<int, int>> next_positions;
            for (int i = 0; i < 8; ++i) {
                int mr = r + dr[i];
                int mc = c + dc[i];
                // Intermediate square must be within bounds? Yes.
                // Does it need to be safe? "Tanpa berhenti di tengah". Usually implies we jump over.
                // But the intermediate position must exist on the board.
                if (mr >= 0 && mr < N && mc >= 0 && mc < N) {
                    for (int j = 0; j < 8; ++j) {
                        int nr = mr + dr[j];
                        int nc = mc + dc[j];
                        if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                            next_positions.insert({nr, nc});
                        }
                    }
                }
            }

            for (auto p : next_positions) {
                int nr = p.first;
                int nc = p.second;
                if (!haz[1].count({nr, nc})) {
                    if (d[nr][nc][1] == -1) {
                        d[nr][nc][1] = dist + 1;
                        q.push({nr, nc, 1, dist + 1});
                    }
                }
            }
        }

        // 2. Portal Swap
        if (portal_set.count({r, c})) {
            int nw = 1 - w;
            if (!haz[nw].count({r, c})) {
                if (d[r][c][nw] == -1) {
                    d[r][c][nw] = dist + 1;
                    q.push({r, c, nw, dist + 1});
                }
            }
        }
    }

    return -1;
}

int main() {
    // Test 1
    // 5x5. Start (0,0). Target (3,2).
    // Light: (0,0) -> (2,1).
    // Portal at (2,1). Swap to Dark.
    // Dark: (2,1) -> (4,0) -> (3,2).
    // Path: (0,0,L) -> (2,1,L) [1 step] -> (2,1,D) [2 steps] -> (3,2,D) [3 steps].
    
    int N = 5;
    pair<int, int> start = {0, 0};
    pair<int, int> target = {3, 2};
    vector<pair<int, int>> portals = {{2, 1}};
    vector<pair<int, int>> l_haz = {};
    vector<pair<int, int>> d_haz = {};

    cout << "Test 1 (Expected 3): " << solve_dual_world(N, start, target, portals, l_haz, d_haz) << endl;

    return 0;
}
