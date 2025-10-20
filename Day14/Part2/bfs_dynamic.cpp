#include <bits/stdc++.h>
using namespace std;

// Part 2 — BFS Traversal with Dynamic Portals (deterministic remap per phase)

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

static set<Pos> portalsForPhase(const vector<Pos>& empties, int pcount, int phase){
    set<Pos> s;
    if (pcount <= 0 || empties.empty()) return s;
    int m = (int)empties.size();
    for (int k = 0; k < pcount; ++k){
        s.insert(empties[(phase + k) % m]);
    }
    return s;
}

static optional<Pos> teleportDestination(const vector<Pos>& portals, Pos current){
    if (portals.size() <= 1) return nullopt;
    for (size_t i = 0; i < portals.size(); ++i){
        if (portals[i] == current){
            size_t nxt = (i + 1) % portals.size();
            if (portals[nxt] == current) return nullopt;
            return portals[nxt];
        }
    }
    return nullopt;
}

int shortestPathWithPortals(vector<vector<char>>& maze, int t){
    int n = (int)maze.size();
    auto starts = collectTargets(maze, 'S');
    auto exits = collectTargets(maze, 'X');
    auto basePortals = collectTargets(maze, 'P');
    auto empties = collectEmpties(maze);
    if (starts.empty() || exits.empty()) return -1;
    Pos S = starts[0];
    Pos X = exits[0];
    int pcount = (int)basePortals.size();

    deque<tuple<int,int,int>> q; // x,y,steps
    q.emplace_back(S.first, S.second, 0);
    vector<vector<char>> vis(n, vector<char>(n, 0));
    vis[S.first][S.second] = 1;

    const int dx[4] = {1,-1,0,0};
    const int dy[4] = {0,0,1,-1};

    while(!q.empty()){
        auto [x,y,steps] = q.front(); q.pop_front();
        if (x == X.first && y == X.second) return steps;

        int phase = steps / t;
        auto pset = portalsForPhase(empties, pcount, phase);
        vector<Pos> plist(pset.begin(), pset.end());

        for (int d=0; d<4; ++d){
            int nx = x + dx[d], ny = y + dy[d];
            if (nx<0 || ny<0 || nx>=n || ny>=n) continue;
            char cell = maze[nx][ny];
            if (cell == 'W') continue;

            int tx = nx, ty = ny;
            if (pset.count({nx,ny})){
                auto dest = teleportDestination(plist, {nx,ny});
                if (dest) { tx = dest->first; ty = dest->second; }
            }

            if (!vis[tx][ty]){
                vis[tx][ty] = 1;
                q.emplace_back(tx, ty, steps+1);
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
    cout << shortestPathWithPortals(maze, 3) << "\n";
    return 0;
}
