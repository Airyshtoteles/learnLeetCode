#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int solve() {
    string s;
    if (!(cin >> s)) return 0;
    
    int n = s.length();
    if (n == 0) return 0;
    if (n == 1) return 0; // Removing 1 char leaves 0. Or maybe 1? "Kamu boleh menghapus satu karakter".
    // If n=1, remove 1 -> length 0.
    // If we don't remove? "Kamu boleh". Optional?
    // "Kamu boleh menghapus satu karakter".
    // Usually implies we can choose to remove 0 or 1.
    // But usually in these problems, we want to maximize score, so we check both.
    
    // L[i]: length of non-decreasing substring ending at i
    vector<int> L(n, 1);
    for (int i = 1; i < n; ++i) {
        if (s[i] >= s[i-1]) {
            L[i] = L[i-1] + 1;
        }
    }
    
    // R[i]: length of non-decreasing substring starting at i
    vector<int> R(n, 1);
    for (int i = n - 2; i >= 0; --i) {
        if (s[i] <= s[i+1]) {
            R[i] = R[i+1] + 1;
        }
    }
    
    int max_score = 0;
    // Case 0: No removal
    for (int x : L) max_score = max(max_score, x);
    
    // Case 1: Remove s[i]
    for (int i = 0; i < n; ++i) {
        // If we remove s[i], we might merge s[i-1] and s[i+1]
        int current = 0;
        if (i > 0) current += L[i-1]; // Left part
        if (i < n - 1) {
            // Check if mergeable
            if (i > 0 && s[i-1] <= s[i+1]) {
                current += R[i+1];
            } else {
                // Not mergeable, take max of left or right
                // Actually, if not mergeable, the new substring is either the one ending at i-1 or starting at i+1.
                // We already counted L[i-1] above.
                // But we should take max(L[i-1], R[i+1]) if not mergeable?
                // Wait. If we remove s[i], the sequence is ... s[i-1], s[i+1] ...
                // If s[i-1] <= s[i+1], we have a contiguous block of length L[i-1] + R[i+1].
                // If not, we have two blocks: one ending at i-1, one starting at i+1.
                // The score is the max length of a valid substring in the NEW string.
                // So it would be max(L[i-1], R[i+1]) (and other parts of string).
                // But since we iterate all i, we will cover all "cuts".
                // So we just need to check the merge at i.
                // The global max will be updated by other i's or the no-removal case.
                // Wait, if we remove s[i], we create a new string.
                // We want max valid substring in that new string.
                // The only *new* valid substring formed is by merging at i.
                // Existing valid substrings (not crossing i) are already covered by "No removal" case (or other removals).
                // So we only care about L[i-1] + R[i+1] if mergeable.
                // If not mergeable, we don't form a *longer* substring crossing the gap.
            }
        }
        // Wait, if we remove s[i], and don't merge, we might just have L[i-1] or R[i+1].
        // These lengths are <= max_score from "No removal" case?
        // Yes, because L[i-1] is a valid substring in original.
        // So we only need to update max_score if merge happens.
        
        if (i > 0 && i < n - 1 && s[i-1] <= s[i+1]) {
            max_score = max(max_score, L[i-1] + R[i+1]);
        }
    }
    
    // Also consider removing s[0] (score is R[1]) or s[n-1] (score is L[n-2]).
    // These are covered by "No removal" case?
    // R[1] is length of substring starting at 1. In original string, this is substring s[1...k].
    // This is valid in original. So covered.
    // So only merge matters.
    
    return max_score;
}

int main() {
    cout << solve() << endl;
    return 0;
}
