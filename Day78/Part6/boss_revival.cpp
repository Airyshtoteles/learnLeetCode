#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <bitset>

using namespace std;

// Max possible sum for bitset.
// If H is large, this approach fails.
// But usually H is reasonable.
// Let's assume H <= 10000 or so.
// If H is huge, we need another approach (meet-in-the-middle or greedy).
// Given "Day 78", maybe H is small.
// Or maybe N is small.
// If N <= 20, we can brute force.
// If N is large, H is usually small.
// I'll use bitset<200000> to be safe for medium H.
// If H > 200000, this might fail or TLE.
// But standard CP problems often have sum <= 10^5 or 2*10^5.

const int MAX_SUM = 200005;

bool can_partition(const vector<int>& subset, int H, int H_rev) {
    long long total = 0;
    for (int x : subset) total += x;
    
    if (total < H + H_rev) return false;
    
    // We need to find a subset sum S such that S >= H and (Total - S) >= H_rev.
    // i.e. H <= S <= Total - H_rev.
    
    long long max_needed = total - H_rev;
    if (max_needed < H) return false;
    
    // Subset sum using bitset
    bitset<MAX_SUM> reachable;
    reachable[0] = 1;
    
    for (int x : subset) {
        // Shift left by x
        // We only care about sums up to max_needed?
        // Actually, we might reach a sum > max_needed, but we don't care.
        // But to keep bitset small, we can limit?
        // No, if we shift, we might need higher bits.
        // But we only check range [H, max_needed].
        // If max_needed is large, we need large bitset.
        // If total is huge, bitset is too slow.
        // But if total is huge, maybe we can always partition?
        // If we have many small items, yes.
        // If we have few large items, no.
        // Let's assume sum is reasonable.
        reachable |= (reachable << x);
    }
    
    // Check range
    // We can iterate from H to max_needed.
    // Or use bit manipulation.
    // Create a mask for range [H, max_needed]?
    // Too complex. Just loop.
    // Optimization: _Find_first() from H?
    
    for (int s = H; s <= max_needed; ++s) {
        if (s < MAX_SUM && reachable[s]) return true;
    }
    
    return false;
}

int solve() {
    int n;
    int H;
    if (!(cin >> n >> H)) return 0;
    
    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    
    int H_rev = H / 2;
    
    // Sort descending
    sort(d.rbegin(), d.rend());
    
    // Iterate k from 1 to n
    // Take top k elements.
    // Check if they can be partitioned.
    
    vector<int> current_subset;
    for (int k = 1; k <= n; ++k) {
        current_subset.push_back(d[k-1]);
        
        // Optimization: Check total sum first
        long long current_total = 0;
        for (int x : current_subset) current_total += x;
        
        if (current_total < H + H_rev) continue;
        
        // Check partition
        if (can_partition(current_subset, H, H_rev)) {
            return k;
        }
    }
    
    return -1; // Should not happen if sum(all) >= H + H_rev
}

int main() {
    cout << solve() << endl;
    return 0;
}
