#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

// Function to get cost to reach target v or v+1 from x
// Returns -1 if impossible
int get_cost(int x, int v) {
    int ops = 0;
    while (x > v + 1) {
        x /= 2;
        ops++;
    }
    if (x == v || x == v + 1) return ops;
    return -1;
}

int main() {
    int n;
    if (cin >> n) {
        vector<int> lvl(n);
        int min_val = 2e9;
        for (int i = 0; i < n; ++i) {
            cin >> lvl[i];
            if (lvl[i] < min_val) min_val = lvl[i];
        }

        // Candidates for target base v are derived from min_val
        // min_val must eventually become some v' or v'+1
        // So v' must be reachable from min_val (as x or x-1)
        
        set<int> candidates;
        int curr = min_val;
        while (true) {
            candidates.insert(curr);
            if (curr > 0) candidates.insert(curr - 1);
            if (curr == 0) break;
            curr /= 2;
        }
        candidates.insert(0); // Always check 0

        long long min_ops = -1;

        for (int v : candidates) {
            if (v < 0) continue;
            long long current_ops = 0;
            bool possible = true;

            for (int x : lvl) {
                int cost = get_cost(x, v);
                if (cost == -1) {
                    possible = false;
                    break;
                }
                current_ops += cost;
            }

            if (possible) {
                if (min_ops == -1 || current_ops < min_ops) {
                    min_ops = current_ops;
                }
            }
        }

        cout << min_ops << endl;
    }
    return 0;
}
