#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

struct State {
    int rA, cA, rB, cB;
    int steps;
};

int main() {
    // Hardcoded Input
    vector<string> grid = {
        "#####",
        "#...#",
        "#.S.#",
        "#...#",
        "#####"
    };
    int N = grid.size();
    int M = grid[0].size();

    pair<int, int> startA = {1, 1};
    pair<int, int> goalA = {1, 3};
    pair<int, int> startB = {3, 3};
    pair<int, int> goalB = {3, 1};

    // BFS
    // dist[rA][cA][rB][cB]
    // Using flattened vector or just a visited array
    // Since N,M are small (5), we can use fixed array or vector
    // Let's use a 4D vector
    vector<vector<vector<vector<int>>>> dist(N, vector<vector<vector<int>>>(M, vector<vector<int>>(N, vector<int>(M, -1))));

    queue<State> q;
    q.push({startA.first, startA.second, startB.first, startB.second, 0});
    dist[startA.first][startA.second][startB.first][startB.second] = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.rA == goalA.first && cur.cA == goalA.second &&
            cur.rB == goalB.first && cur.cB == goalB.second) {
            cout << "Minimum steps: " << cur.steps << endl;
            return 0;
        }

        for (int i = 0; i < 4; ++i) {
            // Move A
            int nrA = cur.rA + dr[i];
            int ncA = cur.cA + dc[i];
            if (nrA < 0 || nrA >= N || ncA < 0 || ncA >= M || grid[nrA][ncA] == '#') {
                nrA = cur.rA;
                ncA = cur.cA;
            }

            // Move B
            int nrB = cur.rB + dr[i];
            int ncB = cur.cB + dc[i];
            if (nrB < 0 || nrB >= N || ncB < 0 || ncB >= M || grid[nrB][ncB] == '#') {
                nrB = cur.rB;
                ncB = cur.cB;
            }

            if (dist[nrA][ncA][nrB][ncB] == -1) {
                dist[nrA][ncA][nrB][ncB] = cur.steps + 1;
                q.push({nrA, ncA, nrB, ncB, cur.steps + 1});
            }
        }
    }

    cout << "-1" << endl;

    return 0;
}
