#include <bits/stdc++.h>
using namespace std;

int trap_rain_water(vector<vector<int>> height){
    int m = (int)height.size();
    if(!m) return 0; int n = (int)height[0].size(); if(!n) return 0;
    vector<vector<int>> vis(m, vector<int>(n,0));
    using T = tuple<int,int,int>; // (h,r,c)
    priority_queue<T, vector<T>, greater<T>> pq;
    for(int r=0;r<m;++r){
        pq.emplace(height[r][0], r, 0); vis[r][0]=1;
        pq.emplace(height[r][n-1], r, n-1); vis[r][n-1]=1;
    }
    for(int c=0;c<n;++c){
        if(!vis[0][c]){ pq.emplace(height[0][c], 0, c); vis[0][c]=1; }
        if(!vis[m-1][c]){ pq.emplace(height[m-1][c], m-1, c); vis[m-1][c]=1; }
    }
    int res=0; int dr[4]={1,-1,0,0}; int dc[4]={0,0,1,-1};
    while(!pq.empty()){
        auto [h,r,c] = pq.top(); pq.pop();
        for(int k=0;k<4;++k){
            int nr=r+dr[k], nc=c+dc[k];
            if(nr<0||nr>=m||nc<0||nc>=n||vis[nr][nc]) continue;
            vis[nr][nc]=1; int nh=height[nr][nc];
            if(h>nh) res += (h-nh);
            pq.emplace(max(h,nh), nr, nc);
        }
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<int>> grid={{1,4,3,1,3,2},{3,2,1,3,2,4},{2,3,3,2,3,1}};
    cout << trap_rain_water(grid) << "\n"; // Expected 4
    return 0;
}
