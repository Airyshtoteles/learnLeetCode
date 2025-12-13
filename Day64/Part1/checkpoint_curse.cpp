#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> curse(n);
    for (int i = 0; i < n; ++i) cin >> curse[i];

    // dp[i] = max cumulative curse at checkpoint i
    // Initialize with a very small number
    vector<long long> dp(n, -1e18);

    // Starting point
    // Assuming we start at 0. Does curse[0] apply?
    // "Start from checkpoint 0". Usually means we land on 0.
    // If curse[0] < 0, can we start?
    // "Respawn to checkpoint last visited with total non-negative".
    // This implies we need non-negative to stay.
    // Let's assume initial state is 0 before entering 0?
    // Or we start at 0 with curse[0].
    // If curse[0] < 0, we might not be able to start.
    // But let's assume we can always start, but maybe we can't proceed if sum < 0.
    // Actually, the problem says "If total cumulative curse becomes negative... respawn".
    // So at any point i, sum must be >= 0.
    
    if (curse[0] >= 0) {
        dp[0] = curse[0];
    } else {
        // If start is negative, we can't even exist there?
        // Or maybe we start with 0 and add curse[0].
        // If result < 0, we respawn... where?
        // "Respawn to checkpoint last visited...".
        // If 0 is the first, we can't respawn.
        // So if curse[0] < 0, impossible.
        cout << "false" << endl;
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        if (dp[i] < 0) continue; // Unreachable or invalid

        // Try moving to i+1
        if (i + 1 < n) {
            long long next_val = dp[i] + curse[i+1];
            if (next_val >= 0) {
                dp[i+1] = max(dp[i+1], next_val);
            }
        }

        // Try moving to i+2
        if (i + 2 < n) {
            long long next_val = dp[i] + curse[i+2];
            if (next_val >= 0) {
                dp[i+2] = max(dp[i+2], next_val);
            }
        }
    }

    if (dp[n-1] >= 0) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}
