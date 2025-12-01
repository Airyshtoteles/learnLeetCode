#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
using namespace std;

int bfsBasic(const vector<string>& grid) {
    int n = grid.size();
    if (n == 0) return -1;
    int m = grid[0].size();
    
    // Find start and end
    pair<int,int> start = {-1, -1}, end = {-1, -1};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'S') start = {i, j};
            if (grid[i][j] == 'E') end = {i, j};
        }
    }
    
    if (start.first == -1 || end.first == -1) return -1;
    
    // BFS
    queue<tuple<int,int,int>> q;
    q.push({start.first, start.second, 0});
    set<pair<int,int>> visited;
    visited.insert(start);
    
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    
    while (!q.empty()) {
        auto [r, c, steps] = q.front();
        q.pop();
        
        if (r == end.first && c == end.second) return steps;
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i], nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && 
                visited.find({nr, nc}) == visited.end()) {
                if (grid[nr][nc] != '#') {
                    visited.insert({nr, nc});
                    q.push({nr, nc, steps + 1});
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
    int result1 = bfsBasic(grid1);
    cout << "Part1 Example: " << result1 << " steps" << endl;
    if (result1 <= 0) return 1;
    
    // Simple test
    vector<string> grid2 = {"S.E"};
    if (bfsBasic(grid2) != 2) return 1;
    
    // Blocked test
    vector<string> grid3 = {"S#E"};
    if (bfsBasic(grid3) != -1) return 1;
    
    cout << "Day12 Part1 magic_portals.cpp: all tests passed" << endl;
    return 0;
}
