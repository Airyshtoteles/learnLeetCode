#include <bits/stdc++.h>
using namespace std;

int max_survival_time(int m, int n, const vector<pair<int,int>>& monsters, pair<int,int> start){
    const int INF = 1e9;
    vector<vector<int>> Tm(m, vector<int>(n, INF));
    deque<pair<int,int>> q;
    for(auto [x,y]: monsters){ if(0<=x&&x<m&&0<=y&&y<n){ Tm[x][y]=0; q.emplace_back(x,y);} }
    int dirs[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
    while(!q.empty()){
        auto [x,y]=q.front(); q.pop_front();
        for(auto &d: dirs){ int nx=x+d[0], ny=y+d[1]; if(0<=nx&&nx<m&&0<=ny&&ny<n && Tm[nx][ny]>Tm[x][y]+1){ Tm[nx][ny]=Tm[x][y]+1; q.emplace_back(nx,ny);} }
    }
    int sx=start.first, sy=start.second; if(!(0<=sx&&sx<m&&0<=sy&&sy<n)) return -1; if(Tm[sx][sy]==0) return -1;
    vector<vector<int>> Tp(m, vector<int>(n, -1)); Tp[sx][sy]=0; q.emplace_back(sx,sy);
    int best=-1;
    while(!q.empty()){
        auto [x,y]=q.front(); q.pop_front(); int t=Tp[x][y];
        if(t < Tm[x][y]) best=max(best,t);
        for(auto &d: dirs){ int nx=x+d[0], ny=y+d[1]; if(0<=nx&&nx<m&&0<=ny&&ny<n && Tp[nx][ny]==-1){ Tp[nx][ny]=t+1; q.emplace_back(nx,ny);} }
    }
    return best;
}

int main(){
    int m=5,n=5; vector<pair<int,int>> monsters={{0,0},{4,4}}; pair<int,int> start={2,2};
    cout<<max_survival_time(m,n,monsters,start)<<"\n";
    return 0;
}
