#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int main() {
    int m, n, k;
    if (!(cin >> m >> n >> k)) return 0;
    
    vector<vector<int>> grid(m, vector<int>(n));
    for(int i=0; i<m; ++i) {
        for(int j=0; j<n; ++j) {
            cin >> grid[i][j];
        }
    }
    
    if (k >= m + n - 2) {
        cout << m + n - 2 << endl;
        return 0;
    }
    
    // state: r, c, k_rem
    queue<tuple<int, int, int, int>> q;
    q.push({0, 0, k, 0});
    
    vector<vector<int>> visited(m, vector<int>(n, -1));
    visited[0][0] = k;
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    while(!q.empty()) {
        auto [r, c, k_rem, steps] = q.front();
        q.pop();
        
        if (r == m - 1 && c == n - 1) {
            cout << steps << endl;
            return 0;
        }
        
        for(int i=0; i<4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                int nk = k_rem - grid[nr][nc];
                
                if (nk >= 0 && nk > visited[nr][nc]) {
                    visited[nr][nc] = nk;
                    q.push({nr, nc, nk, steps + 1});
                }
            }
        }
    }
    
    cout << -1 << endl;
    
    return 0;
}
