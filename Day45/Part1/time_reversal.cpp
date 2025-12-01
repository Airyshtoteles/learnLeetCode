#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

int main() {
    // Hardcoded Input
    vector<vector<int>> grid = {
        {1, 2, 3, 4},
        {2, 1, 4, 3},
        {3, 4, 1, 2},
        {4, 3, 2, 1}
    };
    int M = grid.size();
    int N = grid[0].size();

    // 1. Forward Dijkstra (Time Dependent)
    // dist_fwd[r][c]
    vector<vector<long long>> dist_fwd(M, vector<long long>(N, INF));
    
    // cost, r, c, time
    priority_queue<tuple<long long, int, int, int>, vector<tuple<long long, int, int, int>>, greater<tuple<long long, int, int, int>>> pq;
    
    dist_fwd[0][0] = grid[0][0];
    pq.push({grid[0][0], 0, 0, 0});

    int dr[] = {0, 1};
    int dc[] = {1, 0};

    while (!pq.empty()) {
        auto [cost, r, c, t] = pq.top();
        pq.pop();

        if (cost > dist_fwd[r][c]) continue;

        for (int i = 0; i < 2; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < M && nc >= 0 && nc < N) {
                int nt = t + 1;
                long long dmg = grid[nr][nc] + nt;
                if (cost + dmg < dist_fwd[nr][nc]) {
                    dist_fwd[nr][nc] = cost + dmg;
                    pq.push({dist_fwd[nr][nc], nr, nc, nt});
                }
            }
        }
    }

    // 2. Backward Dijkstra (Static Base HP)
    // dist_bwd[r][c]
    vector<vector<long long>> dist_bwd(M, vector<long long>(N, INF));
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> pq_bwd;

    dist_bwd[M-1][N-1] = grid[M-1][N-1];
    pq_bwd.push({grid[M-1][N-1], M-1, N-1});

    int bdr[] = {0, -1};
    int bdc[] = {-1, 0};

    while (!pq_bwd.empty()) {
        auto [cost, r, c] = pq_bwd.top();
        pq_bwd.pop();

        if (cost > dist_bwd[r][c]) continue;

        for (int i = 0; i < 2; ++i) {
            int nr = r + bdr[i];
            int nc = c + bdc[i];

            if (nr >= 0 && nr < M && nc >= 0 && nc < N) {
                // Moving from nr,nc TO r,c
                // Cost is grid[nr][nc] (entering nr,nc from previous)
                // Wait, we are building path FROM End TO Start.
                // Path: ... -> nr,nc -> r,c -> ... -> End
                // Cost of segment (nr,nc -> End) = Cost(r,c -> End) + Cost(nr,nc)
                long long new_cost = cost + grid[nr][nc];
                if (new_cost < dist_bwd[nr][nc]) {
                    dist_bwd[nr][nc] = new_cost;
                    pq_bwd.push({new_cost, nr, nc});
                }
            }
        }
    }

    // 3. Combine
    long long min_total = INF;

    for (int r = 0; r < M; ++r) {
        for (int c = 0; c < N; ++c) {
            if (dist_fwd[r][c] != INF && dist_bwd[r][c] != INF) {
                // Suffix cost excludes (r,c) because it's counted in Prefix
                long long total = dist_fwd[r][c] + (dist_bwd[r][c] - grid[r][c]);
                if (total < min_total) {
                    min_total = total;
                }
            }
        }
    }

    cout << "Minimum Damage: " << min_total << endl;

    return 0;
}
