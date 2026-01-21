#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    
    // Ensure sorted
    sort(t.begin(), t.end());

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    int count = 1;
    long long last_t = t[0];

    for (int i = 1; i < n; ++i) {
        if (t[i] - last_t <= k) {
            // Merge
            // The new enemy is effectively at t[i] (chaining)
            // Or does it stay at t[0]?
            // "Connected Components" interpretation:
            // If distance between adjacent spawns is <= k, they belong to the same group.
            // This is the standard interpretation of "clustering with distance k".
            last_t = t[i];
        } else {
            // New group
            count++;
            last_t = t[i];
        }
    }

    cout << count << endl;

    return 0;
}
