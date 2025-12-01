#include <bits/stdc++.h>
using namespace std;

// LC 2328 — Number of Increasing Paths in a Grid

static const int MOD = 1'000'000'007;

int m_, n_;
vector<vector<int>> G;
vector<vector<int>> memo;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

int dfs(int x, int y){
    int& res = memo[x][y];
    if (res != -1) return res;
    long long cur = 1; // cell itself
    for(int k=0;k<4;++k){
        int nx = x+dx[k], ny = y+dy[k];
        if (nx<0||ny<0||nx>=m_||ny>=n_) continue;
        if (G[nx][ny] > G[x][y]){
            cur += dfs(nx, ny);
            if (cur >= (long long)4e18) cur %= MOD; // keep small
        }
    }
    res = (int)(cur % MOD);
    return res;
}

int countPaths(vector<vector<int>>& grid){
    G = grid; m_ = G.size(); n_ = G[0].size();
    memo.assign(m_, vector<int>(n_, -1));
    long long ans = 0;
    for(int i=0;i<m_;++i){ for(int j=0;j<n_;++j){ ans += dfs(i,j); if(ans>=(long long)4e18) ans%=MOD; } }
    return (int)(ans % MOD);
}

int main(){
    vector<vector<int>> g = {{1,2},{3,4}};
    cout << countPaths(g) << "\n"; // 8
    return 0;
}
