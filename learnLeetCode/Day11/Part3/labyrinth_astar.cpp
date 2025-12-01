#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <tuple>
#include <cmath>
using namespace std;

int manhattan3D(int z1, int x1, int y1, int z2, int x2, int y2) {
    return abs(z1 - z2) + abs(x1 - x2) + abs(y1 - y2);
}

int astar3DPortal(int n, int m, int h, int k, const vector<vector<vector<int>>>& grid) {
    if (grid[0][0][0] == 1 || grid[h-1][n-1][m-1] == 1) return -1;
    
    tuple<int,int,int> goal = {h-1, n-1, m-1};
    
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
    
    // Priority queue: (f_score, g_score, z, x, y)
    priority_queue<tuple<int,int,int,int,int>, vector<tuple<int,int,int,int,int>>, greater<>> pq;
    auto [gz, gx, gy] = goal;
    pq.push({manhattan3D(0, 0, 0, gz, gx, gy), 0, 0, 0, 0});
    
    map<tuple<int,int,int>, int> visited;
    visited[{0, 0, 0}] = 0;
    
    int dz[] = {1, -1, 0, 0, 0, 0};
    int dx[] = {0, 0, 1, -1, 0, 0};
    int dy[] = {0, 0, 0, 0, 1, -1};
    
    while (!pq.empty()) {
        auto [f, g, z, x, y] = pq.top();
        pq.pop();
        
        if (make_tuple(z, x, y) == goal) return g;
        
        // Skip if better path exists
        auto pos = make_tuple(z, x, y);
        if (visited.count(pos) && visited[pos] < g) continue;
        
        // Normal movement
        for (int i = 0; i < 6; ++i) {
            int nz = z + dz[i], nx = x + dx[i], ny = y + dy[i];
            
            if (nz >= 0 && nz < h && nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nz][nx][ny] != 1) {
                int newG = g + 1;
                auto npos = make_tuple(nz, nx, ny);
                if (!visited.count(npos) || newG < visited[npos]) {
                    visited[npos] = newG;
                    int newF = newG + manhattan3D(nz, nx, ny, gz, gx, gy);
                    pq.push({newF, newG, nz, nx, ny});
                }
            }
        }
        
        // Portal teleportation
        if (grid[z][x][y] == 2) {
            for (auto [pz, px, py] : portals) {
                int newG = g + k;
                auto ppos = make_tuple(pz, px, py);
                if (!visited.count(ppos) || newG < visited[ppos]) {
                    visited[ppos] = newG;
                    int newF = newG + manhattan3D(pz, px, py, gz, gx, gy);
                    pq.push({newF, newG, pz, px, py});
                }
            }
        }
    }
    
    return -1;
}

int main() {
    // Example
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
    int result = astar3DPortal(3, 3, 2, 2, grid);
    cout << "Day11 Part3: A* result = " << result << " (expected ~6)" << endl;
    
    // Simple test
    vector<vector<vector<int>>> grid2 = {
        {{0, 0}, {0, 0}},
        {{0, 0}, {0, 0}}
    };
    int result2 = astar3DPortal(2, 2, 2, 1, grid2);
    if (result2 != 3) return 1;
    
    cout << "Day11 Part3 labyrinth_astar.cpp: tests passed" << endl;
    return 0;
}
