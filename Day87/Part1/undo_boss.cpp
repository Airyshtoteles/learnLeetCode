#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// Problem: Boss With Non-Local Undo
// Boss HP H.
// Rule: Whenever HP <= x (unknown x), boss undos a past attack (worst for us).
// Undo can chain.
// Strategy: Can we guaranteed kill?
// worst case: boss sets x very high (e.g. H-1) and undos whenever we deal damage?
// Or x is a "critical" threshold (e.g. near death).
// If boss can undo attacks, he effectively removes our damage sources.
// If attacks are finite, and he can undo enough of them, we lose.
// However, typically "Undo" implies removing the *single largest* contributor to the current threat?
// Logic: A robust strategy requires TotalDamage - MaxDamage >= H.
// This assumes he can only negate the most powerful move once per "run" or critical event.
// Given "Chain", maybe he can negate more. 
// But without more constraints (like 'boss has N charges'), 
// the standard "Robustness" check is usually (Sum - Max) >= Target.

int main() {
    long long H;
    int N;
    if (!(cin >> H >> N)) return 0;

    vector<long long> D(N);
    long long sum_dmg = 0;
    long long max_dmg = 0;

    for (int i = 0; i < N; ++i) {
        cin >> D[i];
        sum_dmg += D[i];
        max_dmg = max(max_dmg, D[i]);
    }

    // Heuristic: If we can cover HP even if our biggest attack is negated.
    if (sum_dmg - max_dmg >= H) {
        cout << "Possible" << endl;
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
