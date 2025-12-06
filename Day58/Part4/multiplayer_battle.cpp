#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Player {
    int id;
    int hp;
    int atk;
};

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
    }

    int N;
    if (!(cin >> N)) return 0;

    vector<int> HP(N), ATK(N);
    for (int i = 0; i < N; ++i) cin >> HP[i];
    for (int i = 0; i < N; ++i) cin >> ATK[i];

    long long min_total_turns = -1;

    for (int survivor_idx = 0; survivor_idx < N; ++survivor_idx) {
        // Simulation
        vector<Player> targets;
        for (int i = 0; i < N; ++i) {
            if (i != survivor_idx) {
                targets.push_back({i, HP[i], ATK[i]});
            }
        }

        // Sort targets by ATK ascending
        sort(targets.begin(), targets.end(), [](const Player& a, const Player& b) {
            return a.atk < b.atk;
        });

        long long current_turns = 0;
        bool possible = true;

        // We process targets one by one
        // But wait, the attacker set includes the survivor AND all remaining targets.
        // The attacker must be distinct from the victim?
        // "Ketika player A menyerang B". A != B.
        // If we use T_max to attack T_min, that's fine.
        // If we use S to attack T_min, that's fine.
        
        // We iterate through the sorted targets (victims)
        for (size_t i = 0; i < targets.size(); ++i) {
            // Victim is targets[i]
            // Find max ATK among survivor and remaining targets (targets[i...end])
            // Note: targets[i] is the victim, so they cannot attack?
            // "Setiap turn, hanya 1 player yang boleh menyerang".
            // Can the victim attack? No, they are being attacked.
            // Wait, in a turn, A attacks B. B takes damage.
            // B is busy taking damage? The problem doesn't say B cannot attack in *other* turns.
            // But in *this* turn, A is the attacker. B is the victim.
            // So B cannot be the attacker in the *same* turn.
            // So we look for max ATK among all alive players EXCEPT the victim.
            
            int max_atk = 0;
            // Check survivor
            max_atk = max(max_atk, ATK[survivor_idx]);
            
            // Check other targets (j from i+1 to end)
            // Also check targets[i]? No, victim cannot attack themselves.
            // Can targets[i] attack someone else? No, we are calculating turns to kill targets[i].
            // So in the turns where targets[i] is being killed, someone else must be attacking.
            // So we need an attacker != targets[i].
            
            for (size_t j = i + 1; j < targets.size(); ++j) {
                max_atk = max(max_atk, targets[j].atk);
            }
            
            if (max_atk == 0) {
                possible = false; 
                break; // Should not happen if ATK > 0
            }

            int victim_hp = targets[i].hp;
            int turns_needed = (victim_hp + max_atk - 1) / max_atk;
            current_turns += turns_needed;
        }

        if (possible) {
            if (min_total_turns == -1 || current_turns < min_total_turns) {
                min_total_turns = current_turns;
            }
        }
    }

    cout << min_total_turns << endl;

    return 0;
}
