#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct State {
    int r, c, time;
};

int solve_shadow_corridor(int N, int M, int K) {
    if (N == 0 || M == 0) return 0;
    
    vector<vector<vector<bool>>> visited(N, vector<vector<bool>>(M, vector<bool>(K, false)));
    queue<State> q;
    
    q.push({0, 0, 0});
    visited[0][0][0] = true;
    
    int dr[] = {-1, 1, 0, 0, 0}; // Up, Down, Left, Right, Wait
    int dc[] = {0, 0, -1, 1, 0};
    
    while (!q.empty()) {
        State current = q.front();
        q.pop();
        
        if (current.r == N - 1 && current.c == M - 1) {
            return current.time;
        }
        
        int next_time = current.time + 1;
        int next_mod = next_time % K;
        
        for (int i = 0; i < 5; ++i) {
            int nr = current.r + dr[i];
            int nc = current.c + dc[i];
            
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                int shadow_t = (nr + nc) % K;
                if (next_mod == shadow_t) {
                    continue; 
                }
                
                if (!visited[nr][nc][next_mod]) {
                    visited[nr][nc][next_mod] = true;
                    q.push({nr, nc, next_time});
                }
            }
        }
    }
    
    return -1;
}

int main() {
    cout << "Test 1 (3x3 K=3): " << solve_shadow_corridor(3, 3, 3) << endl;
    cout << "Test 2 (2x2 K=2): " << solve_shadow_corridor(2, 2, 2) << endl;
    return 0;
}
