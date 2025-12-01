#include <bits/stdc++.h>
using namespace std;

// LC 407 — Trapping Rain Water II

int trapRainWater(vector<vector<int>>& heightMap){
    int n = heightMap.size();
    if (!n) return 0;
    int m = heightMap[0].size();
    if (!m) return 0;
    vector<vector<char>> vis(n, vector<char>(m, 0));

    using T = tuple<int,int,int>; // (height, x, y)
    priority_queue<T, vector<T>, greater<T>> pq;

    // push borders
    for (int i=0;i<n;++i){
        pq.emplace(heightMap[i][0], i, 0); vis[i][0]=1;
        if (m>1){ pq.emplace(heightMap[i][m-1], i, m-1); vis[i][m-1]=1; }
    }
    for (int j=0;j<m;++j){
        if (!vis[0][j]){ pq.emplace(heightMap[0][j], 0, j); vis[0][j]=1; }
        if (n>1 && !vis[n-1][j]){ pq.emplace(heightMap[n-1][j], n-1, j); vis[n-1][j]=1; }
    }

    long long ans = 0;
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};
    while(!pq.empty()){
        auto [h,x,y] = pq.top(); pq.pop();
        for (int k=0;k<4;++k){
            int nx=x+dx[k], ny=y+dy[k];
            if (nx<0||ny<0||nx>=n||ny>=m||vis[nx][ny]) continue;
            vis[nx][ny]=1;
            int nh=heightMap[nx][ny];
            if (nh < h) ans += (h - nh);
            pq.emplace(max(h, nh), nx, ny);
        }
    }
    return (int)ans;
}

int main(){
    vector<vector<int>> grid = {
        {1,4,3,1,3,2},
        {3,2,1,3,2,4},
        {2,3,3,2,3,1}
    };
    cout << trapRainWater(grid) << "\n"; // 4
    return 0;
}
