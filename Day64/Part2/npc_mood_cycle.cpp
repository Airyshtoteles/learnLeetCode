#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    // Read until EOF or valid input
    if (!(cin >> n)) return 0;

    vector<int> mood(n);
    for (int i = 0; i < n; ++i) cin >> mood[i];

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    while (true) {
        if (mood.empty()) break;

        // Shift right 1 (circular)
        // [1, 2, 2, 1] -> [1, 1, 2, 2]
        // Last element moves to front
        int last = mood.back();
        mood.pop_back();
        mood.insert(mood.begin(), last);

        // Merge adjacent identical
        vector<int> next_mood;
        bool merged = false;
        
        for (size_t i = 0; i < mood.size(); ) {
            if (i + 1 < mood.size() && mood[i] == mood[i+1]) {
                next_mood.push_back(mood[i]); // Merge two into one
                merged = true;
                i += 2;
            } else {
                next_mood.push_back(mood[i]);
                i++;
            }
        }

        if (!merged) {
            // No merge happened, stop
            // But wait, did we shift? Yes.
            // "Process stops when no merge happens".
            // Does it mean we revert the shift?
            // "Every second: Shift... If two identical... merge... Process stops when no merge".
            // This implies the shift happens, then we check for merge.
            // If no merge, we stop. The state is the shifted state?
            // Or the state before shift?
            // Usually "stops" means the loop terminates. The result is the current state.
            // Example: [1,2,2,1] -> Shift [1,1,2,2] -> Merge [1,2].
            // Next: Shift [2,1] -> Merge? No. Stop. Result [2,1] size 2.
            // Output 2.
            // So yes, the state is the one after shift (and failed merge check).
            break;
        }
        mood = next_mood;
    }

    cout << mood.size() << endl;

    return 0;
}
