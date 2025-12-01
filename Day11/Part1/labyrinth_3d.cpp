#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
using namespace std;

// 3D BFS to find minimum cost from (0,0,0) to (n-1,m-1,h-1)
int bfs3DBasic(int n, int m, int h, const vector<vector<vector<int>>>& grid) {
    if (grid[0][0][0] == 1 || grid[h-1][n-1][m-1] == 1) return -1;
    
    // BFS queue: (z, x, y, cost)
    queue<tuple<int,int,int,int>> q;
    q.push({0, 0, 0, 0});
    set<tuple<int,int,int>> visited;
    visited.insert({0, 0, 0});
    
    // 6 directions
    int dz[] = {1, -1, 0, 0, 0, 0};
    int dx[] = {0, 0, 1, -1, 0, 0};
    int dy[] = {0, 0, 0, 0, 1, -1};
    
    while (!q.empty()) {
        auto [z, x, y, cost] = q.front();
        q.pop();
        
        // Check destination
        if (z == h-1 && x == n-1 && y == m-1) return cost;
        
        // Explore neighbors
        for (int i = 0; i < 6; ++i) {
            int nz = z + dz[i], nx = x + dx[i], ny = y + dy[i];
            
            if (nz >= 0 && nz < h && nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (grid[nz][nx][ny] != 1 && visited.find({nz, nx, ny}) == visited.end()) {
                    visited.insert({nz, nx, ny});
                    q.push({nz, nx, ny, cost + 1});
                }
            }
        }
    }
    
    return -1;
}

int main() {
    // Test 1: simple 2x2x2 cube
    vector<vector<vector<int>>> grid1 = {
        {{0, 0}, {0, 0}},
        {{0, 0}, {0, 0}}
    };
    int res1 = bfs3DBasic(2, 2, 2, grid1);
    if (res1 != 3) return 1;
    
    // Test 2: with wall
    vector<vector<vector<int>>> grid2 = {
        {{0, 0}, {1, 0}},
        {{0, 0}, {0, 0}}
    };
    int res2 = bfs3DBasic(2, 2, 2, grid2);
    if (res2 <= 0) return 1;
    
    // Test 3: impossible
    vector<vector<vector<int>>> grid3 = {
        {{0, 1}, {1, 0}},
        {{1, 0}, {0, 1}}
    };
    int res3 = bfs3DBasic(2, 2, 2, grid3);
    if (res3 != -1) return 1;
    
    cout << "Day11 Part1 labyrinth_3d.cpp: all tests passed" << endl;
    return 0;
}
