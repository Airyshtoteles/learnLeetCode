#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int main() {
    int n, D;
    if (cin >> n >> D) {
        if (n == 0) {
            cout << "0" << endl;
            return 0;
        }
        if (n == 1) {
            cout << "1" << endl;
            return 0;
        }
        
        vector<long long> pos(n);
        vector<long long> v(n);
        for (int i = 0; i < n; ++i) cin >> pos[i];
        for (int i = 0; i < n; ++i) cin >> v[i];

        // BFS with time steps
        queue<pair<int, int>> q; // (platform, time)
        set<pair<int, int>> visited;
        
        q.push({0, 0});
        visited.insert({0, 0});
        
        bool reached = false;
        
        // Limit time to avoid infinite loop
        while (!q.empty() && !reached) {
            auto [plat, t] = q.front();
            q.pop();
            
            if (t > 10000) continue; // Safety limit
            
            if (plat == n - 1) {
                reached = true;
                break;
            }
            
            // Try jumping to other platforms at time t
            long long curr_pos = pos[plat] + (long long)v[plat] * t;
            
            for (int next = 0; next < n; ++next) {
                if (next == plat) continue;
                
                long long next_pos = pos[next] + (long long)v[next] * t;
                
                if (abs(curr_pos - next_pos) <= D) {
                    if (visited.find({next, t}) == visited.end()) {
                        visited.insert({next, t});
                        q.push({next, t});
                    }
                }
            }
            
            // Try waiting
            if (visited.find({plat, t + 1}) == visited.end()) {
                visited.insert({plat, t + 1});
                q.push({plat, t + 1});
            }
        }
        
        cout << (reached ? "1" : "0") << endl;
    }
    return 0;
}
