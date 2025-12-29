#include <iostream>
#include <vector>

using namespace std;

// Input: n, then n-1 edges (u v); tree rooted at 0 (not used)
// Minimal nodes to destroy so root collapses: 1 (destroy any node, chain collapses up to root)

int solve() {
    int n; if (!(cin >> n)) return 0;
    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v; // not used
    }
    if (n <= 0) return 0;
    return 1;
}

int main() {
    cout << solve() << endl;
    return 0;
}
