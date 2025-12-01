#include <bits/stdc++.h>
using namespace std;

long long lcmll(long long a,long long b){ if(!a||!b) return a|b; return a/__gcd(a,b)*b; }

bool is_open(char initial, int k, long long t){
    if(initial=='S' || initial=='E') initial='.';
    if(k==0) return initial!='#';
    long long flips = (t / k) % 2;
    if(flips==0) return initial!='#';
    else return initial=='#';
}

long long min_time(vector<vector<char>> grid, const vector<vector<int>>& flip){
    int n=grid.size(); int m=n?grid[0].size():0; if(!n||!m) return -1;
    pair<int,int> S{-1,-1}, E{-1,-1};
    long long L=1;
    for(int i=0;i<n;++i) for(int j=0;j<m;++j){
        if(grid[i][j]=='S') S={i,j};
        if(grid[i][j]=='E') E={i,j};
        if(flip[i][j]>0) L=lcmll(L, 2LL*flip[i][j]);
    }
    if(S.first==-1||E.first==-1) return -1;
    vector<vector<vector<char>>> vis(n, vector<vector<char>>(m, vector<char>(L, 0)));
    deque<tuple<int,int,long long>> q; q.emplace_back(S.first,S.second,0);
    vis[S.first][S.second][0]=1;
    int dirs[5][2]={{-1,0},{1,0},{0,-1},{0,1},{0,0}}; // include wait
    while(!q.empty()){
        auto [x,y,t]=q.front(); q.pop_front();
        if(x==E.first && y==E.second) return t;
        for(auto &d: dirs){
            int nx=x+d[0], ny=y+d[1]; long long nt=t+1;
            if(nx<0||nx>=n||ny<0||ny>=m) continue;
            if(is_open(grid[x][y], flip[x][y], t) && is_open(grid[nx][ny], flip[nx][ny], nt)){
                long long tm = L? (nt % L) : 0;
                if(!vis[nx][ny][tm]){ vis[nx][ny][tm]=1; q.emplace_back(nx,ny,nt); }
            }
        }
    }
    return -1;
}

int main(){
    vector<vector<char>> grid={{'S','.','#'},{'.','#','E'}};
    vector<vector<int>> flip={{0,2,1},{3,0,2}};
    cout<<min_time(grid, flip)<<"\n"; // Expected 5
    return 0;
}
