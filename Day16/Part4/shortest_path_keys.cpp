#include <bits/stdc++.h>
using namespace std;

// LC 864 — Shortest Path to Get All Keys

int shortestPathAllKeys(vector<string> grid){
    int n=grid.size(), m=grid[0].size();
    int sx=-1, sy=-1, allMask=0;
    for (int i=0;i<n;++i) for (int j=0;j<m;++j){
        char c=grid[i][j];
        if (c=='@'){sx=i;sy=j;}
        if (c>='a'&&c<='f') allMask |= 1<<(c-'a');
    }
    deque<tuple<int,int,int,int>> q; // x,y,mask,dist
    vector<vector<array<char,64>>> vis(n, vector<array<char,64>>(m));
    q.emplace_back(sx,sy,0,0); vis[sx][sy][0]=1;
    int dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};
    while(!q.empty()){
        auto [x,y,mask,d]=q.front(); q.pop_front();
        if (mask==allMask) return d;
        for (int k=0;k<4;++k){
            int nx=x+dx[k], ny=y+dy[k];
            if (nx<0||ny<0||nx>=n||ny>=m) continue;
            char c=grid[nx][ny];
            if (c=='#') continue;
            int nmask=mask;
            if (c>='a'&&c<='f') nmask|=1<<(c-'a');
            if (c>='A'&&c<='F') if (!(mask&(1<<(c-'A')))) continue;
            if (!vis[nx][ny][nmask]){ vis[nx][ny][nmask]=1; q.emplace_back(nx,ny,nmask,d+1);}        }
    }
    return -1;
}

int main(){
    vector<string> grid={"@.a..","###.#","b.A.B"};
    cout << shortestPathAllKeys(grid) << "\n"; // 8
    return 0;
}
