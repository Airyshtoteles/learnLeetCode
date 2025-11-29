#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

struct State {
    int r, c, g, flips, steps;
};

// 0:D, 1:U, 2:L, 3:R
int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, -1, 1};

int solve_celestial_shifter(vector<string>& grid, int K) {
    int R = grid.size();
    int C = grid[0].size();
    
    int start_r, start_c, end_r, end_c;
    
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (grid[r][c] == 'S') {
                start_r = r; start_c = c;
            } else if (grid[r][c] == 'E') {
                end_r = r; end_c = c;
            }
        }
    }
    
    queue<State> q;
    q.push({start_r, start_c, 0, K, 0});
    
    set<tuple<int, int, int, int>> visited;
    visited.insert({start_r, start_c, 0, K});
    
    while (!q.empty()) {
        State current = q.front();
        q.pop();
        
        if (current.r == end_r && current.c == end_c) {
            return current.steps;
        }
        
        // Check Falling
        int nr = current.r + dr[current.g];
        int nc = current.c + dc[current.g];
        bool is_falling = false;
        
        if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#') {
            is_falling = true;
        }
        
        if (is_falling) {
            if (visited.find({nr, nc, current.g, current.flips}) == visited.end()) {
                visited.insert({nr, nc, current.g, current.flips});
                q.push({nr, nc, current.g, current.flips, current.steps + 1});
            }
        } else {
            // Grounded
            
            // 1. Walk
            vector<int> perp_dirs;
            if (current.g == 0 || current.g == 1) {
                perp_dirs = {2, 3};
            } else {
                perp_dirs = {0, 1};
            }
            
            for (int d : perp_dirs) {
                int wr = current.r + dr[d];
                int wc = current.c + dc[d];
                
                if (wr >= 0 && wr < R && wc >= 0 && wc < C && grid[wr][wc] != '#') {
                    if (visited.find({wr, wc, current.g, current.flips}) == visited.end()) {
                        visited.insert({wr, wc, current.g, current.flips});
                        q.push({wr, wc, current.g, current.flips, current.steps + 1});
                    }
                }
            }
            
            // 2. Shift
            if (current.flips > 0) {
                for (int ng = 0; ng < 4; ++ng) {
                    if (ng != current.g) {
                        if (visited.find({current.r, current.c, ng, current.flips - 1}) == visited.end()) {
                            visited.insert({current.r, current.c, ng, current.flips - 1});
                            q.push({current.r, current.c, ng, current.flips - 1, current.steps + 1});
                        }
                    }
                }
            }
        }
    }
    
    return -1;
}

int main() {
    vector<string> grid1 = {
        "S..",
        "##.",
        "..E"
    };
    cout << "Min Steps (Ex 1): " << solve_celestial_shifter(grid1, 1) << endl;
    
    return 0;
}
