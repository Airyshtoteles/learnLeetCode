#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct State {
    int r, c, cooldown;
};

int main() {
    int R, C;
    if (cin >> R >> C) {
        vector<vector<int>> grid(R, vector<int>(C));
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j) cin >> grid[i][j];

        int startR, startC, endR, endC;
        cin >> startR >> startC >> endR >> endC;

        // visited[r][c][cooldown]
        // cooldown: 0 = ready, 1 = broken
        vector<vector<vector<bool>>> visited(R, vector<vector<bool>>(C, vector<bool>(2, false)));
        queue<State> q;

        q.push({startR, startC, 0});
        visited[startR][startC][0] = true;

        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};

        while (!q.empty()) {
            State curr = q.front();
            q.pop();

            if (curr.r == endR && curr.c == endC) {
                cout << "True" << endl;
                return 0;
            }

            // Cooldown decreases by 1 each step (if > 0)
            // But wait, "broken for 1 step" means next step it is broken.
            // Step after that it is fixed.
            // So if curr.cooldown is 1, next state has cooldown 0.
            // If curr.cooldown is 0, next state has cooldown 0 (unless used).
            
            int next_cooldown_base = (curr.cooldown > 0) ? 0 : 0;

            for (int i = 0; i < 4; ++i) {
                int nr = curr.r + dr[i];
                int nc = curr.c + dc[i];

                if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                    int new_cooldown = next_cooldown_base;
                    bool possible = true;

                    if (grid[nr][nc] == 1) { // Door
                        if (curr.cooldown > 0) {
                            possible = false; // Key broken
                        } else {
                            new_cooldown = 1; // Use key, broken for next step
                        }
                    }

                    if (possible && !visited[nr][nc][new_cooldown]) {
                        visited[nr][nc][new_cooldown] = true;
                        q.push({nr, nc, new_cooldown});
                    }
                }
            }
        }

        cout << "False" << endl;
    }
    return 0;
}
