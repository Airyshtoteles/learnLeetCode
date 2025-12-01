#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <tuple>

using namespace std;

struct Hex {
    int q, r;
    char type;
};

struct State {
    int q, r;
    int mask;
    int steps;
};

// For set/map keys
using Coord = pair<int, int>;
using VisitedState = tuple<int, int, int>; // q, r, mask

int solve_hex_arena(const vector<Hex>& hex_list) {
    map<Coord, char> grid;
    int start_q, start_r;
    int end_q, end_r;
    bool found_start = false, found_end = false;

    for (const auto& h : hex_list) {
        grid[{h.q, h.r}] = h.type;
        if (h.type == 'S') {
            start_q = h.q;
            start_r = h.r;
            found_start = true;
        } else if (h.type == 'E') {
            end_q = h.q;
            end_r = h.r;
            found_end = true;
        }
    }

    if (!found_start || !found_end) return -1;

    queue<State> q;
    q.push({start_q, start_r, 0, 0});

    set<VisitedState> visited;
    visited.insert({start_q, start_r, 0});

    // Axial neighbors
    int dq[] = {1, 1, 0, -1, -1, 0};
    int dr[] = {0, -1, -1, 0, 1, 1};

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (current.q == end_q && current.r == end_r) {
            return current.steps;
        }

        for (int i = 0; i < 6; ++i) {
            int nq = current.q + dq[i];
            int nr = current.r + dr[i];

            if (grid.find({nq, nr}) == grid.end()) continue;

            char cell = grid[{nq, nr}];
            if (cell == '#') continue;

            int new_mask = current.mask;
            bool is_passable = true;

            // Check Barrier (A-J), excluding E
            if (cell >= 'A' && cell <= 'J' && cell != 'E') {
                int barrier_id = cell - 'A';
                if (!(current.mask & (1 << barrier_id))) {
                    is_passable = false;
                }
            }

            // Check Plate (a-j)
            if (cell >= 'a' && cell <= 'j') {
                int plate_id = cell - 'a';
                new_mask = current.mask ^ (1 << plate_id);
            }

            if (is_passable) {
                if (visited.find({nq, nr, new_mask}) == visited.end()) {
                    visited.insert({nq, nr, new_mask});
                    q.push({nq, nr, new_mask, current.steps + 1});
                }
            }
        }
    }

    return -1;
}

int main() {
    // Example 1
    vector<Hex> hexes1 = {
        {0, 0, 'S'},
        {1, 0, 'a'},
        {2, 0, 'A'},
        {3, 0, 'E'}
    };
    cout << "Min Steps (Ex 1): " << solve_hex_arena(hexes1) << endl;

    // Example 2
    vector<Hex> hexes2 = {
        {0, 0, 'S'},
        {1, 0, 'A'},
        {2, 0, 'E'}
    };
    cout << "Min Steps (Ex 2): " << solve_hex_arena(hexes2) << endl;

    return 0;
}
