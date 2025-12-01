#include <bits/stdc++.h>
using namespace std;

using Pos = pair<int,int>;

class Solution {
public:
    int minStepsToExit(vector<vector<char>>& maze, int t) {
        int n = (int)maze.size();
        Pos S{-1,-1}, X{-1,-1};
        vector<Pos> baseP, empties;
        for (int i=0;i<n;++i){
            for (int j=0;j<(int)maze[i].size();++j){
                char c = maze[i][j];
                if (c=='S') S={i,j};
                else if (c=='X') X={i,j};
                if (c=='P') baseP.emplace_back(i,j);
                if (c=='E' || c=='P') empties.emplace_back(i,j);
            }
        }
        if (S.first<0 || X.first<0) return -1;
        int pcount = (int)baseP.size();

        auto portalsForPhase = [&](int phase){
            vector<Pos> sel;
            if (pcount<=0 || empties.empty()) return sel;
            int m=(int)empties.size();
            for (int k=0;k<pcount;++k) sel.push_back(empties[(phase+k)%m]);
            sort(sel.begin(), sel.end());
            return sel;
        };
        auto teleport = [&](const vector<Pos>& plist, Pos current)->optional<Pos>{
            if (plist.size()<=1) return nullopt;
            for (size_t i=0;i<plist.size();++i){
                if (plist[i]==current){
                    size_t j=(i+1)%plist.size();
                    if (plist[j]==current) return nullopt;
                    return plist[j];
                }
            }
            return nullopt;
        };

        deque<tuple<int,int,int>> q;
        vector<vector<vector<char>>> vis(n, vector<vector<char>>(n, vector<char>(t, 0)));
        q.emplace_back(S.first,S.second,0);
        vis[S.first][S.second][0%t]=1;
        const int dx[4]={1,-1,0,0};
        const int dy[4]={0,0,1,-1};

        while(!q.empty()){
            auto [x,y,steps]=q.front(); q.pop_front();
            if (x==X.first && y==X.second) return steps;
            int phase=steps/t;
            auto plist=portalsForPhase(phase);
            set<Pos> pset(plist.begin(), plist.end());
            for (int d=0; d<4; ++d){
                int nx=x+dx[d], ny=y+dy[d];
                if (nx<0||ny<0||nx>=n||ny>=n) continue;
                if (maze[nx][ny]=='W') continue;
                int tx=nx, ty=ny;
                if (pset.count({nx,ny})){
                    auto dest=teleport(plist,{nx,ny});
                    if (dest){ tx=dest->first; ty=dest->second; }
                }
                int nsteps=steps+1; int nmod=nsteps%t;
                if (!vis[tx][ty][nmod]){
                    vis[tx][ty][nmod]=1;
                    q.emplace_back(tx,ty,nsteps);
                }
            }
        }
        return -1;
    }
};

int main(){
    vector<vector<char>> maze = {
      {'S','E','P','W'},
      {'E','W','E','E'},
      {'E','P','W','E'},
      {'E','E','E','X'}
    };
    cout << Solution().minStepsToExit(maze, 3) << "\n"; // Expected 7 in prompt example
    return 0;
}
