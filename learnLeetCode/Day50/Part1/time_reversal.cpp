#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

long long calculate_damage(const vector<int>& monster) {
    long long damage = 0;
    for (size_t i = 0; i < monster.size(); ++i) {
        damage += (long long)(i + 1) * monster[i];
    }
    return damage;
}

long long solve_time_reversal(vector<int> monster, int k) {
    int n = monster.size();
    
    for (int step = 0; step < k; ++step) {
        // Heuristic: Find best swap among top candidates
        vector<pair<int, int>> indexed_monster(n);
        for(int i=0; i<n; ++i) indexed_monster[i] = {monster[i], i};
        
        sort(indexed_monster.begin(), indexed_monster.end());
        
        // Smallest values (should be at right, currently at left?)
        // Largest values (should be at left, currently at right?)
        
        long long max_gain = -1;
        int best_l = -1, best_r = -1;
        
        int check_limit = min(n, 50);
        
        for (int i = 0; i < check_limit; ++i) { // Smallest values
            for (int j = 0; j < check_limit; ++j) { // Largest values
                int idx_s = indexed_monster[i].second;
                int val_s = indexed_monster[i].first;
                
                int idx_l = indexed_monster[n - 1 - j].second;
                int val_l = indexed_monster[n - 1 - j].first;
                
                if (idx_s < idx_l) {
                    // Potential reversal [idx_s, idx_l]
                    // Heuristic gain: (val_l - val_s) * (idx_l - idx_s)
                    long long gain = (long long)(val_l - val_s) * (idx_l - idx_s);
                    if (gain > max_gain) {
                        max_gain = gain;
                        best_l = idx_s;
                        best_r = idx_l;
                    }
                }
            }
        }
        
        if (best_l != -1) {
            reverse(monster.begin() + best_l, monster.begin() + best_r + 1);
        } else {
            break;
        }
    }
    
    return calculate_damage(monster);
}

int main() {
    vector<int> monster = {1, 2, 3, 4, 5};
    int k = 1;
    cout << solve_time_reversal(monster, k) << endl;
    return 0;
}
