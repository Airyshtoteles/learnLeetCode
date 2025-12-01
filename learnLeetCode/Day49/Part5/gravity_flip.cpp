#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <tuple>

using namespace std;

struct State {
    int r, c, g, cost;
};

int N, M;
int start_r, start_c, target_r, target_c;
int dr[] = {1, -1, 0, 0}; // Down, Up, Right, Left
int dc[] = {0, 0, 1, -1};

// Returns {r, c, hit_target}
tuple<int, int, bool> fall(int r, int c, int g, const vector<string>& grid) {
    int curr_r = r;
    int curr_c = c;
    
    while (true) {
        if (curr_r == target_r && curr_c == target_c) {
            return {curr_r, curr_c, true};
        }
        
        int nr = curr_r + dr[g];
        int nc = curr_c + dc[g];
        
        if (nr < 0 || nr >= N || nc < 0 || nc >= M || grid[nr][nc] == '#') {
            return {curr_r, curr_c, false};
        }
        
        curr_r = nr;
        curr_c = nc;
    }
}

int solve_gravity_flip(const vector<string>& grid) {
    N = grid.size();
    M = grid[0].size();
    
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            if (grid[r][c] == 'S') {
                start_r = r; start_c = c;
            } else if (grid[r][c] == 'T') {
                target_r = r; target_c = c;
            }
        }
    }
    
    // Initial Fall
    auto [fr, fc, hit] = fall(start_r, start_c, 0, grid);
    if (hit) return 0;
    
    deque<State> dq;
    dq.push_back({fr, fc, 0, 0});
    
    // Visited: [r][c][g] -> min_cost
    vector<vector<vector<int>>> dist(N, vector<vector<int>>(M, vector<int>(4, 1e9)));
    dist[fr][fc][0] = 0;
    
    while (!dq.empty()) {
        State current = dq.front();
        dq.pop_front();
        
        int r = current.r;
        int c = current.c;
        int g = current.g;
        int d = current.cost;
        
        if (d > dist[r][c][g]) continue;
        if (r == target_r && c == target_c) return d;
        
        // 1. Walk
        vector<int> walk_dirs;
        if (g <= 1) { walk_dirs = {2, 3}; }
        else { walk_dirs = {0, 1}; }
        
        for (int w : walk_dirs) {
            int nr = r + dr[w];
            int nc = c + dc[w];
            
            if (nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != '#') {
                // Check support
                int sr = nr + dr[g];
                int sc = nc + dc[g];
                bool supported = false;
                
                if (sr < 0 || sr >= N || sc < 0 || sc >= M || grid[sr][sc] == '#') {
                    supported = true;
                }
                
                if (supported) {
                    if (dist[nr][nc][g] > d) {
                        dist[nr][nc][g] = d;
                        dq.push_front({nr, nc, g, d});
                    }
                } else {
                    // Fall
                    auto [ffr, ffc, fhit] = fall(nr, nc, g, grid);
                    if (fhit) return d;
                    
                    if (dist[ffr][ffc][g] > d) {
                        dist[ffr][ffc][g] = d;
                        dq.push_front({ffr, ffc, g, d});
                    }
                }
            }
        }
        
        // 2. Flip
        for (int ng = 0; ng < 4; ++ng) {
            if (ng == g) continue;
            
            auto [ffr, ffc, fhit] = fall(r, c, ng, grid);
            int new_cost = d + 1;
            
            if (fhit) return new_cost;
            
            if (dist[ffr][ffc][ng] > new_cost) {
                dist[ffr][ffc][ng] = new_cost;
                dq.push_back({ffr, ffc, ng, new_cost});
            }
        }
    }
    
    return -1;
}

int main() {
    vector<string> grid = {
        "S....",
        "###.#",
        "....T",
        "#####"
    };
    
    cout << "Minimum Energy: " << solve_gravity_flip(grid) << endl;
    
    return 0;
}
