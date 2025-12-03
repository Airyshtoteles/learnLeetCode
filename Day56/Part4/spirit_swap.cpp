#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int R, C;
long long T;
int initial_grid[20][20];
int grid[20][20];
bool visited[20][20];
bool to_remove[20][20];

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

struct Component {
    vector<pair<int, int>> cells;
    long long sum;
};

void get_component(int r, int c, Component& comp) {
    visited[r][c] = true;
    comp.cells.push_back({r, c});
    comp.sum += grid[r][c];
    
    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nr < R && nc >= 0 && nc < C && !visited[nr][nc] && grid[nr][nc] == grid[r][c]) {
            get_component(nr, nc, comp);
        }
    }
}

void apply_gravity() {
    for (int j = 0; j < C; ++j) {
        vector<int> col;
        for (int i = 0; i < R; ++i) {
            if (grid[i][j] > 0) {
                col.push_back(grid[i][j]);
            }
        }
        for (int i = 0; i < R; ++i) {
            if (i < R - col.size()) {
                grid[i][j] = 0;
            } else {
                grid[i][j] = col[i - (R - col.size())];
            }
        }
    }
}

long long simulate() {
    long long total_score = 0;
    while (true) {
        memset(visited, 0, sizeof(visited));
        memset(to_remove, 0, sizeof(to_remove));
        bool changed = false;
        
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (grid[i][j] > 0 && !visited[i][j]) {
                    Component comp;
                    comp.sum = 0;
                    get_component(i, j, comp);
                    
                    if (comp.sum >= T) {
                        total_score += comp.sum;
                        changed = true;
                        for (auto p : comp.cells) {
                            to_remove[p.first][p.second] = true;
                        }
                    }
                }
            }
        }
        
        if (!changed) break;
        
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (to_remove[i][j]) {
                    grid[i][j] = 0;
                }
            }
        }
        
        apply_gravity();
    }
    return total_score;
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> R >> C >> T)) return 0;
    
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> initial_grid[i][j];
        }
    }
    
    long long max_score = 0;
    
    // Try no swap (optional, but problem says "satu swap". Usually implies exactly one or at most one? "Kamu hanya boleh satu swap." -> "You are allowed only one swap." Could mean 0 or 1. But usually in match-3, you MUST swap. I'll assume MUST swap. But swapping identicals is like no swap. So effectively 0 or 1.)
    // Actually, if I swap identicals, it's same as 0.
    // So I'll just try all adjacent swaps.
    
    // Horizontal swaps
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C - 1; ++j) {
            // Copy grid
            memcpy(grid, initial_grid, sizeof(grid));
            swap(grid[i][j], grid[i][j+1]);
            max_score = max(max_score, simulate());
        }
    }
    
    // Vertical swaps
    for (int i = 0; i < R - 1; ++i) {
        for (int j = 0; j < C; ++j) {
            memcpy(grid, initial_grid, sizeof(grid));
            swap(grid[i][j], grid[i+1][j]);
            max_score = max(max_score, simulate());
        }
    }
    
    cout << max_score << endl;
    
    return 0;
}
