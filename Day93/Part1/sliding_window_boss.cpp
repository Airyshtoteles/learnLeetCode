#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Problem 1: Boss With Sliding Window Immunity
// Goal: Minimize attacks to reach effective damage H.
// Rule: Eff_Damage = Total_Raw - Max_Window_Sum(K).
// Strategy: Use the single largest damage type repeatedly.
// Why? Mixing in smaller damages strictly hurts or is neutral.
// Proof Idea: Replacing a small value with a larger one increases Total by (Diff).
// Max_Window_Sum increases by at most (Diff).
// So Eff_Damage increases by >= 0.
// Thus, using max_damage D for all moves is optimal.
// Eq: L*D - K*D >= H  (for L > K)
// L - K >= H/D
// L >= H/D + K
// Result = ceil(H/D) + K.
// Edge Case: If H=0, 0 moves.

int main() {
    long long H, K, N;
    if (!(cin >> H >> K >> N)) return 0;
    
    long long max_d = 0;
    for (int i = 0; i < N; ++i) {
        long long d;
        cin >> d;
        if (d > max_d) max_d = d;
    }
    
    if (H <= 0) {
        cout << 0 << endl;
        return 0;
    }
    
    if (max_d == 0) {
        cout << -1 << endl; // Impossible
        return 0;
    }
    
    // Formula: L = ceil(H / max_d) + K
    long long steps = (H + max_d - 1) / max_d + K;
    
    cout << steps << endl;
    
    return 0;
}
