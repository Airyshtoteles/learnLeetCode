#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int main() {
    int R, C;
    if (cin >> R >> C) {
        int sr, sc, br, bc, k;
        cin >> sr >> sc >> br >> bc >> k;

        // BFS state: r, c, time
        queue<tuple<int, int, int>> q;
        q.push({sr, sc, 0});

        // Visited array to prevent cycles/redundant checks
        // Since we want shortest time, standard visited is fine.
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        visited[sr][sc] = true;

        bool possible = false;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c, t] = q.front();
            q.pop();

            // Check if current position is valid at current time
            // Actually, we should check validity before pushing or after popping.
            // Let's check after popping to be safe (though pushing check is better for queue size).
            // But the start position must be valid at t=0.
            
            int layer = t / k;
            int min_r = layer;
            int max_r = R - 1 - layer;
            int min_c = layer;
            int max_c = C - 1 - layer;

            if (r < min_r || r > max_r || c < min_c || c > max_c) {
                continue; // Collapsed
            }

            if (r == br && c == bc) {
                possible = true;
                break;
            }

            // Next step
            int nt = t + 1;
            int n_layer = nt / k;
            int n_min_r = n_layer;
            int n_max_r = R - 1 - n_layer;
            int n_min_c = n_layer;
            int n_max_c = C - 1 - n_layer;

            // If arena is completely gone
            if (n_min_r > n_max_r || n_min_c > n_max_c) continue;

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= n_min_r && nr <= n_max_r && nc >= n_min_c && nc <= n_max_c) {
                    if (!visited[nr][nc]) {
                        visited[nr][nc] = true;
                        q.push({nr, nc, nt});
                    }
                }
            }
        }

        cout << (possible ? "1" : "0") << endl;
    }
    return 0;
}
