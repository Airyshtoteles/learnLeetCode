#include <bits/stdc++.h>
using namespace std;

int min_steps(const vector<string>& grid){
    int n = (int)grid.size();
    if(!n) return -1; int m = (int)grid[0].size(); if(!m) return -1;
    map<pair<int,int>, int> key_id; int kid=0;
    for(int r=0;r<n;++r) for(int c=0;c<m;++c) if(grid[r][c]=='K') key_id[{r,c}] = kid++;
    int all_mask = (1<<kid) - 1;
    auto passable = [&](int r,int c,int mask){
        char ch = grid[r][c];
        if(ch=='#') return false;
        if(ch=='D' && mask!=all_mask) return false;
        return true;
    };
    if(grid[0][0]=='#') return -1;
    int start_mask = 0; if(grid[0][0]=='K') start_mask |= 1<<key_id[{0,0}];
    vector<vector<vector<char>>> vis(n, vector<vector<char>>(m, vector<char>(1<<kid, 0)));
    queue<tuple<int,int,int,int>> q; // r,c,mask,dist
    q.emplace(0,0,start_mask,0); vis[0][0][start_mask]=1;
    int dr[4]={1,-1,0,0}, dc[4]={0,0,1,-1};
    while(!q.empty()){
        auto [r,c,mask,dist]=q.front(); q.pop();
        if(r==n-1 && c==m-1) return dist;
        for(int k=0;k<4;++k){
            int nr=r+dr[k], nc=c+dc[k];
            if(nr<0||nr>=n||nc<0||nc>=m) continue;
            int nmask = mask;
            char ch = grid[nr][nc];
            if(ch=='K') nmask = mask | (1<<key_id[{nr,nc}]);
            if(passable(nr,nc,mask) && !vis[nr][nc][nmask]){
                vis[nr][nc][nmask]=1;
                q.emplace(nr,nc,nmask,dist+1);
            }
        }
    }
    return -1;
}

int main(){ ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<string> grid={".K..","##D.","..#.","...K"};
    cout << min_steps(grid) << "\n";
    return 0; }
