#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>

using namespace std;

int N;
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

typedef vector<vector<int>> Grid;

set<pair<int, int>> get_cluster(const Grid& g, int r, int c) {
    int val = g[r][c];
    set<pair<int, int>> cluster;
    if (val == 0) return cluster;
    
    cluster.insert({r, c});
    queue<pair<int, int>> q;
    q.push({r, c});
    set<pair<int, int>> seen;
    seen.insert({r, c});
    
    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        
        for (int i = 0; i < 4; ++i) {
            int nr = curr.first + dr[i];
            int nc = curr.second + dc[i];
            
            if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                if (g[nr][nc] == val && seen.find({nr, nc}) == seen.end()) {
                    seen.insert({nr, nc});
                    cluster.insert({nr, nc});
                    q.push({nr, nc});
                }
            }
        }
    }
    return cluster;
}

Grid apply_collapse(Grid g) {
    set<pair<int, int>> to_zero;
    set<pair<int, int>> visited_cells;
    
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (visited_cells.find({r, c}) == visited_cells.end() && g[r][c] != 0) {
                set<pair<int, int>> cluster = get_cluster(g, r, c);
                visited_cells.insert(cluster.begin(), cluster.end());
                if (cluster.size() >= 3) {
                    to_zero.insert(cluster.begin(), cluster.end());
                }
            }
        }
    }
    
    for (auto p : to_zero) {
        g[p.first][p.second] = 0;
    }
    return g;
}

int solve_quantum_tile(Grid grid, int target_r, int target_c, int K, int M) {
    N = grid.size();
    
    queue<pair<Grid, int>> q;
    q.push({grid, 0});
    
    set<Grid> visited;
    visited.insert(grid);
    
    while (!q.empty()) {
        pair<Grid, int> curr = q.front();
        Grid curr_grid = curr.first;
        int steps = curr.second;
        q.pop();
        
        if (curr_grid[target_r][target_c] == K) {
            return steps;
        }
        
        if (steps >= M) continue;
        
        set<pair<int, int>> candidates;
        candidates.insert({target_r, target_c});
        
        int curr_val = curr_grid[target_r][target_c];
        for (int i = 0; i < 4; ++i) {
            int nr = target_r + dr[i];
            int nc = target_c + dc[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                if (curr_grid[nr][nc] == curr_val) {
                    candidates.insert({nr, nc});
                }
            }
        }
        
        for (auto p : candidates) {
            Grid next_grid = curr_grid;
            next_grid[p.first][p.second] = (next_grid[p.first][p.second] * 2) % 10;
            
            Grid collapsed_grid = apply_collapse(next_grid);
            
            if (visited.find(collapsed_grid) == visited.end()) {
                visited.insert(collapsed_grid);
                q.push({collapsed_grid, steps + 1});
            }
        }
    }
    
    return -1;
}

int main() {
    Grid grid = {
        {1, 1, 2},
        {1, 5, 5},
        {2, 5, 5}
    };
    int r = 0, c = 0, K = 4, M = 5;
    
    cout << "Min Steps: " << solve_quantum_tile(grid, r, c, K, M) << endl;
    
    return 0;
}
