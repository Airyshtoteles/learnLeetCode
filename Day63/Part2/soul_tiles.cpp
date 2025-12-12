#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

bool is_uniform(const vector<vector<int>>& grid, int n) {
    int val = grid[0][0];
    for (const auto& row : grid) {
        for (int x : row) {
            if (x != val) return false;
        }
    }
    return true;
}

int get_majority(const vector<int>& arr) {
    map<int, int> counts;
    for (int x : arr) counts[x]++;
    
    int max_count = -1;
    int best_val = -1;
    
    for (auto const& [val, count] : counts) {
        if (count > max_count) {
            max_count = count;
            best_val = val;
        } else if (count == max_count) {
            if (val > best_val) best_val = val;
        }
    }
    return best_val;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    if (is_uniform(grid, n)) {
        cout << 0 << endl;
        return 0;
    }

    queue<vector<vector<int>>> q;
    q.push(grid);
    
    map<vector<vector<int>>, int> dist;
    dist[grid] = 0;

    while (!q.empty()) {
        vector<vector<int>> curr = q.front();
        q.pop();

        int d = dist[curr];
        if (d >= 2 * n + 1) continue; // Pruning?

        // Try syncing each row
        for (int r = 0; r < n; ++r) {
            vector<vector<int>> next_grid = curr;
            int maj = get_majority(next_grid[r]);
            for (int c = 0; c < n; ++c) next_grid[r][c] = maj;
            
            if (dist.find(next_grid) == dist.end()) {
                if (is_uniform(next_grid, n)) {
                    cout << d + 1 << endl;
                    return 0;
                }
                dist[next_grid] = d + 1;
                q.push(next_grid);
            }
        }

        // Try syncing each col
        for (int c = 0; c < n; ++c) {
            vector<vector<int>> next_grid = curr;
            vector<int> col_vals;
            for (int r = 0; r < n; ++r) col_vals.push_back(next_grid[r][c]);
            
            int maj = get_majority(col_vals);
            for (int r = 0; r < n; ++r) next_grid[r][c] = maj;

            if (dist.find(next_grid) == dist.end()) {
                if (is_uniform(next_grid, n)) {
                    cout << d + 1 << endl;
                    return 0;
                }
                dist[next_grid] = d + 1;
                q.push(next_grid);
            }
        }
    }

    return 0;
}
