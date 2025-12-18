#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n;
    long long H, k;
    if (cin >> n >> H >> k) {
        vector<long long> d(n);
        for (int i = 0; i < n; ++i) cin >> d[i];

        sort(d.rbegin(), d.rend());

        long long current_damage = 0;
        long long multiplier = 1;
        int attacks = 0;

        for (long long dmg : d) {
            if (current_damage >= H) break;

            long long damage_dealt = dmg * multiplier;
            long long old_damage = current_damage;
            current_damage += damage_dealt;
            attacks++;

            // Check thresholds passed
            // Thresholds are k, 2k, 3k...
            // Number of thresholds passed by old_damage: old_damage / k
            // Number of thresholds passed by current_damage: current_damage / k
            
            long long old_thresholds = old_damage / k;
            long long new_thresholds = current_damage / k;
            
            long long diff = new_thresholds - old_thresholds;
            
            for (int i = 0; i < diff; ++i) {
                multiplier *= 2;
            }
        }

        if (current_damage < H) {
            // If we run out of attacks, assume we can't win or just output what we have.
            // Problem implies we need to find min attacks to win.
            // If we can't win with all attacks, maybe output -1 or n.
            // Assuming input guarantees win or we just output n.
            cout << n << endl; 
        } else {
            cout << attacks << endl;
        }
    }
    return 0;
}
