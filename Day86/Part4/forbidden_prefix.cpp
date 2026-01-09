#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

// Problem: Damage With Forbidden Prefixes
// Boss HP H. Damage set D.
// Rule: Prefix sums must be unique.
// Goal: Min attacks to reach >= H.
// Strategy: BFS on prefix sums.
// State: current_sum.
// Transitions: current_sum + d for d in D.
// Constraint: new_sum must not be in visited.

int main() {
    long long H;
    int N;
    if (!(cin >> H >> N)) return 0;

    vector<int> D(N);
    for (int i = 0; i < N; ++i) {
        cin >> D[i];
    }

    // BFS
    // Queue stores {current_sum, steps}
    queue<pair<long long, int>> q;
    q.push({0, 0});
    
    set<long long> visited;
    visited.insert(0);

    while (!q.empty()) {
        long long curr = q.front().first;
        int steps = q.front().second;
        q.pop();

        if (curr >= H) {
            cout << steps << endl;
            return 0;
        }

        for (int d : D) {
            long long next_val = curr + d;
            if (visited.find(next_val) == visited.end()) {
                visited.insert(next_val);
                q.push({next_val, steps + 1});
            }
        }
    }

    cout << "Impossible" << endl;
    return 0;
}
