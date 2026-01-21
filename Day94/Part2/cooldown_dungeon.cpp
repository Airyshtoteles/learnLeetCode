#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <tuple>

using namespace std;

// Problem 2: Dungeon With Direction Cooldown
// BFS State: (r, c, cd0, cd1, cd2, cd3)
// Since C is cooldown length.
// If C is small (e.g. <= 4), we track counters.
// If C is larger, this state space explodes.
// "Cooldown C steps".
// Assuming C is small for typical grid puzzles.
// If Direction D used, D becomes unavailable for C steps.
// State can be: (r, c, mask_of_available_time)
// Actually, tracking (r, c, t_since_last_move[4]) where t capped at C?
// Simplification: We need to know if D is allowed.
// D allowed if current_time - last_used_time_of_D > C.
// BFS usually tracks Min Distance.
// But availability depends on Path History not just current Time.
// Wait: "Setelah bergerak ke suatu arah, arah itu cooldown c langkah".
// If I move UP at t=1. UP is CD until t = 1+C.
// So at t=2...1+C, UP is invalid.
// This is absolute time dependency.
// State: (r, c, last_t0, last_t1, last_t2, last_t3) - relative to current dist?
// Better: (r, c, wait0, wait1, wait2, wait3).
// wait_k = number of steps remaining until dir k is valid.
// Max value of wait_k is C.
// State space: N * M * (C+1)^4.
// If C=3, 4^4 = 256. 20x20x256 ~ 100k states. Feasible.

struct State {
    int r, c;
    int w[4];
};

int main() {
    int R, C_grid, Cooldown;
    if (!(cin >> R >> C_grid >> Cooldown)) return 0;
    
    vector<string> grid(R);
    for(int i=0; i<R; ++i) cin >> grid[i];
    
    // BFS
    // 4 dimensions for cooldowns. Flattening for visited array?
    // Using a set or simpler, mapped array?
    // Limits: assume C <= 4.
    
    int max_cd_state = 1;
    for(int k=0; k<4; k++) max_cd_state *= (Cooldown + 1);
    
    vector<vector<vector<bool>>> visited(R, vector<vector<bool>>(C_grid, vector<bool>(max_cd_state, false)));
    
    queue<pair<State, int>> q;
    State start = {0, 0, {0,0,0,0}};
    q.push({start, 0});
    visited[0][0][0] = true;
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    // 0: U, 1: D, 2: L, 3: R
    
    while(!q.empty()){
        auto [s, dist] = q.front();
        q.pop();
        
        if (s.r == R-1 && s.c == C_grid-1) {
            cout << "YES " << dist << endl;
            return 0;
        }
        
        for(int i=0; i<4; ++i){
            // Check if direction i is on cooldown
            if (s.w[i] > 0) continue;
            
            int nr = s.r + dr[i];
            int nc = s.c + dc[i];
            
            if (nr >= 0 && nr < R && nc >= 0 && nc < C_grid && grid[nr][nc] != '#') {
                State next_s;
                next_s.r = nr;
                next_s.c = nc;
                
                // Update cooldowns
                // Dir i becomes Cooldown.
                // Others decrement by 1.
                int cd_hash = 0;
                int mult = 1;
                
                for(int k=0; k<4; ++k){
                    int val;
                    if (k == i) val = Cooldown;
                    else val = max(0, s.w[k] - 1);
                    
                    next_s.w[k] = val;
                    cd_hash += val * mult;
                    mult *= (Cooldown + 1);
                }
                
                if (!visited[nr][nc][cd_hash]) {
                    visited[nr][nc][cd_hash] = true;
                    q.push({next_s, dist + 1});
                }
            }
        }
    }
    
    cout << "NO" << endl;
    
    return 0;
}
