#include <bits/stdc++.h>
using namespace std;

int min_steps(const vector<string>& maze){
    int n = (int)maze.size();
    int m = n? (int)maze[0].size(): 0;
    if(n==0 || m==0) return -1;
    unordered_map<char, vector<pair<int,int>>> portals;
    pair<int,int> S{-1,-1}, T{-1,-1};
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            char c = maze[i][j];
            if(c=='S') S={i,j};
            else if(c=='T') T={i,j};
            else if('A'<=c && c<='Z') portals[c].push_back({i,j});
        }
    }
    if(S.first==-1 || T.first==-1) return -1;
    auto teleport = [&](int i,int j){
        char c = maze[i][j];
        if(!('A'<=c && c<='Z')) return pair{i,j};
        auto it = portals.find(c);
        if(it==portals.end()) return pair{i,j};
        auto &lst = it->second;
        if(lst.size()==2){
            if(lst[0]==pair{i,j}) return lst[1];
            else return lst[0];
        }
        return pair{i,j};
    };

    queue<pair<int,int>> q; q.push(S);
    vector dist(n, vector<int>(m, -1)); dist[S.first][S.second]=0;
    int dirs[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
    while(!q.empty()){
        auto [x,y] = q.front(); q.pop();
        if(x==T.first && y==T.second) return dist[x][y];
        for(auto &d: dirs){
            int nx=x+d[0], ny=y+d[1];
            if(nx<0||nx>=n||ny<0||ny>=m) continue;
            if(maze[nx][ny]=='#') continue;
            pair<int,int> nxt;
            if(maze[nx][ny]=='.' || maze[nx][ny]=='S' || maze[nx][ny]=='T') nxt={nx,ny};
            else nxt = teleport(nx,ny);
            if(dist[nxt.first][nxt.second]==-1){
                dist[nxt.first][nxt.second]=dist[x][y]+1;
                q.push(nxt);
            }
        }
    }
    return -1;
}

int main(){
    vector<string> maze = {
        "S.A#",
        ".#A.",
        ".#..",
        "...T"
    };
    cout << min_steps(maze) << "\n"; // Expected 7
    return 0;
}
