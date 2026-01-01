#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Problem: Maximize damage over loops such that Sum(Loop i) != Sum(Loop i-1).
// Strategy: Find max possible sum (V1) and second max possible sum (V2).
// Alternate V1, V2, V1, V2...

int main() {
    int N;
    if (!(cin >> N)) return 0;
    vector<int> D(N);
    for (int i = 0; i < N; ++i) cin >> D[i];
    
    int K;
    long long HP;
    cin >> K >> HP;

    // DP to find reachable sums with K items.
    // Since K and D values might be small, we use set.
    // If K is large, this is slow. Assuming K is reasonable (e.g. <= 20 or D is small).
    // If K is huge, we need a different approach (Knapsack with large items).
    // Given "100 Days", usually standard DP.
    
    set<long long> sums;
    sums.insert(0);
    
    for (int k = 0; k < K; ++k) {
        set<long long> next_sums;
        for (long long s : sums) {
            for (int dmg : D) {
                next_sums.insert(s + dmg);
            }
        }
        sums = next_sums;
    }

    if (sums.empty()) {
        cout << -1 << endl;
        return 0;
    }

    vector<long long> sorted_sums(sums.begin(), sums.end());
    sort(sorted_sums.rbegin(), sorted_sums.rend());

    long long v1 = sorted_sums[0];
    long long v2 = (sorted_sums.size() > 1) ? sorted_sums[1] : -1;

    if (v1 >= HP) {
        cout << 1 << endl;
        return 0;
    }

    if (v2 == -1) {
        // Only one possible sum.
        // Loop 1: v1. Remaining HP > 0.
        // Loop 2: v1. Same as Loop 1 -> Erased.
        // Impossible to proceed.
        cout << -1 << endl;
        return 0;
    }

    // Alternate v1, v2
    long long current_hp = HP;
    int loops = 0;
    
    // Loop 1: v1
    current_hp -= v1;
    loops++;
    if (current_hp <= 0) {
        cout << loops << endl;
        return 0;
    }

    // Loop 2: v2
    current_hp -= v2;
    loops++;
    if (current_hp <= 0) {
        cout << loops << endl;
        return 0;
    }

    // Remaining HP
    // Cycle of 2 loops does (v1 + v2) damage.
    long long cycle_dmg = v1 + v2;
    long long cycles_needed = current_hp / cycle_dmg;
    
    // Optimization: Don't simulate one by one if HP is huge.
    loops += cycles_needed * 2;
    current_hp -= cycles_needed * cycle_dmg;

    while (current_hp > 0) {
        // Next is v1 (since we did v2 last in the cycle logic, or we are at start of cycle)
        // Wait, we did v1, v2. So next is v1.
        current_hp -= v1;
        loops++;
        if (current_hp <= 0) break;
        
        current_hp -= v2;
        loops++;
    }

    cout << loops << endl;

    return 0;
}
