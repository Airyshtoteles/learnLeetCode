#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Problem: Infinite Damage With Memory Penalty
// Damage d[i] multiplied by i.
// If prefix sum repeats, next damage is 0.
// Maximize total damage.
// Strategy: Sort positive values ascending.
// If there are zeros, they cause immediate repeat of sum.
// So we can include at most one zero?
// If we include a zero at index k, S_k = S_{k-1}. Repeat!
// So we cannot include ANY zeros if we want to continue.
// But maybe we can include one zero at the very end?
// If we include 0 at end, sum repeats, next is 0. Game over.
// But we already added the 0. Total damage doesn't increase.
// So zeros are useless.
// Negative values? "Damage" usually positive.
// Assuming non-negative.
// Filter out 0s. Sort rest ascending.
// Calculate sum i * d[i].

int main() {
    int N;
    if (!(cin >> N)) return 0;

    vector<long long> D;
    for (int i = 0; i < N; ++i) {
        long long val;
        cin >> val;
        if (val > 0) {
            D.push_back(val);
        }
    }

    sort(D.begin(), D.end());

    long long total_damage = 0;
    for (int i = 0; i < D.size(); ++i) {
        total_damage += (long long)(i + 1) * D[i];
    }

    cout << total_damage << endl;

    return 0;
}
