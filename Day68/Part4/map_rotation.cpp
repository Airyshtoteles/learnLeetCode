#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct State {
    int r, c, steps;
};

int main() {
    int R, C;
    if (cin >> R >> C) {
        vector<vector<int>> grid(R, vector<int>(C));
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j) cin >> grid[i][j];

        int startR, startC, targetR, targetC;
        cin >> startR >> startC >> targetR >> targetC;

        // visited[r][c][step_mod_4]
        vector<vector<vector<bool>>> visited(R, vector<vector<bool>>(C, vector<bool>(4, false)));
        queue<State> q;

        q.push({startR, startC, 0});
        visited[startR][startC][0] = true;

        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};

        while (!q.empty()) {
            State curr = q.front();
            q.pop();

            int r = curr.r;
            int c = curr.c;
            int steps = curr.steps;
            int mod = steps % 4;

            // Check if current position matches target position at this time step
            // Target position depends on rotation state
            // Rotation happens after step 2, 4, 6... (i.e., when steps >= 2, 4...)
            // Wait, the state (r, c) is the position AFTER 'steps' moves.
            // The rotation state is determined by 'steps'.
            // If (steps / 2) % 2 == 1, the map is rotated relative to t=0.
            
            int tr = targetR;
            int tc = targetC;
            if ((steps / 2) % 2 == 1) {
                tr = R - 1 - targetR;
                tc = C - 1 - targetC;
            }

            if (r == tr && c == tc) {
                cout << "True" << endl;
                return 0;
            }

            int next_steps = steps + 1;
            int next_mod = next_steps % 4;

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                // Check bounds and walls on the CURRENT map configuration
                // Map configuration depends on (steps / 2) % 2
                // If rotated, the wall at (wr, wc) in original map is at (R-1-wr, C-1-wc)
                // So to check if (nr, nc) is a wall, we transform (nr, nc) back to original frame
                
                int check_r = nr;
                int check_c = nc;
                if ((steps / 2) % 2 == 1) {
                    check_r = R - 1 - nr;
                    check_c = C - 1 - nc;
                }

                if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                    if (grid[check_r][check_c] == 0) {
                        // Valid move.
                        // Now, apply rotation if needed.
                        // Rotation happens if next_steps is a multiple of 2 (2, 4, 6...)
                        // i.e., we just finished step 2, 4...
                        
                        int final_r = nr;
                        int final_c = nc;
                        
                        if (next_steps % 2 == 0) {
                            final_r = R - 1 - nr;
                            final_c = C - 1 - nc;
                        }

                        if (!visited[final_r][final_c][next_mod]) {
                            visited[final_r][final_c][next_mod] = true;
                            q.push({final_r, final_c, next_steps});
                        }
                    }
                }
            }
        }

        cout << "False" << endl;
    }
    return 0;
}
