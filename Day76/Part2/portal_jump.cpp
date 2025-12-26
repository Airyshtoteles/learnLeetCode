#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

bool solve() {
    int n;
    if (!(cin >> n)) return false;
    
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    
    if (n == 0) return false; // Should not happen based on constraints usually
    if (n == 1) return true; // Start 0, Target 0. Already there.
    
    vector<int> cycle_id(n, -1);
    int current_cycle = 0;
    
    for (int i = 0; i < n; ++i) {
        if (cycle_id[i] == -1) {
            int curr = i;
            while (cycle_id[curr] == -1) {
                cycle_id[curr] = current_cycle;
                curr = p[curr];
            }
            current_cycle++;
        }
    }
    
    if (cycle_id[0] == cycle_id[n-1]) return true;
    
    int start_cycle = cycle_id[0];
    int target_cycle = cycle_id[n-1];
    
    for (int u = 0; u < n; ++u) {
        if (cycle_id[u] == start_cycle) {
            // Try to break p[u] -> p[u] and make p[u] -> u+1
            // We need u+1 to be in target_cycle
            if (u + 1 < n) {
                if (cycle_id[u+1] == target_cycle) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

int main() {
    cout << (solve() ? "true" : "false") << endl;
    return 0;
}
