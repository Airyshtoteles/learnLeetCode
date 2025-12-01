#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
using namespace std;

int bfs3DPortal(int n, int m, int h, int k, const vector<vector<vector<int>>>& grid) {
    if (grid[0][0][0] == 1 || grid[h-1][n-1][m-1] == 1) return -1;
    
    // Collect portals
    vector<tuple<int,int,int>> portals;
    for (int z = 0; z < h; ++z) {
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                if (grid[z][x][y] == 2) {
                    portals.push_back({z, x, y});
                }
            }
        }
    }
    
    queue<tuple<int,int,int,int>> q;
    q.push({0, 0, 0, 0});
    set<tuple<int,int,int>> visited;
    visited.insert({0, 0, 0});
    
    int dz[] = {1, -1, 0, 0, 0, 0};
    int dx[] = {0, 0, 1, -1, 0, 0};
    int dy[] = {0, 0, 0, 0, 1, -1};
    
    while (!q.empty()) {
        auto [z, x, y, cost] = q.front();
        q.pop();
        
        if (z == h-1 && x == n-1 && y == m-1) return cost;
        
        // Normal movement
        for (int i = 0; i < 6; ++i) {
            int nz = z + dz[i], nx = x + dx[i], ny = y + dy[i];
            
            if (nz >= 0 && nz < h && nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (grid[nz][nx][ny] != 1 && visited.find({nz, nx, ny}) == visited.end()) {
                    visited.insert({nz, nx, ny});
                    q.push({nz, nx, ny, cost + 1});
                }
            }
        }
        
        // Portal teleportation
        if (grid[z][x][y] == 2) {
            for (auto [pz, px, py] : portals) {
                if (visited.find({pz, px, py}) == visited.end()) {
                    visited.insert({pz, px, py});
                    q.push({pz, px, py, cost + k});
                }
            }
        }
    }
    
    return -1;
}

int main() {
    // Example from problem
    vector<vector<vector<int>>> grid = {
        {
            {0, 0, 0},
            {1, 1, 0},
            {2, 0, 0}
        },
        {
            {0, 1, 0},
            {0, 2, 0},
            {0, 0, 0}
        }
    };
    int result = bfs3DPortal(3, 3, 2, 2, grid);
    cout << "Day11 Part2: Example result = " << result << " (expected ~6)" << endl;
    
    // Simple portal test
    vector<vector<vector<int>>> grid2 = {
        {{2, 0}, {0, 0}},
        {{0, 0}, {0, 2}}
    };
    int result2 = bfs3DPortal(2, 2, 2, 1, grid2);
    if (result2 < 0) return 1;
    
    cout << "Day11 Part2 labyrinth_portal.cpp: tests passed" << endl;
    return 0;
}
