#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Problem 6: Economy With Compound Interest Trap
// Rule: Mone_new = Money_old * R. Then Money_final = Money_new + Delta.
// Constraint: Money_final >= Money_old (Monotonicity).
// This implies Money_old * R + Delta >= Money_old.
// Money_old * (R - 1) >= -Delta.
// If Delta >= 0, always true (assuming R >= 1 and Money >= 0).
// If Delta < 0, we need Money >= -Delta / (R - 1).
// Basically, we need enough base capital to absorb the negative hit even after growth.
// Goal: Reach Target W.
// Strategy: Order transactions to maximize final W and Maintain feasibility.
// To maximize Final W:
// W_final = W_0 * R^N + Sum (Delta_i * R^(N-i)).
// To maximize this sum, we want largest Delta to be multiplied by largest R power.
// Largest R power is R^(N-1) (processed first). Smallest is R^0 (processed last).
// So maximize Delta_1 (first transaction).
// Sort Delta descending: Positives first (largest to smallest), then Negatives (smallest abs to largest abs).
// Wait. "Smallest abs to largest abs" for negatives?
// Negatives are like -10, -50.
// Sorted descending: 100, 50, -10, -50.
// Is this order best?
// 1. Maximize Final W: Yes, early large deltas grow most.
// 2. Feasibility:
//    - Positives early: W grows fast. High W helps satisfy W(R-1) >= -NegDelta later.
//    - Negatives late: If we put -50 early, W is small, might fail check.
//    - So Descending Sort is optimal for BOTH objectives.
// Logic check for R=1: W >= -Delta implies W + Delta >= W. (Standard).
// If R=1, W_final = W_0 + Sum Deltas. Order doesn't change final, but affects intermediate feasibility.
// Greedy Descending works for R=1 too (Positives build safety buffer).

int main() {
    double W_init, W_target, R;
    int N;
    if (!(cin >> W_init >> W_target >> R >> N)) return 0;
    
    vector<double> deltas(N);
    for(int i=0; i<N; ++i) cin >> deltas[i];
    
    // Sort descending
    sort(deltas.begin(), deltas.end(), greater<double>());
    
    double current_W = W_init;
    bool possible = true;
    
    for(int i=0; i<N; ++i){
        double prev_W = current_W;
        double grew_W = current_W * R;
        double next_W = grew_W + deltas[i];
        
        // Check constraint
        // "turun dari nilai sebelumnya" -> next_W < prev_W
        if (next_W < prev_W - 1e-9) { // Tolerance
            possible = false;
            break;
        }
        
        current_W = next_W;
    }
    
    if (possible && current_W >= W_target - 1e-9) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}
