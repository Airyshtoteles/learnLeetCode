#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

// Problem: Skill DAG With Time-Reversed Dependencies
// Dependencies reverse every K steps.
// Normal: u depends on dependencies[u] (incoming edges in normal graph).
// Reverse: u depends on incoming edges in reverse graph (which are outgoing in normal).
// Skill can be used/acquired if all dependencies active.
// "Active" means acquired? "Skill yang sudah diambil tidak hilang".
// So we accumulate skills.
// Strategy: Simulate time steps.
// In each step, check all unacquired skills.
// If current phase is Normal: check if all normal-parents are in inventory.
// If current phase is Reverse: check if all reverse-parents (children in normal) are in inventory.
// If satisfied, add to inventory.
// Repeat until T acquired or no change in a full cycle (2K steps).
// Cycle length 2K. If no progress for 2K steps, Impossible.

int main() {
    int N, M, K;
    if (!(cin >> N >> M >> K)) return 0;

    int Target;
    cin >> Target;

    vector<vector<int>> normal_deps(N + 1);
    vector<vector<int>> reverse_deps(N + 1);

    for (int i = 0; i < M; ++i) {
        int u, v; // u -> v
        cin >> u >> v;
        // In Normal: v depends on u.
        normal_deps[v].push_back(u);
        // In Reverse: u depends on v.
        reverse_deps[u].push_back(v);
    }

    set<int> inventory;
    // Initial skills? Usually skills with 0 dependencies are roots.
    // In Normal phase, roots are nodes with 0 in-degree.
    // In Reverse phase, roots are nodes with 0 out-degree in normal (leaves).

    int time = 0;
    int limit = 2 * K * (N + 1); // Heuristic limit. If N skills, at most N steps of progress.
    // Each progress might take cycle.
    
    while (time < limit) {
        if (inventory.count(Target)) {
            cout << "Possible" << endl;
            return 0;
        }

        bool is_reverse = (time / K) % 2 == 1;
        vector<int> new_skills;

        for (int i = 1; i <= N; ++i) {
            if (inventory.count(i)) continue;

            bool can_take = true;
            const vector<int>& deps = is_reverse ? reverse_deps[i] : normal_deps[i];

            if (deps.empty()) {
                // No dependencies -> Auto acquire?
                // Yes, roots are available.
            } else {
                for (int d : deps) {
                    if (!inventory.count(d)) {
                        can_take = false;
                        break;
                    }
                }
            }

            if (can_take) {
                new_skills.push_back(i);
            }
        }

        if (new_skills.empty()) {
            // No skills added this step.
            // Doesn't mean impossible, might need to wait for phase change.
            // But if empty for 2K steps, then impossible.
            // Loop controls this via limit.
        }

        for (int s : new_skills) {
            inventory.insert(s);
        }
        
        // Optim: If acquired, check target immediately
        if (inventory.count(Target)) {
            cout << "Possible" << endl;
            return 0;
        }

        time++;
    }

    cout << "Impossible" << endl;

    return 0;
}
