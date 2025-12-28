#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve() {
    int A, n;
    if (!(cin >> A >> n)) return 0;
    
    vector<int> r(n);
    for (int i = 0; i < n; ++i) {
        cin >> r[i];
    }
    
    // Heuristic: Sort descending.
    // Logic: Dividing by large number reduces value significantly.
    // The +1 adds back a bit.
    // If we divide by small number (e.g. 1), value increases (+1).
    // We want to keep value high.
    // If we have r=1, x -> x/1 + 1 = x+1. We want to do this as much as possible?
    // But each recipe used once.
    // If we do x+1 at the end, we add 1.
    // If we do x+1 at start, (x+1)/d + 1 = x/d + 1/d + 1.
    // Since 1/d < 1, floor((x+1)/d) is same as floor(x/d) unless x%d == d-1.
    // So doing +1 early might trigger a higher floor.
    // But doing +1 late definitely adds 1.
    // It seems r=1 should be last?
    // What about r=2 vs r=10?
    // 100 -> 2 -> 51 -> 10 -> 6.
    // 100 -> 10 -> 11 -> 2 -> 6.
    // Tie.
    // Let's try brute force for small N?
    // If N is small (e.g. <= 8), we can permute.
    // If N is large, we need heuristic.
    // Given "Day 78", maybe N is small?
    // Or maybe sort descending is correct.
    // Let's assume sort descending (largest first).
    // Wait, if r=1 should be last, that means smallest last.
    // So sort descending (largest to smallest).
    
    sort(r.rbegin(), r.rend());
    
    int current = A;
    for (int val : r) {
        if (val == 0) continue; // Avoid div by zero
        current = (current / val) + 1;
    }
    
    return current;
}

int main() {
    cout << solve() << endl;
    return 0;
}
