#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

// State: vector<int> hp
// BFS to find min turns

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> hp(n);
    for (int i = 0; i < n; ++i) cin >> hp[i];

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    // Check if already dead
    bool all_dead = true;
    for (int h : hp) if (h > 0) all_dead = false;
    if (all_dead) {
        cout << 0 << endl;
        return 0;
    }

    queue<vector<int>> q;
    q.push(hp);
    
    map<vector<int>, int> dist;
    dist[hp] = 0;

    while (!q.empty()) {
        vector<int> curr = q.front();
        q.pop();

        int d = dist[curr];

        // Try attacking each alive enemy
        for (int target = 0; target < n; ++target) {
            if (curr[target] <= 0) continue; // Only attack alive enemies

            vector<int> next_hp = curr;
            
            // Attack damage
            if (next_hp[target] > 0) {
                next_hp[target] -= 1;
            }
            
            // Poison damage
            bool any_alive = false;
            for (int i = 0; i < n; ++i) {
                if (next_hp[i] > 0) {
                    next_hp[i] -= abs(i - target);
                    if (next_hp[i] > 0) any_alive = true;
                }
            }
            
            if (!any_alive) {
                cout << d + 1 << endl;
                return 0;
            }
            
            if (dist.find(next_hp) == dist.end()) {
                dist[next_hp] = d + 1;
                q.push(next_hp);
            }
        }
    }

    return 0;
}
