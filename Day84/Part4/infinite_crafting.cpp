#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Problem: Infinite Crafting With Degradation.
// Start R.
// Op i: x -> floor(x / a[i]) + b[i].
// Max D steps.
// Maximize final value.
// Assuming D is small enough for DP (e.g. <= 1000).
// If D is large, we need a different approach, but given "Day 84", DP is likely.
// State: dp[steps] = max_value.
// Since we only care about the MAX value at each step, we don't need full DP table if we just track current max.
// Wait, is it possible that a smaller value now leads to a larger value later?
// Example: Op A: x -> x/2 + 100. Op B: x -> x + 10.
// Start 0.
// Step 1: A->100, B->10. Max 100.
// Step 2: From 100: A->150, B->110.
// From 10: A->105, B->20.
// It seems monotonic? If x > y, then floor(x/a) + b >= floor(y/a) + b.
// Yes, f(x) is non-decreasing.
// So if we have a larger x, we can always get a result >= result from smaller x.
// So we only need to track the maximum value at each step.
// Greedy strategy: At each step, apply the operation that yields the maximum result.

struct Op {
    long long a, b;
};

int main() {
    long long R;
    int D, N;
    if (!(cin >> R >> D >> N)) return 0;

    vector<Op> ops(N);
    for (int i = 0; i < N; ++i) {
        cin >> ops[i].a >> ops[i].b;
    }

    long long current_val = R;
    for (int d = 0; d < D; ++d) {
        long long next_max = -1;
        for (const auto& op : ops) {
            long long val = 0;
            if (op.a == 0) {
                // Avoid division by zero, though problem says floor(x/a). Usually a >= 1.
                // If a=0, undefined. Assume a >= 1.
                val = current_val + op.b; // Treat as x/1? No, error.
            } else {
                val = (current_val / op.a) + op.b;
            }
            if (val > next_max) {
                next_max = val;
            }
        }
        current_val = next_max;
    }

    cout << current_val << endl;

    return 0;
}
