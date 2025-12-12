#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> board(n);
    for (int i = 0; i < n; ++i) cin >> board[i];

    int k;
    cin >> k;

    // BFS state: {index, used_rewind}
    // used_rewind: 0 = not used, 1 = used
    queue<pair<int, int>> q;
    q.push({0, 0});

    vector<vector<bool>> visited(n, vector<bool>(2, false));
    visited[0][0] = true;

    while (!q.empty()) {
        auto [u, used] = q.front();
        q.pop();

        if (u == n - 1) {
            cout << "true" << endl;
            return 0;
        }

        // Move forward
        int v_forward = u + board[u];
        if (v_forward >= 0 && v_forward < n) {
            if (!visited[v_forward][used]) {
                visited[v_forward][used] = true;
                q.push({v_forward, used});
            }
        }

        // Rewind (only if not used)
        if (used == 0) {
            int v_rewind = u - k;
            if (v_rewind >= 0 && v_rewind < n) {
                if (!visited[v_rewind][1]) {
                    visited[v_rewind][1] = true;
                    q.push({v_rewind, 1});
                }
            }
        }
    }

    cout << "false" << endl;

    return 0;
}
