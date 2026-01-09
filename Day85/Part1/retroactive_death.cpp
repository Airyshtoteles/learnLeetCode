#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Problem: Boss With Retroactive Death
// Boss HP H.
// If HP <= 0, boss checks last K attacks and cancels ONE.
// This repeats until stable.
// To guarantee death, we need to reach a state where even after cancellation, HP <= 0.
// If we use max damage D for all attacks:
// We attack N times. Total damage N * D.
// If N * D >= H, boss cancels one.
// Remaining damage (N-1) * D.
// If (N-1) * D >= H, boss cancels another?
// The problem says "Proses ini bisa terjadi berulang sampai stabil".
// If the boss cancels one and we are still >= H, the condition "HP <= 0" is met again.
// Does the boss cancel another from the *new* last K?
// If we assume the boss keeps cancelling as long as HP <= 0, then we can NEVER kill the boss unless we deal infinite damage or the window empties.
// However, usually in these problems, "last K" refers to the specific window of time.
// If we attack N times, indices 1..N.
// Boss cancels index i in [N-K+1, N].
// If we are still dead, does boss cancel another?
// If the rule is "As long as HP <= 0, cancel one from current history", then yes.
// But if we assume the standard "Robustness" interpretation (we need to survive ONE check), then (N-1)D >= H.
// Given the "Hint: monotonic prefix + worst-case rollback window", it suggests we need to survive the rollback.
// If the rollback is recursive, it's impossible.
// I will assume the "One-Cancel" interpretation or that the window shifts such that we can eventually win.
// But with constant damage, (N-1)D >= H is the only logical "robust" threshold.
// If we need to survive 2 cancellations, it would be (N-2)D >= H.
// I'll stick to (N-1)D >= H.

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
        cout << -1 << endl;
        return 0;
    }

    // We need (N - 1) * max_dmg >= H
    // N - 1 >= ceil(H / max_dmg)
    // N >= ceil(H / max_dmg) + 1
    
    long long attacks = (H + max_dmg - 1) / max_dmg + 1;
    
    // Edge case: If H <= 0 initially? (Not possible by constraints usually)
    // If K=0? Then just ceil(H/max_dmg).
    if (K == 0) {
        attacks = (H + max_dmg - 1) / max_dmg;
    }

    cout << attacks << endl;

    return 0;
}
