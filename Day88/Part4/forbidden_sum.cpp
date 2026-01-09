#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

// Problem: Infinite Damage With Forbidden Sums
// Damage set D.
// Forbidden set F.
// Goal: Reach sum >= H (very large).
// If we can reach any sum S > max(F), and we have positive damage, we can go to infinity.
// So target is essentially: Can we reach any S > max(F) without touching F?
// Range of interest: [0, max(F) + max(D)].
// Beyond this range, we are "safe" from F (assuming F is finite and bounded).
// "Set terlarang F" usually implies specific values.
// If F contains modulo residues, strategy changes. But "H large" usually pairs with "Escape F".
// BFS on 0..Limit.

int main() {
    long long H;
    int N_D, N_F;
    if (!(cin >> H >> N_D >> N_F)) return 0;

    vector<int> D(N_D);
    for (int i = 0; i < N_D; ++i) cin >> D[i];

    set<long long> F;
    long long max_F = 0;
    for (int i = 0; i < N_F; ++i) {
        long long val;
        cin >> val;
        F.insert(val);
        if (val > max_F) max_F = val;
    }

    // Optimization: If max_F is huge, we can't BFS to max_F.
    // But typically in CP problems, Forbidden set is sparse or small range.
    // If F large, we might need modulo BFS map.
    // Assuming F values are within reasonable reasonable BFS range (e.g. < 1M).
    // If not, "Reachability with forbidden set" is hard (Frobenius number with holes).
    // Given "Day 88", likely bounded F.
    
    long long limit = max_F + 2000; // Buffer
    queue<long long> q;
    set<long long> visited;
    
    q.push(0);
    visited.insert(0);

    while (!q.empty()) {
        long long curr = q.front();
        q.pop();

        if (curr >= H) { // Direct win
            cout << "Possible" << endl;
            return 0;
        }
        if (curr > max_F) { // Escaped the minefield
            // Check if we can proceed indefinitely?
            // If exists d > 0, yes.
            bool has_pos = false;
            for(int d : D) if(d > 0) has_pos = true;
            if (has_pos) {
                 cout << "Possible" << endl;
                 return 0;
            }
        }

        for (int d : D) {
            long long next_val = curr + d;
            if (next_val < 0) continue; // Assume non-negative total? Or just numbers.
            
            // Optimization to prevent infinite loop if all D=0
            if (visited.count(next_val)) continue;

            if (F.count(next_val)) continue;
            
            // If next_val is way beyond max_F, treat as "Win State" essentially?
            // Just push to queue, next iteration catches "curr > max_F".
            
            // Don't expand too far beyond needed check
            if (next_val > limit && next_val < H) {
                // If we are strictly above max_F, and have positive d, we win.
                // We handled this check above.
                // So if we reach here, we add to queue to trigger check next time.
                // But limit visited size.
                // Actually, just pushing is safe if we don't explore excessively.
                // The limit ensures we don't BFS to infinity if H is 1e18.
                // We clip state space to Limit.
                // If node > Limit, it is essentially "Safe Zone".
                // But we need to ensure we don't re-queue "Safe Zone" states forever.
                // Handled by visited.
            }
            
            if (next_val <= limit || next_val >= H) {
                 visited.insert(next_val);
                 q.push(next_val);
            }
        }
    }

    cout << "Impossible" << endl;

    return 0;
}
