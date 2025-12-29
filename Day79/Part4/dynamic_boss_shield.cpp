#include <iostream>

using namespace std;

// Input: H k
// Each attack triggers k seconds of shield with zero damage.
// Optimal: wait k seconds between attacks. Total time = (H-1) * k.

long long solve() {
    long long H, k; if (!(cin >> H >> k)) return 0;
    if (H <= 0) return 0;
    if (H == 1) return 0; // final strike at time 0
    return (H - 1) * k;
}

int main() {
    cout << solve() << endl;
    return 0;
}
