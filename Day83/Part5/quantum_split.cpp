#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <tuple>

using namespace std;

// Problem: Quantum Split.
// Rule: Move U -> (r-1, c) & (r-1, c+1)
//       Move D -> (r+1, c) & (r+1, c-1)
//       Move L -> (r, c-1) & (r-1, c-1)
//       Move R -> (r, c+1) & (r+1, c+1)
// Constraint: If ANY branch hits a wall, the move is INVALID (All blocked).
// Goal: Reach state where at least one branch is at Target.

struct Pos {
    int r, c;
    bool operator<(const Pos& other) const {
        return tie(r, c) < tie(other.r, other.c);
    }
    bool operator==(const Pos& other) const {
        return tie(r, c) == tie(other.r, other.c);
    }
};

int main() {
    int R, C;
    if (!(cin >> R >> C)) return 0;
    
    vector<string> grid(R);
    Pos start = {-1, -1}, target = {-1, -1};
    
    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == 'S') start = {i, j};
            if (grid[i][j] == 'T') target = {i, j};
        }
    }

    set<vector<Pos>> visited;
    queue<pair<vector<Pos>, int>> q;
    
    vector<Pos> initial_state = {start};
    q.push({initial_state, 0});
    visited.insert(initial_state);

    // Directions: 0:U, 1:D, 2:L, 3:R
    // Splits defined arbitrarily to fit "Branching" theme.
    // U: (-1, 0), (-1, 1)
    // D: (1, 0), (1, -1)
    // L: (0, -1), (-1, -1)
    // R: (0, 1), (1, 1)
    
    int dr1[] = {-1, 1, 0, 0};
    int dc1[] = {0, 0, -1, 1};
    int dr2[] = {-1, 1, -1, 1};
    int dc2[] = {1, -1, -1, 1};

    while (!q.empty()) {
        auto [current_positions, steps] = q.front();
        q.pop();

        // Check if target reached
        for (const auto& p : current_positions) {
            if (p == target) {
                cout << steps << endl;
                return 0;
            }
        }

        // Try 4 moves
        for (int i = 0; i < 4; ++i) {
            vector<Pos> next_positions;
            bool possible = true;
            
            for (const auto& p : current_positions) {
                // Branch 1
                int nr1 = p.r + dr1[i];
                int nc1 = p.c + dc1[i];
                
                // Branch 2
                int nr2 = p.r + dr2[i];
                int nc2 = p.c + dc2[i];
                
                // Check bounds and walls
                // If ANY branch hits wall or out of bounds, move is invalid.
                if (nr1 < 0 || nr1 >= R || nc1 < 0 || nc1 >= C || grid[nr1][nc1] == '#') {
                    possible = false; break;
                }
                if (nr2 < 0 || nr2 >= R || nc2 < 0 || nc2 >= C || grid[nr2][nc2] == '#') {
                    possible = false; break;
                }
                
                next_positions.push_back({nr1, nc1});
                next_positions.push_back({nr2, nc2});
            }
            
            if (possible) {
                // Sort and unique (Merge)
                sort(next_positions.begin(), next_positions.end());
                next_positions.erase(unique(next_positions.begin(), next_positions.end()), next_positions.end());
                
                if (visited.find(next_positions) == visited.end()) {
                    visited.insert(next_positions);
                    q.push({next_positions, steps + 1});
                }
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
