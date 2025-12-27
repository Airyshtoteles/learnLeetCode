#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const int INF = 1e9;
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

bool solve() {
    int R, C;
    if (!(cin >> R >> C)) return false;
    
    vector<vector<int>> grid(R, vector<int>(C));
    int startR, startC, targetR, targetC;
    
    queue<pair<int, int>> qCollapse;
    vector<vector<int>> distCollapse(R, vector<int>(C, INF));
    
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 1) {
                qCollapse.push({i, j});
                distCollapse[i][j] = 0;
            }
        }
    }
    
    cin >> startR >> startC >> targetR >> targetC;
    
    // BFS for Collapse
    while (!qCollapse.empty()) {
        auto [r, c] = qCollapse.front();
        qCollapse.pop();
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                if (distCollapse[nr][nc] == INF) {
                    distCollapse[nr][nc] = distCollapse[r][c] + 1;
                    qCollapse.push({nr, nc});
                }
            }
        }
    }
    
    // BFS for Player
    queue<pair<int, int>> qPlayer;
    vector<vector<int>> distPlayer(R, vector<int>(C, INF));
    
    // Check if start is safe at time 0
    if (distCollapse[startR][startC] <= 0) return false;
    
    qPlayer.push({startR, startC});
    distPlayer[startR][startC] = 0;
    
    while (!qPlayer.empty()) {
        auto [r, c] = qPlayer.front();
        qPlayer.pop();
        
        if (r == targetR && c == targetC) return true;
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                if (distPlayer[nr][nc] == INF) {
                    int nextTime = distPlayer[r][c] + 1;
                    // Check if safe
                    // Player arrives at nextTime.
                    // Collapse arrives at distCollapse[nr][nc].
                    // Must be strictly less?
                    // "Setiap langkah, semua sel 1 menyebar".
                    // Time 0: P at start. C at 1s.
                    // Time 1: P moves. C spreads.
                    // If P moves to X, and C spreads to X at same time, P dies?
                    // Usually yes. So we need nextTime < distCollapse[nr][nc].
                    
                    if (nextTime < distCollapse[nr][nc]) {
                        distPlayer[nr][nc] = nextTime;
                        qPlayer.push({nr, nc});
                    }
                }
            }
        }
    }
    
    return false;
}

int main() {
    cout << (solve() ? "true" : "false") << endl;
    return 0;
}
