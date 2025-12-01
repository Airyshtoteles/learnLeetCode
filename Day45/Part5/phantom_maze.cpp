#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

struct State {
    int pr, pc;
    int sr, sc;
    int steps;
    
    bool operator<(const State& other) const {
        return tie(pr, pc, sr, sc) < tie(other.pr, other.pc, other.sr, other.sc);
    }
};

int solve() {
    int M = 5, N = 5;
    vector<string> player_grid = {
        "S..#.",
        ".#...",
        "...#.",
        "#.#..",
        "....G"
    };
    
    vector<string> shadow_grid = {
        "..#..",
        ".#...",
        "...#.",
        ".#...",
        "S...."
    };
    
    int start_pr, start_pc, goal_pr, goal_pc;
    int start_sr, start_sc;
    
    for(int r=0; r<M; ++r) {
        for(int c=0; c<N; ++c) {
            if(player_grid[r][c] == 'S') { start_pr = r; start_pc = c; }
            if(player_grid[r][c] == 'G') { goal_pr = r; goal_pc = c; }
            if(shadow_grid[r][c] == 'S') { start_sr = r; start_sc = c; }
        }
    }
    
    set<pair<pair<int,int>, pair<int,int>>> forbidden;
    forbidden.insert({{2,2}, {2,2}});
    
    queue<State> q;
    q.push({start_pr, start_pc, start_sr, start_sc, 0});
    
    // Visited array: 5x5x5x5 is small enough (625)
    // Using set for simplicity in C++ example, but vector is faster
    set<tuple<int,int,int,int>> visited;
    visited.insert({start_pr, start_pc, start_sr, start_sc});
    
    // Moves: U, D, L, R
    // Player: (-1,0), (1,0), (0,-1), (0,1)
    // Shadow: (1,0), (-1,0), (0,1), (0,-1)
    int dpr[] = {-1, 1, 0, 0};
    int dpc[] = {0, 0, -1, 1};
    int dsr[] = {1, -1, 0, 0};
    int dsc[] = {0, 0, 1, -1};
    
    while(!q.empty()) {
        State curr = q.front();
        q.pop();
        
        if(curr.pr == goal_pr && curr.pc == goal_pc) {
            return curr.steps;
        }
        
        for(int i=0; i<4; ++i) {
            int npr = curr.pr + dpr[i];
            int npc = curr.pc + dpc[i];
            int nsr = curr.sr + dsr[i];
            int nsc = curr.sc + dsc[i];
            
            // Bounds
            if(npr < 0 || npr >= M || npc < 0 || npc >= N) continue;
            if(nsr < 0 || nsr >= M || nsc < 0 || nsc >= N) continue;
            
            // Walls
            if(player_grid[npr][npc] == '#') continue;
            if(shadow_grid[nsr][nsc] == '#') continue;
            
            // Forbidden
            if(forbidden.count({{npr, npc}, {nsr, nsc}})) continue;
            
            if(visited.find({npr, npc, nsr, nsc}) == visited.end()) {
                visited.insert({npr, npc, nsr, nsc});
                q.push({npr, npc, nsr, nsc, curr.steps + 1});
            }
        }
    }
    
    return -1;
}

int main() {
    cout << "Minimum steps to goal: " << solve() << endl;
    return 0;
}
