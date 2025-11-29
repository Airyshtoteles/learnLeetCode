#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <map>
#include <set>

using namespace std;

struct State {
    int r, c, mask, steps;
};

int solve_crystal_labyrinth(const vector<string>& grid, int K) {
    int N = grid.size();
    int M = grid[0].size();
    
    int start_r, start_c, end_r, end_c;
    vector<pair<int, int>> teleports;
    vector<tuple<int, int, int>> crystals;
    
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            char cell = grid[r][c];
            if (cell == 'S') {
                start_r = r; start_c = c;
            } else if (cell == 'E') {
                end_r = r; end_c = c;
            } else if (cell == 'T') {
                teleports.push_back({r, c});
            } else if (cell >= '1' && cell <= '9') {
                crystals.push_back({r, c, cell - '0'});
            }
        }
    }
    
    int num_crystals = crystals.size();
    map<pair<int, int>, int> crystal_map;
    for (int i = 0; i < num_crystals; ++i) {
        crystal_map[{get<0>(crystals[i]), get<1>(crystals[i])}] = i;
    }
    
    // BFS
    deque<State> q;
    
    int start_mask = 0;
    if (crystal_map.count({start_r, start_c})) {
        start_mask |= (1 << crystal_map[{start_r, start_c}]);
    }
    
    q.push_back({start_r, start_c, start_mask, 0});
    
    // Visited: visited[r][c][mask]
    // Use a set or flattened vector?
    // N, M <= 50, Mask <= 512. 50*50*512 = 1.28e6. Vector is fine.
    // vector<vector<vector<bool>>> visited(N, vector<vector<bool>>(M, vector<bool>(1 << num_crystals, false)));
    // But num_crystals is dynamic. Use set for safety or flat vector.
    // Let's use set for simplicity in C++ unless TLE.
    set<tuple<int, int, int>> visited;
    visited.insert({start_r, start_c, start_mask});
    
    int max_value = -1;
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    
    while (!q.empty()) {
        State curr = q.front();
        q.pop_front();
        
        if (curr.r == end_r && curr.c == end_c) {
            int current_val = 0;
            for (int i = 0; i < num_crystals; ++i) {
                if ((curr.mask >> i) & 1) {
                    current_val += get<2>(crystals[i]);
                }
            }
            if (current_val > max_value) max_value = current_val;
        }
        
        if (curr.steps >= K) continue;
        
        // Teleport logic
        if (grid[curr.r][curr.c] == 'T') {
            for (auto t : teleports) {
                if (t.first == curr.r && t.second == curr.c) continue;
                if (visited.find({t.first, t.second, curr.mask}) == visited.end()) {
                    visited.insert({t.first, t.second, curr.mask});
                    q.push_front({t.first, t.second, curr.mask, curr.steps});
                }
            }
        }
        
        for (int i = 0; i < 4; ++i) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];
            
            if (nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != '#') {
                int new_mask = curr.mask;
                if (crystal_map.count({nr, nc})) {
                    new_mask |= (1 << crystal_map[{nr, nc}]);
                }
                
                if (visited.find({nr, nc, new_mask}) == visited.end()) {
                    visited.insert({nr, nc, new_mask});
                    q.push_back({nr, nc, new_mask, curr.steps + 1});
                }
            }
        }
    }
    
    return max_value == -1 ? 0 : max_value;
}

int main() {
    vector<string> grid = {
        "S.1#E",
        ".#.#.",
        "T.2.T"
    };
    int K = 10;
    cout << "Max Value: " << solve_crystal_labyrinth(grid, K) << endl;
    return 0;
}
