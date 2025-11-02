#include <bits/stdc++.h>
using namespace std;

long long lcmll(long long a,long long b){ if(!a||!b) return a|b; return a/__gcd(a,b)*b; }

int min_time(const vector<string>& grid){
    int n=grid.size(); int m=n?grid[0].size():0; if(!n||!m) return -1;
    pair<int,int> S{-1,-1}, E{-1,-1};
    array<vector<pair<int,int>>,10> portals;
    long long L=1;
    for(int i=0;i<n;++i) for(int j=0;j<m;++j){
        char c=grid[i][j];
        if(c=='S') S={i,j}; else if(c=='E') E={i,j};
        else if(isdigit((unsigned char)c)){
            int d=c-'0'; portals[d].push_back({i,j}); if(d) L=lcmll(L,d);
        }
    }
    if(S.first==-1 || E.first==-1) return -1;
    if(L==0) L=1;
    vector vis(n, vector(m, vector<char>(L, 0)));
    deque<tuple<int,int,long long>> q; q.emplace_back(S.first,S.second,0);
    vis[S.first][S.second][0]=1;
    int dirs[5][2]={{-1,0},{1,0},{0,-1},{0,1},{0,0}}; // wait included
    auto is_wall=[&](int i,int j){return grid[i][j]=='W';};
    while(!q.empty()){
        auto [x,y,t]=q.front(); q.pop_front();
        if(x==E.first && y==E.second) return (int)t;
        for(auto &d:dirs){
            int nx=x+d[0], ny=y+d[1]; long long nt=t+1;
            if(nx<0||nx>=n||ny<0||ny>=m) continue;
            if(is_wall(nx,ny) || is_wall(x,y)) continue;
            vector<pair<int,int>> cand;
            char c=grid[nx][ny];
            if(isdigit((unsigned char)c)){
                int X=c-'0';
                if(X==0 || nt%X==0){
                    auto &v=portals[X];
                    for(auto &p:v) if(!(p.first==nx && p.second==ny)) cand.push_back(p);
                    if(v.empty() || cand.empty()) cand.push_back({nx,ny});
                } else continue;
            } else cand.push_back({nx,ny});
            long long tm = nt % L;
            for(auto &p:cand){
                int tx=p.first, ty=p.second;
                if(!vis[tx][ty][tm]){ vis[tx][ty][tm]=1; q.emplace_back(tx,ty,nt);}            }
        }
    }
    return -1;
}

int main(){
    vector<string> grid={"S1.W","..1E","W..W"};
    cout<<min_time(grid)<<"\n";
    return 0;
}
