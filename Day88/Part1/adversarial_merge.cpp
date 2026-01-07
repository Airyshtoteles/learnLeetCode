#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Problem: Boss With Adversarial Timeline Merge
// Boss can merge any two time intervals and take MIN damage.
// Infinite merges allowed.
// Worst case: Boss merges ALL attack intervals into one "Super Interval".
// Resulting effective damage per attack in that merged interval is min(All Attacks involved).
// If we have N attacks, and he merges them all, total damage = N * min(d).
// This assumes 'merging' preserves duration (counts).
// "Menggabungkan dua interval ... mengambil damage minimum".
// If merging [t1] and [t2] (both length 1) results in [t_new] (length 1) with d = min(d1, d2)? 
// Or does it result in length 2 with average?
// Usually "Merge" implies union. 
// If "taking damage minimum" refers to the *rate*, then Sum = Length * MinRate.
// Robust Condition: N * min(D) >= H.
// This is the only safe lower bound if he can merge everything.

int main() {
    long long H;
    int N;
    if (!(cin >> H >> N)) return 0;

    vector<long long> D(N);
    long long min_d = 1e18;
    for (int i = 0; i < N; ++i) {
        cin >> D[i];
        if (D[i] < min_d) min_d = D[i];
    }

    if (min_d * N >= H) {
        cout << "Possible" << endl;
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
