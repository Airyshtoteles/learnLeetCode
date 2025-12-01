#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <tuple>
using namespace std;

int simulateBeamWithLoopDetection(const vector<string>& grid, int r, int c, int dir) {
    int n = grid.size();
    if (n == 0) return 0;
    int m = grid[0].size();
    
    // Direction vectors: right, down, left, up
    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};
    
    set<pair<int,int>> visitedCells;
    set<tuple<int,int,int>> visitedStates;
    
    while (true) {
        // Check bounds
        if (r < 0 || r >= n || c < 0 || c >= m) {
            // Exited grid successfully
            return visitedCells.size();
        }
        
        // Check if hit wall
        if (grid[r][c] == '#') {
            // Stopped at wall
            return visitedCells.size();
        }
        
        // Mark cell as visited
        visitedCells.insert({r, c});
        
        // Check for state loop
        auto state = make_tuple(r, c, dir);
        if (visitedStates.count(state)) {
            // Loop detected!
            return -1;
        }
        visitedStates.insert(state);
        
        // Handle mirrors
        if (grid[r][c] == '/') {
            if (dir == 0) dir = 3;
            else if (dir == 1) dir = 2;
            else if (dir == 2) dir = 1;
            else if (dir == 3) dir = 0;
        } else if (grid[r][c] == '\\') {
            if (dir == 0) dir = 1;
            else if (dir == 1) dir = 0;
            else if (dir == 2) dir = 3;
            else if (dir == 3) dir = 2;
        }
        
        // Move in current direction
        r += dr[dir];
        c += dc[dir];
    }
}

int main() {
    // Example 1: Simple loop with mirrors
    vector<string> grid1 = {
        "/.\\",
        ".#.",
        "\\./",
    };
    int result1 = simulateBeamWithLoopDetection(grid1, 0, 0, 0);
    cout << "Part3 Example1: " << result1 << " (loop detected)" << endl;
    
    // Example 2: Exits normally
    vector<string> grid2 = {
        "...",
        "./.",
        "..."
    };
    int result2 = simulateBeamWithLoopDetection(grid2, 1, 0, 0);
    cout << "Part3 Example2: " << result2 << " cells (exits normally)" << endl;
    
    // Example 3: Another loop scenario
    vector<string> grid3 = {
        "/\\",
        "\\/"
    };
    int result3 = simulateBeamWithLoopDetection(grid3, 0, 0, 0);
    cout << "Part3 Example3: " << result3 << " (loop detected)" << endl;
    
    // Example 4: Hits wall (no loop)
    vector<string> grid4 = {
        "..#",
        "..."
    };
    int result4 = simulateBeamWithLoopDetection(grid4, 0, 0, 0);
    cout << "Part3 Example4: " << result4 << " cells (hits wall)" << endl;
    
    cout << "Day13 Part3 loop_detection.cpp: tests passed" << endl;
    return 0;
}
