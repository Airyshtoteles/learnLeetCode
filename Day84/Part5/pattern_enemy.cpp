#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Problem: Pattern-Learning Enemy Swarm.
// Stream of damage d[i].
// If a substring repeats, damage becomes 0.
// We want to maximize total damage before the first 0.
// This implies we stop at the first index 'i' where the suffix d[0...i] contains a repeated substring?
// Or simply: The enemy learns patterns. If a pattern appears that has appeared before, it blocks.
// Interpretation: We stop at the first element that completes a repeated substring.
// Since any single element is a substring of length 1, if we repeat a single element, we stop.
// So the sequence must consist of unique elements.
// If the problem implies "non-trivial" patterns (length > 1), it would say so.
// "Panjang pola bebas" means length is free (can be 1).
// So, we just sum up elements until we see a duplicate.

int main() {
    int N;
    if (!(cin >> N)) return 0;

    vector<int> D(N);
    for (int i = 0; i < N; ++i) cin >> D[i];

    set<int> seen;
    long long total_damage = 0;

    for (int x : D) {
        if (seen.count(x)) {
            break;
        }
        seen.insert(x);
        total_damage += x;
    }

    cout << total_damage << endl;

    return 0;
}
