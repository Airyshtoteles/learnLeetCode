#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Function to get the target position for a planet at (r, c)
pair<int, int> get_target(int r, int c, int N, const vector<vector<long long>>& grid) {
    if (grid[r][c] == 0) return {r, c}; // Empty space doesn't move

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    long long max_mass = -1;
    vector<int> max_dirs;

    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
            if (grid[nr][nc] > max_mass) {
                max_mass = grid[nr][nc];
                max_dirs.clear();
                max_dirs.push_back(i);
            } else if (grid[nr][nc] == max_mass) {
                max_dirs.push_back(i);
            }
        }
    }

    // If more than one direction has the same max mass, stay
    if (max_dirs.size() != 1) {
        return {r, c};
    }

    // Move to the single direction with max mass
    int dir = max_dirs[0];
    return {r + dr[dir], c + dc[dir]};
}

int main() {
    int N;
    long long T;
    if (!(cin >> N >> T)) return 0;

    vector<vector<long long>> grid(N, vector<long long>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }

    map<vector<vector<long long>>, int> history;
    vector<vector<vector<long long>>> states;

    for (int t = 0; t < T; ++t) {
        // Check for cycle
        if (history.count(grid)) {
            int prev_t = history[grid];
            int period = t - prev_t;
            long long remaining = T - t;
            int offset = remaining % period;
            
            // The state at T will be the same as state at prev_t + offset
            grid = states[prev_t + offset];
            break;
        }

        history[grid] = t;
        states.push_back(grid);

        vector<vector<long long>> next_grid(N, vector<long long>(N, 0));
        bool moved = false;

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (grid[r][c] > 0) {
                    pair<int, int> target = get_target(r, c, N, grid);
                    next_grid[target.first][target.second] += grid[r][c];
                    if (target.first != r || target.second != c) {
                        moved = true;
                    }
                }
            }
        }

        grid = next_grid;

        // Optimization: If no planet moved, the state is stable.
        if (!moved) {
            break; 
        }
    }

    long long max_m = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            max_m = max(max_m, grid[i][j]);
        }
    }

    cout << max_m << endl;

    return 0;
}
