#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Monster {
    double x, y;
    double dist;
    double angle;
    int deadline;
};

bool compareMonsters(const Monster& a, const Monster& b) {
    return a.angle < b.angle;
}

int main() {
    // Hardcoded Input
    vector<pair<double, double>> inputs = {
        {3, 0},
        {0, 5},
        {2, 0},
        {-1, 0},
        {0.5, 0.5}
    };

    vector<Monster> monsters;
    for (auto p : inputs) {
        double x = p.first;
        double y = p.second;
        double dist = sqrt(x*x + y*y);
        int deadline = (int)ceil(dist);
        double angle = atan2(y, x);
        monsters.push_back({x, y, dist, angle, deadline});
    }

    // Sort by angle to group
    sort(monsters.begin(), monsters.end(), compareMonsters);

    vector<int> group_deadlines;
    if (!monsters.empty()) {
        double current_angle = monsters[0].angle;
        int min_deadline = monsters[0].deadline;
        
        for (size_t i = 1; i < monsters.size(); ++i) {
            // Check if angle is same (within epsilon)
            if (abs(monsters[i].angle - current_angle) < 1e-9) {
                min_deadline = min(min_deadline, monsters[i].deadline);
            } else {
                group_deadlines.push_back(min_deadline);
                current_angle = monsters[i].angle;
                min_deadline = monsters[i].deadline;
            }
        }
        group_deadlines.push_back(min_deadline);
    }

    // Sort deadlines ascending
    sort(group_deadlines.begin(), group_deadlines.end());

    // Check schedule
    for (size_t i = 0; i < group_deadlines.size(); ++i) {
        // We shoot at time i.
        // Must kill BEFORE deadline.
        // i < deadline
        if ((int)i >= group_deadlines[i]) {
            cout << "-1" << endl;
            return 0;
        }
    }

    cout << "Minimum barriers: " << group_deadlines.size() << endl;

    return 0;
}
