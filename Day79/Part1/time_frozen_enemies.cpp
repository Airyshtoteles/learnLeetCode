#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Input format:
// n T D
// spawn[0..n-1]
// hp[0..n-1]
// Output: maximum number of enemies killed during a single freeze

long long solve() {
    int n; long long T, D;
    if (!(cin >> n >> T >> D)) return 0;
    vector<long long> spawn(n), hp(n);
    for (int i = 0; i < n; ++i) cin >> spawn[i];
    for (int i = 0; i < n; ++i) cin >> hp[i];

    long long capacity = T * D; // total damage we can deal during freeze

    // We may activate freeze at any time; best is after all are spawned.
    // Choose the smallest-HP enemies to maximize count within capacity.
    sort(hp.begin(), hp.end());

    long long sum = 0; long long cnt = 0;
    for (long long h : hp) {
        if (sum + h <= capacity) {
            sum += h; cnt++;
        } else break;
    }
    return cnt;
}

int main() {
    cout << solve() << endl;
    return 0;
}
