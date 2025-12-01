#include <bits/stdc++.h>
using namespace std;

// Part 4 — Optimized BFS with visited[x][y][step%t]

using Pos = pair<int,int>;

static vector<Pos> collectTargets(const vector<vector<char>>& maze, char target){
    vector<Pos> res;
    for (int i = 0; i < (int)maze.size(); ++i)
        for (int j = 0; j < (int)maze[i].size(); ++j)
            if (maze[i][j] == target) res.emplace_back(i,j);
    return res;
}
static vector<Pos> collectEmpties(const vector<vector<char>>& maze){
    vector<Pos> res;
    for (int i = 0; i < (int)maze.size(); ++i)
        for (int j = 0; j < (int)maze[i].size(); ++j)
            if (maze[i][j] == 'E' || maze[i][j] == 'P') res.emplace_back(i,j);
    return res;
}
static vector<Pos> portalsForPhase(const vector<Pos>& empties, int pcount, int phase){
    vector<Pos> sel;
    if (pcount <= 0 || empties.empty()) return sel;
    int m = (int)empties.size();
    for (int k=0;k<pcount;++k) sel.push_back(empties[(phase + k) % m]);
    sort(sel.begin(), sel.end());
    return sel;
}
static optional<Pos> teleportDestination(const vector<Pos>& portals, Pos current){
    if (portals.size() <= 1) return nullopt;
    for (size_t i=0;i<portals.size();++i){
        if (portals[i] == current){
            size_t j = (i+1)%portals.size();
            if (portals[j] == current) return nullopt;
            return portals[j];
        }
    }
    return nullopt;
}

int shortestPathOptimized(vector<vector<char>>& maze, int t){
    int n = (int)maze.size();
    auto svec = collectTargets(maze, 'S');
    auto xvec = collectTargets(maze, 'X');
    auto baseP = collectTargets(maze, 'P');
    auto empties = collectEmpties(maze);
    if (svec.empty() || xvec.empty()) return -1;
    Pos S = svec[0];
    Pos X = xvec[0];
    int pcount = (int)baseP.size();

    deque<tuple<int,int,int>> q;
    vector<vector<vector<char>>> vis(n, vector<vector<char>>(n, vector<char>(t, 0)));
    q.emplace_back(S.first, S.second, 0);
    vis[S.first][S.second][0 % t] = 1;

    const int dx[4] = {1,-1,0,0};
    const int dy[4] = {0,0,1,-1};

    while(!q.empty()){
        auto [x,y,steps] = q.front(); q.pop_front();
        if (x == X.first && y == X.second) return steps;

        int phase = steps / t;
        auto plist = portalsForPhase(empties, pcount, phase);
        set<Pos> pset(plist.begin(), plist.end());

        for (int d=0; d<4; ++d){
            int nx = x + dx[d], ny = y + dy[d];
            if (nx<0 || ny<0 || nx>=n || ny>=n) continue;
            if (maze[nx][ny] == 'W') continue;

            int tx = nx, ty = ny;
            if (pset.count({nx,ny})){
                auto dest = teleportDestination(plist, {nx,ny});
                if (dest){ tx = dest->first; ty = dest->second; }
            }
            int nsteps = steps + 1;
            int nmod = nsteps % t;
            if (!vis[tx][ty][nmod]){
                vis[tx][ty][nmod] = 1;
                q.emplace_back(tx,ty,nsteps);
            }
        }
    }
    return -1;
}

int main(){
    vector<vector<char>> maze = {
        {'S','E','P','W'},
        {'E','W','E','E'},
        {'E','P','W','E'},
        {'E','E','E','X'}
    };
    cout << shortestPathOptimized(maze, 3) << "\n";
    return 0;
}
