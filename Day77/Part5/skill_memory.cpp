#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int solve() {
    int n, K;
    if (!(cin >> n >> K)) return 0;
    
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    
    // We can reorder skills.
    // We want to minimize total cooldown.
    // Cooldown is 1 if skill NOT in memory, 0 if IN memory.
    // Memory size K.
    // Strategy: Group identical skills together.
    // E.g. A A A B B B C C C.
    // First A: Cost 1. Memory [A].
    // Next A: Cost 0. Memory [A].
    // ...
    // First B: Cost 1. Memory [A, B] (if K>=2) or [B] (if K=1).
    // Next B: Cost 0.
    // ...
    // Total cost = Number of unique skills.
    // Is it possible to do better?
    // No, because the first time we use a skill type, it CANNOT be in memory (unless we used it before, but we grouped them).
    // If we split groups: A ... A.
    // First A: Cost 1.
    // Second group of A: Might cost 1 if A was evicted.
    // So splitting groups can only increase cost.
    // Thus, grouping is optimal.
    // Cost = Number of unique elements.
    
    sort(s.begin(), s.end());
    int unique_count = (n > 0) ? 1 : 0;
    for (int i = 1; i < n; ++i) {
        if (s[i] != s[i-1]) {
            unique_count++;
        }
    }
    
    return unique_count;
}

int main() {
    cout << solve() << endl;
    return 0;
}
