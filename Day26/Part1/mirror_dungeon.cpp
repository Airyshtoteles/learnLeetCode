#include <bits/stdc++.h>
using namespace std;

// Directions: 0=up,1=right,2=down,3=left
static const int dx[4] = {-1,0,1,0};
static const int dy[4] = {0,1,0,-1};
static const int REFLECT_SLASH[4] = {1,0,3,2}; // '/'
static const int REFLECT_BACK[4]  = {3,2,1,0}; // '\\'

int min_mirror_flips(const vector<string>& grid){
    int n = (int)grid.size();
    if(n==0) return -1;
    if(grid[0][0] == '#') return -1;
    const int INF = 1e9;
    vector dist(n, vector(n, array<int,4>{INF,INF,INF,INF}));
    priority_queue<tuple<int,int,int,int>, vector<tuple<int,int,int,int>>, greater<>> pq;
    dist[0][0][1] = 0; // start facing right
    pq.emplace(0,0,0,1);
    auto inb = [&](int x,int y){return 0<=x && x<n && 0<=y && y<n;};
    while(!pq.empty()){
        auto [cost,x,y,d] = pq.top(); pq.pop();
        if(cost != dist[x][y][d]) continue;
        if(x==n-1 && y==n-1) return cost;
        int nx = x + dx[d], ny = y + dy[d];
        if(!inb(nx,ny) || grid[nx][ny]=='#') continue;
        char c = grid[nx][ny];
        if(c=='.'){
            int nd = d;
            if(cost < dist[nx][ny][nd]){
                dist[nx][ny][nd] = cost;
                pq.emplace(cost,nx,ny,nd);
            }
        }else if(c=='/'){
            int nd_keep = REFLECT_SLASH[d];
            if(cost < dist[nx][ny][nd_keep]){
                dist[nx][ny][nd_keep] = cost;
                pq.emplace(cost,nx,ny,nd_keep);
            }
            int nd_flip = REFLECT_BACK[d];
            if(cost+1 < dist[nx][ny][nd_flip]){
                dist[nx][ny][nd_flip] = cost+1;
                pq.emplace(cost+1,nx,ny,nd_flip);
            }
        }else if(c=='\\'){
            int nd_keep = REFLECT_BACK[d];
            if(cost < dist[nx][ny][nd_keep]){
                dist[nx][ny][nd_keep] = cost;
                pq.emplace(cost,nx,ny,nd_keep);
            }
            int nd_flip = REFLECT_SLASH[d];
            if(cost+1 < dist[nx][ny][nd_flip]){
                dist[nx][ny][nd_flip] = cost+1;
                pq.emplace(cost+1,nx,ny,nd_flip);
            }
        } else {
            // treat others as walls
        }
    }
    return -1;
}

int main(){
    vector<string> grid = {
        ".#..",
        "..\\.",
        "#...",
        "...#"
    };
    cout << min_mirror_flips(grid) << "\n"; // Expected 2
    return 0;
}
