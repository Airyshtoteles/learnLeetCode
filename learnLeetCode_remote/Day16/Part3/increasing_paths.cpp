#include <bits/stdc++.h>
using namespace std;

// LC 2328 — Number of Increasing Paths in a Grid

static const int MOD = 1'000'000'007;
int n_, m_;
vector<vector<int>> G;
vector<vector<int>> memo;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

int dfs(int x,int y){
    int &res = memo[x][y];
    if (res != -1) return res;
    long long total = 1; // the cell itself
    for (int k=0;k<4;++k){
        int nx=x+dx[k], ny=y+dy[k];
        if (nx>=0 && ny>=0 && nx<n_ && ny<m_ && G[nx][ny] > G[x][y]){
            total += dfs(nx,ny);
        }
    }
    return res = (int)(total % MOD);
}

int countPaths(vector<vector<int>>& grid){
    G = grid; n_=grid.size(); m_=grid[0].size();
    memo.assign(n_, vector<int>(m_, -1));
    long long ans=0;
    for (int i=0;i<n_;++i) for (int j=0;j<m_;++j){ ans += dfs(i,j); if (ans>=MOD) ans-=MOD; }
    return (int)ans;
}

int main(){
    vector<vector<int>> grid = {{1,2},{3,4}};
    cout << countPaths(grid) << "\n"; // 8
    return 0;
}
