#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct State {
    int r, c, rot;
    long long cost;

    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

int main() {
    int M, N;
    if (!(cin >> M >> N)) return 0;

    vector<vector<int>> grid(M, vector<int>(N));
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j) cin >> grid[i][j];

    vector<vector<int>> cost_grid(M, vector<int>(N));
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j) cin >> cost_grid[i][j];

    int startR, startC, targetR, targetC;
    cin >> startR >> startC >> targetR >> targetC;

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({startR, startC, 0, 0});

    // dist[rot][r][c]
    // Max dimensions are max(M, N)
    int max_dim = max(M, N);
    vector<vector<vector<long long>>> dist(4, vector<vector<long long>>(max_dim, vector<long long>(max_dim, -1)));

    dist[0][startR][startC] = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int r = current.r;
        int c = current.c;
        int rot = current.rot;
        long long current_cost = current.cost;

        if (dist[rot][r][c] != -1 && current_cost > dist[rot][r][c]) continue;

        // Check if target reached
        // Target coordinates are in the ORIGINAL grid (rot=0).
        // We need to check if current (r, c) in current rotation corresponds to target in original.
        // Or simpler: transform target to current rotation frame.
        
        int tr = targetR;
        int tc = targetC;
        int curM = M;
        int curN = N;
        
        for (int k = 0; k < rot; ++k) {
            int next_tr = tc;
            int next_tc = curM - 1 - tr;
            tr = next_tr;
            tc = next_tc;
            swap(curM, curN);
        }

        if (r == tr && c == tc) {
            cout << current_cost << endl;
            return 0;
        }

        // Current grid dimensions
        int R = (rot % 2 == 0) ? M : N;
        int C = (rot % 2 == 0) ? N : M;

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            bool hit_wall = false;
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) {
                hit_wall = true; // Out of bounds is wall? Usually yes.
            } else {
                // Check grid value at (nr, nc) in current rotation
                // Need to map (nr, nc) back to original grid to check value
                int orig_r = nr;
                int orig_c = nc;
                int tempR = R;
                int tempC = C;

                // Inverse rotation 'rot' times: 90 deg CCW
                // (r, c) in RxC -> (R-1-c, r) in CxR
                for (int k = 0; k < rot; ++k) {
                    int next_orig_r = tempC - 1 - orig_c;
                    int next_orig_c = orig_r;
                    orig_r = next_orig_r;
                    orig_c = next_orig_c;
                    swap(tempR, tempC);
                }
                
                if (grid[orig_r][orig_c] == 1) {
                    hit_wall = true;
                }
            }

            if (hit_wall) {
                // Rotate
                int next_rot = (rot + 1) % 4;
                int next_r = c;
                int next_c = R - 1 - r;
                
                if (dist[next_rot][next_r][next_c] == -1 || current_cost < dist[next_rot][next_r][next_c]) {
                    dist[next_rot][next_r][next_c] = current_cost;
                    pq.push({next_r, next_c, next_rot, current_cost});
                }
            } else {
                // Move
                // Cost is from original cost grid
                int orig_r = nr;
                int orig_c = nc;
                int tempR = R;
                int tempC = C;
                for (int k = 0; k < rot; ++k) {
                    int next_orig_r = tempC - 1 - orig_c;
                    int next_orig_c = orig_r;
                    orig_r = next_orig_r;
                    orig_c = next_orig_c;
                    swap(tempR, tempC);
                }
                
                long long new_cost = current_cost + cost_grid[orig_r][orig_c];
                if (dist[rot][nr][nc] == -1 || new_cost < dist[rot][nr][nc]) {
                    dist[rot][nr][nc] = new_cost;
                    pq.push({nr, nc, rot, new_cost});
                }
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
