#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

struct State {
    int flips, time, r, c;
    
    bool operator>(const State& other) const {
        if (flips != other.flips) return flips > other.flips;
        return time > other.time;
    }
};

bool is_wall(int r, int c, int t, const vector<vector<int>>& walls) {
    const vector<int>& row_w = walls[r];
    auto it = upper_bound(row_w.begin(), row_w.end(), c);
    if (it != row_w.begin()) {
        int rightmost_wall_idx = *(--it);
        if (rightmost_wall_idx >= c - t) {
            return true;
        }
    }
    return false;
}

bool solve_shifting_maze(vector<string> maze, int k) {
    int M = maze.size();
    int N = maze[0].size();
    
    vector<vector<int>> walls(M);
    for (int r = 0; r < M; ++r) {
        for (int c = 0; c < N; ++c) {
            if (maze[r][c] == '#') {
                walls[r].push_back(c);
            }
        }
    }
    
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, 0, 0, 0});
    
    vector<vector<pair<int, int>>> visited(M, vector<pair<int, int>>(N, {1e9, 1e9}));
    
    int dr[] = {0, 0, 1, -1, 0};
    int dc[] = {1, -1, 0, 0, 0};
    
    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();
        
        if (current.r == M - 1 && current.c == N - 1) {
            return true;
        }
        
        if (current.flips > k) continue;
        
        if (visited[current.r][current.c].first < current.flips) continue;
        if (visited[current.r][current.c].first == current.flips && visited[current.r][current.c].second <= current.time) continue;
        
        visited[current.r][current.c] = {current.flips, current.time};
        
        int next_time = current.time + 1;
        
        for (int i = 0; i < 5; ++i) {
            int nr = current.r + dr[i];
            int nc = current.c + dc[i];
            
            if (nr >= 0 && nr < M && nc >= 0 && nc < N) {
                int cost = is_wall(nr, nc, next_time, walls) ? 1 : 0;
                int new_flips = current.flips + cost;
                
                if (new_flips <= k) {
                    if (visited[nr][nc].first > new_flips || (visited[nr][nc].first == new_flips && visited[nr][nc].second > next_time)) {
                        pq.push({new_flips, next_time, nr, nc});
                    }
                }
            }
        }
    }
    
    return false;
}

int main() {
    vector<string> maze = {
        "...",
        "#..",
        "..."
    };
    int k = 0;
    cout << "Possible: " << (solve_shifting_maze(maze, k) ? "True" : "False") << endl;
    return 0;
}
