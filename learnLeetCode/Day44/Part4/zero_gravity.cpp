#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
#include <algorithm>
#include <numeric>

using namespace std;

struct Point {
    int x, y, z;
    bool operator<(const Point& other) const {
        return tie(x, y, z) < tie(other.x, other.y, other.z);
    }
    bool operator==(const Point& other) const {
        return tie(x, y, z) == tie(other.x, other.y, other.z);
    }
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

int N = 4;

struct State {
    vector<Point> boxes;
    int steps;
};

// For visited set, we need to compare vectors of points
// vector already has operator<

int main() {
    // Hardcoded Input
    vector<Point> initial_boxes = {
        {0, 0, 0}, // Box 1
        {0, 0, 1}, // Box 2
        {1, 0, 0}  // Box 3
    };
    Point target = {3, 3, 3};

    queue<State> q;
    q.push({initial_boxes, 0});

    set<vector<Point>> visited;
    visited.insert(initial_boxes);

    // Directions: dx, dy, dz, axis (0=x,1=y,2=z), reverse (1=desc, 0=asc)
    struct Move { int dx, dy, dz, axis, rev; };
    vector<Move> moves = {
        {1, 0, 0, 0, 1},  // +x
        {-1, 0, 0, 0, 0}, // -x
        {0, 1, 0, 1, 1},  // +y
        {0, -1, 0, 1, 0}, // -y
        {0, 0, 1, 2, 1},  // +z
        {0, 0, -1, 2, 0}  // -z
    };

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.boxes[0] == target) {
            cout << "Minimum gravity changes: " << cur.steps << endl;
            return 0;
        }

        for (const auto& m : moves) {
            // Create indices to sort
            vector<int> indices(cur.boxes.size());
            iota(indices.begin(), indices.end(), 0);

            // Sort indices
            sort(indices.begin(), indices.end(), [&](int a, int b) {
                int val_a = (m.axis == 0) ? cur.boxes[a].x : (m.axis == 1) ? cur.boxes[a].y : cur.boxes[a].z;
                int val_b = (m.axis == 0) ? cur.boxes[b].x : (m.axis == 1) ? cur.boxes[b].y : cur.boxes[b].z;
                if (m.rev) return val_a > val_b;
                return val_a < val_b;
            });

            // Simulation
            vector<Point> next_boxes = cur.boxes;
            set<Point> occupied(cur.boxes.begin(), cur.boxes.end());
            bool changed = false;

            for (int idx : indices) {
                Point p = next_boxes[idx];
                occupied.erase(p);

                while (true) {
                    Point np = {p.x + m.dx, p.y + m.dy, p.z + m.dz};
                    if (np.x >= 0 && np.x < N && np.y >= 0 && np.y < N && np.z >= 0 && np.z < N && occupied.find(np) == occupied.end()) {
                        p = np;
                    } else {
                        break;
                    }
                }

                if (p != next_boxes[idx]) changed = true;
                next_boxes[idx] = p;
                occupied.insert(p);
            }

            if (changed) {
                if (visited.find(next_boxes) == visited.end()) {
                    visited.insert(next_boxes);
                    q.push({next_boxes, cur.steps + 1});
                }
            }
        }
    }

    cout << "-1" << endl;

    return 0;
}
