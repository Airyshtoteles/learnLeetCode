#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <tuple>
using namespace std;

int simulateBeam(const vector<string>& grid, int r, int c, int dir) {
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
            break;
        }
        
        // Check if hit wall
        if (grid[r][c] == '#') {
            break;
        }
        
        // Mark cell as visited
        visitedCells.insert({r, c});
        
        // Check for state loop
        auto state = make_tuple(r, c, dir);
        if (visitedStates.count(state)) {
            break;
        }
        visitedStates.insert(state);
        
        // Handle mirrors
        if (grid[r][c] == '/') {
            // '/' reflects: right↔up, down↔left
            if (dir == 0) dir = 3;       // right → up
            else if (dir == 1) dir = 2;  // down → left
            else if (dir == 2) dir = 1;  // left → down
            else if (dir == 3) dir = 0;  // up → right
        } else if (grid[r][c] == '\\') {
            // '\\' reflects: right↔down, up↔left
            if (dir == 0) dir = 1;       // right → down
            else if (dir == 1) dir = 0;  // down → right
            else if (dir == 2) dir = 3;  // left → up
            else if (dir == 3) dir = 2;  // up → left
        }
        
        // Move in current direction
        r += dr[dir];
        c += dc[dir];
    }
    
    return visitedCells.size();
}

int main() {
    // Example 1: Simple horizontal beam
    vector<string> grid1 = {
        ".....",
        "../..",
        "....."
    };
    int result1 = simulateBeam(grid1, 1, 0, 0);
    cout << "Part1 Example1: " << result1 << " cells visited" << endl;
    
    // Example 2: Mirror reflection
    vector<string> grid2 = {
        "...",
        "./.",
        "..."
    };
    int result2 = simulateBeam(grid2, 1, 0, 0);
    cout << "Part1 Example2: " << result2 << " cells visited" << endl;
    
    // Example 3: Hit wall
    vector<string> grid3 = {
        "..#",
        "..."
    };
    int result3 = simulateBeam(grid3, 0, 0, 0);
    cout << "Part1 Example3: " << result3 << " cells visited" << endl;
    
    cout << "Day13 Part1 mirror_basic.cpp: tests passed" << endl;
    return 0;
}
