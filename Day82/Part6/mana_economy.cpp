#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int main() {
    int n, T;
    if (!(cin >> n >> T)) return 0;

    vector<int> spell(n);
    for (int i = 0; i < n; ++i) {
        cin >> spell[i];
    }

    // BFS: State = (current mana, set of visited mana values)
    // We want to reach mana = T without visiting the same mana twice.
    // Pigeonhole: If we ever reach a mana value we've seen before, we're in a cycle (infinite loop).

    // The state space is bounded by the number of unique reachable mana values.
    // We can use BFS with state = current mana (and implicitly tracking visited values).

    queue<int> q;
    set<int> visited;

    q.push(0);
    visited.insert(0);

    while (!q.empty()) {
        int mana = q.front();
        q.pop();

        if (mana == T) {
            cout << "true" << endl;
            return 0;
        }

        // Try casting each spell
        for (int s : spell) {
            int new_mana = mana + s;

            if (new_mana >= 0 && new_mana <= 10000) { // Reasonable bound
                if (visited.find(new_mana) == visited.end()) {
                    visited.insert(new_mana);
                    q.push(new_mana);
                }
            }
        }
    }

    cout << "false" << endl;

    return 0;
}
