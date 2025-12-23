#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        vector<int> d(n);
        for (int i = 0; i < n; ++i) {
            cin >> d[i];
        }
        int A, X;
        cin >> A >> X;

        if (A <= 0) {
            cout << "1" << endl;
            return 0;
        }
        if (X <= 0) {
            cout << "0" << endl;
            return 0;
        }

        // Sort descending
        sort(d.rbegin(), d.rend());

        // We can use up to X attacks.
        // We should use the largest available damages.
        // If we use k attacks (1 <= k <= min(n, X)):
        // The best strategy is to use the largest k damages.
        // One of them can be the "finisher" (full damage), others are halved (floor).
        // To maximize total damage, the finisher should be the one with the largest "ceiling half" (x - floor(x/2)).
        // Since d is sorted descending, d[0] usually has the largest ceiling half (or equal).
        // So we sum: d[0] (full) + floor(d[1]/2) + ... + floor(d[k-1]/2).
        
        // Actually, we can just check the max possible damage with X attacks.
        // Max damage = d[0] + sum(floor(d[i]/2) for i in 1..min(n, X)-1).
        
        long long total_damage = 0;
        int count = min(n, X);
        
        if (count > 0) {
            total_damage += d[0];
            for (int i = 1; i < count; ++i) {
                total_damage += d[i] / 2;
            }
        }

        if (total_damage >= A) {
            cout << "1" << endl;
        } else {
            cout << "0" << endl;
        }
    }
    return 0;
}
