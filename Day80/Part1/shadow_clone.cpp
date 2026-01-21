#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

// Check if it's possible to distribute tasks such that no clone works more than 'limit'
// Using First Fit Decreasing heuristic for Bin Packing
bool can_distribute(long long limit, int k, const vector<int>& tasks) {
    vector<long long> clones(k, 0);
    for (int t : tasks) {
        bool placed = false;
        for (int i = 0; i < k; ++i) {
            if (clones[i] + t <= limit) {
                clones[i] += t;
                placed = true;
                break;
            }
        }
        if (!placed) return false;
    }
    return true;
}

// Backtracking for exact check if N is small (<= 20)
// Or improved greedy
bool can_distribute_backtrack(long long limit, int k, const vector<int>& tasks, vector<long long>& clones, int idx) {
    if (idx == tasks.size()) return true;
    
    for (int i = 0; i < k; ++i) {
        if (clones[i] + tasks[idx] <= limit) {
            clones[i] += tasks[idx];
            if (can_distribute_backtrack(limit, k, tasks, clones, idx + 1)) return true;
            clones[i] -= tasks[idx];
            if (clones[i] == 0) break; // Optimization: if empty bin fails, other empty bins will too
        }
    }
    return false;
}

int main() {
    int k, n;
    if (!(cin >> k >> n)) return 0;
    
    vector<int> t(n);
    long long sum_t = 0;
    int max_t = 0;
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
        sum_t += t[i];
        max_t = max(max_t, t[i]);
    }
    
    // Sort descending for better greedy/backtracking performance
    sort(t.rbegin(), t.rend());
    
    long long low = max((long long)max_t, (sum_t + k - 1) / k);
    long long high = sum_t;
    long long ans = high;
    
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        vector<long long> clones(k, 0);
        // Use backtracking for correctness on small inputs, or greedy for large
        // Given constraints aren't specified, we'll use a hybrid or just greedy with sort
        // For this problem, we'll use the recursive check which is exact but might be slow for N > 20
        // If N is large, we'd rely on the greedy check.
        
        bool possible;
        if (n <= 20) {
             possible = can_distribute_backtrack(mid, k, t, clones, 0);
        } else {
             possible = can_distribute(mid, k, t);
        }

        if (possible) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    cout << ans << endl;
    return 0;
}
