#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const int INF = 1e9;

struct State {
    int r, c, damage;
    bool operator>(const State& other) const {
        return damage > other.damage;
    }
};

int solve_tower_defense(int R, int C, vector<vector<int>>& grid) {
    // Grid contains danger levels.
    // Start is (0,0), End is (R-1, C-1).
    // Cost to visit (r,c) is grid[r][c].
    // Total cost = Sum of grid[r][c] for all cells in path.
    
    priority_queue<State, vector<State>, greater<State>> pq;
    vector<vector<int>> min_damage(R, vector<int>(C, INF));

    // Start at (0,0)
    int start_damage = grid[0][0];
    pq.push({0, 0, start_damage});
    min_damage[0][0] = start_damage;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        int r = curr.r;
        int c = curr.c;
        int d = curr.damage;

        if (d > min_damage[r][c]) continue;
        if (r == R - 1 && c == C - 1) return d;

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                int new_damage = d + grid[nr][nc];
                if (new_damage < min_damage[nr][nc]) {
                    min_damage[nr][nc] = new_damage;
                    pq.push({nr, nc, new_damage});
                }
            }
        }
    }

    return -1; // Should not happen if connected
}

int main() {
    // Example 1
    /*
    1 3 1
    1 5 1
    4 2 1
    Path: (0,0)[1] -> (1,0)[1] -> (1,1)[5]... NO
    Path: (0,0)[1] -> (0,1)[3] -> (0,2)[1] -> (1,2)[1] -> (2,2)[1].
    Sum: 1+3+1+1+1 = 7.
    Better: (0,0)[1] -> (1,0)[1] -> (2,0)[4] -> (2,1)[2] -> (2,2)[1]. Sum: 9.
    */
    vector<vector<int>> grid1 = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    cout << "Test 1 (Expected 7): " << solve_tower_defense(3, 3, grid1) << endl;

    // Example 2
    vector<vector<int>> grid2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    // Path: 1->2->3->6->9 = 21?
    // 1->4->7->8->9 = 29
    // 1->2->5->6->9 = 23
    // 1->2->5->8->9 = 25
    cout << "Test 2 (Expected 21): " << solve_tower_defense(3, 3, grid2) << endl;

    return 0;
}
