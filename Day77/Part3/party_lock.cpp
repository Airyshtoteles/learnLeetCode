#include <iostream>
#include <vector>

using namespace std;

int solve() {
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> f(n);
    for (int i = 0; i < n; ++i) {
        cin >> f[i];
    }
    
    if (n == 0) return 0;
    
    // We want to remove minimum elements such that no two adjacent elements are equal.
    // This is equivalent to keeping one element from each run of identical elements.
    // Example: A A B B B A -> Runs: (A, A), (B, B, B), (A).
    // We keep 1 from first run, 1 from second, 1 from third.
    // Total kept = 3. Removed = 6 - 3 = 3.
    // Wait, is it always optimal to keep 1?
    // Yes, because if we keep 2 from a run, they will be adjacent (since we removed everything between them).
    // So we can keep at most 1 from each run.
    // Can we always keep 1? Yes.
    // So answer is sum(run_length - 1) for all runs.
    // Or simply: count indices i where f[i] == f[i-1].
    
    int removals = 0;
    for (int i = 1; i < n; ++i) {
        if (f[i] == f[i-1]) {
            removals++;
        }
    }
    
    return removals;
}

int main() {
    cout << solve() << endl;
    return 0;
}
