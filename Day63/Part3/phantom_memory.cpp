#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> buffs(n);
    for (int i = 0; i < n; ++i) cin >> buffs[i];

    if (n < 2) {
        cout << 0 << endl;
        return 0;
    }

    int initial_conflicts = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (buffs[i] == buffs[i+1]) {
            initial_conflicts++;
        }
    }

    int max_reduction = 0;
    for (int i = 0; i < n; ++i) {
        int current_reduction = 0;
        if (i > 0 && buffs[i-1] == buffs[i]) {
            current_reduction++;
        }
        if (i < n - 1 && buffs[i] == buffs[i+1]) {
            current_reduction++;
        }
        max_reduction = max(max_reduction, current_reduction);
    }

    // If we have conflicts but max_reduction is 0 (impossible if conflicts > 0), handle it.
    // Actually, if conflicts > 0, there is at least one pair.
    // If there is a pair (i, i+1), then at index i, right match is true -> reduction >= 1.
    // So max_reduction >= 1 if initial_conflicts >= 1.
    // Unless n=0? Handled.

    cout << initial_conflicts - max_reduction << endl;

    return 0;
}
