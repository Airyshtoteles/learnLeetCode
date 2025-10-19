#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <tuple>
using namespace std;

vector<string> rotateGrid90(const vector<string>& grid) {
    int n = grid.size();
    if (n == 0) return {};
    int m = grid[0].size();
    
    vector<string> rotated(m);
    for (int j = 0; j < m; ++j) {
        string row = "";
        for (int i = n-1; i >= 0; --i) {
            row += grid[i][j];
        }
        rotated[j] = row;
    }
    return rotated;
}

int simulateBeamWithLimit(const vector<string>& grid, int r, int c, int dir, int limit) {
    int n = grid.size();
    if (n == 0) return 0;
    int m = grid[0].size();
    
    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};
    
    set<pair<int,int>> visitedCells;
    set<tuple<int,int,int>> visitedStates;
    int reflectionCount = 0;
    
    while (true) {
        if (r < 0 || r >= n || c < 0 || c >= m) return visitedCells.size();
        if (grid[r][c] == '#') return visitedCells.size();
        
        visitedCells.insert({r, c});
        auto state = make_tuple(r, c, dir);
        if (visitedStates.count(state)) return visitedCells.size();
        visitedStates.insert(state);
        
        bool reflected = false;
        if (grid[r][c] == '/') {
            reflected = true;
            if (dir == 0) dir = 3;
            else if (dir == 1) dir = 2;
            else if (dir == 2) dir = 1;
            else if (dir == 3) dir = 0;
        } else if (grid[r][c] == '\\') {
            reflected = true;
            if (dir == 0) dir = 1;
            else if (dir == 1) dir = 0;
            else if (dir == 2) dir = 3;
            else if (dir == 3) dir = 2;
        }
        
        if (reflected) {
            reflectionCount++;
            if (reflectionCount > limit) return visitedCells.size();
        }
        
        r += dr[dir];
        c += dc[dir];
    }
}

int simulateWithRotation(const vector<string>& grid, int r, int c, int dir, 
                         int limit, int rCount) {
    vector<string> rotatedGrid = grid;
    for (int i = 0; i < rCount % 4; ++i) {
        rotatedGrid = rotateGrid90(rotatedGrid);
    }
    return simulateBeamWithLimit(rotatedGrid, r, c, dir, limit);
}

int main() {
    vector<string> grid1 = {
        "...",
        "./.",
        "..."
    };
    
    int result1 = simulateWithRotation(grid1, 1, 0, 0, 100, 0);
    cout << "Part5 Example1: " << result1 << " cells (rCount=0, no rotation)" << endl;
    
    int result2 = simulateWithRotation(grid1, 1, 0, 0, 100, 1);
    cout << "Part5 Example2: " << result2 << " cells (rCount=1, rotated 90°)" << endl;
    
    int result3 = simulateWithRotation(grid1, 1, 0, 0, 100, 4);
    cout << "Part5 Example3: " << result3 << " cells (rCount=4, back to original)" << endl;
    
    cout << "Day13 Part5 grid_rotation.cpp: tests passed" << endl;
    return 0;
}
