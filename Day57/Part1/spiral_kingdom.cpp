#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N;
vector<vector<int>> grid;

long long simulate(const vector<pair<int, int>>& path) {
    long long damage = 0;
    long long shield = 0;
    
    for (auto p : path) {
        int r = p.first;
        int c = p.second;
        int power = grid[r][c];
        
        if (power > shield) {
            damage += (power - shield);
        }
        shield += (power / 3);
    }
    return damage;
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    if (!(cin >> N)) return 0;
    cout << "N: " << N << endl;
    
    grid.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }
    
    int start_r, start_c;
    if (N % 2 == 1) {
        start_r = N / 2;
        start_c = N / 2;
    } else {
        start_r = N / 2 - 1;
        start_c = N / 2 - 1;
    }
    
    // Generate CW path
    vector<pair<int, int>> cw_path;
    int r = start_r;
    int c = start_c;
    cw_path.push_back({r, c});
    
    int step = 1;
    int dir_idx = 0;
    // Directions: R, D, L, U
    int dr_cw[] = {0, 1, 0, -1};
    int dc_cw[] = {1, 0, -1, 0};
    
    int count = 1;
    while (count < N * N) {
        for (int k = 0; k < 2; ++k) { // Two segments with same step length
            for (int s = 0; s < step; ++s) {
                if (count >= N * N) break;
                r += dr_cw[dir_idx];
                c += dc_cw[dir_idx];
                if (r >= 0 && r < N && c >= 0 && c < N) {
                    cw_path.push_back({r, c});
                    count++;
                } else {
                    // If out of bounds, we might be done or just skipping corners?
                    // Spiral should stay in bounds if N*N is correct.
                    // But for even N, center is offset.
                    // Let's just continue.
                }
            }
            dir_idx = (dir_idx + 1) % 4;
        }
        step++;
        if (step > 2 * N) break; // Safety break
    }
    
    // Generate CCW path
    // Start same
    // Directions: U, L, D, R? Or R, U, L, D?
    // "Spiral pattern starting from the center"
    // Usually CCW is: R, U, L, D... No, that's just rotated CW.
    // Standard CCW from center usually starts Up or Left?
    // Let's assume symmetric to CW.
    // CW: R, D, L, U
    // CCW: U, L, D, R? Or L, D, R, U?
    // Let's try U, L, D, R.
    
    vector<pair<int, int>> ccw_path;
    r = start_r;
    c = start_c;
    ccw_path.push_back({r, c});
    
    step = 1;
    dir_idx = 0;
    // Directions: U, L, D, R
    int dr_ccw[] = {-1, 0, 1, 0};
    int dc_ccw[] = {0, -1, 0, 1};
    
    count = 1;
    while (count < N * N) {
        for (int k = 0; k < 2; ++k) {
            for (int s = 0; s < step; ++s) {
                if (count >= N * N) break;
                r += dr_ccw[dir_idx];
                c += dc_ccw[dir_idx];
                if (r >= 0 && r < N && c >= 0 && c < N) {
                    ccw_path.push_back({r, c});
                    count++;
                }
            }
            dir_idx = (dir_idx + 1) % 4;
        }
        step++;
        if (step > 2 * N) break;
    }
    
    // Also consider starting directions?
    // "The spiral can be either clockwise or counter-clockwise."
    // Usually implies the orientation.
    // CW: (0,1), (1,0), (0,-1), (-1,0)
    // CCW: (0,-1), (1,0), (0,1), (-1,0)? No.
    // CCW is usually (0,1) -> (-1,0) -> (0,-1) -> (1,0) (Right, Up, Left, Down)
    // My CCW above was Up, Left, Down, Right.
    // Let's try both "Right-Down..." (CW) and "Right-Up..." (CCW).
    // And maybe "Up-Left..."?
    // The problem likely implies the standard two:
    // 1. Right, Down, Left, Up... (CW)
    // 2. Right, Up, Left, Down... (CCW)
    // Or maybe starting Up?
    // Given "choose the direction", I'll check 4 starting directions for CW and 4 for CCW?
    // No, usually spiral is fixed start direction (Right or Up).
    // I'll check:
    // 1. CW starting Right (R, D, L, U)
    // 2. CCW starting Right (R, U, L, D)
    // 3. CW starting Up (U, R, D, L)
    // 4. CCW starting Up (U, L, D, R)
    // Just to be safe.
    
    long long min_damage = simulate(cw_path);
    min_damage = min(min_damage, simulate(ccw_path)); // This was U, L, D, R
    
    // Let's add R, U, L, D (CCW starting Right)
    vector<pair<int, int>> ccw_path_2;
    r = start_r; c = start_c;
    ccw_path_2.push_back({r, c});
    step = 1; dir_idx = 0;
    int dr_ccw2[] = {0, -1, 0, 1}; // R, U, L, D
    int dc_ccw2[] = {1, 0, -1, 0};
    count = 1;
    while (count < N * N) {
        for (int k = 0; k < 2; ++k) {
            for (int s = 0; s < step; ++s) {
                if (count >= N * N) break;
                r += dr_ccw2[dir_idx];
                c += dc_ccw2[dir_idx];
                if (r >= 0 && r < N && c >= 0 && c < N) {
                    ccw_path_2.push_back({r, c});
                    count++;
                }
            }
            dir_idx = (dir_idx + 1) % 4;
        }
        step++;
        if (step > 2 * N) break;
    }
    min_damage = min(min_damage, simulate(ccw_path_2));
    
    // Let's add U, R, D, L (CW starting Up)
    vector<pair<int, int>> cw_path_2;
    r = start_r; c = start_c;
    cw_path_2.push_back({r, c});
    step = 1; dir_idx = 0;
    int dr_cw2[] = {-1, 0, 1, 0}; // U, R, D, L
    int dc_cw2[] = {0, 1, 0, -1};
    count = 1;
    while (count < N * N) {
        for (int k = 0; k < 2; ++k) {
            for (int s = 0; s < step; ++s) {
                if (count >= N * N) break;
                r += dr_cw2[dir_idx];
                c += dc_cw2[dir_idx];
                if (r >= 0 && r < N && c >= 0 && c < N) {
                    cw_path_2.push_back({r, c});
                    count++;
                }
            }
            dir_idx = (dir_idx + 1) % 4;
        }
        step++;
        if (step > 2 * N) break;
    }
    min_damage = min(min_damage, simulate(cw_path_2));
    
    cout << "Result: " << min_damage << endl;
    
    return 0;
}
