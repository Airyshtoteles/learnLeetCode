#include <bits/stdc++.h>
using namespace std;

long long count_paths(int n, const set<pair<int,int>>& forbidden){
    vector<vector<vector<long long>>> dp(2*n+1, vector<vector<long long>>(n+1, vector<long long>(n+1,0)));
    if(forbidden.count({0,0})) return 0;
    dp[0][0][0]=1;
    for(int t=0; t<2*n; ++t){
        int mode = t%4; // 0,1 normal; 2,3 mirror
        for(int x=0;x<=n;++x){
            for(int y=0;y<=n;++y){
                long long ways = dp[t][x][y];
                if(!ways) continue;
                if(forbidden.count({x,y})) continue;
                vector<pair<int,int>> moves={{1,0},{0,1}};
                for(auto [dx,dy]: moves){
                    int ndx=dx, ndy=dy;
                    if(mode==2 || mode==3){
                        ndx=dy; ndy=dx;
                    }
                    int nx=x+ndx, ny=y+ndy;
                    if(nx<0||ny<0||nx>n||ny>n) continue;
                    if(forbidden.count({nx,ny})) continue;
                    dp[t+1][nx][ny]+=ways;
                }
            }
        }
    }
    return dp[2*n][n][n];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout<<count_paths(3, {{1,2}})<<"\n"; // Expected 4
    return 0;
}
