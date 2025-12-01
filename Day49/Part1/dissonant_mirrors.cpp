#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

struct State {
    int r, c, grid_state, steps;
};

int solve_dissonant_mirrors(int n, int m, const vector<vector<int>>& grid) {
    // BFS State: {r, c, grid_state}
    // grid_state: 0 = Normal, 1 = Inverted
    
    queue<State> q;
    q.push({0, 0, 0, 0});
    
    // Visited array: visited[r][c][state]
    vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(2, false)));
    visited[0][0][0] = true;
    
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    
    while (!q.empty()) {
        State current = q.front();
        q.pop();
        
        if (current.r == n - 1 && current.c == m - 1) {
            return current.steps;
        }
        
        for (int i = 0; i < 4; ++i) {
            int nr = current.r + dr[i];
            int nc = current.c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                int cell_val = grid[nr][nc] ^ current.grid_state;
                int new_state = current.grid_state;
                
                if (cell_val == 1) {
                    new_state = 1 - current.grid_state;
                }
                
                if (!visited[nr][nc][new_state]) {
                    visited[nr][nc][new_state] = true;
                    q.push({nr, nc, new_state, current.steps + 1});
                }
            }
        }
    }
    
    return -1;
}

int main() {
    vector<vector<int>> grid = {
        {0, 1},
        {1, 0}
    };
    
    int n = grid.size();
    int m = grid[0].size();
    
    cout << "Minimum Steps: " << solve_dissonant_mirrors(n, m, grid) << endl;
    
    return 0;
}
