#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int N, M;
vector<string> grid;
int start_r, start_c;
vector<pair<int, int>> enemies;
int enemy_id[305][305];

// Returns a bitmask of killed enemies (using long long if K <= 60, else vector<bool>)
// Constraints: Max enemies 300. Need bitset or vector<bool>.
// Since we iterate 2^4 subsets, we can just use vector<int> of killed indices.

vector<int> simulate(int dr, int dc) {
    vector<int> killed;
    int r = start_r;
    int c = start_c;
    int bounces = 0;
    
    // Current direction
    int cdr = dr;
    int cdc = dc;
    
    // Avoid infinite loops (though with bounces=2 it terminates)
    // Max steps? N*M*3 is safe.
    int steps = 0;
    while (bounces < 2 && steps < N * M * 4) {
        int nr = r + cdr;
        int nc = c + cdc;
        
        // Check collision
        bool hit = false;
        if (nr < 0 || nr >= N || nc < 0 || nc >= M || grid[nr][nc] == '#') {
            hit = true;
        }
        
        if (hit) {
            bounces++;
            if (bounces >= 2) break;
            
            // Reflect
            // Since orthogonal, we just reverse the non-zero component
            cdr = -cdr;
            cdc = -cdc;
            
            // Don't move this step?
            // "Pantulan satu kali, lalu terus."
            // Usually it bounces off the surface.
            // So we stay at (r, c) and change direction.
            // Next step we move from (r, c) in new direction.
        } else {
            // Move
            r = nr;
            c = nc;
            if (enemy_id[r][c] != -1) {
                killed.push_back(enemy_id[r][c]);
            }
        }
        steps++;
    }
    return killed;
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> N >> M)) return 0;
    
    grid.resize(N);
    enemies.clear();
    start_r = -1;
    
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
        for (int j = 0; j < M; ++j) {
            enemy_id[i][j] = -1;
            if (grid[i][j] == 'S') {
                start_r = i;
                start_c = j;
                grid[i][j] = '.'; // Treat as empty
            } else if (grid[i][j] == 'E') {
                enemy_id[i][j] = enemies.size();
                enemies.push_back({i, j});
                grid[i][j] = '.'; // Treat as empty for movement
            }
        }
    }
    
    if (start_r == -1) {
        // Should not happen based on problem
        return 0;
    }
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    vector<vector<int>> paths(4);
    for (int i = 0; i < 4; ++i) {
        paths[i] = simulate(dr[i], dc[i]);
    }
    
    int min_arrows = 5;
    int total_enemies = enemies.size();
    
    for (int mask = 0; mask < (1 << 4); ++mask) {
        vector<bool> dead(total_enemies, false);
        int kill_count = 0;
        int arrows = 0;
        
        for (int i = 0; i < 4; ++i) {
            if ((mask >> i) & 1) {
                arrows++;
                for (int e : paths[i]) {
                    if (!dead[e]) {
                        dead[e] = true;
                        kill_count++;
                    }
                }
            }
        }
        
        if (kill_count == total_enemies) {
            min_arrows = min(min_arrows, arrows);
        }
    }
    
    if (min_arrows > 4) cout << -1 << endl;
    else cout << min_arrows << endl;
    
    return 0;
}
