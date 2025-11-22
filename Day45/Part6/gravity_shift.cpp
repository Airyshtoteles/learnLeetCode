#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

struct State {
    int r, c;
    int k; // shifts left
    int steps;
};

int solve() {
    vector<string> grid = {
        "S...#",
        ".#...",
        "...#.",
        "#...G",
        "....."
    };
    int M = grid.size();
    int N = grid[0].size();
    
    int start_r, start_c, goal_r, goal_c;
    for(int r=0; r<M; ++r) {
        for(int c=0; c<N; ++c) {
            if(grid[r][c] == 'S') { start_r = r; start_c = c; }
            if(grid[r][c] == 'G') { goal_r = r; goal_c = c; }
        }
    }
    
    queue<State> q;
    q.push({start_r, start_c, 3, 0});
    
    // Visited: r, c, k
    // M, N <= 20, k <= 3. Array is fine.
    // Using set for simplicity in this snippet
    set<tuple<int,int,int>> visited;
    visited.insert({start_r, start_c, 3});
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    while(!q.empty()) {
        State curr = q.front();
        q.pop();
        
        if(curr.r == goal_r && curr.c == goal_c) return curr.steps;
        
        // 1. Standard Move
        for(int i=0; i<4; ++i) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];
            
            if(nr >= 0 && nr < M && nc >= 0 && nc < N && grid[nr][nc] != '#') {
                if(visited.find({nr, nc, curr.k}) == visited.end()) {
                    visited.insert({nr, nc, curr.k});
                    q.push({nr, nc, curr.k, curr.steps + 1});
                }
            }
        }
        
        // 2. Gravity Shift
        if(curr.k > 0) {
            for(int i=0; i<4; ++i) {
                int cr = curr.r;
                int cc = curr.c;
                
                while(true) {
                    int nr = cr + dr[i];
                    int nc = cc + dc[i];
                    if(nr >= 0 && nr < M && nc >= 0 && nc < N && grid[nr][nc] != '#') {
                        cr = nr;
                        cc = nc;
                    } else {
                        break;
                    }
                }
                
                if(cr != curr.r || cc != curr.c) {
                    if(visited.find({cr, cc, curr.k - 1}) == visited.end()) {
                        visited.insert({cr, cc, curr.k - 1});
                        q.push({cr, cc, curr.k - 1, curr.steps + 1});
                    }
                }
            }
        }
    }
    
    return -1;
}

int main() {
    cout << "Minimum actions to goal: " << solve() << endl;
    return 0;
}
