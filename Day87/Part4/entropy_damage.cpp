#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Problem: Infinite Damage With Entropy Limit
// Damage sequence can be infinite.
// Entropy <= E.
// Damage D[i] available.
// "Damage ke-i dikalikan i" -> i-th term in sequence is scaled by index i.
// Meaning total damage grows quadratically/linearly if terms are > 0.
// If we can repeat a positive damage value, H is reachable.
// Entropy of a sequence of identical symbols is 0.
// So if max(D) > 0, we can pick that damage repeatedly.
// Sequence: d, d, d, ....
// Terms: d*1, d*2, d*3 ... Sum diverges to +inf.
// Entropy = 0 <= E.
// Condition: Exists d in D such that d > 0.
// If all d <= 0, sum decreases or stays 0. Impossible for positive H.

int main() {
    long long H;
    int N;
    if (!(cin >> H >> N)) return 0;
    
    // Read E (entropy limit) - not strictly needed for logic if E >= 0
    double E;
    cin >> E;

    vector<int> D(N);
    int max_d = -1e9;
    for (int i = 0; i < N; ++i) {
        cin >> D[i];
        if (D[i] > max_d) max_d = D[i];
    }

    if (max_d > 0) {
        cout << "Possible" << endl;
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
