#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

// Problem 6: Asynchronous Turn-Based
// Enemy attacks every A steps. (Damage E_dmg).
// Player attacks every B steps. (Damage P_dmg).
// Stacking Decay? "Damage bersifat stacking decay".
// Interpretation: 
// Damage taken/dealt decreases? Or accumulates?
// "Decay" usually means decrease. "Stacking" usually means increase.
// Maybe: Dmg = Base + (Stack * DecayFactor)?
// Or: NextDmg = CurrentDmg * Decay.
// "Stacking Decay" -> Like Bleed that reduces over time?
// Or: Each hit adds a Stack, but Stacks decay?
//
// Simple interpretation for Day 97:
// Timeline Simulation.
// Enemy HP, Player HP.
// Events Time 0..Max.
// Enemy hits at A, 2A, 3A...
// Player hits at B, 2B, 3B...
// Who dies first?
//
// But "Damage stacking decay".
// Maybe Damage reduces each hit? D, D*k, D*k^2...?
// Or Stacks add up?
// Let's assume standard "Stacking" mechanics in games:
// Each attack deals D. And applies a DOT (Damage Over Time)?
// OR: Damage value IS Stacking.
// "Damage bersifat stacking decay".
// Maybe D_n = D_{n-1} * decay?
// If decay < 1, damage approaches 0.
// Let's read inputs to guess.
// Inputs: A, B, HP_enemy, HP_player, D_enemy, D_player, Decay.
//
// Simulation:
// Time moves forward.
// NextEnemy = A, NextPlayer = B.
// While both alive:
//   T = min(NextEnemy, NextPlayer).
//   If NextPlayer == T:
//      EnemyHP -= PlayerCurrentDmg.
//      PlayerCurrentDmg *= Decay.
//      NextPlayer += B.
//   If NextEnemy == T: (Concurrent? usually Enemy prio or simultaneous?)
//      PlayerHP -= EnemyCurrentDmg.
//      EnemyCurrentDmg *= Decay.
//      NextEnemy += A.
//
// Check who survives.
// Note: Floating point damage? Or Integer.
// "day97 biasa" -> Simple simulation.

int main() {
    long long A, B;
    double HP_enemy, HP_player;
    double D_enemy, D_player, Decay;
    
    if (!(cin >> A >> B >> HP_enemy >> HP_player >> D_enemy >> D_player >> Decay)) return 0;
    
    long long time_e = A;
    long long time_p = B;
    
    while(HP_enemy > 1e-9 && HP_player > 1e-9) {
        long long t = min(time_e, time_p);
        
        bool enemy_acts = (time_e == t);
        bool player_acts = (time_p == t);
        
        // Simultaneous resolution
        double dmg_to_player = 0;
        double dmg_to_enemy = 0;
        
        if (enemy_acts) {
            dmg_to_player = D_enemy;
            D_enemy *= Decay;
            time_e += A;
        }
        
        if (player_acts) {
            dmg_to_enemy = D_player;
            D_player *= Decay;
            time_p += B;
        }
        
        HP_player -= dmg_to_player;
        HP_enemy -= dmg_to_enemy;
        
        if (D_enemy < 1e-9 && D_player < 1e-9) break; // Stalemate
    }
    
    if (HP_player > 1e-9 && HP_enemy <= 1e-9) cout << "YES" << endl; // Win
    else if (HP_player <= 1e-9 && HP_enemy <= 1e-9) cout << "Draw" << endl; // Draw (usually consider lose or special)
    else cout << "NO" << endl; // Lose
    
    return 0;
}
