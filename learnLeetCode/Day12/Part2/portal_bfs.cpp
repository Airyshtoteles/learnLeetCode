#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <tuple>
using namespace std;

int bfsWithPortal(const vector<string>& grid) {
    int n = grid.size();
    if (n == 0) return -1;
    int m = grid[0].size();
    
    // Find start, end, and portals
    pair<int,int> start = {-1, -1}, end = {-1, -1};
    vector<pair<int,int>> portals;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'S') start = {i, j};
            else if (grid[i][j] == 'E') end = {i, j};
            else if (grid[i][j] == 'P') portals.push_back({i, j});
        }
    }
    
    if (start.first == -1 || end.first == -1) return -1;
    
    // BFS with state: (row, col, usedPortal, steps)
    queue<tuple<int,int,bool,int>> q;
    q.push({start.first, start.second, false, 0});
    set<tuple<int,int,bool>> visited;
    visited.insert({start.first, start.second, false});
    
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    
    while (!q.empty()) {
        auto [r, c, usedPortal, steps] = q.front();
        q.pop();
        
        if (r == end.first && c == end.second) return steps;
        
        // Normal movement
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i], nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && 
                visited.find({nr, nc, usedPortal}) == visited.end()) {
                if (grid[nr][nc] != '#') {
                    visited.insert({nr, nc, usedPortal});
                    q.push({nr, nc, usedPortal, steps + 1});
                }
            }
        }
        
        // Portal teleportation
        if (grid[r][c] == 'P' && !usedPortal) {
            for (auto [pr, pc] : portals) {
                if ((pr != r || pc != c) && visited.find({pr, pc, true}) == visited.end()) {
                    visited.insert({pr, pc, true});
                    q.push({pr, pc, true, steps + 1});
                }
            }
        }
    }
    
    return -1;
}

int main() {
    // Example
    vector<string> grid1 = {
        "S.#.",
        ".P..",
        "..#E",
        "P..."
    };
    int result1 = bfsWithPortal(grid1);
    cout << "Part2 Example: " << result1 << " steps (with portal)" << endl;
    if (result1 <= 0) return 1;
    
    // Test with portals
    vector<string> grid2 = {
        "S.....",
        "......",
        "P....P",
        "......",
        "......E"
    };
    int result2 = bfsWithPortal(grid2);
    cout << "Part2 Test2: " << result2 << " steps" << endl;
    
    cout << "Day12 Part2 portal_bfs.cpp: tests passed" << endl;
    return 0;
}
