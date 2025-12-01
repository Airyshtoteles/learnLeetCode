// Flip Matrix to Zero — BFS on bitmask state space
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

int min_flips(vector<vector<int>> mat) {
    int m = static_cast<int>(mat.size());
    int n = static_cast<int>(mat[0].size());
    auto idx = [&](int r, int c) { return r * n + c; };

    int start = 0;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (mat[r][c]) start |= (1 << idx(r, c));
        }
    }
    if (start == 0) return 0;

    vector<int> masks;
    const int dr[5] = {1, -1, 0, 0, 0};
    const int dc[5] = {0, 0, 1, -1, 0};
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            int mask = 0;
            for (int k = 0; k < 5; ++k) {
                int nr = r + dr[k], nc = c + dc[k];
                if (0 <= nr && nr < m && 0 <= nc && nc < n) {
                    mask |= (1 << idx(nr, nc));
                }
            }
            masks.push_back(mask);
        }
    }

    queue<pair<int, int>> q;
    q.push({start, 0});
    unordered_set<int> vis;
    vis.insert(start);

    while (!q.empty()) {
        auto [s, d] = q.front();
        q.pop();
        if (s == 0) return d;
        for (int mask : masks) {
            int ns = s ^ mask;
            if (!vis.count(ns)) {
                vis.insert(ns);
                q.push({ns, d + 1});
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << min_flips({{0, 0}, {0, 1}}) << "\n"; // Expected 3
    return 0;
}
