#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <set>

using namespace std;

int main() {
    int R, C, k;
    if (!(cin >> R >> C >> k)) return 0;

    vector<string> grid(R);
    int startR, startC, targetR, targetC;
    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == 'S') {
                startR = i; startC = j;
            } else if (grid[i][j] == 'T') {
                targetR = i; targetC = j;
            }
        }
    }

    // State: (r, c, recent_cells_as_bitmask or set)
    // Recent cells: last k cells visited (in order)
    // We can't enter a cell that's currently in our "remembered" set, except the starting point.
    // BFS to find if target is reachable.

    // For simplicity, represent recent cells as a deque or queue.
    // If R*C is small enough, we can use a set of recent cells.

    typedef pair<int, int> Cell;
    typedef deque<Cell> Memory;

    queue<pair<pair<int, int>, Memory>> q;
    set<pair<pair<int, int>, Memory>> visited;

    Memory initial_memory;
    q.push({{startR, startC}, initial_memory});

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    bool found = false;

    while (!q.empty() && !found) {
        auto [pos, mem] = q.front();
        q.pop();

        auto [r, c] = pos;

        if (r == targetR && c == targetC) {
            found = true;
            break;
        }

        // Try all 4 directions
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#') {
                // Check if (nr, nc) is in current memory
                bool in_memory = false;
                for (auto [mr, mc] : mem) {
                    if (mr == nr && mc == nc) {
                        in_memory = true;
                        break;
                    }
                }

                if (!in_memory || (nr == targetR && nc == targetC)) {
                    Memory new_mem = mem;
                    new_mem.push_back({nr, nc});
                    if (new_mem.size() > k) {
                        new_mem.pop_front();
                    }

                    auto new_state = make_pair(make_pair(nr, nc), new_mem);
                    if (visited.find(new_state) == visited.end()) {
                        visited.insert(new_state);
                        q.push(new_state);
                    }
                }
            }
        }
    }

    if (found) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}
