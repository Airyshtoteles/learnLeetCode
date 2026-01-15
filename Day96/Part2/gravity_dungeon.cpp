#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <map>

using namespace std;

// Problem 2: Gravity Dungeon
// State: (Time, R, C).
// We want minimum time.
// Gravity changes every K steps.
// Gravity Sequence: 0 (Down?), 1 (Left?), 2 (Up?), 3 (Right?).
// Or usually: Down -> Right -> Up -> Left (Clockwise).
// Directions: 0: (1, 0), 1: (0, -1), 2: (-1, 0), 3: (0, 1). (Clockwise from Down? D, L, U, R).
// Let's assume Clockwise starting Down.
// D: (1,0), L: (0,-1), U: (-1,0), R: (0,1).
// Rotatiing 90 deg?
// D -> L -> U -> R -> D?
//
// Logic:
// Priority Queue BFS.
// Map<State, MinTime>. State = (r, c, phase).
// Phase = (Time / K) % 4.
// Wait, Time is the cost. Logic:
// 1. Pop (time, r, c).
// 2. Try Move U,D,L,R (Time+1).
// 3. At Time+1:
//    Check Gravity Phase: P = ((Time+1)/K) % 4.
//    Apply Gravity fall loop.
//    New Pos (nr, nc).
// 4. Update Dist[(nr, nc, P)].

struct State {
    int r, c, phase;
    bool operator<(const State& other) const {
        return tie(r, c, phase) < tie(other.r, other.c, other.phase);
    }
};

int N_rows, M_cols, K_steps;
vector<string> grid;

int dr[] = {1, 0, -1, 0}; // Down, Left, Up, Right
int dc[] = {0, -1, 0, 1};

bool isValid(int r, int c) {
    return r >= 0 && r < N_rows && c >= 0 && c < M_cols && grid[r][c] != '#';
}

int main() {
    if (!(cin >> N_rows >> M_cols >> K_steps)) return 0;
    grid.resize(N_rows);
    int sr, sc, tr, tc;
    for(int i=0; i<N_rows; ++i) {
        cin >> grid[i];
        for(int j=0; j<M_cols; ++j) {
            if (grid[i][j] == 'S') { sr = i; sc = j; }
            if (grid[i][j] == 'E') { tr = i; tc = j; }
        }
    }
    
    // Dist map
    // vector<vector<vector<int>>> dist(N_rows, vector<vector<int>>(M_cols, vector<int>(4, 1e9)));
    // Actually phase is enough?
    // We visit a state (r,c,phase) with minimum time.
    // Is it possible that reaching later is better? 
    // Yes, if we need to wait for gravity.
    // But we iterate time.
    // To handle "Waiting", we can allow staying in place?
    // "Hanya bisa bergerak". Maybe staying is allowed? Usually yes.
    // I will add (0,0) move.
    
    // Priority Queue: Min time.
    priority_queue<tuple<int, int, int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
    
    // We need to track visited for (r, c, time % (4*K))? 
    // Just (r,c, phase) is NOT enough because phase transition time matters.
    // But time % (4*K) represents the full cycle.
    // Let's use 4*K states per cell. K can be 100? 400 * 2500 = 1,000,000. Feasible.
    
    int cycle = 4 * K_steps;
    vector<vector<vector<int>>> min_time(N_rows, vector<vector<int>>(M_cols, vector<int>(cycle, 1e9)));
    
    min_time[sr][sc][0] = 0;
    pq.push({0, sr, sc});
    
    while(!pq.empty()) {
        auto [t, r, c] = pq.top();
        pq.pop();
        
        int time_mod = t % cycle;
        if (t > min_time[r][c][time_mod]) continue;
        if (r == tr && c == tc) {
            cout << t << endl;
            return 0;
        }
        
        // Moves: U, D, L, R
        // Also Stay? Assuming yes.
        int move_dr[] = {0, 0, 1, -1};
        int move_dc[] = {1, -1, 0, 0};
        
        for(int i=0; i<4; ++i) {
            int nr = r + move_dr[i];
            int nc = c + move_dc[i];
            
            if (isValid(nr, nc)) {
                int nt = t + 1;
                
                // Resolving Gravity at nt
                // Phase at nt
                int g_phase = (nt / K_steps) % 4;
                int g_idx = g_phase; // 0=Down, 1=Left..
                
                // Fall
                int cr = nr, cc = nc;
                while(true) {
                    int nkr = cr + dr[g_idx]; // Fall dir
                    int nkc = cc + dc[g_idx];
                    if (isValid(nkr, nkc)) {
                        cr = nkr;
                        cc = nkc;
                        // Determine if we hit 'E' during fall?
                        // "Jatuh sampai mentok". Usually you stop AT the wall.
                        // Can you trigger exit while falling? Usually yes.
                        if (cr == tr && cc == tc) break; 
                    } else {
                        break;
                    }
                }
                
                // Check if better
                int nt_mod = nt % cycle;
                if (nt < min_time[cr][cc][nt_mod]) {
                    min_time[cr][cc][nt_mod] = nt;
                    pq.push({nt, cr, cc});
                }
            }
        }
    }
    
    cout << -1 << endl;
    
    return 0;
}
