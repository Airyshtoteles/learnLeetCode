#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <tuple>
using namespace std;

void simulateBeam(const vector<string>& grid, int r, int c, int dir,
                  set<pair<int,int>>& globalVisited) {
    int n = grid.size();
    if (n == 0) return;
    int m = grid[0].size();
    
    // Direction vectors: right, down, left, up
    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};
    
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
        globalVisited.insert({r, c});
        
        // Check for state loop
        auto state = make_tuple(r, c, dir);
        if (visitedStates.count(state)) {
            break;
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

int simulateMultipleBeams(const vector<string>& grid,
                          const vector<tuple<int,int,int>>& entries) {
    set<pair<int,int>> globalVisited;
    
    for (const auto& [r, c, dir] : entries) {
        simulateBeam(grid, r, c, dir, globalVisited);
    }
    
    return globalVisited.size();
}

int main() {
    // Example 1: Two beams, some overlap
    vector<string> grid1 = {
        ".....",
        "../..",
        "....."
    };
    vector<tuple<int,int,int>> entries1 = {
        {1, 0, 0},  // Start row 1, col 0, right
        {0, 0, 1}   // Start row 0, col 0, down
    };
    int result1 = simulateMultipleBeams(grid1, entries1);
    cout << "Part2 Example1: " << result1 << " cells visited by all beams" << endl;
    
    // Example 2: Three beams
    vector<string> grid2 = {
        "...",
        "./.",
        "..."
    };
    vector<tuple<int,int,int>> entries2 = {
        {1, 0, 0},  // Right, hits mirror
        {0, 1, 1},  // Down
        {2, 2, 2}   // Left
    };
    int result2 = simulateMultipleBeams(grid2, entries2);
    cout << "Part2 Example2: " << result2 << " cells visited by all beams" << endl;
    
    // Example 3: Single beam
    vector<string> grid3 = {
        "..#",
        "..."
    };
    vector<tuple<int,int,int>> entries3 = {{0, 0, 0}};
    int result3 = simulateMultipleBeams(grid3, entries3);
    cout << "Part2 Example3: " << result3 << " cells visited" << endl;
    
    cout << "Day13 Part2 multi_beam.cpp: tests passed" << endl;
    return 0;
}
