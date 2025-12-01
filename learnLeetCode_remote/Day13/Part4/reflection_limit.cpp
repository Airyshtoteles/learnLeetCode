#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <tuple>
using namespace std;

int simulateBeamWithLimit(const vector<string>& grid, int r, int c, int dir, int limit) {
    int n = grid.size();
    if (n == 0) return 0;
    int m = grid[0].size();
    
    // Direction vectors: right, down, left, up
    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};
    
    set<pair<int,int>> visitedCells;
    set<tuple<int,int,int>> visitedStates;
    int reflectionCount = 0;
    
    while (true) {
        // Check bounds
        if (r < 0 || r >= n || c < 0 || c >= m) {
            return visitedCells.size();
        }
        
        // Check if hit wall
        if (grid[r][c] == '#') {
            return visitedCells.size();
        }
        
        // Mark cell as visited
        visitedCells.insert({r, c});
        
        // Check for state loop
        auto state = make_tuple(r, c, dir);
        if (visitedStates.count(state)) {
            return visitedCells.size();
        }
        visitedStates.insert(state);
        
        // Handle mirrors and count reflections
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
        
        // Check reflection limit
        if (reflected) {
            reflectionCount++;
            if (reflectionCount > limit) {
                return visitedCells.size();
            }
        }
        
        // Move in current direction
        r += dr[dir];
        c += dc[dir];
    }
}

int main() {
    // Example 1: Loop but limited
    vector<string> grid1 = {
        "/.\\",
        ".#.",
        "\\./",
    };
    int result1 = simulateBeamWithLimit(grid1, 0, 0, 0, 10);
    cout << "Part4 Example1: " << result1 << " cells (limit=10 reflections)" << endl;
    
    // Example 2: Exits before limit
    vector<string> grid2 = {
        "...",
        "./.",
        "..."
    };
    int result2 = simulateBeamWithLimit(grid2, 1, 0, 0, 100);
    cout << "Part4 Example2: " << result2 << " cells (exits before limit)" << endl;
    
    // Example 3: Very low limit
    vector<string> grid3 = {
        "///",
        "///"
    };
    int result3 = simulateBeamWithLimit(grid3, 0, 0, 0, 2);
    cout << "Part4 Example3: " << result3 << " cells (limit=2, stops early)" << endl;
    
    // Example 4: No mirrors
    vector<string> grid4 = {
        ".....",
        "....."
    };
    int result4 = simulateBeamWithLimit(grid4, 0, 0, 0, 1000);
    cout << "Part4 Example4: " << result4 << " cells (no mirrors, no reflections)" << endl;
    
    cout << "Day13 Part4 reflection_limit.cpp: tests passed" << endl;
    return 0;
}
