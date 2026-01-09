#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Problem: Boss has HP H.
// We can attack with available damage values D[i].
// Boss can retroactively cancel 'k' attacks (the largest ones).
// We want to minimize the number of attacks N to kill the boss.
// Strategy: To minimize N, we should always use the strongest attack available.
// Let max_dmg be the maximum damage we can deal.
// If we attack N times, the boss removes min(N, k) attacks.
// Since we always use max_dmg, the boss removes min(N, k) * max_dmg.
// Effective damage = N * max_dmg - min(N, k) * max_dmg.
// If N <= k, effective damage is 0.
// If N > k, effective damage is (N - k) * max_dmg.
// We need (N - k) * max_dmg >= H.
// N - k >= ceil(H / max_dmg).
// N >= k + ceil(H / max_dmg).

int main() {
    long long H;
    int K;
    if (!(cin >> H >> K)) return 0;
    
    int N_types;
    cin >> N_types;
    long long max_dmg = 0;
    for (int i = 0; i < N_types; ++i) {
        long long d;
        cin >> d;
        max_dmg = max(max_dmg, d);
    }

    if (max_dmg == 0) {
        cout << -1 << endl; // Impossible if we can't deal damage
        return 0;
    }

    // Calculation
    // (N - K) * max_dmg >= H
    // N - K >= (H + max_dmg - 1) / max_dmg
    long long attacks_needed = (H + max_dmg - 1) / max_dmg;
    long long total_attacks = K + attacks_needed;

    cout << total_attacks << endl;

    return 0;
}
