#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;
// Problem 1: Boss With Nonlinear Damage Scaling
// Effective Damage = floor(d / sqrt(TotalSoFar + 1))
// Strategy: Sort D descending.
// Apply largest first to minimize the denominator penalty for the largest terms.
// See logic in thought block: Summing Large + Small/sqrt(Large) is worse than Small + Large/sqrt(Small).
// Wait, my thought block concluded:
// Case A (100, 10): 100 + 10/10 = 101.
// Case B (10, 100): 10 + 100/3.3 = 40.
// So Largest First (Case A) is much better.

int main() {
    long long H;
    int N;
    if (!(cin >> H >> N)) return 0;
    
    vector<long long> D(N);
    for (int i = 0; i < N; ++i) cin >> D[i];
    
    // Sort descending
    sort(D.begin(), D.end(), greater<long long>());
    
    long long current_total = 0; // "Total Damage So Far" refers to Effective accumulation?
    // "total damage so far" usually means effective damage inflicted on boss.
    // Prompt: "Damage efektif = damage - pajak ... pajak dihitung dari total damage".
    // Here: "floor(d[i] / sqrt(total_damage_so_far + 1))".
    // Yes, accumulated effective damage.
    
    int moves = 0;
    for (long long raw_d : D) {
        if (current_total >= H) break;
        
        long long effective = raw_d / (long long)sqrt(current_total + 1); // problem says floor
        // Note: integer division is floor.
        // sqrt returns double, cast to long long?
        // sqrt(int) is double.
        // floor(d / (double))
        
        effective = floor(raw_d / sqrt(current_total + 1.0));
        
        moves++;
        current_total += effective;
    }
    
    if (current_total >= H) {
        cout << moves << endl;
    } else {
        cout << "-1" << endl;
    }

    return 0;
}
