#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct State {
    int r, c;
};

int main() {
    int R, C;
    if (!(cin >> R >> C)) return 0;

    vector<string> grid(R);
    int startR, startC, targetR, targetC;
    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == 'S') {
                startR = i; startC = j;
            } else if (grid[i][j] == 'T') {
                targetR = i; targetC = j;
            }
        }
    }

    // BFS
    // 'P' acts as a wall because it bounces you back to where you came from.
    // If you go A -> P -> A, you are back at A.
    // If A was visited, you are fine (you are currently at A).
    // But can you go anywhere else?
    // If A's other neighbors are visited, you are stuck.
    // Effectively, P doesn't help you reach new nodes.
    // So we treat P as a wall.
    
    queue<State> q;
    q.push({startR, startC});
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    visited[startR][startC] = true;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    bool reachable = false;

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.r == targetR && curr.c == targetC) {
            reachable = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                char cell = grid[nr][nc];
                if (cell != '#' && cell != 'P' && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }

    if (reachable) cout << "true" << endl;
    else cout << "false" << endl;

    return 0;
}
