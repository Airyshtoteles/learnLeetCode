#include <bits/stdc++.h>
using namespace std;

// The Dungeon of Echoes — Assumptions:
// - Move 4-dir on 0 or 2 cells (1 is wall).
// - Teleport from portal (2) to any other portal costs 1.
// - After teleport, destroy source row and source column: all 0 in that row/col become 1 (portals remain passable).
// BFS on state (r,c,rowMask,colMask).

int shortest_path_dungeon(const vector<vector<int>>& grid){
    int m = grid.size(); if(!m) return -1; int n = grid[0].size(); if(!n) return -1;
    vector<pair<int,int>> portals;
    for(int i=0;i<m;++i) for(int j=0;j<n;++j) if(grid[i][j]==2) portals.push_back({i,j});
    auto is_blocked = [&](int i, int j, int rm, int cm){
        if(grid[i][j]==1) return true;
        if(grid[i][j]==2) return false;
        if((rm>>i)&1) return true;
        if((cm>>j)&1) return true;
        return false;
    };
    if(is_blocked(0,0,0,0) || is_blocked(m-1,n-1,0,0)) return -1;
    queue<tuple<int,int,int,int,int>> q; // r,c,rm,cm,d
    unordered_set<long long> seen;
    auto keyOf=[&](int r,int c,int rm,int cm){ return ( (long long)r<<48 ) | ( (long long)c<<32 ) | ( (long long)rm<<16 ) | (long long)cm; };
    q.emplace(0,0,0,0,0); seen.insert(keyOf(0,0,0,0));
    while(!q.empty()){
        auto [r,c,rm,cm,d] = q.front(); q.pop();
        if(r==m-1 && c==n-1) return d;
        const int dr[4]={1,-1,0,0}; const int dc[4]={0,0,1,-1};
        for(int t=0;t<4;++t){ int nr=r+dr[t], nc=c+dc[t];
            if(nr>=0&&nr<m&&nc>=0&&nc<n && !is_blocked(nr,nc,rm,cm)){
                long long k = keyOf(nr,nc,rm,cm);
                if(!seen.count(k)){ seen.insert(k); q.emplace(nr,nc,rm,cm,d+1); }
            }
        }
        if(grid[r][c]==2 && !portals.empty()){
            int nrm = rm | (1<<r); int ncm = cm | (1<<c);
            for(auto [pr,pc]: portals){ if(pr==r && pc==c) continue; long long k=keyOf(pr,pc,nrm,ncm); if(!seen.count(k)){ seen.insert(k); q.emplace(pr,pc,nrm,ncm,d+1);} }
        }
    }
    return -1;
}

int main(){
    vector<vector<int>> grid={{0,2,0},{1,0,0},{2,1,0}};
    cout << shortest_path_dungeon(grid) << "\n"; // ~4
    return 0;
}
