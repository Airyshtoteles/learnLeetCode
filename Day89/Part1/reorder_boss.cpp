#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// Problem: Boss With Damage Reordering Oracle
// Boss HP H.
// Damage multiset D.
// Boss reorders D to minimize max prefix sum.
// Player wins if chosen multiset has SOME prefix >= H in the boss's best ordering.
// Wait. "Boss reorders to minimize prefix damage".
// Player chooses the multiset (subset of D? or just D?).
// Text: "Tentukan apakah ada multiset serangan". Implies we can pick a subset.
// Strategy: To maximize chance of winning against boss's minimization:
// We should pick all Positives.
// Why? Adding a negative value N helps the boss. He puts N first. 
// This lowers the prefix curve.
// Adding a positive P helps the player.
// The max prefix sum of a sequence with negatives and positives (where boss puts negatives first)
// is simply the Total Sum of the sequence.
// Because the sequence goes down (negatives), then up (positives).
// The peak is at the end.
// So: Winning Condition <-> Sum(Chosen Subset) >= H.
// To maximize this sum, picking all positives is optimal.
// If taking constraints (e.g. "multiset size k") existed, we'd pick k largest.
// No constraint mentioned. Implies "Exists ANY multiset".
// So we just take all positive values.

int main() {
    long long H;
    int N;
    if (!(cin >> H >> N)) return 0;

    vector<long long> D(N);
    long long pos_sum = 0;
    
    for (int i = 0; i < N; ++i) {
        cin >> D[i];
        if (D[i] > 0) {
            pos_sum += D[i];
        }
    }

    if (pos_sum >= H) {
        cout << "Possible" << endl;
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
