#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <cmath>
using namespace std;

int manhattan(int r1, int c1, int r2, int c2) {
    return abs(r1 - r2) + abs(c1 - c2);
}

int astarOptimized(const vector<string>& grid, int t) {
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
    
    // A* priority queue: (f_score, steps, row, col, usedPortal)
    priority_queue<tuple<int,int,int,int,bool>, 
                   vector<tuple<int,int,int,int,bool>>,
                   greater<tuple<int,int,int,int,bool>>> pq;
    
    int h_start = manhattan(start.first, start.second, end.first, end.second);
    pq.push({h_start, 0, start.first, start.second, false});
    set<tuple<int,int,bool>> visited;
    
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    
    while (!pq.empty()) {
        auto [f_score, steps, r, c, usedPortal] = pq.top();
        pq.pop();
        
        // Skip if already visited
        if (visited.count({r, c, usedPortal})) continue;
        visited.insert({r, c, usedPortal});
        
        if (r == end.first && c == end.second) return steps;
        
        int newSteps = steps + 1;
        int blockedRow = (t > 0) ? (newSteps / t) : -1;
        bool portalsActive = (t > 0) ? (newSteps / t < 3) : true;
        
        // Normal movement
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i], nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                if (nr == blockedRow) continue;
                if (grid[nr][nc] == '#') continue;
                if (grid[nr][nc] == 'P' && !portalsActive) continue;
                
                if (!visited.count({nr, nc, usedPortal})) {
                    int h = manhattan(nr, nc, end.first, end.second);
                    int f = newSteps + h;
                    pq.push({f, newSteps, nr, nc, usedPortal});
                }
            }
        }
        
        // Portal teleportation
        if (grid[r][c] == 'P' && !usedPortal && portalsActive) {
            for (auto [pr, pc] : portals) {
                if ((pr != r || pc != c) && pr != blockedRow) {
                    if (!visited.count({pr, pc, true})) {
                        int h = manhattan(pr, pc, end.first, end.second);
                        int f = newSteps + h;
                        pq.push({f, newSteps, pr, pc, true});
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
    int result1 = astarOptimized(grid1, 2);
    cout << "Part5 Example: " << result1 << " steps (A* optimized)" << endl;
    
    // Test without dynamic walls interfering
    vector<string> grid2 = {
        "S..",
        "...",
        "..E"
    };
    int result2 = astarOptimized(grid2, 1000);
    cout << "Part5 Test2: " << result2 << " steps (no blocking)" << endl;
    if (result2 != 4) return 1;  // Manhattan: 2 down + 2 right = 4
    
    cout << "Day12 Part5 optimized.cpp: tests passed" << endl;
    return 0;
}
