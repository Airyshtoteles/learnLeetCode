#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Day 8 — Minimum Number of Taps to Open to Water a Garden (#1326)
// Greedy (Jump Game II style): build max reach from each left boundary and sweep.
// Time: O(n), Space: O(n)
int minTaps(int n, const vector<int>& ranges) {
    if (n == 0) return 0;
    vector<int> maxReach(n + 1, 0);
    for (int i = 0; i <= n; ++i) {
        int left = max(0, i - ranges[i]);
        int right = min(n, i + ranges[i]);
        maxReach[left] = max(maxReach[left], right);
    }

    int taps = 0;
    int currEnd = 0;
    int farthest = 0;
    for (int i = 0; i < n; ++i) { // cover up to n
        farthest = max(farthest, maxReach[i]);
        if (i == currEnd) {
            if (farthest == currEnd) return -1; // stuck
            ++taps;
            currEnd = farthest;
            if (currEnd >= n) break;
        }
    }
    return (currEnd >= n) ? taps : -1;
}

int main() {
    cout << minTaps(5, {3,4,1,1,0,0}) << "\n"; // 1

    // Basic checks
    if (minTaps(0, {0}) != 0) return 1;
    if (minTaps(3, {0,0,0,0}) != -1) return 1;
    if (minTaps(3, {3,0,0,0}) != 1) return 1;
    if (minTaps(7, {1,2,1,0,2,1,0,1}) != 3) return 1;

    return 0;
}