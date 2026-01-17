#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

// Problem 2: Boss With Damage Memory
// Input: BossHP, K, N_attacks, Attacks[]
// State: (CurrentHP, Tuple(Last K Attacks)) - Wait, CurrentHP isn't relevant for loop detection.
// Loop detection is on the sequence of attacks.
// State for recursion: (Tuple(Last K), AccumDamage). 
// But AccumDamage is monotonic.
// The constraint is: We cannot visit the same Node in the De Bruijn graph twice.
// Node = Sequence of last K.
// We want max path sum in this graph.
// If MaxPath >= BossHP -> Win.
// Graph nodes: N^K. If N=3, K=3 -> 27. Small.
// If N=10, K=5 -> 100,000. Limit?
// Assume N, K match typical CP problem (total states ~10^5 or small).
// DFS for Longest Path in DAG.
// Memoization?
// dp[node] = max damage starting from this history state?
// Yes.
// Base case: No valid moves (all next states visited in current path? No, global visited?).
// Problem: "Jika pola damage pernah berulang... boss immune".
// "Pola damage" = The sequence of length K.
// If we execute a1, a2, a3, a4...
// Windows: (a1..ak), (a2..ak+1)...
// All windows must be unique.
// So we visit nodes in N^K graph. Each node visited at most once.
// Longest path in N^K graph.
// Memoization works because it's a DAG? No, the graph has cycles, but we can't take them.
// "Visited" constraint transforms it into finding Simple Path.
// Simple Longest Path is NP-Hard.
// BUT here we just need to exceed BossHP.
// If BossHP is small, BFS state (Node, damage) works.
// If BossHP large and N, K small -> Hamiltonian Path flavor.
// Since it's Day 99, I'll use DFS with backtracking (small scale assumption) or simple Memoization if I ignore path-history (meaning, treating immunity as "State Repeated GLOBALLY" not just in current fight segment? No, in current fight).
// Actually, graph is static. If we treat "Immune if Repeated" as "Cycle Detection":
// We just need a simple path.
// Standard DP on subsets? No.
// Let's assume standard "Max path possible without repeating nodes".
// Map<Node, int> max_dmg_from.
// But `max_dmg_from` depends on `visited` set? Yes -> NP hard.
// However, if we just want "Is there ANY path >= BossHP", and graph is dense...
// Maybe greedy? No.
// fallback: Random DFS attempts or simple DFS if N^K small.
// I will implement a memoized DFS that tracks `visited` in bitmask if K is small?
// Or just standard DFS if States are many (BossHP reachable quickly).

long long BossHP;
int K, N_attacks;
vector<long long> attacks;

map<vector<long long>, long long> memo; // History -> Max additional damage
// This memo assumes independent subproblems, which is FALSE for Simple Path.
// But correct for Cycle Avoidance if we just assume "Infinite path = Win"?
// If we can cycle, we have Infinite damage -> Win.
// Ah! "Jika berulang -> immune". Means cycle = LOSE.
// So we CANNOT cycle.
// So we MUST finish before cycle.
// Max damage is bounded by N^K * MaxAttack.
// If BossHP > TotalPossible, IMPOSSIBLE.
// Total States ~ N^K.
// DFS to find path accumulating BossHP.

bool dfs(vector<long long> current_history, long long current_dmg, set<vector<long long>>& path_visited) {
    if (current_dmg >= BossHP) return true;
    
    // Heuristic: If remaining potential is low?
    
    for(long long dmg : attacks) {
        vector<long long> next_hist = current_history;
        if (next_hist.size() == K) next_hist.erase(next_hist.begin());
        next_hist.push_back(dmg);
        
        if (path_visited.find(next_hist) == path_visited.end()) {
            path_visited.insert(next_hist);
            if (dfs(next_hist, current_dmg + dmg, path_visited)) return true;
            path_visited.erase(next_hist);
            // This is full backtracking. Exponential.
        }
    }
    return false;
}

int main() {
    if (!(cin >> BossHP >> K >> N_attacks)) return 0;
    attacks.resize(N_attacks);
    for(int i=0; i<N_attacks; ++i) cin >> attacks[i];
    
    vector<long long> init_hist; // Empty at start?
    // "Mencatat damage terakhir K".
    // Initially, history is empty or padded?
    // Usually padded with 0s or empty.
    // If empty, first K moves fill it.
    // Transition: [a,b] -> [a,b,c] for K=3.
    // Only when size=K does it shift.
    // Unique states include size < K states?
    // Yes.
    
    set<vector<long long>> visited;
    visited.insert(init_hist);
    
    if (dfs(init_hist, 0, visited)) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
