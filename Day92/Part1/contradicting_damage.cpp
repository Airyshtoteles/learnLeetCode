#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

// Problem 1: Boss With Self-Contradicting Damage
// Condition: Prefix sums must be unique until sum >= H.
// Input: H, N (number of available damage types), D vector.
// Strategy: BFS on 'current_sum' to find if H is reachable without visiting any sum twice.
// Since valid damage values can be negative, loops are possible.
// BFS with 'visited' set naturally avoids cycles and repeated states.
// We seek ANY path to >= H.

int main() {
    long long H;
    int N;
    if (!(cin >> H >> N)) return 0;
    
    vector<long long> D(N);
    for(int i=0; i<N; ++i) {
        cin >> D[i];
    }
    
    // BFS State: current_sum
    queue<long long> q;
    set<long long> visited;
    
    // Start at 0?
    // "Prefix damage". First attack creates prefix.
    // Initial sum is 0 (before attacks).
    // Usually prefix doesn't include 0-th empty prefix?
    // "Jika dua prefix berbeda punya total damage sama".
    // Does empty prefix (0) count? Usually yes.
    // If we return to 0, satisfied?
    // Assuming standard: We start at 0. 0 is in history.
    
    q.push(0);
    visited.insert(0);
    
    bool possible = false;
    
    // Limit iterations to prevent TLE if H is unreachable and space is huge
    int limit = 200000; 
    
    while(!q.empty()) {
        if (limit-- < 0) break;
        long long curr = q.front(); q.pop();
        
        if (curr >= H) {
            possible = true;
            break;
        }
        
        for (long long d : D) {
            long long next_val = curr + d;
            if (visited.find(next_val) == visited.end()) {
                visited.insert(next_val);
                q.push(next_val);
                if (next_val >= H) {
                    possible = true;
                    goto end_loop;
                }
            }
        }
    }
    
    end_loop:;
    
    if (possible) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
