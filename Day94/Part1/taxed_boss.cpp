#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Problem 1: Boss With Damage Taxation
// Rule: Tax = floor(TotalDamage / K)
// Effective = Damage - Tax
// TotalDamage accumulates Effective Damage.
// Goal: Minimize attacks.
// Strategy: Always use the largest damage source.
// This maximizes growth and pushes through tax brackets efficiently.

int main() {
    long long H, K;
    int N;
    if (!(cin >> H >> K >> N)) return 0;

    long long max_d = 0;
    for(int i=0; i<N; ++i){
        long long d;
        cin >> d;
        if(d > max_d) max_d = d;
    }

    if (max_d == 0) {
        if (H <= 0) cout << 0 << endl;
        else cout << -1 << endl;
        return 0;
    }

    long long current_total = 0;
    int steps = 0;

    // Simulation
    // Optimization: If max_d allows passing multiple tax brackets or large chunks?
    // If H is huge, simulation might be slow.
    // Eff = D - floor(S/K).
    // Loop until S >= H.
    // If Eff <= 0, we are stuck (Tax >= D).
    
    while (current_total < H) {
        long long tax = current_total / K;
        long long eff = max_d - tax;
        
        if (eff <= 0) {
            cout << -1 << endl; // Cannot damage anymore
            return 0;
        }
        
        current_total += eff;
        steps++;
        
        if (steps > 2000000) { // Safety break for infinite/large
             // In competitive setting, might need math calc if loop too long.
             // But usually simulation is fine for constraints unless specified.
             // If tax grows slowly (large K), steps ~ H/D.
             // If H ~ 10^9, D ~ 100... 10^7 steps. Fine for C++.
        }
    }
    
    cout << steps << endl;

    return 0;
}
