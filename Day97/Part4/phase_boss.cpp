#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Problem 4: Boss Fight With Phase Prediction
// Phases 1..N.
// Decision at Phase i:
// 1. Fight: depends on HP. New HP? Cost?
// 2. Skip: Cost S. Jump to i+1 or i+k?
//    "Kamu boleh skip fase". Assume skip to i+1.
//    "Skill mahal".
// Constraint: "Salah prediksi fase = instant death".
// This implies Probability? Or Hidden State?
// But problem asks "Apakah ada strategi AMAN" (Guaranteed Win).
// Strategy Aman implies we must cover ALL possibilities or the logic is deterministic.
// "Damage tiap fase tergantung sisa HP di fase sebelumnya".
// So P(i) damage depends on HP(i-1).
// We track HP.
// DP State: `dp[phase] = Max HP remaining` ?
// Or `dp[phase] = Min Damage taken`.
// If `dp[phase] > 0`, we survived.
//
// Let's assume input defines:
// N Phases.
// Skip Cost.
// Initial HP.
// For each phase: BaseDamage. Factor.
// Damage = Base + Factor * (CurrentHP / MaxHP?). Or (MaxHP - CurrentHP)?
// "Tergantung sisa HP". Usually Damage taken = f(PlayerHP).
//
// Logic:
// dp[i] = Max HP at start of phase i.
// Transitions:
// 1. Fight Phase i:
//    Dmg = CalcDamage(Phase i, dp[i]).
//    NextHP = dp[i] - Dmg.
//    If NextHP > 0: dp[i+1] = max(dp[i+1], NextHP).
// 2. Skip Phase i:
//    Cost = SkipCost.
//    NextHP = dp[i] - Cost.
//    If NextHP > 0: dp[i+1] = max(dp[i+1], NextHP).
//
// Goal: dp[N+1] > 0.
//
// Input format assumption:
// N, HP_init, SkipCost.
// N lines: BaseDmg, ScalingFactor.
// Damage Formula: Base + (Factor * current_HP / 100). Or similiar.
// Assume simpler: Dmg = Base + (current_HP * Factor / 100).

int main() {
    int N;
    long long HP_init, SkipCost;
    if (!(cin >> N >> HP_init >> SkipCost)) return 0;
    
    vector<long long> Base(N), Factor(N);
    for(int i=0; i<N; ++i) cin >> Base[i] >> Factor[i];
    
    vector<long long> dp(N + 2, -1);
    dp[0] = HP_init; // Start Phase 0 (0-indexed logic 0..N-1)
    
    for(int i=0; i<N; ++i) {
        if (dp[i] == -1) continue;
        
        // Option 1: Fight
        long long dmg = Base[i] + (dp[i] * Factor[i] / 100);
        long long next_hp_fight = dp[i] - dmg;
        if (next_hp_fight > 0) {
            dp[i+1] = max(dp[i+1], next_hp_fight);
        }
        
        // Option 2: Skip
        long long next_hp_skip = dp[i] - SkipCost;
        if (next_hp_skip > 0) {
            dp[i+1] = max(dp[i+1], next_hp_skip);
        }
    }
    
    if (dp[N] > 0) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
