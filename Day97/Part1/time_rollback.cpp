#include <iostream>#include <iostream>





































































}    return 0;        else cout << "NO" << endl;    if (possible) cout << "YES" << endl;        }        }            }                break;                possible = true;            if (dmg >= req_hp) {                        unsigned long long dmg = Rate * (L + (long long)k * max_segment);            unsigned long long req_hp = H * (1ULL << k);                        if (k > 60) break;            // If k > 60, impossible.            // If k=30, 2^30 ~ 10^9. H ~ 10^9. Product 10^18. Fits in long long.            // H * 2^k            // Check overflow for RHS        for(int k=1; k<=K_limit; ++k) {                // Intersection is small K.        // H * 2^k is exponential.        // Rate * (L + K*Seg) is linear.        // Or check if 2^k exceeds reasonable limits.        // Use double to avoid overflow for large H*2^k comparison?        // Check k=1..K    if (!possible && M_saves > 0) {        if (Rate * L >= H) possible = true;    // Check k=0        bool possible = false;        if (M_saves == 0) max_segment = 0;    long long max_segment = L - min_s;        // Actually typically 0 is start.    // If M_saves == 0, can't rollback.    // "Save point di waktu tertentu". If none, maybe cant rollback?    if (min_s == -1) min_s = 0; // Default if no saves? Start is save 0?        }        if (min_s == -1 || s < min_s) min_s = s;        long long s; cin >> s;    for(int i=0; i<M_saves; ++i) {    long long min_s = -1;        if (!(cin >> H >> Rate >> L >> K_limit >> M_saves)) return 0;        int K_limit, M_saves;    long long H, Rate, L;int main() {// Check if Total Damage >= Required HP.// Required HP = H * 2^k.// Total Damage = Total Time * Rate.// Total Time = L + k * (L - Min_Save_Time).// Check k = 0 to K_limit.// Logic:using namespace std;#include <cmath>#include <algorithm>#include <vector>#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Problem 1: Time-Fractured Save Points
// We have K rollbacks.
// Each rollback doubles Enemy HP.
// We start with Time T_total.
// We can set Save Points? Or they are fixed?
// "Game punya save point di waktu tertentu." (Fixed).
// Let Save Points be S_1, S_2, ..., S_m.
// We are at End (Time L).
// If we rollback to S_i, we replay interval [S_i, L].
// Time gained: (L - S_i).
// Boss HP factor: * 2.
// Damage Rate: D.
// Initial HP: H.
// Original Time: L (from 0 to L). Dmg = L * D.
// Check: L*D >= H?
//
// If we use 1 rollback to S_i:
// Total Time = L + (L - S_i).
// HP = H * 2.
// Check: (2L - S_i) * D >= 2H?
//
// Generally, we choose a sequence of rollbacks.
// But "HP x2" applies to the Boss. Is the HP accumulated or reset?
// Usually, "Boss Evaluates" means the Boss we fight NOW has HPx2.
// If we rollback, we are fighting the SAME boss again but stronger?
// Or does rollback mean we gain time to GRIND/PREPARE?
// "Damage kamu tetap" suggests we don't get stronger.
// This implies we simply have MORE TIME to hit the SAME boss which now has MORE HP.
// This seems counter-intuitive if HP doubles. Gaining time <= L implies factor < 2.
// Time_New = Time_Old + (L - S).
// Factor = (T + Delta)/T. If Delta < T, Factor < 2.
// So HP doubling (Factor 2) > Time Factor (<2).
// So Rollback makes it HARDER.
//
// Unless... we can rollback MULTIPLE times to the SAME point?
// If we rollback to 0 repeatedly:
// Time += L. HP *= 2.
// Ratio Time/HP: (T+L) / 2H vs T/H.
// If T=L, ratio -> 2T/2H = T/H. Same.
// If we rollback to S > 0, Delta < L. Ratio decreases.
// So rolling back strictly hurts or is neutral (at best).
//
// UNLESS: "Semua musuh berevolusi". Boss is a specific enemy.
// Maybe we rollback to heal? But damage is the constraint.
//
// IS THERE A CASE WHERE IT HELPS?
// Maybe Damage is PER HIT, and we have Attack Speed?
// Total Dmg = Time * DPS.
// Maybe "HP x 2" is base HP?
//
// Alternative interpretation: Save Points allow us to RESTORE state?
// Maybe we failed, so we MUST rollback?
// "Apakah boss terakhir bisa dikalahkan?" implies checking feasibility.
//
// Perhaps the key is: We can rollback to specific points where we had advantages?
// Or maybe: We deal damage D *in that segment*?
//
// Let's look at "Monotonic Feasibility".
// Maybe the "HP x 2" is the COST of using the mechanic.
// But the mechanic gives us something huge?
// What if "Damage kamu tetap" means "Cumulative Damage is Preserved"?
// "Damage kamu tetap" -> Your Damage STAT is constant. It does NOT say "Damage Dealt is kept".
// If Damage Dealt is kept, then:
// Time 1: Deal D1. Rollback. Boss HP is 2H. Dmg Dealt D1 kept. Reset time.
// Time 2: Deal D2. Total D1+D2 > 2H?
// This makes sense!
// If damage dealt is preserved ("Memory of battle"), but Boss gets stronger.
// We trade Time for Difficulty.
//
// Let Base HP = H.
// Round 0: Time T0. Damage = T0 * Rate.
// If T0*R >= H, Win.
// If not, Rollback to S_i.
// HP becomes 2H. Damage dealt T0*R is PRESERVED.
// We now play segment [S_i, End] again. Duration T_new = End - S_i.
// Damage added: T_new * Rate.
// Total Dmg: T0*R + T_new*R.
// Check: D_total >= 2H?
// Repeat k times.
// Total Damage = Rate * (L + Sum(L - S_{choice_j})).
// Target HP = H * 2^k.
// Condition: Rate * (L + Sum(Delta_j)) >= H * 2^k.
// Rate * L + Rate * Sum(Delta) >= H * 2^k.
// Rate * Sum(Delta) >= H * 2^k - Rate * L.
// Delta_j = L - S_{choice_j}. To maximize LHS, we pick smallest S (S=0 implies Delta=L).
// So effective strategy: Always rollback to S=0 (Max time gain).
// If S=0 is not available, pick min available S.
// Let MaxDelta = L - Min(S).
// We have `k` rollbacks. We should use all `k`?
// LHS grows linearly with k (add L). RHS grows exponentially (2^k).
// H * 2^k grows much faster.
// So usually K=0 is best.
//
// UNLESS: H is very small initially, but L is small.
// Or Rate is huge?
// If Rate * L < H.
// Try k=1: Rate * 2L vs 2H. Same ratio.
// Try k=2: Rate * 3L vs 4H. Worse.
//
// Is it possible "HP x2" refers to something else? "HP + HP_base"?
// "HP x 2" usually means doubling.
//
// Let's reconsider "Damage kamu tetap".
// Maybe Damage STACKS? "Damage kamu tetap" = "Your Damage Stat Stays".
// What if we get Loot/Powerups in the run?
// No mention of powerups.
//
// Wait. "Inti: binary search + rollback DP".
// This implies finding a Value? Or checking feasibility?
// Maybe "Save Point" has a COST?
//
// Let's implementing the "Preserved Damage" logic check for k=0..MaxK.
// Maximize Time / 2^k ? No, simply check:
// Max_Possible_Damage(k) >= H * 2^k.
// Max_Possible_Damage(k) = Rate * (L + k * Max_Segment).
// Check if ANY k in [0, K_limit] works.
// Because maybe for small k it works?
// E.g. H=100. Rate=10. L=5.
// k=0: 50 < 100. Fail.
// k=1: 50 + 50 = 100. HP=200. Fail.
// Ratio 100/200 = 0.5.
// It never catches up if growth is linear vs exp.
//
// UNLESS: "Damage Dealt" is Reset?
// If Damage Dealt is Reset, then we just fight a 2H boss with same time. Impossible.
//
// UNLESS: "HP x 2" is False interpretation?
// Re-read: "Semua musuh berevolusi (HP x 2)".
//
// Maybe the "Save Point" is later?
// Time: 0 -- S1 -- S2 -- End.
// We fight Boss at End.
// We deal damage.
// Problem: If we rollback, we go back in time.
//
// "Time-Fractured".
// Maybe we CLONE ourselves? "Damage kamu tetap" (You stay).
// Rollback -> There are now 2 of you?
// "Semua musuh berevolusi".
// If there are 2 of us, DPS doubles.
// HP doubles.
// DPS * 2 vs HP * 2. Neutral.
// Time acts as the differentiator.
// If we rollback to 0, we have 2 copies for time L. Total Dmg 2 * D * L. HP 2H.
// If we rollback to L/2.
// Copy 1 runs 0..L.
// Copy 2 runs L/2..L.
// Segment 0..L/2: DPS D.
// Segment L/2..L: DPS 2D.
// Total Dmg: D*(L/2) + 2D*(L/2) = 1.5 D L.
// Boss HP: 2H.
// Ratio: 1.5 DL / 2H = 0.75 (DL/H).
// Original: DL / H.
// Worse.
//
// Everything implies Rollback is BAD.
// UNLESS "Damage kamu tetap" means "Damage dealt to boss is Kept".
// AND "HP x 2" means Current HP? Or Max HP?
// Let's assume the standard "New Game+" logic: Max HP scales.
//
// Is there ANY mechanic where Rollback wins?
// Maybe "Boss HP" is FIXED at start?
// "Semua musuh berevolusi".
//
// Let's assume the user wants the "Cumulative Damage vs Scaled HP" check.
// Iterate k from 0 to K.
// If (BaseDamage + k * MaxSegmentDamage) >= (H * pow(2, k)): return YES.
// Else NO.
// Note: Boss HP might scale huge, so use Log or BigInt?
// C++ `double` or `unsigned long long` should suffice for standard inputs.
// Python handles large ints.

int main() {
    long long H, Rate, L;
    int K_limit, M_saves;
    if (!(cin >> H >> Rate >> L >> K_limit >> M_saves)) return 0;
    
    long long max_segment = L; // Default rollback to 0 if 0 is a save point?
    // "Save point di waktu tertentu". We assume 0 is Start.
    // Inputs: Save points S_i.
    // Segment = L - S_i.
    // Shortest S_i gives Longest Segment.
    
    // Read saves
    for(int i=0; i<M_saves; ++i) {
        long long s; cin >> s;
        if ((L - s) > max_segment) {
            // Should not happen if s >= 0.
            // But we want MAX (L-S), so MIN S.
        }
        // Actually we just pay attention to MIN S.
        // Assuming we ALWAYS pick the best save point to maximize time.
    }
    long long min_s = 0;
    for(int i=0; i<M_saves; ++i) {
        long long s; cin >> s; // Wait, reading again? Logic flow error.
        // Re-structure with vector.
    }
    
    return 0;
}
