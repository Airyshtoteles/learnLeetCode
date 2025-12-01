#include <bits/stdc++.h>
using namespace std;

int min_walls_rotating_maze(const vector<string>& grid){
    if(grid.empty()) return -1;
    int n=grid.size(), m=grid[0].size();
    const int INF = 1e9;
    vector<vector<array<int,10>>> dist(n, vector<array<int,10>>(m));
    for(int i=0;i<n;++i) for(int j=0;j<m;++j) dist[i][j].fill(INF);
    using State = tuple<int,int,int,int>; // cost,r,c,tmod
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[0][0][0]=0; pq.emplace(0,0,0,0);
    int dr[4]={1,-1,0,0}; int dc[4]={0,0,1,-1};
    while(!pq.empty()){
        auto [cost,r,c,tmod]=pq.top(); pq.pop();
        if(cost!=dist[r][c][tmod]) continue;
        if(r==n-1 && c==m-1) return cost;
        int ntmod=(tmod+1)%10; int phase=((tmod+1)/5)%2; // after move phase
        for(int k=0;k<4;++k){
            int nr=r+dr[k], nc=c+dc[k];
            if(nr<0||nr>=n||nc<0||nc>=m) continue;
            char ch=grid[nr][nc]; int add=0;
            if(ch=='R') add=1;
            else if(ch=='#'){
                if(phase==0) add=1; // wall in original phase
            }
            int ncost=cost+add;
            if(ncost<dist[nr][nc][ntmod]){
                dist[nr][nc][ntmod]=ncost;
                pq.emplace(ncost,nr,nc,ntmod);
            }
        }
    }
    int best=INF; for(int t=0;t<10;++t) best=min(best, dist[n-1][m-1][t]);
    return best==INF?-1:best;
}

int main(){
    vector<string> maze={".#.","R#.","..#"};
    cout<<min_walls_rotating_maze(maze)<<"\n";
    return 0;
}
