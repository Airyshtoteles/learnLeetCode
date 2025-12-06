#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int W, H;
vector<string> blocks;
int min_final_height = 1e9;

// Grid is represented as vector<int> of size H.
// Each int is a bitmask of width W.
// Row 0 is bottom.

struct Shape {
    vector<int> mask; // mask[0] is bottom row of shape
    int w, h;
};

map<string, vector<Shape>> shapes;

void init_shapes() {
    // I
    shapes["I"].push_back({{1, 1, 1, 1}, 1, 4}); // Vertical
    shapes["I"].push_back({{15}, 4, 1}); // Horizontal (1111 = 15)

    // O
    shapes["O"].push_back({{3, 3}, 2, 2}); // 11, 11

    // L
    // L: 
    // 1 0
    // 1 0
    // 1 1
    // Bottom row is 1 1 (3). Middle 1 0 (1? No, 1<<1? No, usually 1 is rightmost?)
    // Let's define bit 0 as left.
    // 1 1 -> 1 | 2 = 3.
    // 1 0 -> 1.
    // So {{3, 1, 1}, 2, 3}
    shapes["L"].push_back({{3, 1, 1}, 2, 3}); 
    // Rotations...
    // L rot 90:
    // 1 1 1
    // 1 0 0
    // Bottom 1 0 0 (1). Top 1 1 1 (7).
    shapes["L"].push_back({{1, 7}, 3, 2});
    // L rot 180:
    // 1 1
    // 0 1
    // 0 1
    // Bottom 0 1 (2). Top 1 1 (3).
    shapes["L"].push_back({{2, 2, 3}, 2, 3});
    // L rot 270:
    // 0 0 1
    // 1 1 1
    // Bottom 7. Top 4.
    shapes["L"].push_back({{7, 4}, 3, 2});

    // J
    // J:
    // 0 1
    // 0 1
    // 1 1
    // Bottom 3. Top 2, 2.
    shapes["J"].push_back({{3, 2, 2}, 2, 3});
    // Rotations...
    shapes["J"].push_back({{7, 1}, 3, 2}); // 1 0 0 / 1 1 1
    shapes["J"].push_back({{1, 1, 3}, 2, 3}); // 1 1 / 1 0 / 1 0
    shapes["J"].push_back({{4, 7}, 3, 2}); // 1 1 1 / 0 0 1

    // T
    // 1 1 1
    // 0 1 0
    // Bottom 2. Top 7.
    shapes["T"].push_back({{2, 7}, 3, 2});
    // 0 1
    // 1 1
    // 0 1
    // Bottom 2. Mid 3. Top 2.
    shapes["T"].push_back({{2, 3, 2}, 2, 3});
    // 0 1 0
    // 1 1 1
    // Bottom 7. Top 2.
    shapes["T"].push_back({{7, 2}, 3, 2});
    // 1 0
    // 1 1
    // 1 0
    // Bottom 1. Mid 3. Top 1.
    shapes["T"].push_back({{1, 3, 1}, 2, 3});

    // S
    // 0 1 1
    // 1 1 0
    // Bottom 3. Top 6.
    shapes["S"].push_back({{3, 6}, 3, 2});
    // 1 0
    // 1 1
    // 0 1
    // Bottom 2. Mid 3. Top 1.
    shapes["S"].push_back({{2, 3, 1}, 2, 3});

    // Z
    // 1 1 0
    // 0 1 1
    // Bottom 6. Top 3.
    shapes["Z"].push_back({{6, 3}, 3, 2});
    // 0 1
    // 1 1
    // 1 0
    // Bottom 1. Mid 3. Top 2.
    shapes["Z"].push_back({{1, 3, 2}, 2, 3});
}

int get_grid_height(const vector<int>& grid) {
    for (int r = H - 1; r >= 0; --r) {
        if (grid[r] != 0) return r + 1;
    }
    return 0;
}

// Memoization
map<pair<int, vector<int>>, int> memo;

void dfs(int idx, vector<int> grid) {
    if (idx == blocks.size()) {
        int h = get_grid_height(grid);
        if (h < min_final_height) min_final_height = h;
        return;
    }

    // Pruning
    int current_h = get_grid_height(grid);
    if (current_h >= min_final_height) return; // Can't improve? Wait, clearing lines reduces height.
    // But if current height is already >= min_final_height found so far, and we add blocks...
    // Clearing lines can reduce height. So this pruning is risky.
    // But if current_h >= H, it's game over.
    if (current_h >= H) return;

    // Memoization check
    if (memo.count({idx, grid})) {
        if (memo[{idx, grid}] <= current_h) return; // Already visited with better or equal height?
        // Wait, memo should store min final height reachable?
        // Or just visited state?
        // Since we want global min, we can just store visited.
        // But different paths might reach same state.
        // If we reached this state before, we don't need to explore again.
    }
    memo[{idx, grid}] = current_h;

    string type = blocks[idx];
    for (const auto& shape : shapes[type]) {
        for (int col = 0; col <= W - shape.w; ++col) {
            // Try to drop at col
            // Find landing row
            // We drop from top.
            // Check collision.
            // Start from row H - shape.h down to 0.
            // Actually, we can just find the highest obstruction in the columns.
            
            int land_r = -1;
            for (int r = H - shape.h; r >= 0; --r) {
                bool collision = false;
                for (int sr = 0; sr < shape.h; ++sr) {
                    if (grid[r + sr] & (shape.mask[sr] << col)) {
                        collision = true;
                        break;
                    }
                }
                if (collision) {
                    // Can't place here. Must place above.
                    // So valid placement was r+1.
                    land_r = r + 1;
                    break;
                }
                if (r == 0) land_r = 0; // Reached bottom
            }

            if (land_r != -1 && land_r + shape.h <= H) {
                // Place block
                vector<int> next_grid = grid;
                for (int sr = 0; sr < shape.h; ++sr) {
                    next_grid[land_r + sr] |= (shape.mask[sr] << col);
                }

                // Clear lines
                vector<int> cleared_grid;
                int full_mask = (1 << W) - 1;
                for (int r = 0; r < H; ++r) {
                    if (next_grid[r] != full_mask) {
                        cleared_grid.push_back(next_grid[r]);
                    }
                }
                while (cleared_grid.size() < H) {
                    cleared_grid.push_back(0);
                }

                dfs(idx + 1, cleared_grid);
            }
        }
    }
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    int N_blocks;
    if (!(cin >> N_blocks)) return 0;
    blocks.resize(N_blocks);
    for (int i = 0; i < N_blocks; ++i) cin >> blocks[i];
    cin >> W >> H;

    init_shapes();

    vector<int> grid(H, 0);
    dfs(0, grid);

    cout << min_final_height << endl;

    return 0;
}
