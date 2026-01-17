#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Problem 5: Cooperative Boss With Betrayal
// Minimax or simple Worst Case?
// "Strategi menang tanpa bergantung NPC".
// Treat NPC as Enemy.
// Input: BossHP. Moves.
// My turn: Choose move. Result: Damage.
// NPC turn: Choose move (Help/Betray). Result: Damage or Heal Boss?
// "Betray" usually means healing boss or damaging player?
// Let's assume outcomes are +Dmg or -Dmg(Heal).
// We want to reach BossHP <= 0.
// Is it finite game? "Damage history".
// If NPC can heal indefinitely, we might never win.
// We need winning strategy in FINITE steps?
// Or just "Can force win".
//
// Model:
// State: BossHP.
// Player: Choose d in MyDmg. HP -= d.
// NPC: Choose d in NpcOptions. HP -= d (d can be negative).
// If NPC chooses strictly worst for us.
// Can we force HP <= 0?
// This is simply: EffectiveDamage = MyMove + WorstNPCMove.
// If EffectiveDamage > 0, we eventally win.
// If EffectiveDamage <= 0, we stall or lose.
// "History dependent" implies NPC behavior changes?
// "Threshold threshold".
// The problem asks: "Without relying on NPC".
// This means assuming NPC is ALWAYS Worst Case?
// Yes. "Tanpa bergantung" = Worst Case.
// So, check if (Max(MyMoves) + Min(NpcMoves)) > 0?
// Actually, we play turn by turn.
// Round damage = MyBest - NPCWorstHeal.
// If Round > 0 -> YES.
// Else -> NO.
// Unless we have limited turns. Assuming infinite turns until win/loss.
// If BossHP starts positive.

int main() {
    int BossHP;
    if (!(cin >> BossHP)) return 0;
    
    int N_my, N_npc;
    cin >> N_my;
    vector<int> my_dmg(N_my);
    int max_my = -1e9;
    for(int i=0; i<N_my; ++i) {
        cin >> my_dmg[i];
        if (my_dmg[i] > max_my) max_my = my_dmg[i];
    }
    
    cin >> N_npc;
    vector<int> npc_dmg(N_npc);
    int min_npc = 1e9; // Worst case (smallest damage, most heal)
    for(int i=0; i<N_npc; ++i) {
        cin >> npc_dmg[i];
        if (npc_dmg[i] < min_npc) min_npc = npc_dmg[i];
    }
    
    // Net progress per round
    if (max_my + min_npc > 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}
