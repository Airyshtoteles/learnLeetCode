#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int main() {
    int R, C;
    if (cin >> R >> C) {
        vector<vector<int>> grid(R, vector<int>(C));
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j) cin >> grid[i][j];

        int startR, startC, endR, endC;
        cin >> startR >> startC >> endR >> endC;

        if (grid[startR][startC] == 1 || grid[endR][endC] == 1) {
            cout << "False" << endl;
            return 0;
        }

        vector<vector<bool>> visited(R, vector<bool>(C, false));
        queue<pair<int, int>> q;

        q.push({startR, startC});
        visited[startR][startC] = true;

        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            if (r == endR && c == endC) {
                cout << "True" << endl;
                return 0;
            }

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                    if (grid[nr][nc] == 0 && !visited[nr][nc]) {
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
        }

        cout << "False" << endl;
    }
    return 0;
}
