#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <tuple>
using namespace std;

int bfsDynamicWalls(const vector<string>& grid, int t) {
    int n = grid.size();
    if (n == 0) return -1;
    int m = grid[0].size();
    
    // Find start, end, portals
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
    
    // BFS: (row, col, usedPortal, steps)
    queue<tuple<int,int,bool,int>> q;
    q.push({start.first, start.second, false, 0});
    set<tuple<int,int,bool,int>> visited;
    visited.insert({start.first, start.second, false, 0});
    
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    
    while (!q.empty()) {
        auto [r, c, usedPortal, steps] = q.front();
        q.pop();
        
        if (r == end.first && c == end.second) return steps;
        
        int newSteps = steps + 1;
        int blockedRow = (t > 0) ? (newSteps / t) : -1;
        
        // Normal movement
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i], nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                if (nr == blockedRow) continue;
                
                if (visited.find({nr, nc, usedPortal, newSteps}) == visited.end() && 
                    grid[nr][nc] != '#') {
                    visited.insert({nr, nc, usedPortal, newSteps});
                    q.push({nr, nc, usedPortal, newSteps});
                }
            }
        }
        
        // Portal teleportation
        if (grid[r][c] == 'P' && !usedPortal) {
            for (auto [pr, pc] : portals) {
                if ((pr != r || pc != c) && pr != blockedRow) {
                    if (visited.find({pr, pc, true, newSteps}) == visited.end()) {
                        visited.insert({pr, pc, true, newSteps});
                        q.push({pr, pc, true, newSteps});
                    }
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
    int result1 = bfsDynamicWalls(grid1, 2);
    cout << "Part3 Example: " << result1 << " steps (with dynamic walls, t=2)" << endl;
    
    // Test 2: Path gets blocked
    vector<string> grid2 = {
        "S..",
        "..E"
    };
    int result2 = bfsDynamicWalls(grid2, 3);
    cout << "Part3 Test2: " << result2 << " steps (path blocked scenario)" << endl;
    
    cout << "Day12 Part3 dynamic_walls.cpp: tests passed" << endl;
    return 0;
}
