#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>
#include <set>

using namespace std;

struct State {
    int r1, c1, r2, c2;
    int pending; // 0=None, 1=Wait K1, 2=Wait K2
    int timer;
    
    bool operator<(const State& other) const {
        return tie(r1, c1, r2, c2, pending, timer) < tie(other.r1, other.c1, other.r2, other.c2, other.pending, other.timer);
    }
};

int main() {
    cout << "Starting..." << endl;
    int N = 8;
    int M = 8;
    double D = 8.0;
    
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 2, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    int tr = 7, tc = 7;
    
    queue<pair<int, State>> q;
    set<State> visited;
    
    State startState = {0, 0, 0, 2, 0, 0};
    q.push({0, startState});
    visited.insert(startState);
    
    int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    
    while (!q.empty()) {
        auto [steps, s] = q.front();
        q.pop();
        
        if (s.r1 == tr && s.c1 == tc && s.r2 == tr && s.c2 == tc) {
            cout << "Minimum Steps: " << steps << endl;
            return 0;
        }
        
        // Generate moves
        vector<pair<int, int>> moves1, moves2;
        for (int i = 0; i < 8; ++i) {
            int nr = s.r1 + dr[i];
            int nc = s.c1 + dc[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != 1)
                moves1.push_back({nr, nc});
        }
        for (int i = 0; i < 8; ++i) {
            int nr = s.r2 + dr[i];
            int nc = s.c2 + dc[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != 1)
                moves2.push_back({nr, nc});
        }
        
        for (auto m1 : moves1) {
            for (auto m2 : moves2) {
                double dist = sqrt(pow(m1.first - m2.first, 2) + pow(m1.second - m2.second, 2));
                if (dist > D) continue;
                
                bool onRune1 = (grid[m1.first][m1.second] == 2);
                bool onRune2 = (grid[m2.first][m2.second] == 2);
                
                int nPending = s.pending;
                int nTimer = s.timer;
                bool valid = true;
                
                if (s.pending == 0) {
                    if (onRune1 && !onRune2) {
                        nPending = 2;
                        nTimer = 3;
                    } else if (!onRune1 && onRune2) {
                        nPending = 1;
                        nTimer = 3;
                    } else {
                        nPending = 0;
                        nTimer = 0;
                    }
                } else if (s.pending == 1) {
                    if (onRune1) {
                        nPending = 0;
                        nTimer = 0;
                    } else {
                        nTimer--;
                        if (nTimer == 0) valid = false;
                    }
                } else if (s.pending == 2) {
                    if (onRune2) {
                        nPending = 0;
                        nTimer = 0;
                    } else {
                        nTimer--;
                        if (nTimer == 0) valid = false;
                    }
                }
                
                if (valid) {
                    State nextState = {m1.first, m1.second, m2.first, m2.second, nPending, nTimer};
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
