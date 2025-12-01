#include <bits/stdc++.h>
using namespace std;

struct State{int r,c; unsigned int rm, cm; int d;};

int min_steps_sliding_trap_maze(vector<string> maze){
    int m = maze.size(), n = maze[0].size();
    pair<int,int> S{-1,-1}, E{-1,-1};
    for(int r=0;r<m;++r){
        for(int c=0;c<n;++c){
            if(maze[r][c]=='S') S={r,c};
            if(maze[r][c]=='E') E={r,c};
        }
    }
    if(S.first==-1||E.first==-1) return -1;
    auto inb = [&](int r,int c){return 0<=r&&r<m&&0<=c&&c<n;};

    queue<State> q;
    q.push({S.first,S.second,0u,0u,0});
    unordered_set<unsigned long long> vis;
    auto key = [&](int r,int c,unsigned int rm,unsigned int cm){
        return ( (unsigned long long)r<<48 ) ^ ( (unsigned long long)c<<32 ) ^ ((unsigned long long)rm<<16) ^ (unsigned long long)cm;
    };
    vis.insert(key(S.first,S.second,0u,0u));

    while(!q.empty()){
        auto cur = q.front(); q.pop();
        if(cur.r==E.first && cur.c==E.second) return cur.d;

        unsigned int nrm = cur.rm, ncm = cur.cm;
        if(maze[cur.r][cur.c]=='T'){
            nrm = cur.rm | (1u<<cur.r);
            ncm = cur.cm | (1u<<cur.c);
        }
        static int dr[4]={1,-1,0,0};
        static int dc[4]={0,0,1,-1};
        for(int i=0;i<4;++i){
            int nr = cur.r+dr[i], nc = cur.c+dc[i];
            if(!inb(nr,nc)) continue;
            if(maze[nr][nc]=='#') continue;
            if( (nrm>>nr)&1 ) continue;
            if( (ncm>>nc)&1 ) continue;
            auto k = key(nr,nc,nrm,ncm);
            if(vis.count(k)) continue;
            vis.insert(k);
            q.push({nr,nc,nrm,ncm,cur.d+1});
        }
    }
    return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> maze = {
        "S.T.",
        "....",
        ".T.E"
    };
    cout<<min_steps_sliding_trap_maze(maze)<<"\n"; // Expected 7
    return 0;
}
