#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int solve_bfs(int start_r, int start_c, int R, int C, const vector<vector<int>>& grid) {
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    
    long long current_power = grid[start_r][start_c];
    visited[start_r][start_c] = true;
    int count = 1;
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    // Add neighbors to PQ
    for(int i=0; i<4; ++i) {
        int nr = start_r + dr[i];
        int nc = start_c + dc[i];
        if(nr >= 0 && nr < R && nc >= 0 && nc < C) {
            pq.push({grid[nr][nc], nr, nc});
            visited[nr][nc] = true; // Mark as in-queue/visited to avoid duplicates
        }
    }
    
    while(!pq.empty()) {
        auto [val, r, c] = pq.top();
        
        if (current_power >= val) {
            pq.pop();
            current_power += val;
            count++;
            
            for(int i=0; i<4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if(nr >= 0 && nr < R && nc >= 0 && nc < C && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    pq.push({grid[nr][nc], nr, nc});
                }
            }
        } else {
            // Cannot eat the smallest neighbor. Stuck.
            break;
        }
    }
    return count;
}

int main() {
    int R, C;
    if (cin >> R >> C) {
        vector<vector<int>> grid(R, vector<int>(C));
        int max_val = -1;
        for(int i=0; i<R; ++i) {
            for(int j=0; j<C; ++j) {
                cin >> grid[i][j];
                if (grid[i][j] > max_val) {
                    max_val = grid[i][j];
                }
            }
        }
        
        // Optimization: Only start from cells with max_val.
        // Starting with max_val gives the highest initial power.
        int max_revealed = 0;
        for(int i=0; i<R; ++i) {
            for(int j=0; j<C; ++j) {
                if (grid[i][j] == max_val) {
                    max_revealed = max(max_revealed, solve_bfs(i, j, R, C, grid));
                }
            }
        }
        
        cout << max_revealed << endl;
    }
    return 0;
}
