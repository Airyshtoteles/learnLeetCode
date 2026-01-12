#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

// Problem 2: Dungeon With Energy That Remembers
// Cost 1 per step.
// Rule: Cannot visit (r, c) with current_energy <= previously_visited_energy_at_rc.
// This is effectively standard BFS.
// BFS visits nodes in order of decreasing energy (Steps 0, 1, 2... implies Energy E, E-1, ...).
// First visit is always optimal. Any later visit has Energy' <= Energy.
// So standard `visited` array is sufficient.
// Wait, "Inti: state dominance pruning".
// This confirms the logic. If current state is dominated (same pos, less or equal energy), Drop it.
// Standard BFS does this naturally.

int R, C;
int StartR, StartC, EndR, EndC, InitialEnergy;
vector<string> grid;

int main() {
    if (!(cin >> R >> C)) return 0;
    cin >> StartR >> StartC >> EndR >> EndC >> InitialEnergy;
    
    grid.resize(R);
    for (int i = 0; i < R; ++i) cin >> grid[i];

    // BFS
    // Queue stores {r, c, energy}
    // But since dist is uniform, we just prioritize steps.
    // Visited[r][c] stores Max Energy seen so far.
    // Actually simpler: Visited bool is enough?
    // "strictly forbidden if <= e".
    // 1st visit: Energy E_max.
    // 2nd visit: Energy E_curr < E_max.
    // Is E_curr <= E_max? Yes. So forbidden.
    // So yes, strictly one visit per cell is allowed.
    // We just need to check if Target is reachable.
    
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    queue<pair<int, int>> q;
    vector<vector<int>> dist(R, vector<int>(C, -1));
    
    q.push({StartR, StartC});
    visited[StartR][StartC] = true;
    dist[StartR][StartC] = 0;
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        int d = dist[r][c];
        int current_energy = InitialEnergy - d;
        
        if (r == EndR && c == EndC) {
            cout << "YES " << d << endl;
            return 0;
        }
        
        if (current_energy <= 0) continue; // Out of energy
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#') {
                if (!visited[nr][nc]) {
                    visited[nr][nc] = true;
                    dist[nr][nc] = d + 1;
                    q.push({nr, nc});
                }
            }
        }
    }
    
    cout << "NO" << endl;
    
    return 0;
}
