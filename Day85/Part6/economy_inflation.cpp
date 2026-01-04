#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Problem: Economy With Irreversible Inflation
// Each transaction increases inflation.
// Value = Money / Inflation.
// If Inflation >= Limit, collapse.
// Target Wealth W.
// Assume:
// Initial Money M0 = 0? Or given?
// Initial Inflation I0 = 1?
// Gain per transaction G.
// Inflation increase per transaction C.
// Limit L.
// After k transactions:
// Money = k * G (assuming start 0)
// Inflation = 1 + k * C
// Value = (k * G) / (1 + k * C)
// Constraint: 1 + k * C < L => k * C < L - 1 => k < (L - 1) / C.
// Maximize Value over valid k.
// Function f(k) = G*k / (1 + C*k).
// Derivative f'(k) = (G(1+Ck) - Gk(C)) / (1+Ck)^2 = G / (1+Ck)^2 > 0.
// So Value is strictly increasing with k.
// We should choose the largest possible k such that Inflation < Limit.
// Max k = floor((L - 1 - epsilon) / C).
// Or simply: k_max such that 1 + k_max * C < L.
// If 1 + k * C == L, it collapses? "mencapai batas -> collapse". Yes.
// So strictly less than L.
// If C=0, we can go infinite? But usually C > 0.
// If C=0, Value = k*G. Can reach any W.
// If C > 0, Value approaches G/C. If W >= G/C, impossible (unless C=0).
// Actually, if W < G/C, we can reach it eventually.
// We just need to check if Value(k_max) >= W.

int main() {
    long long G, C, L, W;
    if (!(cin >> G >> C >> L >> W)) return 0;

    if (C == 0) {
        // Inflation stays 1. Value = k * G.
        // Can always reach W if G > 0.
        if (G > 0) cout << "Possible" << endl;
        else if (W <= 0) cout << "Possible" << endl;
        else cout << "Impossible" << endl;
        return 0;
    }

    // Max k such that 1 + k * C < L
    // k * C < L - 1
    // k <= (L - 1 - 1) / C  (integer division)
    // Wait, if L-1 is divisible by C, strictly less means -1.
    // Let's use: k_max = (L - 1 - 1) / C?
    // Example: L=10, C=2. 1 + 2k < 10 => 2k < 9 => k <= 4.
    // (10 - 1 - 1) / 2 = 8 / 2 = 4. Correct.
    // Example: L=11, C=2. 1 + 2k < 11 => 2k < 10 => k < 5 => k <= 4.
    // (11 - 1 - 1) / 2 = 9 / 2 = 4. Correct.
    
    if (L <= 1) {
        // Already collapsed or at limit?
        // If Limit is 1, and start is 1. 1 >= 1 -> Collapse immediately?
        // "mencapai batas". If start >= limit, collapse.
        cout << "Impossible" << endl;
        return 0;
    }

    long long k_max = (L - 1 - 1) / C;
    
    // Calculate Value at k_max
    // Use double for precision or cross multiply
    // Value >= W  =>  (k * G) / (1 + k * C) >= W
    // k * G >= W * (1 + k * C)
    // k * G >= W + W * k * C
    // k * (G - W * C) >= W
    
    // Check if G - W * C > 0
    // If G > W * C, then k >= W / (G - W * C).
    // If we can pick such k <= k_max, possible.
    // If G <= W * C, then LHS <= 0 (for k>=0). RHS = W > 0. Impossible.
    
    // Wait, simpler: Just check condition at k_max.
    // Since f(k) is increasing, if f(k_max) >= W, then possible.
    // Check: k_max * G >= W * (1 + k_max * C)
    
    // Use __int128 to avoid overflow
    __int128 lhs = (__int128)k_max * G;
    __int128 rhs = (__int128)W * (1 + (__int128)k_max * C);
    
    if (lhs >= rhs) {
        cout << "Possible" << endl;
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
