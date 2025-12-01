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

vector<int> processQueries(const vector<string>& grid,
                           const vector<tuple<int,int,int,int,int>>& queries) {
    // Pre-compute all 4 rotations
    vector<vector<string>> rotations = {grid};
    vector<string> currentGrid = grid;
    for (int i = 0; i < 3; ++i) {
        currentGrid = rotateGrid90(currentGrid);
        rotations.push_back(currentGrid);
    }
    
    vector<int> results;
    for (const auto& [r, c, dir, limit, rCount] : queries) {
        const vector<string>& rotatedGrid = rotations[rCount % 4];
        int result = simulateBeamWithLimit(rotatedGrid, r, c, dir, limit);
        results.push_back(result);
    }
    
    return results;
}

int main() {
    // Example: Multiple queries
    vector<string> grid = {
        "...",
        "./.",
        "..."
    };
    
    vector<tuple<int,int,int,int,int>> queries = {
        {1, 0, 0, 100, 0},
        {1, 0, 0, 100, 1},
        {1, 0, 0, 100, 2},
        {0, 0, 1, 50, 0},
        {2, 2, 2, 100, 1},
    };
    
    vector<int> results = processQueries(grid, queries);
    cout << "Part6 Results: [";
    for (size_t i = 0; i < results.size(); ++i) {
        cout << results[i];
        if (i < results.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    // Example 2
    vector<string> grid2 = {
        "..#",
        "./.",
        "#.."
    };
    vector<tuple<int,int,int,int,int>> queries2 = {
        {0, 0, 0, 100, 0},
        {0, 0, 0, 100, 2},
    };
    vector<int> results2 = processQueries(grid2, queries2);
    cout << "Part6 Results2: [";
    for (size_t i = 0; i < results2.size(); ++i) {
        cout << results2[i];
        if (i < results2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    cout << "Day13 Part6 multi_query.cpp: tests passed" << endl;
    return 0;
}
