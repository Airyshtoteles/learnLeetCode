#include <bits/stdc++.h>
using namespace std;

string winner_after_expansion(vector<vector<char>> grid){
    if(grid.empty() || grid[0].empty()) return "Draw";
    int n=grid.size(), m=grid[0].size();
    const int A=1,B=2;
    vector<vector<int>> owner(n, vector<int>(m, -1)); // -1=unreached,0=contested,1=A,2=B
    vector<vector<int>> dist(n, vector<int>(m, -1));
    deque<tuple<int,int,int,int>> q;
    int cntA=0, cntB=0;
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            if(grid[i][j]=='A'){
                owner[i][j]=A; dist[i][j]=0; q.emplace_back(i,j,0,A); ++cntA;
            } else if(grid[i][j]=='B'){
                owner[i][j]=B; dist[i][j]=0; q.emplace_back(i,j,0,B); ++cntB;
            }
        }
    }
    int dirs[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
    while(!q.empty()){
        auto [x,y,t,typ]=q.front(); q.pop_front();
        if(owner[x][y]==0) continue; // no expansion from contested
        for(auto &d: dirs){
            int nx=x+d[0], ny=y+d[1];
            if(nx<0||nx>=n||ny<0||ny>=m) continue;
            if(grid[nx][ny] != '.') continue;
            if(dist[nx][ny]==-1){
                dist[nx][ny]=t+1; owner[nx][ny]=typ; q.emplace_back(nx,ny,t+1,typ);
                if(typ==A) ++cntA; else ++cntB;
            } else {
                if(dist[nx][ny]==t+1 && owner[nx][ny]!=0 && owner[nx][ny]!=typ){
                    if(owner[nx][ny]==A) --cntA; else if(owner[nx][ny]==B) --cntB;
                    owner[nx][ny]=0; // contested
                }
            }
        }
    }
    if(cntA>cntB) return "A";
    if(cntB>cntA) return "B";
    return "Draw";
}

int main(){
    vector<vector<char>> grid={{'A','.','.'},{'.','B','.'},{'.','.','.'}};
    cout<<winner_after_expansion(grid)<<"\n";
    return 0;
}
