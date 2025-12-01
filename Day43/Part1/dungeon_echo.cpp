#include <bits/stdc++.h>
using namespace std;

struct State {
    int r, c, bounced;
};

int count_heard_cells(const vector<vector<int>>& grid) {
    if (grid.empty()) return 0;
    int m = grid.size();
    int n = grid[0].size();
    
    queue<State> q;
    // visited[r][c][bounced]
    vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(2, false)));
    vector<vector<bool>> heard(m, vector<bool>(n, false));
    
    for(int i=0; i<m; ++i) {
        for(int j=0; j<n; ++j) {
            if(grid[i][j] == 2) {
                q.push({i, j, 0});
                visited[i][j][0] = true;
                heard[i][j] = true;
            }
        }
    }
    
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    
    while(!q.empty()) {
        State cur = q.front(); q.pop();
        
        for(int k=0; k<4; ++k) {
            int nr = cur.r + dr[k];
            int nc = cur.c + dc[k];
            
            if(nr >= 0 && nr < m && nc >= 0 && nc < n) {
                if(grid[nr][nc] == 1) {
                    // Wall hit
                    if(cur.bounced == 0) {
                        // Bounce: move opposite from current
                        int br = cur.r - dr[k];
                        int bc = cur.c - dc[k];
                        if(br >= 0 && br < m && bc >= 0 && bc < n && grid[br][bc] != 1) {
                            if(!visited[br][bc][1]) {
                                visited[br][bc][1] = true;
                                heard[br][bc] = true;
                                q.push({br, bc, 1});
                            }
                        }
                    }
                } else {
                    // Normal move
                    if(!visited[nr][nc][cur.bounced]) {
                        visited[nr][nc][cur.bounced] = true;
                        heard[nr][nc] = true;
                        q.push({nr, nc, cur.bounced});
                    }
                }
            }
        }
    }
    
    int count = 0;
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
            if(heard[i][j]) count++;
            
    return count;
}

int main() {
    vector<vector<int>> grid = {
        {0,1,0,0},
        {2,1,0,1},
        {0,0,0,0}
    };
    cout << count_heard_cells(grid) << endl;
    return 0;
}
