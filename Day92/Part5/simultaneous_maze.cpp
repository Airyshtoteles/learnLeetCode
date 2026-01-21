#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

// Problem 5: Player in All Possible Mazes
// Objective: Find a single sequence of moves that navigates K different mazes simultaneously.
// Rule: Moving a direction applies to all mazes.
// If a move is blocked by a wall in a specific maze, the player in that maze stays put.
// Goal: Reach the destination (R-1, C-1) in ALL mazes simultaneously (or eventually? Let's say reaching and staying there? Or just visiting? Usually simple reach).
// Simpler version: Reach state where all are at target.
// Optimizations:
// State: (r1, c1, r2, c2, ..., rK, cK)
// Dimensions: 20x20 max? K=4 max? 20^4 is 160,000. manageable.

struct State {
    vector<pair<int, int>> positions;
    
    bool operator<(const State& other) const {
        return positions < other.positions;
    }
    bool operator==(const State& other) const {
        return positions == other.positions;
    }
};

int R, C, K;
vector<vector<string>> mazes;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
// U, D, L, R

bool is_wall(int k, int r, int c) {
    if (r < 0 || r >= R || c < 0 || c >= C) return true;
    return mazes[k][r][c] == '#';
}

int main() {
    if (!(cin >> K >> R >> C)) return 0;
    
    mazes.resize(K, vector<string>(R));
    for (int k = 0; k < K; ++k) {
        for (int i = 0; i < R; ++i) {
            cin >> mazes[k][i];
        }
    }

    State start_state;
    for (int k = 0; k < K; ++k) start_state.positions.push_back({0, 0});
    
    queue<pair<State, int>> q;
    q.push({start_state, 0});
    
    set<State> visited;
    visited.insert(start_state);
    
    while (!q.empty()) {
        auto [curr, dist] = q.front();
        q.pop();
        
        bool all_at_target = true;
        for (const auto& pos : curr.positions) {
            if (pos.first != R - 1 || pos.second != C - 1) {
                all_at_target = false;
                break;
            }
        }
        
        if (all_at_target) {
            cout << dist << endl;
            return 0;
        }
        
        // Try 4 directions
        for (int i = 0; i < 4; ++i) {
            State next_state = curr;
            bool changed = false;
            
            for (int k = 0; k < K; ++k) {
                int nr = curr.positions[k].first + dr[i];
                int nc = curr.positions[k].second + dc[i];
                
                // Check bounds and walls
                // Logic: If in bounds and not wall, move. Else stay.
                // Boundary check: If out of bounds, treat as wall? Or invalid move?
                // Usually "Grid" implies boundaries are hard walls.
                
                bool blocked = false;
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) blocked = true;
                else if (mazes[k][nr][nc] == '#') blocked = true;
                
                if (!blocked) {
                    next_state.positions[k] = {nr, nc};
                    // However, if we are already at target, do we stay?
                    // "Reach the destination".
                    // Usually if you move off target, you move off.
                    // Unless target is sticky. Assuming normal physics.
                }
            }
            
            if (visited.find(next_state) == visited.end()) {
                visited.insert(next_state);
                q.push({next_state, dist + 1});
            }
        }
    }
    
    cout << "-1" << endl;
    
    return 0;
}
