#include <bits/stdc++.h>
using namespace std;

long long max_tokens(const vector<vector<long long>>& grid){
    int n=grid.size(); if(!n) return -1; const long long INF_NEG = -(1LL<<60);
    vector<vector<long long>> dp(n, vector<long long>(n, INF_NEG));
    if(grid[0][0] >= 0) dp[0][0] = grid[0][0];
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(i==0 && j==0) continue;
            long long best=INF_NEG;
            if(i>0 && dp[i-1][j]!=INF_NEG && dp[i-1][j]+grid[i][j] >= 0) best=max(best, dp[i-1][j]+grid[i][j]);
            if(j>0 && dp[i][j-1]!=INF_NEG && dp[i][j-1]+grid[i][j] >= 0) best=max(best, dp[i][j-1]+grid[i][j]);
            dp[i][j]=best;
        }
    }
    return dp[n-1][n-1]==INF_NEG? -1: dp[n-1][n-1];
}

int main(){
    vector<vector<long long>> g={{1,-2,3},{2,-1,2},{1,2,1}};
    cout<<max_tokens(g)<<"\n";
    return 0;
}
