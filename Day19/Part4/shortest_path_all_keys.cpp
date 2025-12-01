#include <bits/stdc++.h>
using namespace std;

// LC 864 — Shortest Path to Get All Keys
// BFS with state (x, y, mask)

int shortestPathAllKeys(vector<string>& grid){
    int R = grid.size(), C = grid[0].size();
    int sx=0, sy=0, totalKeys=0;
    for(int i=0;i<R;++i){
        for(int j=0;j<C;++j){
            char ch = grid[i][j];
            if (ch=='@'){ sx=i; sy=j; }
            if (ch>='a' && ch<='f') totalKeys = max(totalKeys, ch - 'a' + 1);
        }
    }
    int allMask = (1<<totalKeys) - 1;
    vector<vector<vector<char>>> vis(R, vector<vector<char>>(C, vector<char>(1<<totalKeys, 0)));
    queue<tuple<int,int,int,int>> q; // x,y,mask,dist
    vis[sx][sy][0]=1; q.emplace(sx,sy,0,0);
    int dx[4]={1,-1,0,0}; int dy[4]={0,0,1,-1};
    while(!q.empty()){
        auto [x,y,mask,dist] = q.front(); q.pop();
        if (mask == allMask) return dist;
        for(int k=0;k<4;++k){
            int nx=x+dx[k], ny=y+dy[k];
            if (nx<0||ny<0||nx>=R||ny>=C) continue;
            char ch = grid[nx][ny];
            if (ch=='#') continue;
            int nmask = mask;
            if (ch>='a' && ch<='f') nmask |= 1 << (ch - 'a');
            if (ch>='A' && ch<='F'){
                int need = 1 << (ch - 'A');
                if ((nmask & need) == 0) continue;
            }
            if (!vis[nx][ny][nmask]){
                vis[nx][ny][nmask]=1;
                q.emplace(nx,ny,nmask,dist+1);
            }
        }
    }
    return -1;
}

int main(){
    vector<string> grid = {"@.a..","###.#","b.A.B"};
    cout << shortestPathAllKeys(grid) << "\n"; // 8
    return 0;
}
