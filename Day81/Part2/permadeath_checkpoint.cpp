#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Problem Analysis:
// "Mati di node -> respawn di checkpoint terdekat di atasnya"
// "Setiap checkpoint hanya bisa dipakai sekali"
// "Kamu ingin menjamin bisa mencapai leaf terdalam, tidak peduli di node mana kamu mati sekali"
//
// Interpretation:
// We need to be robust against a SINGLE death at ANY node.
// If we die at node U, we respawn at the nearest ancestor checkpoint.
// Since we only die once, a single checkpoint at the Root (or start node) is sufficient to cover all possible death locations.
// If we die at U, we respawn at Root, and since we don't die again, we can reach the leaf.
// The "used once" constraint is satisfied because in any single scenario, we only use the checkpoint once.
//
// However, if the problem implies "Game with Lives" where every node might kill us (worst case), then we need more.
// But "mati sekali" (die once) strongly implies a single failure event.
//
// We will output 1 if the tree has any depth (n > 1), and 0 if n=1.
//
// Wait, what if we can't put a checkpoint at the root?
// "Dungeon berbentuk tree berakar". Usually we can put checkpoints at nodes.
// If we assume we can put a checkpoint at the root (node 1), the answer is 1.

int main() {
    int n;
    if (!(cin >> n)) return 0;

    // We need to read the tree structure even if the answer is simple, 
    // to handle the input format correctly.
    // Assuming input format: N, then N-1 edges? Or parent array?
    // Standard competitive programming tree input: N, then N-1 pairs.
    
    if (n <= 1) {
        cout << 0 << endl;
        return 0;
    }

    // Consume input
    int u, v;
    for (int i = 0; i < n - 1; ++i) {
        cin >> u >> v;
    }

    cout << 1 << endl;

    return 0;
}
