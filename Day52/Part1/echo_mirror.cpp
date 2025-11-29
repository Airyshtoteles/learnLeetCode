#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

struct State {
    int pr, pc, br, bc, steps;
};

int solve_echo_mirror(vector<string>& grid) {
    int R = grid.size();
    int C = grid[0].size();
    
    int start_pr, start_pc, start_br, start_bc, exit_r, exit_c;
    
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (grid[r][c] == 'P') {
                start_pr = r; start_pc = c;
            } else if (grid[r][c] == 'B') {
                start_br = r; start_bc = c;
            } else if (grid[r][c] == 'E') {
                exit_r = r; exit_c = c;
            }
        }
    }
    
    if (start_pr == start_br && start_pc == start_bc) return -1;
    
    queue<State> q;
    q.push({start_pr, start_pc, start_br, start_bc, 0});
    
    set<tuple<int, int, int, int>> visited;
    visited.insert({start_pr, start_pc, start_br, start_bc});
    
    // Player: U, D, L, R
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    // Boss: D, U, R, L
    int b_dr[] = {1, -1, 0, 0};
    int b_dc[] = {0, 0, 1, -1};
    
    while (!q.empty()) {
        State current = q.front();
        q.pop();
        
        if (current.pr == exit_r && current.pc == exit_c) {
            return current.steps;
        }
        
        for (int i = 0; i < 4; ++i) {
            // Player Move
            int npr = current.pr + dr[i];
            int npc = current.pc + dc[i];
            
            if (!(npr >= 0 && npr < R && npc >= 0 && npc < C && grid[npr][npc] != '#')) {
                npr = current.pr;
                npc = current.pc;
            }
            
            // Boss Move
            int nbr = current.br + b_dr[i];
            int nbc = current.bc + b_dc[i];
            
            if (!(nbr >= 0 && nbr < R && nbc >= 0 && nbc < C && grid[nbr][nbc] != '#')) {
                nbr = current.br;
                nbc = current.bc;
            }
            
            // Collision Check
            if (npr == nbr && npc == nbc) continue;
            
            if (visited.find({npr, npc, nbr, nbc}) == visited.end()) {
                visited.insert({npr, npc, nbr, nbc});
                q.push({npr, npc, nbr, nbc, current.steps + 1});
            }
        }
    }
    
    return -1;
}

int main() {
    vector<string> grid1 = {
        "P..",
        ".#.",
        ".BE"
    };
    cout << "Min Steps (Ex 1): " << solve_echo_mirror(grid1) << endl;
    
    vector<string> grid2 = {"PBE"};
    cout << "Min Steps (Ex 2): " << solve_echo_mirror(grid2) << endl;
    
    return 0;
}
