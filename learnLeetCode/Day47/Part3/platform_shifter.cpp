#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const long long INF = 1e18;

struct State {
    long long cost;
    int r, c;

    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

long long solvePlatformShifter(int n, int k, const vector<vector<int>>& grid) {
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, 0, 0});

    vector<vector<long long>> dist(n, vector<long long>(n, INF));
    dist[0][0] = 0;

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        long long current_cost = current.cost;
        int r = current.r;
        int c = current.c;

        if (r == n - 1 && c == n - 1) {
            return current_cost;
        }

        if (current_cost > dist[r][c]) {
            continue;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                int h_curr = grid[r][c];
                int h_next = grid[nr][nc];

                long long move_cost = 1;
                long long penalty = 0;

                if (h_next > h_curr + k) {
                    penalty = h_next - (h_curr + k);
                }

                long long total_move_cost = move_cost + penalty;
                long long new_cost = current_cost + total_move_cost;

                if (new_cost < dist[nr][nc]) {
                    dist[nr][nc] = new_cost;
                    pq.push({new_cost, nr, nc});
                }
            }
        }
    }

    return -1;
}

int main() {
    int N = 3;
    int K = 2;
    vector<vector<int>> Grid = {
        {0, 5, 10},
        {2, 3, 8},
        {10, 1, 9}
    };

    long long result = solvePlatformShifter(N, K, Grid);
    cout << "Minimum Cost: " << result << endl;

    return 0;
}
