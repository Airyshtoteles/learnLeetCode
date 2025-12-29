#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Function to check if it's possible to achieve a minimum mana level of 'target'
// with at most 'k' transfers.
bool can_achieve(long long target, long long k, const vector<int>& mana) {
    long long needed = 0;
    long long available = 0;

    for (int m : mana) {
        if (m < target) {
            needed += (target - m);
        } else {
            available += (m - target);
        }
    }

    // We need enough available mana to cover the need.
    // And the total amount moved (needed) must not exceed k.
    return needed <= available && needed <= k;
}

int main() {
    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    vector<int> mana(n);
    long long max_val = 0;
    for (int i = 0; i < n; ++i) {
        cin >> mana[i];
        if (mana[i] > max_val) max_val = mana[i];
    }

    long long low = 0;
    long long high = max_val + k + 1; // Upper bound estimation
    long long ans = 0;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (can_achieve(mid, k, mana)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << ans << endl;

    return 0;
}
