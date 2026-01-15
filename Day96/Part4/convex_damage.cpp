#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Problem 4: Infinite Damage / Monotonic Average
// Logic:
// We need Sequence d_1, d_2... such that Avg_k >= Avg_{k-1}.
// This is satisfied if we pick d_k >= Avg_{k-1}.
// If we simply pick Max(D) every time:
// Avg_1 = M.
// Avg_2 = (M+M)/2 = M. Ratio const. Valid.
// Loop forever. Total damage -> Inf.
// So impossible only if Max(D) <= 0 (and H > 0).
// Assuming D has only positive integers usually in "Damage" problems.
// If D has negative?
// If Max(D) > 0, YES.
// If Max(D) <= 0, then we can never deal positive damage. NO.
// Unless H <= 0?
//
// Simple Check.

int main() {
    long long H;
    int N;
    if (!(cin >> H >> N)) return 0;
    long long max_d = -1e18;
    for(int i=0; i<N; ++i){
        long long val;
        cin >> val;
        if(val > max_d) max_d = val;
    }
    
    if (H <= 0) cout << "YES" << endl;
    else if (max_d > 0) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
