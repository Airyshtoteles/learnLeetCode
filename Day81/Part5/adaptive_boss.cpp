#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long long H;
    int n;
    if (!(cin >> H >> n)) return 0;

    vector<long long> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    sort(d.rbegin(), d.rend());

    if (n == 0) {
        cout << -1 << endl;
        return 0;
    }

    if (n == 1) {
        // Only one attack type.
        // Pattern: A, A, 0, A, A, 0...
        // Damage per 3 attacks: 2 * d[0].
        long long cycle_dmg = 2 * d[0];
        long long cycles = H / cycle_dmg;
        long long rem = H % cycle_dmg;
        long long attacks = cycles * 3;

        if (rem > 0) {
            attacks++; // A
            rem -= d[0];
        }
        if (rem > 0) {
            attacks++; // A
            rem -= d[0];
        }
        // If rem still > 0, we need the 0-damage turn and then more As.
        // But rem <= 2*d[0] - d[0] - d[0] = 0. So we are done.
        
        cout << attacks << endl;
    } else {
        // We have at least 2 attacks.
        // Alternate max1 and max2.
        // Cycle: max1, max2.
        long long max1 = d[0];
        long long max2 = d[1];
        long long cycle_dmg = max1 + max2;
        
        long long cycles = H / cycle_dmg;
        long long rem = H % cycle_dmg;
        long long attacks = cycles * 2;
        
        if (rem > 0) {
            attacks++; // max1
            rem -= max1;
        }
        if (rem > 0) {
            attacks++; // max2
            rem -= max2;
        }
        
        cout << attacks << endl;
    }

    return 0;
}
