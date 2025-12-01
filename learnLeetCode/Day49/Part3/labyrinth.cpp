#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct State {
    int r, c, time;
};

int solve_labyrinth(const vector<vector<int>>& grid, int K) {
    int N = grid.size();
    int M = grid[0].size();
    
    queue<State> q;
    q.push({0, 0, 0});
    
    // Visited: visited[r][c][time % K]
    vector<vector<vector<bool>>> visited(N, vector<vector<bool>>(M, vector<bool>(K, false)));
    visited[0][0][0] = true;
    
    // Directions: Right, Left, Down, Up, Wait
    int dr[] = {0, 0, 1, -1, 0};
    int dc[] = {1, -1, 0, 0, 0};
    
    while (!q.empty()) {
        State current = q.front();
        q.pop();
        
        if (current.r == N - 1 && current.c == M - 1) {
            return current.time;
        }
        
        int next_time = current.time + 1;
        int mod_time = next_time % K;
        
        for (int i = 0; i < 5; ++i) {
            int nr = current.r + dr[i];
            int nc = current.c + dc[i];
            
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                // Check if blocked: (next_time + grid[nr][nc]) % K == 0
                if ((next_time + grid[nr][nc]) % K != 0) {
                    if (!visited[nr][nc][mod_time]) {
                        visited[nr][nc][mod_time] = true;
                        q.push({nr, nc, next_time});
                    }
                }
            }
        }
    }
    
    return -1;
}

int main() {
    vector<vector<int>> grid = {
        {1, 2},
        {3, 4}
    };
    int K = 3;
    
    cout << "Minimum Time: " << solve_labyrinth(grid, K) << endl;
    
    return 0;
}
