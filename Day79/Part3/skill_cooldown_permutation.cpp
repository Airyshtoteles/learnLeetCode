#include <iostream>
#include <vector>

using namespace std;

// Minimal time to use all skills once, assuming per-skill cooldown only matters for reuse.
// We can chain distinct skills back-to-back. If each use takes 1 unit, time = n.

long long solve() {
    int n; if (!(cin >> n)) return 0;
    vector<long long> c(n);
    for (int i = 0; i < n; ++i) cin >> c[i];
    return n; // one unit per skill
}

int main() {
    cout << solve() << endl;
    return 0;
}
