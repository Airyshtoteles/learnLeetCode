#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

// Problem: Economy With Adversarial Precision Loss
// Reach T starting from S using operations (+1, *2).
// Adversary adds error delta per step.
// Condition: Total Error < Limit.
// Worst case error accumulation = (Steps) * Delta.
// Thus we need Shortest Path Length <= Floor((Limit - epsilon)/Delta).
// BFS to find min steps.

int main() {
    long long S, T;
    double Limit, Delta;
    // Input format: S T Limit Delta
    if (!(cin >> S >> T >> Limit >> Delta)) return 0;

    if (S == T) {
        cout << "YES" << endl;
        return 0;
    }
    
    // Max Steps allowed (strictly less than Limit/Delta? Limit implies >= Limit lose?)
    // "Accumulated error >= E -> lose".
    // So Steps * Delta < Limit.
    // Max Steps = ceil(Limit/Delta) - 1?
    // Let's use floating point check or integer conversion if precise.
    // Usually Limit is small enough.
    
    long long max_steps = (long long)(Limit / Delta);
    if (max_steps * Delta >= Limit) max_steps--; 
    // If exact division, strict inequality means -1.
    // E.g. Limit 1.0, Delta 0.1 -> 10 steps -> Error 1.0 -> Lose? Yes. So 9 steps.
    
    if (max_steps < 0) {
        cout << "NO" << endl;
        return 0;
    }
    
    // BFS from S to T
    // Ops: x+1, x*2.
    // Optimizations:
    // If x > T (and no subtract), stop branch.
    // Visited set.

    queue<pair<long long, int>> q;
    q.push({S, 0});
    
    map<long long, int> dist;
    dist[S] = 0;
    
    bool possible = false;
    
    while (!q.empty()) {
        auto [u, d] = q.front();
        q.pop();
        
        if (u == T) {
            if (d <= max_steps) possible = true;
            break; // BFS guarantees finding shortest first
        }
        
        if (d >= max_steps) continue;
        
        // Next ops
        long long next_vals[] = {u + 1, u * 2};
        
        for (long long v : next_vals) {
            if (v <= T + 1) { // Heuristic bound? If target is T, and we go way past T...
                // If T is reachable via *2, we might overshoot?
                // But generally shortest path won't overshoot massively unless subtract exists.
                // Assuming only increasing ops for now as per "Economy growth".
                // If subtract allowed, T+something is valid.
                // Assuming only {+1, *2}.
                if (v <= T + 2) { // Just a bit over T in case we need to hit exactly? No, if >T we can't go down.
                     if (dist.find(v) == dist.end()) {
                         dist[v] = d + 1;
                         q.push({v, d + 1});
                     }
                }
            }
        }
    }
    
    if (possible) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
