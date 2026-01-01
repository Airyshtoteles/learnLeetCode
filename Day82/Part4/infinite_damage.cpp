#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

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

    // Greedy: Use largest damage values first.
    // Total damage = d[0]*1 + d[1]*2 + d[2]*3 + ...
    // We want to minimize the number of attacks.

    long long total = 0;
    long long attacks = 0;

    for (int i = 0; i < n; ++i) {
        attacks++;
        total += d[i] * attacks;
        if (total >= H) {
            cout << attacks << endl;
            return 0;
        }
    }

    // If we've used all available damages and still not enough,
    // we can repeat a damage value.
    // If we use d[0] again, it gets multiplied by (attacks + 1).
    // Subsequent uses get higher multipliers.

    // We need total >= H.
    // We can keep using d[0] (the max damage).

    long long remaining = H - total;
    long long damage = d[0];

    while (remaining > 0) {
        attacks++;
        total += damage * attacks;
        remaining = H - total;
    }

    cout << attacks << endl;

    return 0;
}
