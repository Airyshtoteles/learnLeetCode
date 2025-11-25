#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

struct State {
    int px, py, bx, by;
    
    bool operator<(const State& other) const {
        return tie(px, py, bx, by) < tie(other.px, other.py, other.bx, other.by);
    }
};

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };
    int N = grid.size();
    int M = grid[0].size();
    
    int sx = 0, sy = 0;
    int bx = 5, by = 5;
    int tx = 5, ty = 5;
    
    queue<pair<int, State>> q;
    set<State> visited;
    
    State startState = {sx, sy, bx, by};
    q.push({0, startState});
    visited.insert(startState);
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    while (!q.empty()) {
        auto [steps, s] = q.front();
        q.pop();
        
        // cout << "Step " << steps << ": P(" << s.px << "," << s.py << ") B(" << s.bx << "," << s.by << ")" << endl;

        if (s.px == tx && s.py == ty) {
            cout << "Minimum Steps: " << steps << endl;
            return 0;
        }
        
        for (int i = 0; i < 4; ++i) {
            int npx = s.px + dx[i];
            int npy = s.py + dy[i];
            
            int nbx = s.bx - dx[i];
            int nby = s.by - dy[i];
            
            // Check Player
            if (npx >= 0 && npx < N && npy >= 0 && npy < M && grid[npx][npy] == 0) {
                // Check Boss
                if (nbx >= 0 && nbx < N && nby >= 0 && nby < M && grid[nbx][nby] == 0) {
                    State nextState = {npx, npy, nbx, nby};
                    if (visited.find(nextState) == visited.end()) {
                        visited.insert(nextState);
                        q.push({steps + 1, nextState});
                    }
                }
            }
        }
    }
    
    cout << "-1" << endl;
    return 0;
}
