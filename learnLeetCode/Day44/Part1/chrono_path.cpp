#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

struct State {
    int r, c;
    int energy;
    int time;
};

int main() {
    int N = 4, M = 4;
    int E = 10;

    vector<vector<int>> costs = {
        {0, 2, 1, 1},
        {1, 5, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 0}
    };

    // Map (r, c) -> set of forbidden times
    map<pair<int, int>, set<int>> time_gates;
    time_gates[{1, 1}] = {2};
    time_gates[{0, 2}] = {2};

    // max_energy[r][c]
    vector<vector<int>> max_energy(N, vector<int>(M, -1));

    queue<State> q;
    q.push({0, 0, E, 0});
    max_energy[0][0] = E;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.r == N - 1 && cur.c == M - 1) {
            cout << "Minimum time: " << cur.time << endl;
            return 0;
        }

        int next_t = cur.time + 1;

        for (int i = 0; i < 4; ++i) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                // Check Time Gate
                if (time_gates.count({nr, nc}) && time_gates[{nr, nc}].count(next_t)) {
                    continue;
                }

                int move_cost = costs[nr][nc];
                int next_e = cur.energy - move_cost;

                if (next_e >= 0) {
                    if (next_e > max_energy[nr][nc]) {
                        max_energy[nr][nc] = next_e;
                        q.push({nr, nc, next_e, next_t});
                    }
                }
            }
        }
    }

    cout << "Impossible" << endl;

    return 0;
}
