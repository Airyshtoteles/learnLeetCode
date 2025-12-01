#include <bits/stdc++.h>
using namespace std;

int shortest_path_all_keys(vector<string> grid){
    int m=grid.size(), n=grid[0].size();
    int sr=-1, sc=-1; int allmask=0;
    for(int r=0;r<m;++r){
        for(int c=0;c<n;++c){
            char ch=grid[r][c];
            if(ch=='@'){ sr=r; sc=c; }
            if(ch>='a' && ch<='f'){ allmask |= 1<<(ch-'a'); }
        }
    }
    queue<tuple<int,int,int,int>> q; // r,c,mask,dist
    q.emplace(sr,sc,0,0);
    unordered_set<long long> vis;
    auto enc=[&](int r,int c,int mask){ return ((long long)r<<40) ^ ((long long)c<<32) ^ mask; };
    vis.insert(enc(sr,sc,0));
    int dr[4]={1,-1,0,0}; int dc[4]={0,0,1,-1};
    while(!q.empty()){
        auto [r,c,mask,d]=q.front(); q.pop();
        if(mask==allmask) return d;
        for(int i=0;i<4;++i){
            int nr=r+dr[i], nc=c+dc[i]; if(nr<0||nr>=m||nc<0||nc>=n) continue;
            char ch=grid[nr][nc]; if(ch=='#') continue; int nmask=mask;
            if(ch>='a'&&ch<='f') nmask |= 1<<(ch-'a');
            if(ch>='A'&&ch<='F'){
                int need = 1<<(ch-'A'); if(!(nmask&need)) continue;
            }
            long long key=enc(nr,nc,nmask); if(vis.count(key)) continue; vis.insert(key);
            q.emplace(nr,nc,nmask,d+1);
        }
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<string> grid = {"@.a.#","###.#","b.A.B"};
    cout<<shortest_path_all_keys(grid)<<"\n"; // Expected 8
    return 0;
}
