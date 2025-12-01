#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

struct Node {
    int k, r, c;
};

int main() {
    // Hardcoded Input
    // 3 Layers, 3x3
    int L = 3, N = 3, M = 3;
    vector<vector<vector<int>>> layers = {
        {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1}
        },
        {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
        },
        {
            {1, 0, 1},
            {0, 0, 0},
            {1, 0, 1}
        }
    };

    vector<vector<vector<bool>>> visited(L, vector<vector<bool>>(N, vector<bool>(M, false)));
    vector<int> cc_sizes;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int k = 0; k < L; ++k) {
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                if (layers[k][r][c] == 1 && !visited[k][r][c]) {
                    // BFS
                    queue<Node> q;
                    q.push({k, r, c});
                    visited[k][r][c] = true;
                    int size = 0;

                    while (!q.empty()) {
                        Node cur = q.front();
                        q.pop();
                        size++;

                        // Same layer neighbors
                        for (int i = 0; i < 4; ++i) {
                            int nr = cur.r + dr[i];
                            int nc = cur.c + dc[i];
                            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                                if (layers[cur.k][nr][nc] == 1 && !visited[cur.k][nr][nc]) {
                                    visited[cur.k][nr][nc] = true;
                                    q.push({cur.k, nr, nc});
                                }
                            }
                        }

                        // Other layers same pos
                        for (int nk = 0; nk < L; ++nk) {
                            if (nk != cur.k) {
                                if (layers[nk][cur.r][cur.c] == 1 && !visited[nk][cur.r][cur.c]) {
                                    visited[nk][cur.r][cur.c] = true;
                                    q.push({nk, cur.r, cur.c});
                                }
                            }
                        }
                    }
                    cc_sizes.push_back(size);
                }
            }
        }
    }

    sort(cc_sizes.rbegin(), cc_sizes.rend());

    int ans = 0;
    if (cc_sizes.size() >= 1) ans += cc_sizes[0];
    if (cc_sizes.size() >= 2) ans += cc_sizes[1];

    cout << "Max Dominoes: " << ans << endl;

    return 0;
}
