#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }
        vector<int> d(n);
        for (int i = 0; i < n; ++i) cin >> d[i];
        vector<int> w(n);
        for (int i = 0; i < n; ++i) cin >> w[i];

        // Strategy: Sort by damage descending and pair them up
        // The highest damage should be critical
        sort(d.rbegin(), d.rend());

        long long total = 0;
        for (int i = 0; i < n; i += 2) {
            if (i + 1 < n) {
                // Pair i and i+1, make i+1 critical
                total += d[i] + 2LL * d[i + 1];
            } else {
                // Odd one out, no critical
                total += d[i];
            }
        }

        cout << total << endl;
    }
    return 0;
}
